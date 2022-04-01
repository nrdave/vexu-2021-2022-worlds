/**
 * \file autonEnums.hpp
 *
 * This file holds the type definition for an enumerated type used to represent
 * which autonomous program to run when the autonomous function is run.
 */

#ifndef AUTONENUMS_HPP
#define AUTONENUMS_HPP

enum class Auton { none, competition_sideGoal, competition_middleGoal, skills };

Auton auton = Auton::none;

#endif /* autonEnums.hpp */