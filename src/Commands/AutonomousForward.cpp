/*
 * AutonomousForward.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: Robotics
 */

#include "Commands/AutonomousForward.h"
#include "../RobotMap.h"
#include <iostream>


AutonomousForward::AutonomousForward(double seconds, double speed, double wait)
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
	this->pTimer2 = new frc::Timer();

	this->m_secondsToRun = seconds + wait;
	this->m_secondsToWait = wait;
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

	this->pTimer2->Reset();
	this->pTimer2->Start();

	return;
}




void AutonomousForward::Execute()
{
//	::SmartDashboard::PutNumber("Selected TalonID:", this->m_selectedTalonID);
//	::SmartDashboard::PutString("Y+A = Select Talon", "Right Joy for +ve, -ve power");

	double timeElapsed = this->pTimer2->Get();

	if(timeElapsed > m_secondsToWait){
		CommandBase::pDriveTrain->ArcadeDrive( this->m_speed, 0.0 );

	}


	return;
}


bool AutonomousForward::IsFinished()
{
	double timeElapsed = this->pTimer->Get();

	{
		double timeLeft = this->m_secondsToRun - timeElapsed;

		std::cout << "AutonomousForward(): " << timeLeft << " seconds to go" << std::endl;
	}

	if ( timeElapsed > this->m_secondsToRun )
	{
		return true;
	}

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


