#include "controller.h"
#include "main.h"

extern pros::Motor lower_intake,
			shooter1,
			shooter2,
			shooter3,
			r1_drive,
			r2_drive,
			l1_drive,
			l2_drive;


extern pros::ADIDigitalOut pneumatics_port;

//Speed in tiles per second, turnspeed in deg per second
constexpr double speed = 2.0, turnSpeed = 570.0 / 2, dt = 0.02;

void driveFor(double tiles)
{
	if(tiles > 0)
	{
		r1_drive = 127 * 2.0 / 3.0;
		r2_drive = 127 * 2.0 / 3.0;
		l1_drive = -127 * 2.0 / 3.0;
		l2_drive = -127 * 2.0 / 3.0;

		while(tiles > 0)
		{
			tiles -= speed  * dt;
			pros::delay((uint32_t)(dt * 1000));
		}

		r2_drive = 0;
		l1_drive = 0;
		r1_drive = 0;
		l2_drive = 0;
	}

	if(tiles < 0)
	{
		r1_drive = -127*2.0 / 3.0;
		r2_drive = -127*2.0 / 3.0;
		l1_drive = 127*2.0 / 3.0;
		l2_drive = 127*2.0 / 3.0;

		while(tiles < 0)
		{
			tiles += speed  * dt;
			pros::delay((uint32_t)(dt * 1000));
		}

		r2_drive = 0;
		l1_drive = 0;
		r1_drive = 0;
		l2_drive = 0;
	}
}



void turnFor(double degrees)
{
	if(degrees > 0)
	{
		r1_drive = 127 *0.5;
		r2_drive = 127 *0.5;
		l1_drive = 127 *0.5;
		l2_drive = 127 *0.5;
		
		while(degrees > 0)
		{
			degrees -= turnSpeed  * dt;
			pros::delay((uint32_t)(dt * 1000));
		}

		r2_drive = 0;
		l1_drive = 0;
		r1_drive = 0;
		l2_drive = 0;
	}

	if(degrees < 0)
	{
		r1_drive = -127 *0.5;
		r2_drive = -127 *0.5;
		l1_drive = -127 *0.5;
		l2_drive = -127 *0.5;

		while(degrees < 0)
		{
			degrees += turnSpeed * dt;
			pros::delay((uint32_t)(dt * 1000));
		}

		r2_drive = 0;
		l1_drive = 0;
		r1_drive = 0;
		l2_drive = 0;
	}
}

void resetCata()
{
	shooter1 = -127;
	shooter2 = 127;
	shooter3 = -127;
	pros::delay(500);
	shooter1 = 0;
	shooter2 = 0;
	shooter3 = 0;
}

void runCata(uint32_t ms)
{
	shooter1 = -127*0.5;
	shooter2 =  127*0.5;
	shooter3 = -127*0.5;
	pros::delay(ms);
	shooter1 = 0;
	shooter2 = 0;
	shooter3 = 0;
}

bool pneumaticsState = false;
void flipPneumatics()
{
	pneumaticsState = !pneumaticsState;
	pneumatics_port.set_value(pneumaticsState);
}


void tankDrive(controllerReader &data)
{
	/* set the drive motor speeds */
	r1_drive = data.cRy;
	r2_drive = data.cRy;
	l1_drive = -data.cLy;
	l2_drive = -data.cLy;
	/* Adjust the speeds and the direction of the intake motors */
	
	if(data.intaking)
	{
		lower_intake = 127;
	}
	else if(data.un_intaking)
	{
		lower_intake = -127;
	}
	else 
	{
		lower_intake = 0;
	}

	if(data.extaking)
	{
		shooter1 = -127*0.5;
		shooter2 =  127*0.5;
		shooter3 = -127*0.5;
	}
	else 
	{
		shooter1 = 0;
		shooter2 = 0;
		shooter3 = 0;
	}
}

void skillsAuton()
{
	pros::lcd::set_text(0, "Running Autonomous Code");

	resetCata();

	pros::lcd::set_text(1, "Matchloading...");
	//Matchload for 35s
	//runCata(30000);

	pros::lcd::set_text(1, "Going under the bar");
	//Turn and cross under the center bar
	turnFor(-245);
	pros::delay(350);
	driveFor(3.5);
	pros::delay(350);


	pros::lcd::set_text(1, "pushing balls in from the right side");
	//turn and push the balls in from the right side
	turnFor(90);
	pros::delay(350);
	driveFor(0.5);
	pros::delay(350);
	turnFor(90);
	pros::delay(350);
	driveFor(2.75);
	pros::delay(350);
	driveFor(-0.8);

	//now, turn around and go back to the center vertically
	pros::lcd::set_text(1, "going to top");
	turnFor(95);
	pros::delay(350);
	driveFor(2.5);
	pros::delay(350);

	//go to the center in front of the goal
	pros::lcd::set_text(1, "going to center");
	turnFor(-135);
	pros::delay(350);
	//driveFor(0.9);
	pros::delay(350);
	//turnFor(-70);

	//push balls in with wings
	flipPneumatics();
	pros::delay(350);
	driveFor(4);
	pros::delay(350);
	flipPneumatics();
}