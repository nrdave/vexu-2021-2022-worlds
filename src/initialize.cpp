#include "main.h"

// lift. claw, and drive, as extern objects, must be initialized in the global
// scope
FourBar lift({10, 20}, {false, true});
// Claw claw({9}, {false});
PneumaticClaw claw('e', false);
TankDrive drive({11, 12}, {4, 8}, {false, false}, {true, true});

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

// Declaring all LVGL objects and function prototypes
LV_IMG_DECLARE(background)

lv_obj_t* scrMain;
lv_obj_t* scrAuton;
lv_obj_t* backgroundIMG;
lv_obj_t* navToAuton;
lv_obj_t* navFromAuton;
lv_obj_t* autonSelect;
lv_obj_t* curAutonLbl;

lv_res_t updateAutonID(lv_obj_t* btnm, const char* txt);
void updateAutonLbl();
lv_res_t goToAuton(lv_obj_t* btn);
lv_res_t goToMain(lv_obj_t* btn);

void initialize() {
    // Configuring lift
    lift.setExternalGearRatio(12.0 / 60.0);
    lift.setGearing(MOTOR_GEARSET_18);
    lift.setMaxSpeeds(150, 80);
    lift.setHoldThreshold(20);

    // Configuring drive
    // Dimensions for encoder wheels
    // drive.setDimensions(2.75, 9.84375);
    // Dimensions for drive wheels
    drive.setDimensions(3.25, 9.875);
    drive.setGearing(pros::E_MOTOR_GEARSET_18);
    // drive.addADIEncoders('g', false, 'a', false);
    drive.setPIDConstants(50, 0, 1);
    drive.setPIDTurnConstants(90, 0, 1);

    scrMain = lv_obj_create(NULL, NULL);
    scrAuton = lv_obj_create(NULL, NULL);

    // GUI initialization
    backgroundIMG = lv_img_create(scrMain, NULL);
    lv_img_set_src(backgroundIMG, &background);
    lv_obj_align(backgroundIMG, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    navToAuton = GUI::createButton(scrMain, LV_BTN_ACTION_CLICK, goToAuton,
                                   "Auton Menu");
    lv_obj_align(navToAuton, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);

    navFromAuton = GUI::createButton(scrAuton, LV_BTN_ACTION_CLICK, goToMain,
                                     "Home Screen");
    lv_obj_align(navFromAuton, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);

    autonSelect = GUI::createButtonMatrix(
        scrAuton, Autonomous::buttonMatrixList, updateAutonID);
    lv_obj_align(autonSelect, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 25);
    lv_obj_set_size(autonSelect, 250, 200);

    curAutonLbl = GUI::createLabel(scrAuton, "Auton");
    lv_obj_align(curAutonLbl, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

    lv_scr_load(scrMain);

    claw.close();
}

/**
 * Runs while the robot is in the disabled state of Field Management System
 * or the VEX Competition Switch, following either autonomous or opcontrol.
 * When the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the
 * Field Management System or the VEX Competition Switch. This is intended
 * for competition-specific initialization routines, such as an autonomous
 * selector on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

// GUI function definition
void updateAutonLbl() {
    /**
     * Using autonID as a switch, the function determines
     * the current autonomous routine selected and sets
     * the current Autonomous label to the corresponding
     * text
     */
    switch (autonID) {
        case Autonomous::Routine::skills:
            lv_label_set_text(curAutonLbl, "Skills");
            break;
        case Autonomous::Routine::test:
            lv_label_set_text(curAutonLbl, "Test");
            break;
        case Autonomous::Routine::sideGoal_WP:
            lv_label_set_text(curAutonLbl, "Side Goal - Win Point");
            break;
        case Autonomous::Routine::sideGoal_NoWP:
            lv_label_set_text(curAutonLbl, "Side Goal - No Win Point");
            break;
        case Autonomous::Routine::middleGoal_WP:
            lv_label_set_text(curAutonLbl, "Middle Goal - Win Point");
            break;
        case Autonomous::Routine::none:
            lv_label_set_text(curAutonLbl, "No Auton Selected");
            break;
    }
}

lv_res_t updateAutonID(lv_obj_t* btnm, const char* txt) {
    /**
     * Running the current selected button in the matrix through a
     * series of if-else-if statements to determine which autonomous
     * routine is selected. If there are any issues, the function
     * defaults to no autonomous
     */
    if (txt == "None")
        autonID = Autonomous::Routine::none;

    else if (txt == "Skills")
        autonID = Autonomous::Routine::skills;

    else if (txt == "Test")
        autonID = Autonomous::Routine::test;

    else if (txt == "Side Goal - WP")
        autonID = Autonomous::Routine::sideGoal_WP;

    else if (txt == "Side Goal - No WP")
        autonID = Autonomous::Routine::sideGoal_NoWP;

    else if (txt == "Middle Goal - WP")
        autonID = Autonomous::Routine::middleGoal_WP;

    else
        autonID = Autonomous::Routine::none;

    // Updating the label for the current selected autonomous
    updateAutonLbl();
    return LV_RES_OK;
}

/**
 * LVGL doesn't allow functions with parameters to be a callback function
 * for a button action, so I had to wrap lv_scr_load(), which loads a screen, in
 * a format that the lv_btn_set_action() function would accept
 */
lv_res_t goToAuton(lv_obj_t* btn) {
    lv_scr_load(scrAuton);
    return LV_RES_OK;
}

lv_res_t goToMain(lv_obj_t* btn) {
    lv_scr_load(scrMain);
    return LV_RES_OK;
}
