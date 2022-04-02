#ifndef AUTONOMOUS_HPP
#define AUTONOMOUS_HPP

/**
 * \file autonomous.hpp
 *
 * This file holds the Autonomous namespace, used for types and variables
 * used in selecting an autonomous program.
 */

namespace Autonomous {

// List of autonomous routines formatted for use in the LVGL button matrix
// Initialize this in initialize()
extern const char* buttonMatrixList[];

// Defining the autonomous enumerator
// Change this between years
enum class Routine {
    none,
    test,
    competition_sideGoal,
    competition_middleGoal,
    skills
};

// Creating a Auton variable, with default value of NULL
extern Routine autonID;

}  // namespace Autonomous

#endif /* autonomous.hpp */