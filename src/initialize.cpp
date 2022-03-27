#include "main.h"

// Defining vars declared in externs
std::shared_ptr<okapi::ChassisController> drive;
okapi::Controller controller;

// lift, as an extern class, must be initialized in the global scope
Lift lift({20, 10}, {false, true});

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

    drive = okapi::ChassisControllerBuilder()
        .withMotors(
            {11, 12},
            {-3, -4}
        )
        .withDimensions(okapi::AbstractMotor::gearset::green, {{3.25_in, 11_in}, okapi::quadEncoderTPR})
        .build();

    lift.setExternalGearRatio(12.0 / 60.0);
    lift.setGearing(MOTOR_GEARSET_06);
    lift.setMaxSpeeds(75, 60);
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