/*
 * Wait.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: Robotics
 */
#include <Commands/Waiter.h>
#include "../RobotMap.h"


Waiter::Waiter()
{
	std::cout << "[MyAutoCommand] Constructed" << std::endl;

	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(&Robot::chassis);
}

// Called just before this Command runs the first time
void Waiter::Initialize()
{
	std::cout << "[MyAutoCommand] Initialized" << std::endl;
	this->timer = new frc::Timer();
	this->timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void Waiter::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool Waiter::IsFinished()
{
	return (this->timer->Get() > 5.0);
}

// Called once after isFinished returns true
void Waiter::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Waiter::Interrupted()
{

}





