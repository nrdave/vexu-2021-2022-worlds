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
void autonomous() {
    switch
        auton {
            case Auton::competition_sideGoal:

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
                drive->moveDistance(-12, 60);
                drive->turnAngle(180);
                drive->moveDistance(12, 75);

                // Set up for Driver
                claw.openTo(90);
                drive->moveDistance(-5, 50);
                break;
            case Auton::competition_middleGoal:

                // Gets ring on alliance goal, then gets middle neutral goal
                // Score ring
                drive->moveDistance(5, 35);
                claw.closeTo(110);

                // Move alliance mobile goal to middle
                drive->moveDistance(-5, 50);
                drive->turnAngle(-85);
                drive->moveDistance(36, 50);

                // clear rings using alliance goal
                drive->turnAngle(105);

                // let go of mobile goal
                drive->moveDistance(3, 50);
                claw.openTo(90);
                drive->moveDistance(-3, 20);

                // Go for middle neutral mobile goal
                drive->turnAngle(-50);
                drive->moveDistance(30, 60);
                claw.closeTo(90);

                // Score middle neutral goal
                drive->moveDistance(-18, 50);
                drive->turnAngle(180);
                drive->moveDistance(36, 60);

                // Set up for Driver
                claw.openTo(90);
                drive->moveDistance(-5, 50);
                drive->turnAngle(135);

                break;
            case Auton::skills:
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
            case Auton::none:
                break;
            default:
                break;
        }
}