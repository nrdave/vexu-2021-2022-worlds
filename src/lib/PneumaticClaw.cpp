#include "lib/PneumaticClaw.hpp"

PneumaticClaw::PneumaticClaw(char port, bool initPosition)
    : p{port}, closed{initPosition} {
    pros::c::adi_port_set_config(p, pros::E_ADI_DIGITAL_OUT);
}

void PneumaticClaw::driver(pros::controller_id_e_t controller,
                           pros::controller_digital_e_t button) {
    /**
     * The driver function requires that the button to control the claw is held
     * down for multiple cycles. This prevents the claw from opening on a button
     * press, then immediately closing since the button is still pressed on the
     * next iteration of the opcontrol while loop.
     */
    if (pros::c::controller_get_digital(controller, button)) ++pressedCount;
    if (pressedCount >= 10) {
        if (closed)
            open();
        else
            close();
        pressedCount = 0;
    }
}

void PneumaticClaw::close() {
    if (!closed) {
        pros::c::adi_digital_write(p, true);
        closed = true;
    }
}

void PneumaticClaw::open() {
    if (closed) {
        pros::c::adi_digital_write(p, false);
        closed = false;
    }
}