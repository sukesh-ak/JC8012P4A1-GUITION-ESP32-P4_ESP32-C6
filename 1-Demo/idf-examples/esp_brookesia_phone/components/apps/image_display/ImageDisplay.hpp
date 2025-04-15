#pragma once

#include <vector>
#include "lvgl.h"
#include "esp_brookesia.hpp"
#include "file_iterator.h"

class AppImageDisplay: public ESP_Brookesia_PhoneApp
{
private:

    static void image_change_cb(lv_event_t *e);
    static void image_delay_change(AppImageDisplay *app);
    char _image_path[256];
    const char *_image_name;
    file_iterator_instance_t *_image_file_iterator;

public:
    AppImageDisplay(/* args */);
    ~AppImageDisplay();
    
    bool run(void);
    bool pause(void);
    bool resume(void);
    bool back(void);
    bool close(void);

    bool init(void) override;

};


