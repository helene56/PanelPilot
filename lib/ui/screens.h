#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *plant_status;
    lv_obj_t *plant_status_1;
    lv_obj_t *main;
    lv_obj_t *plants_screen;
    lv_obj_t *main_test;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *water_percentage;
    lv_obj_t *water_percentage_1;
    lv_obj_t *sunlight_percentage;
    lv_obj_t *humidity_percentage;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *water_percentage_2;
    lv_obj_t *water_percentage_3;
    lv_obj_t *sunlight_percentage_1;
    lv_obj_t *humidity_percentage_1;
    lv_obj_t *water;
    lv_obj_t *plant;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_PLANT_STATUS = 1,
    SCREEN_ID_PLANT_STATUS_1 = 2,
    SCREEN_ID_MAIN = 3,
    SCREEN_ID_PLANTS_SCREEN = 4,
    SCREEN_ID_MAIN_TEST = 5,
};

void create_screen_plant_status();
void tick_screen_plant_status();

void create_screen_plant_status_1();
void tick_screen_plant_status_1();

void create_screen_main();
void tick_screen_main();

void create_screen_plants_screen();
void tick_screen_plants_screen();

void create_screen_main_test();
void tick_screen_main_test();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/