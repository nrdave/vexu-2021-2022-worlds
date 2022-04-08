#ifndef TANKDRIVE_HPP
#define TANKDRIVE_HPP

#include <initializer_list>

#include "api.h"
#include "lib/MotorGroup.hpp"

/**
 * \file TankDrive.hpp
 *
 * The TankDrive class is used to abstract the motors and (optionally)
 * ADI quadrature encoders on the drivetrain.
 */
class TankDrive {
   private:
    /**
     * The MotorGroups representing each group of motors on the drivetrain.
     */
    MotorGroup leftMotors, rightMotors;

    /**
     * The constants for the drivetrain's PID controller.
     * kP is the proportional constant, kI is the integral constant, and kD is
     * the derivative constant.
     */
    double kP, kI, kD;

    /**
     * A variable used to store the radius of the wheels on the drivetrain.
     * This value is used in autonomous to calculate the distance to travel.
     */
    double wheelRadius;

    /**
     * A variable used to store the distance between the robot's center of
     * rotation and the location of the encoders used to track position, is used
     * in the turnAngle function.
     */
    double encoderRadius;

    /**
     * Pointers to PROS ADI encoders that can be added to the drivetrain. By
     * default, the drivetrain uses the internal motor encoders in its functions
     * to get position, but adding encoders causes the drivetrain to use them
     * instead.
     *
     * I use pointers so that the get position functions can check if the
     * drivetrain has encoders by testing if the pointers are NULL.
     */
    pros::ADIEncoder* leftEncoder = NULL;
    pros::ADIEncoder* rightEncoder = NULL;

    /**
     * Function: drivePID
     * This function contains the actual PID controller used to control the
     * drivetrain in autonomous control. It is used as the base for all
     * autonomous functions. Individual functions conduct any calculations
     * needed to get the needed target values before passing those values
     * into drivePID. Important: drivePID is a blocking function (the robot
     * must reach the target before the controller exits)
     *
     * The function is private, as I feel like being able to directly assign
     * the targets for the controller doesn't make sense.
     *
     * @param leftTarg: The target length to move to, in inches, for the
     * left side of the drivetrain Can be negative to indicate rotating
     * backwards
     * @param rightTarg: The target length to move to, in inches, for the
     * right side of the drivetrain Can be negative to indicate rotating
     * backwards
     */
    void drivePID(double leftTarg, double rightTarg);

   public:
    /**
     * A constructor for the TankDrive class. This one is used for initializing
     * a TankDrive object that uses the internal motor encoders in autonomous
     * control.
     *
     * @param leftPorts: A list of the ports for the left side of the drive
     * @param rightPorts: A list of the ports for the right side of the
     * drivetrain
     * @param leftRevs: A list of booleans determining which motor(s) on the
     * left side need to be reversed
     * @param rightRevs: A list of booleans determining which motor(s) on the
     * left side need to be reversed The individual booleans in leftRevs and
     * rightRevs match to the ports for each side of the drivetrain that match
     * to the port numbers in the corresponding indeces in leftPorts/rightPorts
     */
    TankDrive(std::initializer_list<int> leftPorts,
              std::initializer_list<int> rightPorts,
              std::initializer_list<bool> leftRevs,
              std::initializer_list<bool> rightRevs);

    /*-------------------------
     * Configuration functions
     *-------------------------*/
    /**
     * Function: setGearing
     * This function configures the internal gearing on the motors.
     * If this is not called, the MotorGroups will assume a default
     * value of green motor cartrigdes (max 200 RPM)
     *
     * @param gearing The type of gear cartridge in the actual motors
     */
    void setGearing(pros::motor_gearset_e_t gearing);

    /**
     * Function: setPIDConstants
     * This function sets the PID constants of the drivetrain.
     *
     * @param Pconst: the value of the proportional constant in the PID
     * controller
     * @param Iconst: the value of the integral constant in the PID controller
     * @param Dconst: the value of the derivative constant in the PID controller
     */
    void setPIDConstants(double Pconst, double Iconst, double Dconst);

    /**
     * Function: setDimensions
     * This function sets the dimensions of the drivetrain. These values are
     * important for autonomous control, as the dimensions of the drive are
     * required for calculating distances to travel.
     *
     * @param wheelDiameter The diameter of the wheels on the drivetrain. If
     * encoders are being used, then this should be the diameter of the encoder
     * wheels.
     * @param wheelTrackWidth The distance between the wheels on each side of
     * the drivetrain.
     */
    void setDimensions(double wheelDiameter, double wheelTrackWidth);

    /**
     * Function: addADIEncoders
     * This function initializes the ADI encoders that can be used for getting
     * the robot's position.
     * @param leftEncoderTopPort The "top" port of the ADI Encoder for the left
     * side of the drivetrain. The "bottom" wire must be plugged into the next
     * port. See PROS Docs for value constraints:
     * https://pros.cs.purdue.edu/v5/api/cpp/adi.html#pros-adiencoder
     * @param leftEncoderRev Whether or not the left encoder needs to be
     * reversed
     * @param rightEncoderTopPort The "top" port of the ADI Encoder for the
     * right side of the drivetrain. The "bottom" wire must be plugged into the
     * next port. See PROS Docs for value constraints:
     * https://pros.cs.purdue.edu/v5/api/cpp/adi.html#pros-adiencoder
     * @param rightEncoderRev Whether or not the right encoder needs to be
     * reversed
     */
    void addADIEncoders(char leftEncoderTopPort, bool leftEncoderRev,
                        char rightEncoderTopPort, bool rightEncoderRev);

    /*-------------------
     * Movement functions
     *-------------------*/
    /**
     * Function: driver
     * This function is used to control the drivetrain in driver control. It
     * uses a 2 joystick tank drive style of control, with the Y axes on
     * each joystick controlling their respective sides of the drive.
     *
     * @param controller the ID of the controller to get joystick values
     * from
     */
    void driver(pros::controller_id_e_t controller);

    /**
     * Function: moveStraight
     * This function tells the drivetrain to drive forward or backward a given
     * amount of inches. Used in autonomous.
     *
     * @param distance: the distance to travel, in inches. Negative values =
     * backwards
     */
    void moveStraight(double distance);

    /**
     * Function: turnAngle
     * This function makes the drivetrain turn a given amount of degrees. Used
     * in autonomous
     *
     * @param angle: the angle to which to turn. Clockwise is positive,
     * counterclockwise is negative. For example, passing in 45 would make the
     * robot turn 45 degrees to the right (clockwise, from an overhead view)
     */
    void turnAngle(double angle);

    /*--------------------
     * Telemetry Functions
     *--------------------*/
    /**
     * Function: getLeftPosition
     * Gets the current position of the left drivetrain. Either uses the
     * MotorGroup getPosition function or the ADI encoder (if it is initialized)
     *
     * @return the current position of the left side of the base (in the encoder
     * ticks - which is equivalent to degrees)
     */
    double getLeftPosition();

    /**
     * Function: getRightPosition
     * Gets the current position of the right drivetrain. Either uses the
     * MotorGroup getPosition function or the ADI encoder (if it is initialized)
     *
     * @return the current position of the right side of the base (in the
     * encoder ticks - which is equivalent to degrees)
     */
    double getRightPosition();

    /**
     * Function: resetPositions
     * This function resets the positions of whatever mechanism the drivetrain
     * is using to track its position in autonomous control.
     */
    void resetPositions();
};

#endif /* TankDrive.hpp*/