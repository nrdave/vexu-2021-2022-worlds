#include "lib/Lift.hpp"

Lift::Lift(std::initializer_list<int> ports, std::initializer_list<bool> revs)
    : motors(ports, revs) {
    // Encoders output their rotation in degrees (Other options don't really
    // make sense)
    motors.setEncoderUnits(
        pros::motor_encoder_units_e::E_MOTOR_ENCODER_DEGREES);
}

// Configuration Functions
void Lift::setGearing(pros::motor_gearset_e_t gearing) {
    motors.setGearing(gearing);
}

void Lift::setExternalGearRatio(double ratio) { extGearRatio = ratio; }

void Lift::setMaxSpeeds(int maxUpRPM, int maxDownRPM) {
    maxUpSpd = maxUpRPM;
    maxDownSpd = maxDownRPM;
}

// Movement Functions
void Lift::driver(pros::controller_id_e_t controller,
                  pros::controller_digital_e_t upButton,
                  pros::controller_digital_e_t downButton) {
    if (pros::c::controller_get_digital(controller, upButton))
        up();
    else if (pros::c::controller_get_digital(controller, downButton))
        down();
    else
        stop();
}

void Lift::up() { motors.moveVelocity(maxUpSpd); }

void Lift::down() { motors.moveVelocity(maxDownSpd); }

void Lift::stop() {
    /** If the motors current position is less than the holdThreshold *
     * extGearRatio, set the brake mode to coast. Otherwise, have the motors
     * hold position when they stop.
     *
     * holdThreshold * extGearRatio is used because it represents the rotation
     * of the motors themselves to get the lift to the holdThreshold.
     * extGearRatio represents the number of rotations done by the lift in one
     * full rotation of the motor.
     */
    if (motors.getPosition() <= (holdThreshold * extGearRatio))
        motors.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    else
        motors.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    motors.moveVelocity(0);
};