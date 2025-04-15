#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_check.h"
#include "esp_memory_utils.h"

#include "esp_lcd_panel_ops.h"
#include "esp_lcd_mipi_dsi.h"
#include "esp_ldo_regulator.h"
#include "esp_lcd_touch_gsl3680.h"
#include "esp_lcd_jd9365.h"

static const char *TAG = "esp_draw_bit";

#define BSP_I2C_SCL           (GPIO_NUM_8)
#define BSP_I2C_SDA           (GPIO_NUM_7)

#define LCD_BACKLIGHT     (GPIO_NUM_23)
#define LCD_RST           (GPIO_NUM_27)
#define LCD_TOUCH_RST     (GPIO_NUM_22)
#define LCD_TOUCH_INT     (GPIO_NUM_21)

#define LCD_H_RES         (800)
#define LCD_V_RES         (1280)

#define BSP_LCD_MIPI_DSI_LANE_NUM          (2)    // 2 data lanes
#define BSP_LCD_MIPI_DSI_LANE_BITRATE_MBPS (1500) // 1Gbps

#define BSP_MIPI_DSI_PHY_PWR_LDO_CHAN       (3)  // LDO_VO3 is connected to VDD_MIPI_DPHY
#define BSP_MIPI_DSI_PHY_PWR_LDO_VOLTAGE_MV (2500)

static i2c_master_bus_handle_t i2c_handle = NULL; 
static esp_lcd_touch_handle_t ret_touch;
static SemaphoreHandle_t refresh_finish = NULL;
static esp_lcd_panel_handle_t disp_panel = NULL;

IRAM_ATTR static bool test_notify_refresh_ready(esp_lcd_panel_handle_t panel, esp_lcd_dpi_panel_event_data_t *edata, void *user_ctx)
{
    SemaphoreHandle_t refresh_finish = (SemaphoreHandle_t)user_ctx;
    BaseType_t need_yield = pdFALSE;

    xSemaphoreGiveFromISR(refresh_finish, &need_yield);

    return (need_yield == pdTRUE);
}

static esp_err_t bsp_enable_dsi_phy_power(void)
{
#if BSP_MIPI_DSI_PHY_PWR_LDO_CHAN > 0
    // Turn on the power for MIPI DSI PHY, so it can go from "No Power" state to "Shutdown" state
    static esp_ldo_channel_handle_t phy_pwr_chan = NULL;
    esp_ldo_channel_config_t ldo_cfg = {
        .chan_id = BSP_MIPI_DSI_PHY_PWR_LDO_CHAN,
        .voltage_mv = BSP_MIPI_DSI_PHY_PWR_LDO_VOLTAGE_MV,
    };
    ESP_RETURN_ON_ERROR(esp_ldo_acquire_channel(&ldo_cfg, &phy_pwr_chan), TAG, "Acquire LDO channel for DPHY failed");
    ESP_LOGI(TAG, "MIPI DSI PHY Powered on");
#endif // BSP_MIPI_DSI_PHY_PWR_LDO_CHAN > 0

    return ESP_OK;
}


void app_main(void)
{
    ESP_LOGI(TAG, "Turn on LCD backlight");
    gpio_config_t bk_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << LCD_BACKLIGHT
    };
    gpio_config(&bk_gpio_config);
    gpio_set_level(LCD_BACKLIGHT, 1);

    refresh_finish = xSemaphoreCreateBinary();

    i2c_master_bus_config_t i2c_bus_conf = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = BSP_I2C_SDA,
        .scl_io_num = BSP_I2C_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority = 0,
        .trans_queue_depth = 0,
        .flags = {
            .enable_internal_pullup = 1,
        },
    };
    i2c_new_master_bus(&i2c_bus_conf, &i2c_handle);

    const esp_lcd_touch_config_t tp_cfg = {
        .x_max = LCD_H_RES,
        .y_max = LCD_V_RES,
        .rst_gpio_num = LCD_TOUCH_RST, // Shared with LCD reset
        .int_gpio_num = LCD_TOUCH_INT,
        .levels = {
            .reset = 0,
            .interrupt = 0,
        },
        .flags = {
            .swap_xy = 0,
#if CONFIG_BSP_LCD_TYPE_1024_600
            .mirror_x = 1,
            .mirror_y = 1,
#else
            .mirror_x = 0,
            .mirror_y = 1,
#endif
        },
    };
    esp_lcd_panel_io_handle_t tp_io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_GSL3680_CONFIG();
    tp_io_config.scl_speed_hz = 100000;
    esp_lcd_new_panel_io_i2c(i2c_handle, &tp_io_config, &tp_io_handle);
    esp_lcd_touch_new_i2c_gsl3680(tp_io_handle, &tp_cfg, &ret_touch);

    bsp_enable_dsi_phy_power();

    esp_lcd_dsi_bus_handle_t mipi_dsi_bus;
    esp_lcd_dsi_bus_config_t bus_config = {
        .bus_id = 0,
        .num_data_lanes = BSP_LCD_MIPI_DSI_LANE_NUM,
        .phy_clk_src = MIPI_DSI_PHY_CLK_SRC_DEFAULT,
        .lane_bit_rate_mbps = BSP_LCD_MIPI_DSI_LANE_BITRATE_MBPS,
    };
    esp_lcd_new_dsi_bus(&bus_config, &mipi_dsi_bus);

    ESP_LOGI(TAG, "Install MIPI DSI LCD control panel");
    // we use DBI interface to send LCD commands and parameters
    esp_lcd_panel_io_handle_t io;
    esp_lcd_dbi_io_config_t dbi_config = {
        .virtual_channel = 0,
        .lcd_cmd_bits = 8,   // according to the LCD ILI9881C spec
        .lcd_param_bits = 8, // according to the LCD ILI9881C spec
    };
    esp_lcd_new_panel_io_dbi(mipi_dsi_bus, &dbi_config, &io);

   
    ESP_LOGI(TAG, "Install JD9365 LCD control panel");

    esp_lcd_dpi_panel_config_t dpi_config = JD9365_800_1280_PANEL_60HZ_DPI_CONFIG(LCD_COLOR_PIXEL_FORMAT_RGB565);

    //  dpi_config.num_fbs = CONFIG_BSP_LCD_DPI_BUFFER_NUMS;
    
    jd9365_vendor_config_t vendor_config = {
        .mipi_config = {
            .dsi_bus = mipi_dsi_bus,
            .dpi_config = &dpi_config,
        },
    };
    esp_lcd_panel_dev_config_t lcd_dev_config = {
        .bits_per_pixel = 16,
        .rgb_ele_order = ESP_LCD_COLOR_SPACE_RGB,
        .reset_gpio_num = LCD_RST,
        .vendor_config = &vendor_config,
    };
    esp_lcd_new_panel_jd9365(io, &lcd_dev_config, &disp_panel);
    esp_lcd_panel_reset(disp_panel);
    esp_lcd_panel_init(disp_panel);
    esp_lcd_panel_disp_on_off(disp_panel, true);
    
    esp_lcd_dpi_panel_event_callbacks_t cbs = {
        .on_color_trans_done = test_notify_refresh_ready,
    };
    esp_lcd_dpi_panel_register_event_callbacks(disp_panel, &cbs, refresh_finish);
    
    uint16_t x[5] = {0};
    uint16_t y[5] = {0};
    uint8_t touchpad_cnt = 0;

    int h_res = 800;
    int v_res = 1280;
    uint8_t byte_per_pixel = (16 + 7) / 8;
    uint16_t row_line = v_res / byte_per_pixel / 8;
    size_t color_size = row_line * h_res * byte_per_pixel;
    uint8_t *color = (uint8_t *)heap_caps_calloc(1, color_size, MALLOC_CAP_DMA);
    assert(color);
    for(int i = 0;i<color_size;i++)
    {
        color[i] = 0x00;
    }
    ESP_LOGI(TAG,"%d",row_line);
    for(int i=0;i<byte_per_pixel*8;i++)
    {
        esp_lcd_panel_draw_bitmap(disp_panel, 0, i*row_line, 800,(i+1)*row_line, color);
        xSemaphoreTake(refresh_finish, portMAX_DELAY);
    }
    
    size_t bit_data_size = 5*5*2;
    uint8_t *bit_data = (uint8_t *)heap_caps_calloc(1, bit_data_size, MALLOC_CAP_DMA);
    assert(bit_data);
    for(int i = 0;i<bit_data_size;i++)
    {
        bit_data[i]=0xee;
    }

    size_t res_bit_size = 50*50*2;
    uint8_t *res_bit = (uint8_t *)heap_caps_calloc(1, res_bit_size, MALLOC_CAP_DMA);
    for(int i =0;i<res_bit_size;i++)
    {
        res_bit[i] = 0xff;
    } 
    esp_lcd_panel_draw_bitmap(disp_panel, 0, 0,50,50, res_bit);
    xSemaphoreTake(refresh_finish, portMAX_DELAY);

    ESP_LOGI(TAG,"read tou data");

    while(1)
    {
        esp_lcd_touch_read_data(ret_touch);
        esp_lcd_touch_get_coordinates(ret_touch,x,y,NULL,&touchpad_cnt,10);
        for(int i=0;i<touchpad_cnt;i++)
        {
            y[i] = 1280 -y[i];
            x[i] = 800 - x[i];
            if(x[i]<50 && y[i]<50)
            {
                for(int i=0;i<byte_per_pixel*8;i++)
                {
                    esp_lcd_panel_draw_bitmap(disp_panel, 0, i*row_line, 800,(i+1)*row_line, color);
                    xSemaphoreTake(refresh_finish, portMAX_DELAY);
                }
                esp_lcd_panel_draw_bitmap(disp_panel, 0, 0,50,50, res_bit);
                xSemaphoreTake(refresh_finish, portMAX_DELAY);
            }
            esp_lcd_panel_draw_bitmap(disp_panel, x[i]-2, y[i]-2, x[i]+2,y[i]+2, bit_data);
            xSemaphoreTake(refresh_finish, portMAX_DELAY);
        }
        // ESP_LOGI(TAG,"read touch cnt = %d",touchpad_cnt);
        // for(int i =0;i<touchpad_cnt-1;i++)
        // {
        //     ESP_LOGI(TAG,"x[%d] = %d, y[%d] = %d",i,touchpad_x,i,touchpad_y);
        // }
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
