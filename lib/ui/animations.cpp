#include "screens.h"


void set_bar_value(void * bar, int32_t value)
{
    lv_bar_set_value((lv_obj_t *)bar, value, LV_ANIM_ON); 
}

void bar_anim()
{
    
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_bar_value);
    lv_anim_set_duration(&a, 3000);
    // sunlight object
    lv_anim_set_var(&a, objects.obj0);
    lv_anim_set_values(&a, 10, 50);
    lv_anim_start(&a);
}


//     // water carrier object
// lv_anim_set_var(&a, objects.obj4);
// lv_anim_set_var(&a, objects.obj5);

void gradual_bar_anim(int32_t start)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_bar_value);
    lv_anim_set_duration(&a, 1000);
    // water carrier object
    lv_anim_set_var(&a, objects.obj4);
    lv_anim_set_values(&a, start, start + 30);
    lv_anim_start(&a);

    lv_anim_t a2;
    lv_anim_init(&a2);
    lv_anim_set_exec_cb(&a2, set_bar_value);
    lv_anim_set_duration(&a2, 1000);
    lv_anim_set_var(&a2, objects.obj5); // Set the second bar as the target
    lv_anim_set_values(&a2, start, start + 30);
    lv_anim_start(&a2);

}