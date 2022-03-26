#include "lib/MotorGroup.hpp"

/* The Constructor for MotorGroup*/
MotorGroup::MotorGroup(std::initializer_list<int> ports, std::initializer_list<bool> revs) {
    /* Store the ports in the motorPorts vector*/
    motorPorts = ports;
    std::vector<bool> motorRevs = revs;
    for(int i = 0; i < motorPorts.size(); ++i) {
        // Set the reversed state of each motor to match the revs argument
        pros::c::motor_set_reversed(motorPorts[i], motorRevs[i]);
    }
}

/**
 * As noted in MotorGroup.hpp, all of these functions simply call
 * their respective pros functions on each motor.
 */

/* Movement Functions */
void MotorGroup::move(int voltage) {
    for(int p : motorPorts) {
        pros::c::motor_move(p, voltage);
    }
}

void MotorGroup::moveAbsolute(double position, int velocity) {
    for(int p : motorPorts) {
        pros::c::motor_move_absolute(p, position, velocity);
    }
}

void MotorGroup::moveRelative(double position, int velocity) {
    for(int p : motorPorts) {
        pros::c::motor_move_relative(p, position, velocity);
    }
}

void MotorGroup::moveVelocity(int velocity) {
    for(int p : motorPorts) {
        pros::c::motor_move_velocity(p, velocity);
    }
}

void MotorGroup::moveVoltage(int voltage) {
    for(int p : motorPorts) {
        pros::c::motor_move_voltage(p, voltage);
    }
}

/* Configuration Functions */
void MotorGroup::setEncoderUnits(pros::motor_encoder_units_e_t encoderUnits) {
    for(int p : motorPorts) {
        pros::c::motor_set_encoder_units(p, encoderUnits);
    }
}

void MotorGroup::setBrakeMode(pros::motor_brake_mode_e_t brakeMode) {
    for(int p : motorPorts) {
        pros::c::motor_set_brake_mode(p, brakeMode);
    }
}

void MotorGroup::setGearing(pros::motor_gearset_e_t gearing) {
    for(int p : motorPorts) {
        pros::c::motor_set_gearing(p, gearing);
    }    
}

/* Telemetry Functions */

double MotorGroup::getPosition() {
    return pros::c::motor_get_position(motorPorts[0]);
}