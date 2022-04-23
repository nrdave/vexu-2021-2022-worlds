#ifndef EXTERNS_HPP
#define EXTERNS_HPP

#include "lib/FourBar.hpp"
#include "lib/PneumaticClaw.hpp"
#include "lib/TankDrive.hpp"
#include "lib/autonomous.hpp"

// My Subsytem objects

// The 4-bar lift
extern FourBar lift;

// The drivetrain
extern TankDrive drive;

// The claw
extern PneumaticClaw claw;

// Creating a Auton variable to track which autonomous routine to run
extern Autonomous::Routine autonID;

#endif  // externs.hpp