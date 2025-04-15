#ifndef __APP_IMAGE_DISPLAY_H
#define __APP_IAMGE_DISPLAY_H

#include "lvgl.h"
#include "file_iterator.h"
#include "esp_brookesia.h"

#ifdef __cplusplus
extern "C" {
#endif

extern lv_obj_t *app_image_screen;
extern lv_obj_t *app_image_screen1;
extern lv_obj_t *app_image_mian;
extern lv_timer_t *app_image_timer;


void app_image_display_init(void);
void app_image_display_pause(void);
void app_image_display_resume(void);
void app_image_display_close(void);

void app_image_display_screen(void);
void app_image_display_screen1(void);

#ifdef __cplusplus
}
#endif

#endif