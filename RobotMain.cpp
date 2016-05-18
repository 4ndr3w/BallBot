#include <stdio.h>
#include <WPILib/WPILib.h>
#include "hardware/Robot.h"

#include "TCPServer.h"

Robot* robot = NULL;

class TestServer : public TCPServer {
public:
	TestServer() : TCPServer(8080)
	{

	}

	void handleClient(int client) {
		char* hello = "hello world!";

		send(client, hello, strlen(hello), 0);
		close(client);
	}
};


class RobotMain : public IterativeRobot {
	Joystick *js;
	public:
		RobotMain() {}

		void RobotInit() {
			js = new Joystick(1);
			robot = new Robot();
			new TestServer();
		}

		void AutonomousInit() {
		}

		void AutonomousPeriodic() {
			robot->shooter->setRate(43);
			printf("%2.4f\n", robot->shooter->getPID()->getError());
		}

		void TeleopInit() {
		}

		void TeleopPeriodic() {
			printf("%2.4f\n", robot->shooter->getRate());
			/*
			double throttle = js->GetRawAxis(2);
			double twist = js->GetRawAxis(3);

			robot->drivetrain->set(-(throttle-twist), throttle+twist);

			if (js->GetRawButton(1))
				robot->shooter->setRaw(-1.0);
			else
				robot->shooter->setRaw(0);

			if ( js->GetRawButton(2) )
			{
				if ( robot->intake->getState() == Intake::OFF )
					robot->intake->setState(Intake::WANT);
				else if ( robot->intake->getState() == Intake::HAS )
					robot->intake->setState(Intake::SHOOT);
			}*/
			robot->shooter->setRaw(-0.7);
		}

		void DisabledPeriodic() {
			robot->shooter->getPID()->reset(0);
		}
};

START_ROBOT_CLASS(RobotMain);
