#include "lib/Claw.hpp"

Claw::Claw(std::initializer_list<int> ports, std::initializer_list<bool> revs)
    : motors(ports, revs) {
    // Encoders output their rotation in degrees (Other options don't really
    // make sense)
    motors.setEncoderUnits(pros::E_MOTOR_ENCODER_DEGREES);
}

void Claw::setGearing(pros::motor_gearset_e_t gearing) {
    motors.setGearing(gearing);
}

void Claw::setMaxSpeed(int maxRPM) { maxSpd = maxRPM; }

void Claw::setDigitalRotation(double degrees) { digitalRotation = degrees; }

void Claw::driver(pros::controller_id_e_t controller,
                  pros::controller_digital_e_t closeButton,
                  pros::controller_digital_e_t openButton) {
    if (pros::c::controller_get_digital(controller, closeButton))
        close();
    else if (pros::c::controller_get_digital(controller, openButton))
        open();

    else
        motors.moveVelocity(0);
}

void Claw::driver(pros::controller_id_e_t controller,
                  pros::controller_digital_e_t closeButton,
                  pros::controller_digital_e_t openButton,
                  pros::controller_digital_e_t digitalCloseButton,
                  pros::controller_digital_e_t digitalOpenButton) {
    if (pros::c::controller_get_digital(controller, digitalCloseButton))
        closeTo();
    else if (pros::c::controller_get_digital(controller, digitalOpenButton))
        openTo();

    else
        // If neither digital button is pressed, call the simpler driver
        // function for analog control
        driver(controller, closeButton, openButton);
}

void Claw::open() {
    // If the claw is opening, holding position is not important. So, it's
    // better to not have the motors hold position
    motors.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    // The direction for the motors to rotate in order to open the claw is
    // assumed to be negative
    motors.moveVelocity(-maxSpd);
}

void Claw::close() {
    // If the claw is closing, holding position is important in order to ensure
    // that the object being held is not let go of.
    motors.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    motors.moveVelocity(maxSpd);
}

void Claw::openTo(double degrees) {
    int timeout = 0;

    // If the claw is opening, holding position is not important. So, it's
    // better to not have the motors hold position
    motors.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    // The direction for the motors to rotate in order to open the claw is
    // assumed to be negative
    motors.moveRelative(-degrees, maxSpd);
    while (!((motors.getPosition() > -degrees + 5) &&
             (motors.getPosition() < -degrees - 5)) &&
           timeout < 5) {
        pros::delay(2);
        ++timeout;
    }
}

void Claw::closeTo(double degrees) {
    int timeout = 0;

    // If the claw is closing, holding position is important in order to ensure
    // that the object being held is not let go of.
    motors.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    motors.moveRelative(degrees, maxSpd);
    while (!((motors.getPosition() < degrees + 5) &&
             (motors.getPosition() > degrees - 5)) &&
           timeout < 5) {
        pros::delay(2);
        ++timeout;
    }
}

// Overloaded openTo and closeTo functions that use digitalRotation
void Claw::openTo() { openTo(digitalRotation); }
void Claw::closeTo() { closeTo(digitalRotation); }