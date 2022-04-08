#include "lib/gui.hpp"

/**
 * The implementations for the GUI namespace functions.
 * The functions initialize LVGL objects, as well as doing some configuration
 * for the objects.
 */

void GUI::createImage(lv_obj_t* object, lv_obj_t* parent, const void* img_src) {
    object = lv_img_create(parent, NULL);
    lv_img_set_src(object, img_src);
}

void GUI::createButton(lv_obj_t* object, lv_obj_t* parent,
                       lv_btn_action_t pressType, lv_action_t function,
                       const char* text) {
    // Creating an LVGL button
    object = lv_btn_create(parent, NULL);
    // Setting the button's action upon a given type of trigger
    lv_btn_set_action(object, pressType, function);

    // Creating a label for the button
    lv_obj_t* label;
    createLabel(label, object, text);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
}

void GUI::createLabel(lv_obj_t* object, lv_obj_t* parent, const char* text) {
    // Creating a LVGL Label
    object = lv_label_create(parent, NULL);

    // Setting the label's text
    lv_label_set_text(object, text);
}

void GUI::createButtonMatrix(lv_obj_t* object, lv_obj_t* parent,
                             const char* map[], lv_btnm_action_t function) {
    // Creating an LVGL button matrix
    object = lv_btnm_create(parent, NULL);
    // Setting the button matrix's action upon a given type of trigger
    lv_btnm_set_action(object, function);
    // Set the String array to be used to create the button matrix
    lv_btnm_set_map(object, map);
}
