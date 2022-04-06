#ifndef GUI_HPP
#define GUI_HPP

#include "pros/apix.h"

/**
 * The header file for the GUI namespace. The GUI uses a namespace rather
 * than a class due to the nature of the LittleVGL C graphics library. I've
 * tried using classes, but they run into too many issues with LVGL functions
 *
 * The GUI namespace contains functions for creating more complex LVGL objects.
 */

namespace GUI {

// Declaring all LVGL objects
extern lv_obj_t* scrMain;
extern lv_obj_t* scrAuton;
extern lv_obj_t* backgroundIMG;
extern lv_obj_t* navToAuton;
extern lv_obj_t* navFromAuton;
extern lv_obj_t* autonSelect;
extern lv_obj_t* curAutonLbl;

/**
 * A function to create an LVGL button object. It packages all the LVGL
 * functions to create, set the press type and action, and align a button
 * into one function, as well as handling the creation of a label for the
 * button
 *
 * @param object Pointer to the LVGL object in which to create a button
 * @param parent Pointer to the parent LVGL object
 * @param pressType the button press type (Click, hold, long press, etc.)
 * @param function the function to be called when the button is triggered
 * @param text the label text on the button
 */
void createButton(lv_obj_t* object, lv_obj_t* parent, lv_btn_action_t pressType,
                  lv_action_t function, const char* text);

/**
 * A function to create an LVGL label object. It packages all the LVGL functions
 * to create, align, and set the text of a label
 *
 * @param object Pointer to the LVGL object in which to create a button
 * @param parent Pointer to the parent LVGL object
 * @param text: the text of
 * the label
 *
 * @return A pointer to a new LVGL label created using the given specs
 */
void createLabel(lv_obj_t* object, lv_obj_t* parent, const char* text);

/**
 * A function to create an LVGL button matrix object. It packages all the LVGL
 * functions to create, set the character map of, and align and size the button
 * matrix into one function
 *
 * @param object Pointer to the LVGL object in which to create a button
 * @param parent Pointer to the parent LVGL object
 * @param map: a pointer to a
 * String array used to generate the matrix of buttons and their labels
 * @param function: the function to be called when a button in the matrix is
 * clicked
 */
void createButtonMatrix(lv_obj_t* object, lv_obj_t* parent, const char* map[],
                        lv_btnm_action_t function);

/**
 * The callback function for the auton selection button matrix
 * Although the function is never explicitly called, the parameters
 * exist to allow LVGL to pass in the needed values from the button
 * matrix
 *
 * As such, the parameters are not defined here.
 */
lv_res_t updateAutonID(lv_obj_t* btnm, const char* txt);

// The function to update label displaying the selected autonomous routine
void updateAutonLbl();

// Functions to navigate to specific LVGL Screens. Used in the navigation
// buttons
lv_res_t goToMain(lv_obj_t* btn);
lv_res_t goToAuton(lv_obj_t* btn);

}  // namespace GUI

#endif  // gui.hpp