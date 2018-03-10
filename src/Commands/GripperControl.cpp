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
		std::cout << "GripperControl::CylinderRetract() called..." << std::endl;
		CommandBase::pGripper->CylinderRetract();
	}
	else if ( pJoyDriver->GetBumperPressed(frc::GenericHID::kRightHand) )
	{
		std::cout << "GripperControl::CylinderExtend() called..." << std::endl;
		CommandBase::pGripper->CylinderExtend();
	}


	if ( pJoyDriver->GetXButtonReleased() )
	{
		std::cout << "GripperControl::CompressorsOn() called..." << std::endl;
		CommandBase::pGripper->CompressorOn();
	}
	else if ( pJoyDriver->GetYButtonReleased() )
	{
		std::cout << "GripperControl::CompressorOff() called..." << std::endl;
		CommandBase::pGripper->CompressorOff();
	}



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


