#include "main.h"

// Defining vars declared in externs
std::shared_ptr<okapi::ChassisController> drive;
okapi::Controller controller;

// lift and claw, as extern objects, must be initialized in the global scope
Lift lift({10, 20}, {false, true});
// Claw claw({9}, {false});
// PneumaticClaw claw('e', false);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
LV_IMG_DECLARE(background)

void initialize() {
    // Configuring lift
    lift.setExternalGearRatio(12.0 / 60.0);
    lift.setGearing(MOTOR_GEARSET_18);
    lift.setMaxSpeeds(150, 80);
    lift.setHoldThreshold(20);

    // Configuring claw
    // claw.setGearing(MOTOR_GEARSET_18);
    // claw.setMaxSpeed(60);

    GUI::scrMain = lv_obj_create(NULL, NULL);
    GUI::scrAuton = lv_obj_create(NULL, NULL);

    GUI::backgroundIMG = lv_img_create(GUI::scrMain, NULL);
    lv_img_set_src(GUI::backgroundIMG, &background);
    lv_obj_align(GUI::backgroundIMG, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    GUI::navToAuton = GUI::createButton(GUI::scrMain, LV_BTN_ACTION_CLICK,
                                        GUI::goToAuton, "Auton Menu");
    lv_obj_align(GUI::navToAuton, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);

    GUI::navFromAuton = GUI::createButton(GUI::scrAuton, LV_BTN_ACTION_CLICK,
                                          GUI::goToMain, "Home Screen");
    lv_obj_align(GUI::navFromAuton, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);

    GUI::autonSelect = GUI::createButtonMatrix(
        GUI::scrAuton, Autonomous::buttonMatrixList, GUI::updateAutonID);
    lv_obj_align(GUI::autonSelect, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 20);
    lv_obj_set_size(GUI::autonSelect, 250, 200);

    GUI::curAutonLbl = GUI::createLabel(GUI::scrAuton, "Auton");
    lv_obj_align(GUI::curAutonLbl, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

    lv_scr_load(GUI::scrMain);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}