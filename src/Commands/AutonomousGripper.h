/*
 * AutonomousGripper.h
 *
 *  Created on: Mar 13, 2018
 *      Author: Robotics
 */

#ifndef SRC_COMMANDS_AUTONOMOUSGRIPPER_H_
#define SRC_COMMANDS_AUTONOMOUSGRIPPER_H_

#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"
#include "MyAutoCommand.h" //Do we need this?

/**
 *
 */

class AutonomousGripper: public CommandBase
{
public:
	void AutonomousOpenGripper(double seconds);
	void AutonomousCloseGripper(double seconds);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;


private:

	double m_secondsToRun;

	void AutonomousOpenGripper();
	void AutonomousCloseGripper();
	frc::Timer* pTimer;

};



#endif /* SRC_COMMANDS_AUTONOMOUSGRIPPER_H_ */
