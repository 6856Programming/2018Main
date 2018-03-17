#include "GripperControl.h"


#include "../RobotMap.h"

#include <iostream>


GripperControl::GripperControl()
{
	std::cout << "[GripperControl] Constructed" << std::endl;

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pGripper);
	}
	else
	{
		std::cout << "[GripperControl] driveTrain is null!" << std::endl;
	}


	return;
}


void GripperControl::Initialize()
{
	std::cout << "[GripperControl] Initialized" << std::endl;


	return;
}





void GripperControl::Execute()
{
//	::SmartDashboard::PutNumber("Selected TalonID:", this->m_selectedTalonID);
//	::SmartDashboard::PutString("Y+A = Select Talon", "Right Joy for +ve, -ve power");

	frc::XboxController* pJoyDriver = CommandBase::pOI->GetJoystickDrive();

	if ( pJoyDriver->GetBumperPressed(frc::GenericHID::kLeftHand) )
	{
		std::cout << "GripperControl::Open() called..." << std::endl;
		CommandBase::pGripper->Open();
	}
	else if ( pJoyDriver->GetBumperPressed(frc::GenericHID::kRightHand) )
	{
		std::cout << "GripperControl::Close() called..." << std::endl;
		CommandBase::pGripper->Close();
	}


//	NOW: A - intake in
//	     B - intake out

	// Gripper control:
	// Push ONCE to do FULL close
	// (i.e. They DON'T have to hold the button to move the claw)


	Gripper* pGripper = ::CommandBase::pGripper;

	::SmartDashboard::PutBoolean( "Gripper Open Limit", pGripper->getGripperOpenLimitSwitchStatus() );
	::SmartDashboard::PutBoolean( "Gripper Closed Limit", pGripper->getGripperClosedLimitSwitchStatus() );

	return;
}


bool GripperControl::IsFinished()
{
	return false;
}


void GripperControl::End()
{
	return;
}


void GripperControl::Interrupted()
{
	return;
}

