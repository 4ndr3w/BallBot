#include <stdio.h>
#include <WPILib/WPILib.h>
#include "hardware/Robot.h"
#include "math.h"
#include "TCPServer.h"
#include "Timer.h"

extern "C" {
	uint32_t niTimestamp32(void);
};

#include "datastructure/RobotStateMessage.h"

Robot* robot = NULL;


void debugServerThread(void *ptr);


class RobotMain : public IterativeRobot {
	Joystick *js;
	double setP;
	BroadcastTCPServer serv;
	Timer startTimer;
	public:
		RobotMain(): serv(8080), startTimer() {}

		void RobotInit() {
			js = new Joystick(1);
			robot = new Robot();
			setP = 45;
			robot->shooter->setRate(45);
			startTimer.Reset();
			startTimer.Start();

			taskSpawn("DebugServer", 101, VX_FP_TASK, 2048, (FUNCPTR)debugServerThread, (int)this,0,0,0,0,0,0,0,0,0);
		}

		void AutonomousInit() {
		}

		void AutonomousPeriodic() {
			robot->shooter->setRate(45);

			if ( fabs(robot->shooter->getPID()->getError()) < 0.5 )
				robot->intake->setState(Intake::MANUAL_ROLLIN);
			else
				robot->intake->setState(Intake::OFF);

			printf("%2.4f\n", robot->shooter->getPID()->getError());
		}

		void TeleopInit() {
			robot->intake->setState(Intake::MANUAL_ROLLIN);
		}

		void TeleopPeriodic() {
			printf("%2.2f || %2.4f\n", setP, robot->shooter->getRate());

			double throttle = js->GetRawAxis(2)/3;
			double twist = js->GetRawAxis(3)/3;

			robot->drivetrain->set(-(throttle-twist), throttle+twist);

			if (js->GetRawButton(2))
			{
				robot->shooter->setRate(robot->shooter->getPID()->getSetpoint()+2.0);
				setP += 2.0;
				Wait(0.50);
			}
			else if ( js->GetRawButton(3) ) {
				robot->shooter->setRate(robot->shooter->getPID()->getSetpoint()-2.0);
				setP -= 2.0;
				Wait(0.50);
			}

/*
			if ( js->GetRawButton(1) )
			{
				if ( robot->intake->getState() == Intake::OFF )
					robot->intake->setState(Intake::WANT);
				else if ( robot->intake->getState() == Intake::HAS )
					robot->intake->setState(Intake::SHOOT);
			}*/
		}

		void DisabledPeriodic() {
			robot->shooter->getPID()->reset(0);
			robot->gyro->test();
		}



		void sendStateMsg() {
			RobotStateMessage msg;
			msg.ts = startTimer.Get();
			robot->shooter->getPIDSnapshot(&msg.shooter);
			msg.intakeState = robot->intake->getState();
			serv.broadcast((char*)&msg, sizeof(RobotStateMessage));
		}
};

void debugServerThread(void *ptr)
{
	while ( true ) {
		((RobotMain*)ptr)->sendStateMsg();
		Wait(0.25);
	}
}

START_ROBOT_CLASS(RobotMain);
