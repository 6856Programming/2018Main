/*
 * AutonomousForward.h
 *
 *  Created on: Mar 11, 2018
 *      Author: Robotics
 */

#ifndef SRC_COMMANDS_AUTONOMOUSFORWARD_H_
#define SRC_COMMANDS_AUTONOMOUSFORWARD_H_

#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"
#include "MyAutoCommand.h"

/**
 *
 */

class AutonomousForward: public CommandBase
{
public:
	AutonomousForward(double seconds, double speed);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;


private:

	double m_secondsToRun;
	double m_speed;

	AutonomousForward();
	frc::Timer* pTimer;
//	class DriveTrain *myDrive;
//	drive = Driv(1,3)
};


#endif /* SRC_COMMANDS_AUTONOMOUSFORWARD_H_ */
