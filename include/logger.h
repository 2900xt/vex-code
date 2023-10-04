#pragma once

#include "main.h"

class logger
{
public:
    const static int startLine = 0;
    int cLx, cLy, cRx, cRy;

    bool intaking;

    void log_info()
    {
		pros::lcd::print(1, "Lx: %d   Ly:%d", cLx, cLy);
		pros::lcd::print(2, "Rx: %d   Ry:%d", cRx, cRy);
    }

    void update_info(pros::Controller& controller)
    {
        cRy = controller.get_analog(ANALOG_RIGHT_Y);
        cRx = controller.get_analog(ANALOG_RIGHT_X);
        cLy = controller.get_analog(ANALOG_LEFT_Y);
        cLx = controller.get_analog(ANALOG_LEFT_X);

        intaking = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    }
};