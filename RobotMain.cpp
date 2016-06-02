#include <stdio.h>
#include <WPILib/WPILib.h>
#include "hardware/Robot.h"
#include "math.h"
#include "TCPServer.h"
#include "Timer.h"
#include "VisionListener.h"

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
	VisionListener vision;
			bool useVision;
	public:
		RobotMain(): serv(8080), startTimer(), vision(8081), useVision(false) {}
		double  boundAngle0to360(double angle)
		{
		    while(angle < 0.0) angle += 360.0;
		    while(angle >= 360.0) angle -= 360.0;
				return angle;
		}

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
			robot->intake->setState(Intake::OFF);
			robot->shooter->setRate(0);
			robot->drivetrain->setState(Drivetrain::PID_ANGLE);
		}

		void AutonomousPeriodic() {
			VisionMessage frame = vision.getNewestMessage();
			//RobotStateMessage pastState = robot->history->stateAt(frame.ts);
			double turnTo = boundAngle0to360(frame.theta);
			robot->drivetrain->getTurnPID()->setSetpoint(turnTo);
		//	printf("want to go to %2.2f got %2.2f\n", turnTo, frame.theta);
		}

		void TeleopInit() {
			robot->intake->setState(Intake::WANT);
			robot->drivetrain->setState(Drivetrain::RAW);
			robot->drivetrain->set(0,0);
			robot->shooter->setRate(44);
		}

		void TeleopPeriodic() {
			printf("%2.2f || %2.4f\n", setP, robot->shooter->getRate());

			if (js->GetRawButton(2))
			{
				if ( robot->intake->getState() == Intake::HAS ) {
					robot->intake->setState(Intake::SHOOT);
				}
				else
					robot->intake->setState(Intake::WANT);
			}


			if ( js->GetRawButton(3) ) {
				robot->drivetrain->getTurnPID()->reset();
				robot->drivetrain->setState(Drivetrain::PID_ANGLE);
				useVision = true;
			}

			double throttle = js->GetRawAxis(2)/3;
			double twist = js->GetRawAxis(3)/3;

			if ( useVision ) {
				VisionMessage frame = vision.getNewestMessage();
				//RobotStateMessage pastState = robot->history->stateAt(frame.ts);
				double turnTo = boundAngle0to360(frame.theta);
				robot->drivetrain->getTurnPID()->setSetpoint(turnTo);

				if (fabs(twist) > 0.15 )
				{
					useVision = false;
					robot->drivetrain->setState(Drivetrain::RAW);
				}
			}
			else {


				robot->drivetrain->set(-(throttle-twist), throttle+twist);
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
			robot->shooter->getPID()->reset();
			robot->drivetrain->getTurnPID()->reset();
		}



		void sendStateMsg() {
			RobotStateMessage msg;
			msg.ts = startTimer.Get();
			robot->shooter->getPIDSnapshot(&msg.shooter);
			msg.intakeState = robot->intake->getState();
			msg.yaw = robot->drivetrain->getAngle();
			//robot->history->insert(&msg);
			serv.broadcast((char*)&msg, sizeof(RobotStateMessage));
		}
};

void debugServerThread(void *ptr)
{
	while ( true ) {
		((RobotMain*)ptr)->sendStateMsg();
		Wait(0.125);
	}
}

START_ROBOT_CLASS(RobotMain);
