/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoMastLiftToTopLimit.h"
#include "../CommandBase.h"


AutoMastLiftToTopLimit::AutoMastLiftToTopLimit(double speed)
{
	this->m_WatchDogTimerTimeOut = this->m_DEFAULT_WATCH_DOG_TIME_OUT;

	this->m_Speed = speed;

	this->m_Init();

	return;
}

AutoMastLiftToTopLimit::AutoMastLiftToTopLimit(double speed, double watchDogTimeOutInSeconds)
{
	this->m_WatchDogTimerTimeOut = watchDogTimeOutInSeconds;

	this->m_Speed = speed;

	this->m_Init();

	return;
}


void AutoMastLiftToTopLimit::m_Init(void)
{
	Requires(CommandBase::pLiftMast);

	this->m_pWatchDogTimer = new frc::Timer();

	// Check that the speed is limited to 1
	if ( this->m_Speed > 1.0 )	{ this->m_Speed = 1.0; }
	if ( this->m_Speed < -1.0 ) { this->m_Speed = 1.0; }

	return;
}


// Called just before this Command runs the first time
void AutoMastLiftToTopLimit::Initialize()
{
	this->m_pWatchDogTimer->Reset();
	this->m_pWatchDogTimer->Start();

	// Start lifting the mast
	CommandBase::pLiftMast->DEBUG_SetMotorSpeed( this->m_Speed );

	return;
}

// Called repeatedly when this Command is scheduled to run
void AutoMastLiftToTopLimit::Execute()
{
	// Start lifting the mast
	CommandBase::pLiftMast->DEBUG_SetMotorSpeed( this->m_Speed );

	return;
}

// Make this return true when this Command no longer needs to run execute()
bool AutoMastLiftToTopLimit::IsFinished()
{
	// Watch dog?
	if ( this->m_pWatchDogTimer->Get() >= this->m_WatchDogTimerTimeOut )
	{
		std::cout << "WARNING: AutoMastLiftToTopLimit() Watch Dog timer timed out in " << this->m_WatchDogTimerTimeOut << " seconds." << std::endl;
	}

	// Top limit switch hit?
	if ( CommandBase::pLiftMast->isUpperLimitSwitchClosed() )
	{
		// We're done
		CommandBase::pLiftMast->EnableMastHold();

		std::cout << "AutoMastLiftToTopLimit() complete." << std::endl;
		return true;
	}

	return false;
}

// Called once after isFinished returns true
void AutoMastLiftToTopLimit::End()
{
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoMastLiftToTopLimit::Interrupted()
{
	return;
}
