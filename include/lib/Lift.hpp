#ifndef LIFT_HPP
#define LIFT_HPP

#include <initializer_list>

#include "lib/MotorGroup.hpp"

/**
 * \file Lift.hpp
 *
 * The Lift class is used to abstract any sort of lift. It provides a simple
 * interface to control a MotorGroup.
 *
 * Generally, the naming conventions map best to a n-bar style lift.
 */
class Lift {
   private:
    // The MotorGroup that represents the motors on the lift
    MotorGroup motors;
    /**
     * The maximum speeds (in RPM) that the motors can travel at. 100 is the
     * default as that is both a) a reasonable speed, and b) is the fastest
     * motors with red gear cartridges can go.
     */
    int maxUpSpd = 100;
    int maxDownSpd = 100;

    /**
     * The external gear ratio transferring power from the motor to the lift.
     * Defaults to 1, which means that the rate of rotation for the motor and
     * the mechanism driving the lift are the same.
     */
    double extGearRatio = 1.0;

    /**
     * The minimum position of the motors for them to hold position,
     * in degrees. The threshold is used
     * to determine whether to have the motors hold their position or
     * simply coast to a stop. This is useful for having the motors not hold
     * position when close to the ground, where holding position is not
     * important. This allows the motors to rest until their next use.
     */
    double holdThreshold = 0;

   public:
    /**
     * The constructor for the Lift class
     *
     * @param ports A list of the ports of the motors on the lift
     * @param revs A list of booleans indicating which motors are reversed
     */
    Lift(std::initializer_list<int> ports, std::initializer_list<bool> revs);

    /*-------------------------
     * Configuration functions
     *-------------------------*/
    /**
     * Function: setGearing
     * This function configures the internal gearing on the motors.
     * If this is not called, the MotorGroup will assume a default
     * value of green motor cartrigdes (max 200 RPM)
     *
     * @param gearing The type of gear cartridge in the actual motors
     */
    void setGearing(pros::motor_gearset_e_t gearing);

    /**
     * Function: setExternalGearRatio
     * This function defines the external gear ratio on the lift.
     * Most lifts are not powered directly from a motor, instead
     * being driven off of some sort of torque gear ratio, such as
     * a 1:5 ratio, with a 12 tooth gear driving a 60 tooth gear.
     * This function allows position-based measurements, such as
     * the holdThreshold in stop() to account for the gear ratio.
     *
     * @param ratio The gear ratio of the gear train transferring
     *              power from the motor to the lift. It should be
     *              input like so (teeth on driving gear) / (teeth on driven
     * gear) For example, for a 12 tooth to 60 tooth gear train, ratio is 12 /
     * 60
     */
    void setExternalGearRatio(double ratio);

    /**
     * Function: setMaxSpeeds
     * This function changes the maximum speeds, in RPM, of the lift motors.
     * There are separate up and down speeds as, generally,
     * having a lift go down slower is a good idea, as it prevents
     * a rough impact on wherever the end of the lift rests.
     *
     * @param maxUpRPM The maximum speed of the motors while going up, in RPM
     * @param maxDownRPM The maximum speed of the motors while going down, in
     * RPM
     */
    void setMaxSpeeds(int maxUpRPM, int maxDownRPM);

    /**
     * Function: setHoldThreshold
     * This function changes the threshold at which the motors on the lift
     * will start holding their position, rather than allowing free movement.
     *
     * @param degrees The rotation from the 0 position at which the motors
     * should begin holding their position
     */
    void setHoldThreshold(double degrees);
    /*-------------------
     * Movement functions
     *-------------------*/

    /**
     * Function: driver
     * This function is used to control the lift while in opcontrol.
     *
     * @param controller The controller ID representing the physical controller
     * @param upButton The button on the controller used to move the lift up
     * @param downButton The button on the controller used to move the lift down
     */
    void driver(pros::controller_id_e_t controller,
                pros::controller_digital_e_t upButton,
                pros::controller_digital_e_t downButton);

    /**
     * Function: up
     * Wraps the MotorGroup calls to move the lift up
     */
    void up();
    /**
     * Function: down
     * Wraps the MotorGroup calls to move the lift down
     */
    void down();
    /**
     * Function: stop
     * Wraps the MotorGroup calls to stop the lift
     */
    void stop();
};

#endif /* Lift.hpp */