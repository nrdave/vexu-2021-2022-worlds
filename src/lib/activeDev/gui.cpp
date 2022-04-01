#include "lib/gui.hpp"

#include "lib/autonomous.hpp"

/**
 * The implementations for the GUI namespace functions, along with the
 * declarations of all LVGL objects used.
 * The functions initialize LVGL objects or handle
 * event triggers from those objects.
 */

// LGVL objects
lv_obj_t* GUI::scrMain;
lv_obj_t* GUI::scrAuton;
lv_obj_t* GUI::backgroundIMG;
lv_obj_t* GUI::navToAuton;
lv_obj_t* GUI::navFromAuton;
lv_obj_t* GUI::autonSelect;
lv_obj_t* GUI::curAutonLbl;

lv_obj_t* GUI::createButton(lv_obj_t* parent, lv_btn_action_t pressType,
                            lv_action_t function, const char* text) {
    // Creating an LVGL button
    lv_obj_t* btn = lv_btn_create(parent, NULL);
    // Setting the button's action upon a given type of trigger
    lv_btn_set_action(btn, pressType, function);

    // Creating a label for the button
    lv_obj_t* label = createLabel(btn, text);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
    /**
     * Return the created button
     * This returns the button to the declared LVGL object in
     * initialize, making that object into an identical button to
     * the button btn created in this function.
     */
    return btn;
}

lv_obj_t* GUI::createLabel(lv_obj_t* parent, const char* text) {
    // Creating a LVGL Label
    lv_obj_t* lbl = lv_label_create(parent, NULL);

    // Setting the label's text
    lv_label_set_text(lbl, text);
    /**
     * Return the created label
     * This returns the label to the declared LVGL object in
     * initialize, making that object into an identical label to
     * the label lbl created in this function.
     */
    return lbl;
}

lv_obj_t* GUI::createButtonMatrix(lv_obj_t* parent, const char* map[],
                                  lv_btnm_action_t function) {
    // Creating an LVGL button matrix
    lv_obj_t* btnm = lv_btnm_create(parent, NULL);
    // Setting the button matrix's action upon a given type of trigger
    lv_btnm_set_action(btnm, function);
    // Set the String array to be used to create the button matrix
    lv_btnm_set_map(btnm, map);

    /**
     * Return the created button matrix
     * This returns the button matrix to the declared LVGL object in
     * initialize, making that object into an identical button matrix to
     * the button matrix btnm created in this function.
     */
    return btnm;
}

lv_res_t GUI::updateAutonID(lv_obj_t* btnm, const char* txt) {
    /**
     * Running the current selected button in the matrix through a
     * series of if-else-if statements to determine which autonomous
     * routine is selected. If there are any issues, the function
     * defaults to no autonomous
     */
    if (txt == "None")
        Autonomous::autonID = Autonomous::Routine::none;

    else if (txt == "Skills")
        Autonomous::autonID = Autonomous::Routine::skills;

    else if (txt = "Competition - Middle Goal")
        Autonomous::autonID = Autonomous::Routine::competition_middleGoal;

    else if (txt = "Competition - Side Goal")
        Autonomous::autonID = Autonomous::Routine::competition_sideGoal;

    else
        Autonomous::autonID = Autonomous::Routine::none;

    // Updating the label for the current selected autonomous
    updateAutonLbl();
    return LV_RES_OK;
}

void GUI::updateAutonLbl() {
    /**
     * Using autonID as a switch, the function determines
     * the current autonomous routine selected and sets
     * the current Autonomous label to the corresponding
     * text
     */
    switch (Autonomous::autonID) {
        case Autonomous::Routine::skills:
            lv_label_set_text(curAutonLbl, "Skills");
            break;
        case Autonomous::Routine::competition_middleGoal:
            lv_label_set_text(curAutonLbl, "Competition - Middle Goal");
            break;
        case Autonomous::Routine::competition_sideGoal:
            lv_label_set_text(curAutonLbl, "Competition - Side Goal");
            break;
        case Autonomous::Routine::none:
            lv_label_set_text(curAutonLbl, "No Auton Selected");
            break;
    }
}

/**
 * LVGL doesn't allow functions with parameters to be a callback function for a
 * button action, so I had to wrap a few functions, such as lv_scr_load(), which
 * loads a screen, in a format that the lv_btn_set_action() function would
 * accept
 */
lv_res_t GUI::goToAuton(lv_obj_t* btn) {
    lv_scr_load(scrAuton);
    return LV_RES_OK;
}

lv_res_t GUI::goToMain(lv_obj_t* btn) {
    lv_scr_load(scrMain);
    return LV_RES_OK;
}