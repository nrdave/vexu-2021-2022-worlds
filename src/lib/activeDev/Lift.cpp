#include "lib/Lift.hpp"

Lift::Lift(std::initializer_list<int> ports, std::initializer_list<bool> revs,
           pros::controller_digital_e_t upButton, pros::controller_digital_e_t downButton,
           pros::motor_encoder_units_e_t encoderUnits,
           pros::motor_gearset_e_t gearing,
           int maxUpRPM, int maxDownRPM): 
           motors(ports, revs)
           {
               motors.setEncoderUnits(encoderUnits);
               motors.setGearing(gearing);
               motors.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

               upBtn = upButton;
               downBtn = downButton;
               maxUpVelo = maxUpRPM;
               maxDownVelo = maxDownRPM;
}

void Lift::driver(pros::controller_id_e_t controller) {
    if (pros::c::controller_get_digital(controller, upBtn)) up();
    else if (pros::c::controller_get_digital(controller, downBtn)) down();
    else stop();
}

void Lift::up() {
    motors.moveVelocity(maxUpVelo);
}

void Lift::down() {
    motors.moveVelocity(maxDownVelo);
}

void Lift::stop() {
    if(motors.getPosition() <= 20) motors.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    else motors.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    motors.moveVelocity(0);
};