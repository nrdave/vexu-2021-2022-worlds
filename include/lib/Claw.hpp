#ifndef CLAW_HPP
#define CLAW_HPP

#include "lib/MotorGroup.hpp"

/**
 * \file Claw.hpp
 *
 * The claw class is used to represent any sort of claw or grabbing device.
 * It encapsulates my MotorGroup class with various functions.
 */
class Claw {
   private:
    // The MotorGroup representing all motors controlling the claw
    MotorGroup motors;

    /**
     * The maximum speed (in RPM) that the motors can travel at. 100 is the
     * default as that is both a) a reasonable speed, and b) is the fastest
     * motors with red gear cartridges can go.
     */
    int maxSpd = 100;

    /**
     * A variable holding the amount of degrees for the claw to rotate
     * to open/close. Used in digital claw control, which is when a single
     * button is pressed once to open/close the claw. In contrast, analog
     * claw control involves having to hold a button to keep the claw moving
     *
     * Defaults to 90 degrees (generally a good amount)
     */
    double digitalRotation = 90;

   public:
    /**
     * The constructor for the Claw class
     *
     * @param ports A list of the ports of the motors on the claw
     * @param revs A list of booleans indicating which motors are reversed
     * (close is assumed to be the positive direction)
     */
    Claw(std::initializer_list<int> ports, std::initializer_list<bool> revs);

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
     * Function: setMaxSpeed
     * This function changes the maximum speeds, in RPM, of the claw motors.
     *
     * @param maxRPM The maximum speed of the motors, in RPM
     */
    void setMaxSpeed(int maxRPM);

    /**
     * Function: setDigitalRotation
     * This function sets the value of digitalRotation, which is used
     * to determine how many degrees the motors rotate to open/close the
     * claw in digital control mode. This is when a single button is pressed
     * once to open/close the claw. In contrast, analog claw control involves
     * having to hold a button to keep the claw moving
     *
     * @param degrees The degrees for the claw to rotate in order to open/close
     */
    void setDigitalRotation(double degrees);

    /**------------------
     * Movement Functions
     *-------------------*/

    /**
     * Function: driver
     * This implementation simply calls either open() or close() if the related
     * buttons are pressed, and sets the velocity of the motors to 0 otherwise
     *
     * @param controller The controller ID representing the physical controller
     * @param openButton The button on the controller used to open the claw
     * @param closeButton The button on the controller used to close the claw
     */
    void driver(pros::controller_id_e_t controller,
                pros::controller_digital_e_t closeButton,
                pros::controller_digital_e_t openButton);

    /**
     * Function: driver
     * This implementation of the driver function builds on the previous one
     * by adding digital claw control, which is when a single button is pressed
     * once to open/close the claw. In contrast, analog claw control involves
     * having to hold a button to keep the claw moving
     *
     * @param controller The controller ID representing the physical controller
     * @param openButton The button on the controller used to open the claw
     * manually (must be held down)
     * @param closeButton The button on the controller used to close the claw
     * manually (must be held down)
     * @param digitalOpenButton The button on the controller used to open the
     * claw digitally (single press)
     * @param digitalCloseButton The button on the controller used to close the
     * claw digitally (single press)
     */
    void driver(pros::controller_id_e_t controller,
                pros::controller_digital_e_t closeButton,
                pros::controller_digital_e_t openButton,
                pros::controller_digital_e_t digitalCloseButton,
                pros::controller_digital_e_t digitalOpenButton);

    /**
     * Function: open()
     * Wraps the MotorGroup calls to open the claw
     * Simply sets the velocity of the motors, does not set a target
     */
    void open();

    /**
     * Function: close()
     * Wraps the MotorGroup calls to close the claw
     * Simply sets the velocity of the motors, does not set a target
     */
    void close();

    /**
     * Function: openTo
     * Rotates the claw open by a given degree amount.
     *
     * @param degrees The amount of degrees to rotate the claw open by
     */
    void openTo(double degrees);

    /**
     * Function: closeTo
     * Rotates the claw closed by a given degree amount.
     *
     * @param degrees The amount of degrees to rotate the claw closed by
     */
    void closeTo(double degrees);

    /**
     * Function: openTo
     * Calls openTo with digitalRotation (the default rotation of the claw in
     * digital control)
     */
    void openTo();

    /**
     * Function: closeTo
     * Calls openTo with digitalRotation (the default rotation of the claw in
     * digital control)
     */
    void closeTo();
};

#endif  // Claw.hpp