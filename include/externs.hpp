#include "okapi/api.hpp"
#include "lib/Lift.hpp"

#ifndef EXTERNS_HPP
#define EXTERNS_HPP

// The OkapiLib ChassisController and Controller, used solely for the drive
extern std::shared_ptr<okapi::ChassisController> drive;

extern okapi::Controller controller;

// My Subsytem objects
extern Lift lift;

#endif // externs.hpp