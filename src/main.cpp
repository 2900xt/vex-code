#include "main.h"
#include "controller.h"
#include "drive.h"

pros::Motor lower_intake{5},
			shooter1{10},
			shooter2{13},
			shooter3{15},
			r1_drive{3},
			r2_drive{4},
			l1_drive{1},
			l2_drive{2};

pros::ADIDigitalOut pneumatics_port{1, false};
pros::c::ext_adi_ultrasonic_t distance_sensor{};

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	pros::lcd::set_text_color(lv_color_t{0, 0, 0});
	pros::lcd::set_background_color(lv_color_t{255, 255, 255});
	pros::c::adi_pin_mode(0, OUTPUT);
	distance_sensor = pros::c::adi_ultrasonic_init(7, 8);
	
	pros::lcd::set_text(0, "Initializing...");

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 * 
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 * 
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() 
{
	skillsAuton();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 * 
 * If no competition control is connected, this function will run immediately
 * following initialize().
 * 
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() 
{

	pros::lcd::set_text(0, "Running Controller Code");
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	controllerReader inputReader{master};

	while (true) {

		inputReader.update_info();

		tankDrive(inputReader);

		pros::delay(20);

		pros::lcd::print(3, "Distance: %d cm", pros::c::ext_adi_ultrasonic_get(distance_sensor));
	}
}