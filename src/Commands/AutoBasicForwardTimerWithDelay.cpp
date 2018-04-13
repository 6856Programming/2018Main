/*
 * AutonomousForward.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: Robotics
 */

#include "Commands/AutoBasicForwardTimerWithDelay.h"
#include "../RobotMap.h"
#include <iostream>


AutoBasicForwardTimerWithDelay::AutoBasicForwardTimerWithDelay( double secondsToWaitToStart, double speed, double secondsToRun )
{
	std::cout << "[AutoBasicForwardTimerWithDelay] Constructed" << std::endl;
	std::cout << "\t secondsToWaitToStart = " << secondsToWaitToStart << std::endl;
	std::cout << "\t speed = " << speed << std::endl;
	std::cout << "\t secondsToRun = " << secondsToRun << std::endl;

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
	}
	else
	{
		std::cout << "[AutoBasicForwardTimerWithDelay] driveTrain is null!" << std::endl;
	}

	this->m_pTimerWaitToStart = new frc::Timer();
	this->m_pTimerDrive = new frc::Timer();

	this->m_secondsToRun = secondsToRun;
	this->m_secondsToWaitToStart = secondsToWaitToStart;
	this->m_speed = speed;

	this->m_currentState = AutoBasicForwardTimerWithDelay::COMMAND_NOT_STARTED;

	return;
}

AutoBasicForwardTimerWithDelay::~AutoBasicForwardTimerWithDelay()
{
	delete this->m_pTimerWaitToStart;
	delete this->m_pTimerDrive;
	return;
}

// Is private, so should never be called
AutoBasicForwardTimerWithDelay::AutoBasicForwardTimerWithDelay()
{
	//**** IS NEVER CALLED ****
	this->m_secondsToRun = 0.0;
	this->m_speed = 0.0;
	this->m_secondsToWaitToStart = 0.0;
	this->m_currentState = AutoBasicForwardTimerWithDelay::UNKNOWN;
	return;
}



void AutoBasicForwardTimerWithDelay::Initialize()
{
	std::cout << "[AutoBasicForwardTimerWithDelay] Initialized" << std::endl;

	// Start the "wait to start" (delay) timer

	this->m_pTimerWaitToStart->Reset();
	this->m_pTimerWaitToStart->Start();

	this->m_pTimerDrive->Reset();

	this->m_currentState = IS_WAITING_TO_START_DRIVING;

	// Set the drive to zero (0.0) speed
	CommandBase::pDriveTrain->ArcadeDrive( 0.0, 0.0 );

	return;
}




void AutoBasicForwardTimerWithDelay::Execute()
{
	::SmartDashboard::PutString( "AutoBasicForwardTimerWithDelayState", this->GetCurrentStateString() )
;
	switch ( this->m_currentState )
	{
	case COMMAND_NOT_STARTED:
		break;
	case IS_WAITING_TO_START_DRIVING:

		CommandBase::pDriveTrain->ArcadeDrive( 0.0, 0.0 );

		// Done waiting to start?
//		::SmartDashboard::PutNumber( "Auto: Wait to start timer", this->m_pTimerWaitToStart->Get() );

		if ( this->m_pTimerWaitToStart->Get() >= this->m_secondsToWaitToStart )
		{
			// Yes, so start the driving timer
			this->m_pTimerDrive->Reset();
			this->m_pTimerDrive->Start();

			std::cout << "Switching state to: IS_DRIVING" << std::endl;
			this->m_currentState = IS_DRIVING;
		}
		break;
	case IS_DRIVING:

		//std::cout << "Drive speed = " << this->m_speed << std::endl;
		CommandBase::pDriveTrain->ArcadeDrive( this->m_speed, 0.0 );

		// Done driving?
//		::SmartDashboard::PutNumber( "Auto: driving time timer", this->m_pTimerDrive->Get() );

		if ( this->m_pTimerDrive->Get() >= this->m_secondsToRun )
		{
			// All done
			this->m_currentState = IS_DONE;

			std::cout << "Switching state to: IS_DONE" << std::endl;

			CommandBase::pDriveTrain->ArcadeDrive(0.0, 0.0);
		}
		break;
	case IS_DONE:

		CommandBase::pDriveTrain->ArcadeDrive(0.0, 0.0);

		break;
	case UNKNOWN:
		break;
	}// switch ( this->m_currentState )


	return;
}


bool AutoBasicForwardTimerWithDelay::IsFinished()
{
	if ( this->m_currentState == IS_DONE )
	{
		return true;
	}

	return false;
}


void AutoBasicForwardTimerWithDelay::End()
{
	return;
}


void AutoBasicForwardTimerWithDelay::Interrupted()
{
	return;
}

std::string AutoBasicForwardTimerWithDelay::GetCurrentStateString(void)
{
	switch ( this->m_currentState )
	{
	case COMMAND_NOT_STARTED:	// c'tor called, but Initialize() not called, yet
		return "COMMAND_NOT_STARTED";
		break;
	case IS_WAITING_TO_START_DRIVING:
		return "IS_WAITING_TO_START_DRIVING";
		break;
	case IS_DRIVING:
		return "IS_DRIVING";
		break;
	case IS_DONE:
		return "IS_DONE";
		break;
	case UNKNOWN:					// WTF? (should never happen)
		return "UNKNOWN";
		break;
	}

	return "UNKNOWN";
}


