#include "screens.h"


void set_sunlight_value(void * bar, int32_t lux)
{
    lv_bar_set_value((lv_obj_t *)bar, lux, LV_ANIM_ON); 
}

void sunlight_bar_anim()
{
    
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_sunlight_value);
    lv_anim_set_duration(&a, 3000);
    lv_anim_set_var(&a, objects.obj0);
    lv_anim_set_values(&a, 10, 50);
    lv_anim_start(&a);
}