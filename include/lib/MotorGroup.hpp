/**
 * \file MotorGroup.hpp
 *
 * The MotorGroup class is the base of every class I write.
 * It encapsulates the PROS C Motor API by storing a vector
 * of ports for each motor and wrapping most PROS
 * functions so that they are called on all motors in the group.
 */

#ifndef MOTORGROUP_HPP
#define MOTORGROUP_HPP

#include <initializer_list>
#include <vector>

#include "api.h"

class MotorGroup {
   private:
    // The ports for all the motors
    std::vector<int> motorPorts;

   public:
    /**
     * The Constructor for a MotorGroup
     *
     * @param ports A list of integers representing the ports for each motor.
     * Ports are input like so: {<port1>, <port2>, etc.}
     * @param revs A list of whether each motor in the group is reversed
     */
    MotorGroup(std::initializer_list<int> ports,
               std::initializer_list<bool> revs);

    /*-------------------
     * Movement functions
     *-------------------*/
    /**
     * Function: move
     * This function serves as a "wrapper" for the pros::Motor::move function.
     * It calls the motor_move function on each motor with the given input
     *
     * @param voltage The motor voltage from -127 to 127 - the same as
     * pros::Motor::move
     */
    void move(int voltage);

    /**
     * Function: moveAbsolute
     * This function serves as a "wrapper" for the pros::Motor::move_absolute
     * function. It calls the motor_move_absolute function on each motor with
     * the given input
     *
     * @param position The absolute position to move to in the motor’s encoder
     * units - same as pros::Motor::move_absolute
     * @param velocity The maximum allowable velocity for the movement - same as
     * pros::Motor::move_absolute
     */
    void moveAbsolute(double position, int velocity);

    /**
     * Function: moveRelative
     * This function serves as a "wrapper" for the pros::Motor::move_relative
     * function. It calls the motor_move_relative function on each motor with
     * the given input
     *
     * @param position The absolute position to move to in the motor’s encoder
     * units - same as pros::Motor::move_relative
     * @param velocity The maximum allowable velocity for the movement - same as
     * pros::Motor::move_relative
     */
    void moveRelative(double position, int velocity);

    /**
     * Function: moveVelocity
     * This function serves as a "wrapper" for the PROS Motor::move_velocity
     * function. It calls the motor_move_velocity function on each motor with
     * the given input
     *
     * @param velocity The new motor velocity from +-100, +-200, or +-600
     * depending on the motor’s gearset - same as PROS Motor::move_velocity
     */
    void moveVelocity(int velocity);

    /**
     * Function: moveVoltage
     * This function serves as a "wrapper" for the PROS Motor::move_voltage
     * function. It calls the motor_move_voltage function on each motor with the
     * given input
     *
     * @param voltage The new voltage for the motor from -12000 mV to 12000 mV -
     * same as PROS Motor::move_voltage
     */
    void moveVoltage(int voltage);

    /**------------------------
     * Configuration Functions
     *-------------------------*/
    /**
     * Function: setEncoderUnits
     * This function sets the encoder units to be used by all of the motors.
     * It calls the motor_set_encoder_units function on each motor
     *
     * @param encoderUnits The new encoder units for the motors - of type
     * pros::motor_encoder_units_e_t
     */
    void setEncoderUnits(pros::motor_encoder_units_e_t encoderUnits);

    /**
     * Function: setBrakeMode
     * This function sets the brake mode to be used by all of the motors.
     * It calls the motor_set_brake_mode function on each motor
     *
     * @param brakeMode The new brake mode for the motors - of type
     * pros::motor_brake_mode_e_t
     */
    void setBrakeMode(pros::motor_brake_mode_e_t brakeMode);

    /**
     * Function: setGearing
     * This function sets the internal gearing for all of the motors.
     * It calls the motor_set_gearing function on each motor
     *
     * @param gearing The new gearing for the motors - of type
     * pros::motor_gearset_e_t
     */
    void setGearing(pros::motor_gearset_e_t gearing);

    /**-------------------
     * Telemetry Functions
     *--------------------*/
    /**
     * Function getPosition
     * This function returns the average current position of every motor
     * in the group, using the internal motor encoders
     *
     * @returns The average position of the
     */
    double getPosition();
};

#endif /* MotorGroup.hpp */