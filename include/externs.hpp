#include "lib/Claw.hpp"
#include "lib/Lift.hpp"
#include "lib/autonEnums.hpp"
#include "okapi/api.hpp"

#ifndef EXTERNS_HPP
#define EXTERNS_HPP

// The OkapiLib ChassisController and Controller, used solely for the drive
extern std::shared_ptr<okapi::ChassisController> drive;

extern okapi::Controller controller;

// My Subsytem objects
extern Lift lift;

extern Claw claw;

// extern Auton enum for specifying which autonomous routine to run
extern Auton auton;

#endif  // externs.hpp