#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

// Autonomous namespace variables - initialized here for organization
Autonomous::Routine Autonomous::autonID = Autonomous::Routine::none;
const char* Autonomous::buttonMatrixList[] = {
    "Skills", "Test",
    "\n",     "Competition - Side Goal",
    "\n",     "Competition - Middle Goal",
    "\n",     "None",
    ""};

void autonomous() {
    switch (Autonomous::autonID) {
        case Autonomous::Routine::skills:
            // Skills Auton
            // Score ring
            drive->moveDistance(5_in);
            claw.closeTo(110);

            // Move around platform
            drive->moveDistance(-5_in);
            drive->turnAngle(-90_deg);

            // Push blue mogo to blue home zone
            drive->moveDistance(80_in);
            drive->turnAngle(-30_deg);
            claw.openTo(90);
            drive->moveDistance(-10_in);
            break;
        case Autonomous::Routine::test:
            drive->moveDistance(5_in);
            break;
        case Autonomous::Routine::competition_sideGoal:

            // Gets ring on alliance goal, then gets side neutral goal
            // Score ring
            drive->moveDistance(5_in);
            claw.closeTo(110);

            // Move alliance mobile goal to middle
            drive->moveDistance(-5_in);
            drive->turnAngle(-75_deg);
            drive->moveDistance(30_in);
            drive->turnAngle(75_deg);

            // let go of mobile goal
            claw.openTo(90);
            drive->moveDistance(-3_in);

            // Go for side neutral mobile goal
            drive->turnAngle(-85_deg);
            drive->moveDistance(18_in);
            claw.closeTo(90);

            // Score side neutral goal
            drive->moveDistance(-12_in);
            drive->turnAngle(180_deg);
            drive->moveDistance(12_in);

            // Set up for Driver
            claw.openTo(90);
            drive->moveDistance(-5_in);
            break;
        case Autonomous::Routine::competition_middleGoal:

            // Gets ring on alliance goal, then gets middle neutral goal
            // Score ring
            drive->moveDistance(5_in);
            claw.closeTo(110);

            // Move alliance mobile goal to middle
            drive->moveDistance(-5_in);
            drive->turnAngle(-85_deg);
            drive->moveDistance(36_in);

            // clear rings using alliance goal
            drive->turnAngle(105_deg);

            // let go of mobile goal
            drive->moveDistance(3_in);
            claw.openTo(90);
            drive->moveDistance(-3_in);

            // Go for middle neutral mobile goal
            drive->turnAngle(-50_deg);
            drive->moveDistance(30_in);
            claw.closeTo(90);

            // Score middle neutral goal
            drive->moveDistance(-18_in);
            drive->turnAngle(180_deg);
            drive->moveDistance(36_in);

            // Set up for Driver
            claw.openTo(90);
            drive->moveDistance(-5_in);
            drive->turnAngle(135_deg);

            break;
        case Autonomous::Routine::none:
            break;
        default:
            break;
    }
}