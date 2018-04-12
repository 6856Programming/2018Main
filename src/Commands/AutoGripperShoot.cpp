/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoGripperShoot.h"

AutoGripperShoot::AutoGripperShoot(double secondsToRun, double speed)
{
	Requires(CommandBase::pGripper);

	this->m_secondsToRun = secondsToRun;
	this->m_speed = speed;

	return;
}

// Called just before this Command runs the first time
void AutoGripperShoot::Initialize()
{

	CommandBase::pGripper->PulseIntake( this->m_speed, this->m_secondsToRun );

	return;
}

// Called repeatedly when this Command is scheduled to run
void AutoGripperShoot::Execute()
{
	CommandBase::pGripper->UpdateState();
	return;
}

// Make this return true when this Command no longer needs to run execute()
bool AutoGripperShoot::IsFinished()
{
	if ( CommandBase::pGripper->isPulseIntakeOnRightNow() )
	{
		// Intake motors are still running
		return false;
	}

	// Intake pulse is done
	return true;
}

// Called once after isFinished returns true
void AutoGripperShoot::End()
{
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoGripperShoot::Interrupted()
{
	return;
}
