#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_sun2;
extern const lv_img_dsc_t img_drop2;
extern const lv_img_dsc_t img_humidity2;
extern const lv_img_dsc_t img_pot1;
extern const lv_img_dsc_t img_return3;
extern const lv_img_dsc_t img_right_arrow;
extern const lv_img_dsc_t img_left_arrow;
extern const lv_img_dsc_t img_plant1;
extern const lv_img_dsc_t img_water_carrier;
extern const lv_img_dsc_t img_water_carrier4;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[10];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/