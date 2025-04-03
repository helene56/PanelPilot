#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

void create_screen_plant_status() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.plant_status = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9cd49a), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 19, 96);
            lv_obj_set_size(obj, 281, 144);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 120, 8);
            lv_obj_set_size(obj, 80, 80);
            lv_img_set_src(obj, &img_pot1);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            lv_obj_set_pos(obj, 81, 124);
            lv_obj_set_size(obj, 162, 15);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 81, 168);
            lv_obj_set_size(obj, 162, 15);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe5c84e), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffd4db7c), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 81, 209);
            lv_obj_set_size(obj, 162, 15);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff69d2e9), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4ecfeb), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_msgbox_create(parent_obj);
            lv_obj_set_pos(obj, 209, 40);
            lv_obj_set_size(obj, 100, 32);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 234, 48);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "(-_- )");
        }
        {
            // water_percentage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.water_percentage = obj;
            lv_obj_set_pos(obj, 228, 108);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "x");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 237, 108);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
        }
        {
            // water_percentage_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.water_percentage_1 = obj;
            lv_obj_set_pos(obj, 228, 108);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "x");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 237, 108);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
        }
        {
            // sunlight_percentage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sunlight_percentage = obj;
            lv_obj_set_pos(obj, 229, 152);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "x");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 238, 152);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
        }
        {
            // humidity_percentage
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.humidity_percentage = obj;
            lv_obj_set_pos(obj, 230, 193);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "x");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 239, 193);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
        }
        // TODO: if there are no next screens it should not show the right arrow object
        // {
        //     lv_obj_t *obj = lv_obj_create(parent_obj);
        //     lv_obj_set_pos(obj, 280, 144);
        //     lv_obj_set_size(obj, 40, 40);
        // }
        // {
        //     lv_obj_t *obj = lv_img_create(parent_obj);
        //     lv_obj_set_pos(obj, 285, 149);
        //     lv_obj_set_size(obj, 30, 30);
        //     lv_img_set_src(obj, &img_right_arrow);
        // }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 9, 6);
            lv_obj_set_size(obj, 40, 40);
            lv_img_set_src(obj, &img_return3);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 77, 184);
            lv_obj_set_size(obj, 25, 25);
            lv_img_set_src(obj, &img_humidity2);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 77, 99);
            lv_obj_set_size(obj, 25, 25);
            lv_img_set_src(obj, &img_drop2);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 77, 143);
            lv_obj_set_size(obj, 25, 25);
            lv_img_set_src(obj, &img_sun2);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 144);
            lv_obj_set_size(obj, 40, 40);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 5, 149);
            lv_obj_set_size(obj, 30, 30);
            lv_img_set_src(obj, &img_left_arrow);
        }
    }
    
    tick_screen_plant_status();
}

void tick_screen_plant_status() {
}

void create_screen_plant_status_1() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.plant_status_1 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9cd49a), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 19, 96);
            lv_obj_set_size(obj, 281, 144);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 120, 8);
            lv_obj_set_size(obj, 80, 80);
            lv_img_set_src(obj, &img_plant1);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            lv_obj_set_pos(obj, 81, 124);
            lv_obj_set_size(obj, 162, 15);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 81, 168);
            lv_obj_set_size(obj, 162, 15);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe5c84e), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffd4db7c), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 81, 209);
            lv_obj_set_size(obj, 162, 15);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff69d2e9), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff4ecfeb), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_msgbox_create(parent_obj);
            lv_obj_set_pos(obj, 209, 40);
            lv_obj_set_size(obj, 100, 32);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 234, 48);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "(>< )");
        }
        {
            // water_percentage_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.water_percentage_2 = obj;
            lv_obj_set_pos(obj, 228, 108);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "x");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 237, 108);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
        }
        {
            // water_percentage_3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.water_percentage_3 = obj;
            lv_obj_set_pos(obj, 228, 108);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "x");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 237, 108);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
        }
        {
            // sunlight_percentage_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sunlight_percentage_1 = obj;
            lv_obj_set_pos(obj, 229, 152);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "x");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 238, 152);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
        }
        {
            // humidity_percentage_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.humidity_percentage_1 = obj;
            lv_obj_set_pos(obj, 230, 193);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "x");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 239, 193);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 280, 144);
            lv_obj_set_size(obj, 40, 40);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 285, 149);
            lv_obj_set_size(obj, 30, 30);
            lv_img_set_src(obj, &img_right_arrow);
            lv_obj_add_event_cb(obj, action_next_page, LV_EVENT_PRESSED, (void *)0);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 9, 6);
            lv_obj_set_size(obj, 40, 40);
            lv_img_set_src(obj, &img_return3);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 77, 184);
            lv_obj_set_size(obj, 25, 25);
            lv_img_set_src(obj, &img_humidity2);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 77, 99);
            lv_obj_set_size(obj, 25, 25);
            lv_img_set_src(obj, &img_drop2);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 77, 143);
            lv_obj_set_size(obj, 25, 25);
            lv_img_set_src(obj, &img_sun2);
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 144);
            lv_obj_set_size(obj, 40, 40);
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 5, 149);
            lv_obj_set_size(obj, 30, 30);
            lv_img_set_src(obj, &img_left_arrow);
            lv_obj_add_event_cb(obj, action_back_page, LV_EVENT_PRESSED, (void *)0);
        }
    }
    
    tick_screen_plant_status_1();
}

void tick_screen_plant_status_1() {
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff9cdad1), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 104, 47);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Hello, world!");
        }
        {
            // water
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.water = obj;
            lv_obj_set_pos(obj, 34, 94);
            lv_obj_set_size(obj, 70, 70);
            lv_obj_set_style_bg_image_tiled(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff70b6ed), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // plant
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.plant = obj;
            lv_obj_set_pos(obj, 123, 94);
            lv_obj_set_size(obj, 70, 70);
            // lv_obj_add_event_cb(obj, action_status, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff5be0b6), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_image_tiled(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_plants_screen() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.plants_screen = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe4d1bc), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            lv_obj_set_pos(obj, 34, 116);
            lv_obj_set_size(obj, 70, 36);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "plant 1");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
        }
        {
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            lv_obj_set_pos(obj, 127, 117);
            lv_obj_set_size(obj, 70, 36);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "plant 2");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
        }
        {
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            lv_obj_set_pos(obj, 216, 117);
            lv_obj_set_size(obj, 70, 36);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "plant 3");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
        }
    }
    
    tick_screen_plants_screen();
}

void tick_screen_plants_screen() {
}

void create_screen_main_test() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main_test = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff6d5cc3), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 0, 49);
            lv_obj_set_size(obj, 320, 191);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff5641be), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 87, 0);
            lv_obj_set_size(obj, 46, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_color(obj, lv_color_hex(0xff5641be), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 37, 0);
            lv_obj_set_size(obj, 46, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff5641be), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff3e27ac), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_shadow_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            lv_obj_set_pos(obj, 160, 13);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            lv_dropdown_set_options(obj, "Plant 1\nPlant 2\nPlant 3");
        }
        {
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            lv_obj_set_pos(obj, 24, 76);
            lv_obj_set_size(obj, 73, 36);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "Vandet");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
        }
        {
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            lv_obj_set_pos(obj, 246, 76);
            lv_obj_set_size(obj, 51, 37);
            lv_textarea_set_max_length(obj, 10);
            lv_textarea_set_placeholder_text(obj, "11111");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
        }
    }
    
    tick_screen_main_test();
}

void tick_screen_main_test() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_plant_status,
    tick_screen_plant_status_1,
    tick_screen_main,
    tick_screen_plants_screen,
    tick_screen_main_test,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_plant_status();
    create_screen_plant_status_1();
    create_screen_main();
    create_screen_plants_screen();
    create_screen_main_test();
}
