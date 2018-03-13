/*
 * AutonomousForward.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: Robotics
 */

#include "Commands/AutonomousForward.h"
#include "../RobotMap.h"
#include <iostream>


AutonomousForward::AutonomousForward(double seconds, double speed)
{
	std::cout << "[AutonomousForward] Constructed" << std::endl;

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
	}
	else
	{
		std::cout << "[AutonomousForward] driveTrain is null!" << std::endl;
	}

	this->pTimer = new frc::Timer();

	this->m_secondsToRun = seconds;
	this->m_speed = speed;

	return;
}

// Is private, so should never be called
AutonomousForward::AutonomousForward()
{
	this->m_secondsToRun = 0.0;
	this->m_speed = 0.0;
	return;
}



void AutonomousForward::Initialize()
{
	std::cout << "[AutonomousForward] Initialized" << std::endl;

	this->pTimer->Reset();
	this->pTimer->Start();

	return;
}




void AutonomousForward::Execute()
{
//	::SmartDashboard::PutNumber("Selected TalonID:", this->m_selectedTalonID);
//	::SmartDashboard::PutString("Y+A = Select Talon", "Right Joy for +ve, -ve power");


//	const double DRIVE_FORWARD_SPEED = 0.25;
//	const double DRIVE_FORWARD_TIME = 4.0;


	double timeElapsed = this->pTimer->Get();

	{
		double timeLeft = this->m_secondsToRun - timeElapsed;

		std::cout << "AutonomousForward(): " << timeLeft << " seconds to go" << std::endl;
	}

	if ( timeElapsed < this->m_secondsToRun )
	{
		CommandBase::pDriveTrain->ArcadeDrive( this->m_speed, 0.0 );
	}

	return;
}


bool AutonomousForward::IsFinished()
{
	return false;
}


void AutonomousForward::End()
{
	return;
}


void AutonomousForward::Interrupted()
{
	return;
}


