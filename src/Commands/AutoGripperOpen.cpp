/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoGripperOpen.h"

AutoGripperOpen::AutoGripperOpen(double secondsToOpen)
{
	Requires(CommandBase::pGripper);

	this->m_secondsToOpen = secondsToOpen;

	this->m_pGripperOpenTimer = new frc::Timer();

	return;
}


// Called just before this Command runs the first time
void AutoGripperOpen::Initialize()
{
	this->m_pGripperOpenTimer->Reset();
	this->m_pGripperOpenTimer->Start();

	return;
}

// Called repeatedly when this Command is scheduled to run
void AutoGripperOpen::Execute()
{
	CommandBase::pGripper->ClawOpen();
	return;
}

// Make this return true when this Command no longer needs to run execute()
bool AutoGripperOpen::IsFinished()
{
	if ( this->m_pGripperOpenTimer->Get() < this->m_secondsToOpen )
	{
		// Still openning
		return false;
	}
	// Open enough.
	return true;
}

// Called once after isFinished returns true
void AutoGripperOpen::End()
{
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoGripperOpen::Interrupted()
{
	return;
}
