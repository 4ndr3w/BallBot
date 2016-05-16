#include <stdio.h>
#include <WPILib/WPILib.h>
#include "hardware/Robot.h"

Robot* robot = NULL;

class RobotMain : public IterativeRobot {
	Joystick *js;
	public:
		RobotMain() {}

		void RobotInit() {
			js = new Joystick(1);
			robot = new Robot();
		}

		void AutonomousInit() {

		}

		void AutonomousPeriodic() {

		}

		void TeleopInit() {

		}

		void TeleopPeriodic() {
			double throttle = js->GetRawAxis(2)/3;
			double twist = js->GetRawAxis(3)/3;

			robot->drivetrain->set(-(throttle-twist), throttle+twist);

			if (js->GetRawButton(1))
				robot->shooter->setRaw(-0.5);
			else
				robot->shooter->setRaw(0);

			robot->intake->setRoller(js->GetRawButton(2));
		}
};

START_ROBOT_CLASS(RobotMain);
