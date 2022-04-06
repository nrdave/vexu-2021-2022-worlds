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
        /*
        case Autonomous::Routine::skills:
            // Skills Auton
            // Score ring
            drive->moveDistance(5);
            claw.closeTo(110);

            // Move around platform
            drive->moveDistance(-5);
            drive->turnAngle(-90);

            // Push blue mogo to blue home zone
            drive->moveDistance(80);
            drive->turnAngle(-30);
            claw.openTo(90);
            drive->moveDistance(-10);
            break;

        case Autonomous::Routine::competition_sideGoal:

            // Gets ring on alliance goal, then gets side neutral goal
            // Score ring
            drive->moveDistance(5);
            claw.closeTo(110);

            // Move alliance mobile goal to middle
            drive->moveDistance(-5);
            drive->turnAngle(-75);
            drive->moveDistance(30);
            drive->turnAngle(75);

            // let go of mobile goal
            claw.openTo(90);
            drive->moveDistance(-3);

            // Go for side neutral mobile goal
            drive->turnAngle(-85);
            drive->moveDistance(18);
            claw.closeTo(90);

            // Score side neutral goal
            drive->moveDistance(-12);
            drive->turnAngle(180);
            drive->moveDistance(12);

            // Set up for Driver
            claw.openTo(90);
            drive->moveDistance(-5);
            break;
        case Autonomous::Routine::competition_middleGoal:

            // Gets ring on alliance goal, then gets middle neutral goal
            // Score ring
            drive->moveDistance(5);
            claw.closeTo(110);

            // Move alliance mobile goal to middle
            drive->moveDistance(-5);
            drive->turnAngle(-85);
            drive->moveDistance(36);

            // clear rings using alliance goal
            drive->turnAngle(105);

            // let go of mobile goal
            drive->moveDistance(3);
            claw.openTo(90);
            drive->moveDistance(-3);

            // Go for middle neutral mobile goal
            drive->turnAngle(-50);
            drive->moveDistance(30);
            claw.closeTo(90);

            // Score middle neutral goal
            drive->moveDistance(-18);
            drive->turnAngle(180);
            drive->moveDistance(36);

            // Set up for Driver
            claw.openTo(90);
            drive->moveDistance(-5);
            drive->turnAngle(135);

            break;
            */
        case Autonomous::Routine::test:
            break;

        case Autonomous::Routine::none:
            break;
        default:
            break;
    }
}