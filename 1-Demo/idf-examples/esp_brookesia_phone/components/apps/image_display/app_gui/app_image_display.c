
#include "app_image_display.h"


lv_obj_t *app_image_screen;
lv_obj_t *app_image_screen1;
lv_obj_t *app_image_mian;
lv_timer_t *app_image_timer;


void app_image_display_init(void)
{
    app_image_screen = lv_obj_create(NULL);
    lv_obj_set_size(app_image_screen,800,1280);
    lv_obj_clear_flag( app_image_screen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_flex_flow(app_image_screen,LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(app_image_screen, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_bg_color(app_image_screen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(app_image_screen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(app_image_screen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(app_image_screen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(app_image_screen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(app_image_screen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(app_image_screen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(app_image_screen, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    app_image_mian = lv_canvas_create(app_image_screen);
    lv_obj_set_size(app_image_mian,800,1280);
    lv_obj_set_align( app_image_mian, LV_ALIGN_CENTER );
    lv_obj_add_flag( app_image_mian, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
    lv_obj_clear_flag( app_image_mian, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

    lv_scr_load(app_image_screen);
}

