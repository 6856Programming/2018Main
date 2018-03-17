#include "Commands/AutonomousGripper.h"
#include "../RobotMap.h"
#include <iostream>

//THIS CODE IS NOT COMPLETE --- SPECIFICLY THE EXECUTE CAN NOT DIFFERENTIATE BETWEEN OPEN AND CLOSE. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Super easy to fix, I just have to make separate commands. Will only take about an hour max to fix.

void AutonomousGripper::AutonomousOpenGripper(double seconds) //This used to have speed but in ClawOpen() they just use the max speed anyways
{
	std::cout << "[AutonomousGripper] Constructed" << std::endl;

	if (CommandBase::pGripper != nullptr)
	{
		Requires(CommandBase::pGripper);
	}
	else
	{
		std::cout << "[AutonomousGripper] gripper is null!" << std::endl;
	}

	this->pTimer = new frc::Timer();

	this->m_secondsToRun = seconds;

	return;
}


void AutonomousGripper::AutonomousOpenGripper()
{
	this->m_secondsToRun = 0.0;
	return;
}

void AutonomousGripper::AutonomousCloseGripper(double seconds) //This used to have speed but in ClawOpen() they just use the max speed anyways
{
	std::cout << "[AutonomousGripper] Constructed" << std::endl;

	if (CommandBase::pGripper != nullptr)
	{
		Requires(CommandBase::pGripper);
	}
	else
	{
		std::cout << "[AutonomousGripper] gripper is null!" << std::endl;
	}

	this->pTimer = new frc::Timer();

	this->m_secondsToRun = seconds;

	return;
}

void AutonomousGripper::AutonomousCloseGripper()
{
	this->m_secondsToRun = 0.0;
	return;
}


void AutonomousGripper::Initialize()
{
	std::cout << "[AutonomousForward] Initialized" << std::endl;

	this->pTimer->Reset();
	this->pTimer->Start();

	return;
}




void AutonomousGripper::Execute()
{

//ThinkThisDoTheSameThing
//	CommandBase::pGripper->Open();

//The only thing is that in the ClawOpen() has the code right after... This is it
	/*
	if ( this->m_pClawOffTimer->Get() >= GRIPPER_CLAW_SHUT_OFF_TIME )
		{
			std::cout << "Gripper: Claw timer timeout - turning off claw" << std::endl;
			this->m_pClawOffTimer->Stop();
			CommandBase::pGripper->ClawStop();
		}
*/

}


bool AutonomousGripper::IsFinished()
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


void AutonomousGripper::End()
{
	return;
}


void AutonomousGripper::Interrupted()
{
	return;
}

