#include "lib/TankDrive.hpp"

TankDrive::TankDrive(std::initializer_list<int> leftPorts,
                     std::initializer_list<int> rightPorts,
                     std::initializer_list<bool> leftRevs,
                     std::initializer_list<bool> rightRevs)
    : leftMotors(leftPorts, leftRevs), rightMotors(rightPorts, rightRevs) {
    leftMotors.setEncoderUnits(pros::E_MOTOR_ENCODER_DEGREES);
    rightMotors.setEncoderUnits(pros::E_MOTOR_ENCODER_DEGREES);
}

// Configuration Functions
void TankDrive::setGearing(pros::motor_gearset_e_t gearing) {
    leftMotors.setGearing(gearing);
    rightMotors.setGearing(gearing);
}

void TankDrive::setPIDConstants(double Pconst, double Iconst, double Dconst) {
    kP = Pconst;
    kI = Iconst;
    kD = Dconst;
}

void TankDrive::setDimensions(double wheelDiameter, double wheelTrackWidth) {
    wheelRadius = wheelDiameter / 2;
    trackWidth = wheelTrackWidth / 2;
    printf("Tank Drive dimensions: Wheel Radius: %.2lf, Track width: %.2lf\n",
           wheelRadius, trackWidth);
}

void TankDrive::addADIEncoders(char leftEncoderTopPort, bool leftEncoderRev,
                               char rightEncoderTopPort, bool rightEncoderRev) {
    /**
     * ADI encoders require that the two wires are in adjacent ports, with the
     * "top" port being in one of ports A, C, E, or G. So, rather than passing
     * in both ports, the function accepts the top port and assumes the bottom
     * wire is in the next port.
     */
    leftEncoder = new pros::ADIEncoder(
        leftEncoderTopPort, static_cast<char>(leftEncoderTopPort + 1),
        leftEncoderRev);
    rightEncoder = new pros::ADIEncoder(
        rightEncoderTopPort, static_cast<char>(rightEncoderTopPort + 1),
        rightEncoderRev);
}

// Movement Functions
void TankDrive::driver(pros::controller_id_e_t controller) {
    leftMotors.move(pros::c::controller_get_analog(
        controller, pros::E_CONTROLLER_ANALOG_LEFT_Y));
    rightMotors.move(pros::c::controller_get_analog(
        controller, pros::E_CONTROLLER_ANALOG_RIGHT_Y));
}

void TankDrive::drivePID(double leftTarg, double rightTarg) {
    // Counts the number of cycles the robot has not moved - used for timeout
    // condition
    short int stoppedCount = 0;
    double leftTarg_Deg = (leftTarg / wheelRadius) * (180 / 3.1415);
    double rightTarg_Deg = (rightTarg / wheelRadius) * (180 / 3.1415);
    // Reset the encoders of  each side
    resetPositions();

    // Declare or initialize all variables used in the PID controller loop
    double leftError = leftTarg_Deg - getLeftPosition();
    double rightError = rightTarg_Deg - getRightPosition();
    double leftOutput;
    double rightOutput;
    double voltCap = 0.0;

    // Integral variables are initiated so that the += operator can be used
    // throughout the while loop
    double leftIntegral = 0;
    double rightIntegral = 0;
    double leftDerivative;
    double rightDerivative;
    // Declaring the Previous Error Variable
    double leftPrevError;
    double rightPrevError;
    // Enter a while loop that runs until both sides are within 10 degrees
    // of target rotation
    while ((abs(leftError) > 5 || abs(rightError) > 5) && stoppedCount < 5) {
        printf("Left Targ: %f, Left Error: %f\n", leftTarg_Deg, leftError);
        printf("Right Targ: %f, Right Error: %f\n", rightTarg_Deg, rightError);
        // Calculate the integral
        leftIntegral += leftError;
        rightIntegral += rightError;

        // Calculate the derivative
        leftDerivative = leftError - leftPrevError;
        rightDerivative = rightError - rightPrevError;

        // Set the previous error
        leftPrevError = leftError;
        rightPrevError = rightError;

        // Set the output values
        leftOutput =
            (leftError * kP) + (leftIntegral * kI) + (leftDerivative * kD);
        rightOutput =
            (rightError * kP) + (rightIntegral * kI) + (rightDerivative * kD);

        // Voltage slewing - prevents motors from recieving 12 volts from the
        // start
        if (voltCap < 12000)
            voltCap += 600;
        else
            voltCap = 12000;

        if (abs(leftOutput) > voltCap)
            leftOutput = copysign(voltCap, leftOutput);
        if (abs(rightOutput) > voltCap)
            rightOutput = copysign(voltCap, rightOutput);
        printf("Left Output: %f Right Output: %f\n", leftOutput, rightOutput);

        // Set the motor group voltages to the output velocity levels
        leftMotors.moveVoltage(leftOutput);
        rightMotors.moveVoltage(rightOutput);

        // Calculate the new error
        leftError = leftTarg_Deg - getLeftPosition();
        rightError = rightTarg_Deg - getRightPosition();

        // Timeout condition in case the drive gets stuck - rather not get to
        // correct position and continue than stop entirely
        if (leftError == leftPrevError && rightError == rightPrevError &&
            voltCap >= 6000)
            stoppedCount++;
        else
            stoppedCount = 0;
        pros::delay(5);
    }
    leftMotors.moveVelocity(0);
    rightMotors.moveVelocity(0);
    pros::delay(20);
}

void TankDrive::moveStraight(double distance) {
    /**
     * moveStraight simply calls drivePID with both sides having the same target
     */
    drivePID(distance, distance);
}

void TankDrive::turnAngle(double angle) {
    /**
     * Converting the angle to turn into the length of the arc each side needs
     * to turn.
     *
     * Uses the arc length formula: s = r * theta, where r is encoderRadius,
     * angle is the angle to turn (converted to radians), and turnLength is the
     * arc length, or the length each side of the base needs to travel
     */
    double turnLength = angle * trackWidth * (3.1415 / 180);

    /**
     * Calling the drivePID. The right side gets -turnLength as that causes the
     * robot to turn clockwise (right) when a positive angle is entered
     */
    drivePID(turnLength, -turnLength);
}

// Telemetry Functions
double TankDrive::getLeftPosition() {
    double output = 0;
    /**
     * If the drivetrain has ADI encoders, use them for the position. If not,
     * use the internal motor encoders
     */
    if (leftEncoder != NULL)
        output = leftEncoder->get_value();
    else
        output = leftMotors.getPosition();
    printf("Left Encoder Value: %.3lf\n", output);
    return output;
}

double TankDrive::getRightPosition() {
    double output = 0;
    /**
     * If the drivetrain has ADI encoders, use them for the position. If not,
     * use the internal motor encoders
     */
    if (rightEncoder != NULL)
        output = rightEncoder->get_value();
    else
        output = rightMotors.getPosition();
    printf("Right Encoder Value: %.3lf\n", output);
    return output;
}

void TankDrive::resetPositions() {
    if (leftEncoder != NULL)
        leftEncoder->reset();
    else
        leftMotors.resetPosition();

    if (rightEncoder != NULL)
        rightEncoder->reset();
    else
        rightMotors.resetPosition();

    printf("Encoders have been reset.\n");
}