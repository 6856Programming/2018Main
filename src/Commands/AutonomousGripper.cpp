#include "Commands/AutonomousGripper.h"
#include "../RobotMap.h"
#include <iostream>

AutonomousGripper::AutonomousGripper(eGripperState openOrClose) //'o' = open or 'c' = closed
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
    this->m_openOrClose = openOrClose;

    return;
}

AutonomousGripper::AutonomousGripper()
{
    this->m_openOrClose = AutonomousGripper::GRIPPER_ERROR_OR_UNKNOWN;	// 'e'; //e for error
    //We shouldn't leave this blank just incase of that 1-in-a-million chance it declares as 'o' or 'p'

    return;
}

void AutonomousGripper::Initialize()
{
    std::cout << "[AutonomousForward] Initialized" << std::endl;

    return;
}

void AutonomousGripper::Execute()
{

//   if (this->m_openOrClose == 'o')
//   {
//      std::cout << "[AutonomousForward] Opening Grippers" << std::endl;
//      CommandBase::pGripper->OpenCompletely(false);
//   }
//   else if (this->m_openOrClose == 'c')
//   {
//      std::cout << "[AutonomousForward] Closing Grippers" << std::endl;
//      CommandBase::pGripper->CloseCompletely();
//    }

	return;
}

bool AutonomousGripper::IsFinished()
{
	if ( this->m_openOrClose == AutonomousGripper::GRIPPER_OPEN )
	{
       return true;
    }
    else if (this->m_openOrClose == AutonomousGripper::GRIPPER_CLOSED)
    {
       return true;
    }
    else
    {
    	this->m_openOrClose = AutonomousGripper::GRIPPER_ERROR_OR_UNKNOWN;
       std::cout << "[AutonomouseGripper] Failed to construct properly. Pass through 'o' or 'c'." << std::endl;
       return true;
    }
    return false;
}

void AutonomousGripper::End()
{
    std::cout << "[AutonomousGripper] Ended." << std::endl;
    return;
}

void AutonomousGripper::Interrupted()
{
    std::cout << "[AutonomousGripper] was Interrupted." << std::endl;
    return;
}
