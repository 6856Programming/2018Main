#include "Commands/AutonomousMast.h"
#include "../RobotMap.h"
#include <iostream>

AutonomousMast::AutonomousMast(double SecondsToRun, double SpeedAndDirection)
{
    std::cout << "[AutonomousMast] Constructed" << std::endl;

    if (CommandBase::pLiftMast != nullptr)
    {
       Requires(CommandBase::pLiftMast);
    }
    else
    {
       std::cout << "[AutonomousGripper] gripper is null!" << std::endl;
    }
    this->m_secondsToRun = SecondsToRun;
    this->m_speed = -SpeedAndDirection;

    this->pTimer = new frc::Timer();

    return;
}

AutonomousMast::AutonomousMast()
{
	this->pTimer = NULL;
		this->m_secondsToRun = 0.0;
		this->m_speed = 0.0;
		return;

	return;
}

void AutonomousMast::Initialize()
{
    std::cout << "[AutonomousMast] Initialized" << std::endl;

    this->pTimer->Reset();
    this->pTimer->Start();

    return;
}

void AutonomousMast::Execute()
{
	CommandBase::pLiftMast->DEBUG_SetMotorSpeed(m_speed);

    return;
}

bool AutonomousMast::IsFinished()
{

	double timeElapsed = this->pTimer->Get();

	{
		double timeLeft = this->m_secondsToRun - timeElapsed;

		std::cout << "AutonomousMast(): " << timeLeft << " seconds to go" << std::endl;
	}

	if ( timeElapsed > this->m_secondsToRun )
	{
		CommandBase::pLiftMast->DEBUG_SetMotorSpeed(0.0);

		return true;
	}

    return false;
}

void AutonomousMast::End()
{
    std::cout << "[AutonomousGripper] Ended." << std::endl;
    return;
}

void AutonomousMast::Interrupted()
{
    std::cout << "[AutonomousGripper] was Interrupted." << std::endl;
    return;
}
