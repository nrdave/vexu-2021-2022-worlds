#include "lib/MotorGroup.hpp"

#ifndef LIFT_HPP
#define LIFT_HPP

class Lift {
    private:
        MotorGroup motors;

        pros::controller_digital_e_t upBtn, downBtn;

        int maxUpVelo, maxDownVelo;

    public:
        Lift(std::initializer_list<int> ports, std::initializer_list<bool> revs,
           pros::controller_digital_e_t upButton, pros::controller_digital_e_t downButton,
           pros::motor_encoder_units_e_t encoderUnits,
           pros::motor_gearset_e_t gearing,
           int maxUpRPM, int maxDownRPM);

        void driver(pros::controller_id_e_t controller);

        void up();

        void down();
        
        void stop();
};

#endif // Lift.hpp