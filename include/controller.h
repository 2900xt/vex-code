#pragma once

#include "main.h"
#include "pros/misc.hpp"

void flipPneumatics();

class controllerReader
{
  
public:

    pros::Controller &controller;
    const static int startLine = 0;
    int cLx, cLy, cRx, cRy;

    bool un_intaking, pneumatics = false;
    bool intaking, extaking;

    void update_info()
    {
      cRy = controller.get_analog(ANALOG_RIGHT_Y);
      cRx = controller.get_analog(ANALOG_RIGHT_X);
      cLy = controller.get_analog(ANALOG_LEFT_Y);
      cLx = controller.get_analog(ANALOG_LEFT_X);

      intaking = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
      un_intaking = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
      extaking = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    }

    void update_pneumatics()
    {
      if(!pneumatics && controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
      {
        flipPneumatics();
      }
      pneumatics = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);
    }
};