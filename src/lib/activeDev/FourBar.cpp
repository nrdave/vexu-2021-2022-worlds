#include "lib/FourBar.hpp"

FourBar::FourBar(std::initializer_list<int> ports,
                 std::initializer_list<bool> revs)
    : motors(ports, revs) {
    // Encoders output their rotation in degrees (Other options don't really
    // make sense)
    motors.setEncoderUnits(pros::E_MOTOR_ENCODER_DEGREES);
}

// Configuration Functions
void FourBar::setGearing(pros::motor_gearset_e_t gearing) {
    motors.setGearing(gearing);
}

void FourBar::setExternalGearRatio(double ratio) { extGearRatio = ratio; }

void FourBar::setMaxSpeeds(int maxUpRPM, int maxDownRPM) {
    maxUpSpd = maxUpRPM;
    maxDownSpd = maxDownRPM;
}

void FourBar::setHoldThreshold(double degrees) { holdThreshold = degrees; }

// Movement Functions
void FourBar::driver(pros::controller_id_e_t controller,
                     pros::controller_digital_e_t upButton,
                     pros::controller_digital_e_t downButton) {
    if (pros::c::controller_get_digital(controller, upButton))
        up();
    else if (pros::c::controller_get_digital(controller, downButton))
        down();
    else
        stop();
}

void FourBar::up() { motors.moveVelocity(maxUpSpd); }

void FourBar::down() { motors.moveVelocity(-maxDownSpd); }

void FourBar::stop() {
    /** If the motors current position is less than the holdThreshold *
     * extGearRatio, set the brake mode to coast. Otherwise, have the motors
     * hold position when they stop.
     *
     * holdThreshold / extGearRatio is used because it represents the rotation
     * of the motors themselves to get the four bar lift to the holdThreshold.
     * extGearRatio represents the number of rotations done by the four bar lift
     * in one full rotation of the motor.
     */
    if (motors.getPosition() <= (holdThreshold / extGearRatio))
        motors.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    else
        motors.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    motors.moveVelocity(0);
};

void FourBar::moveTo(double degrees, int speed) {
    int velocity = speed;
    if (degrees < motors.getPosition()) velocity *= -1;
    degrees /= extGearRatio;
    while (motors.getPosition() > degrees + 5 ||
           motors.getPosition() < degrees - 5)
        motors.moveVelocity(velocity);
    stop();
}