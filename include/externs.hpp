#ifndef EXTERNS_HPP
#define EXTERNS_HPP

#include "lib/Lift.hpp"
#include "lib/PneumaticClaw.hpp"
#include "lib/TankDrive.hpp"
#include "lib/autonomous.hpp"

// My Subsytem objects
extern Lift lift;

extern TankDrive drive;

extern PneumaticClaw claw;

// Creating a Auton variable
extern Autonomous::Routine autonID;

#endif  // externs.hpp