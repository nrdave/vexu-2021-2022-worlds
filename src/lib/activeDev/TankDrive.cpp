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
    encoderRadius = wheelTrackWidth / 2;
}

void TankDrive::addADIEncoders(char leftEncoderTopPort,
                               char leftEncoderBottomPort, bool leftEncoderRev,
                               char rightEncoderTopPort,
                               char rightEncoderBottomPort,
                               bool rightEncoderRev) {
    leftEncoder = new pros::ADIEncoder(leftEncoderTopPort,
                                       leftEncoderBottomPort, leftEncoderRev);
    rightEncoder = new pros::ADIEncoder(
        rightEncoderTopPort, rightEncoderBottomPort, rightEncoderRev);
}

// Movement Functions
void TankDrive::driver(pros::controller_id_e_t controller) {
    leftMotors.move(pros::c::controller_get_analog(
        controller, pros::E_CONTROLLER_ANALOG_LEFT_Y));
    rightMotors.move(pros::c::controller_get_analog(
        controller, pros::E_CONTROLLER_ANALOG_RIGHT_Y));
}

void TankDrive::drivePID(double leftTarg, double rightTarg) {
    short int count = 0;
    double leftTarg_Deg = (leftTarg / wheelRadius) * (180 / 3.1415);
    double rightTarg_Deg = (rightTarg / wheelRadius) * (180 / 3.1415);
    // Reset the encoders of the first motor on each side
    resetPositions();
    // Declare or initialize all variables used in the loop
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
    while (abs(leftError) > 5 || abs(rightError) > 5) {
        printf("\nLeft Targ: %f, Left Error: %f", leftTarg_Deg, leftError);
        printf("\nRight Targ: %f, Right Error: %f", rightTarg_Deg, rightError);
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
        printf("\nLeft Output: %f Right Output: %f", leftOutput, rightOutput);

        // Set the motor group voltages to the output velocity levels
        leftMotors.moveVoltage(leftOutput);
        rightMotors.moveVoltage(rightOutput);

        // Calculate the new error
        leftError = leftTarg_Deg - getLeftPosition();
        rightError = rightTarg_Deg - getRightPosition();

        // Timeout condition in case the drive gets stuck - rather not get to
        // correct position and continue than stop entirely
        if (leftError == leftPrevError && rightError == rightPrevError)
            count++;
        else
            count = 0;
        if (count >= 5) break;
        pros::delay(20);
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
     * Uses the arc length formula: s = r * theta
     */
    double turnLength = angle * encoderRadius * (3.1415 / 180);
}

// Telemetry Functions
double TankDrive::getLeftPosition() {
    if (leftEncoder != NULL)
        return leftEncoder->get_value();
    else
        return leftMotors.getPosition();
}

double TankDrive::getRightPosition() {
    if (rightEncoder != NULL)
        return rightEncoder->get_value();
    else
        return rightMotors.getPosition();
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
}