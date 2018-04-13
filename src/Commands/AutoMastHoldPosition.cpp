/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoMastHoldPosition.h"
#include <WPILib.h>
#include "../CommandBase.h"

AutoMastHoldPosition::AutoMastHoldPosition(bool bEnableHold)
{
	this->m_Init();

	this->m_bEnableHold = bEnableHold;

	return;
}


void AutoMastHoldPosition::m_Init(void)
{
	Requires(CommandBase::pLiftMast);
	return;
}


// Called just before this Command runs the first time
void AutoMastHoldPosition::Initialize()
{
	if ( this->m_bEnableHold )
	{
		CommandBase::pLiftMast->EnableMastHold();
	}
	else
	{
		CommandBase::pLiftMast->DisableMastHold();
	}

	return;
}

// Called repeatedly when this Command is scheduled to run
void AutoMastHoldPosition::Execute()
{
	return;
}

// Make this return true when this Command no longer needs to run execute()
bool AutoMastHoldPosition::IsFinished()
{
	// Always returns immediately
	return true;
}

// Called once after isFinished returns true
void AutoMastHoldPosition::End()
{
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoMastHoldPosition::Interrupted()
{
	return;
}
