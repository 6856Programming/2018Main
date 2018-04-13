/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "cWaitDelay.h"

cWaitDelay::cWaitDelay(double secondsToWait)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->m_pTimer = new frc::Timer();
	this->m_secondsToWait = secondsToWait;

	return;
}

// Called just before this Command runs the first time
void cWaitDelay::Initialize()
{
	this->m_pTimer->Reset();
	this->m_pTimer->Start();
	return;
}

// Called repeatedly when this Command is scheduled to run
void cWaitDelay::Execute()
{
	return;
}

// Make this return true when this Command no longer needs to run execute()
bool cWaitDelay::IsFinished()
{
	if ( this->m_pTimer->Get() >= this->m_secondsToWait )
	{
		return true;
	}
	// keep waiting
	return false;
}

// Called once after isFinished returns true
void cWaitDelay::End()
{
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void cWaitDelay::Interrupted()
{
	return;
}


