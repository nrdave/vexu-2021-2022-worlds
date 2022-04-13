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
            drive.moveStraight(5);
            claw.close();

            // Move around platform
            drive.moveStraight(-5);
            drive.turnAngle(-90);

            // Push blue mogo to blue home zone
            drive.moveStraight(80);
            drive.turnAngle(-30);
            claw.open();
            drive.moveStraight(-10);

            break;
        case Autonomous::Routine::competition_sideGoal:

            // Gets ring on alliance goal, then gets side neutral goal
            // Score ring
            drive.moveStraight(5);
            claw.close();

            // Move alliance mobile goal to middle
            drive.moveStraight(-5);
            drive.turnAngle(-75);
            drive.moveStraight(30);
            drive.turnAngle(75);

            // let go of mobile goal
            claw.open();
            drive.moveStraight(-3);

            // Go for side neutral mobile goal
            drive.turnAngle(-85);
            drive.moveStraight(18);
            claw.close();

            // Score side neutral goal
            drive.moveStraight(-12);
            drive.turnAngle(180);
            drive.moveStraight(12);

            // Set up for Driver
            claw.open();
            drive.moveStraight(-5);

            break;
        case Autonomous::Routine::competition_middleGoal:

            // Gets ring on alliance goal, then gets middle neutral goal
            // Score ring
            drive.moveStraight(5);
            claw.close();

            // Move alliance mobile goal to middle
            drive.moveStraight(-5);
            drive.turnAngle(-85);
            drive.moveStraight(36);

            // clear rings using alliance goal
            drive.turnAngle(105);

            // let go of mobile goal
            drive.moveStraight(3);
            claw.open();
            drive.moveStraight(-3);

            // Go for middle neutral mobile goal
            drive.turnAngle(-50);
            drive.moveStraight(30);
            claw.close();

            // Score middle neutral goal
            drive.moveStraight(-18);
            drive.turnAngle(180);
            drive.moveStraight(36);

            // Set up for Driver
            claw.open();
            drive.moveStraight(-5);
            drive.turnAngle(135);

            break;
        case Autonomous::Routine::test:
            drive.moveStraight(5);

            break;
        case Autonomous::Routine::none:
        default:
            break;
    }
}