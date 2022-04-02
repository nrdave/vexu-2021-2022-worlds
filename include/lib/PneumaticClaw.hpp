#ifndef PNEUMATICCLAW_HPP
#define PNEUMATICCLAW_HPP

#include "api.h"

class PneumaticClaw {
   private:
    /* The port in which the pneumatic solenoid (the part of a pneumatic system
     * that controls air flow) is plugged into in the brain. Can range between
     * 'a' and 'h' (lower or upper case)
     */
    char p;

    /**
     * Stores whether the claw is currently in its extended position
     */
    bool closed;

    /**
     * Counts how many cycles the button to toggle the claw has been pressed for
     * in driver control. This is useful to prevent the claw from opening and
     * then immediately closing, which is caused by the button to control the
     * claw being held for 2 clock cycles
     */
    int pressedCount = 0;

   public:
    /**
     * The constructor for the PneumaticClaw class
     *
     * @param port The ADI port that the pneumatic solenoid controlling the claw
     * is plugged into. Can range between 'a' and 'h'.
     * @param initExtended Specifies what position the claw starts in: true for
     * closed, false for open.
     */
    PneumaticClaw(char port, bool initPosition);

    /**
     * Function: driver
     * Used to control the claw in driver control.
     *
     * @param controller The controller ID representing the physical controller
     * @param button The button ID on the controller used to toggle the claw
     */
    void driver(pros::controller_id_e_t controller,
                pros::controller_digital_e_t button);
    /**
     * Function: close
     * If the claw is open, calling this function closes the claw
     * If not, this function won't do anything
     */
    void close();

    /**
     * Function: open
     * If the claw is closed, calling this function opens the claw
     * If not, this function won't do anything
     */
    void open();
};

#endif /* PneumaticClaw.hpp */