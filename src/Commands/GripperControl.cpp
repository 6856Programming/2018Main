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

	// Gripper control:
	// Push ONCE to do FULL close
	// (i.e. They DON'T have to hold the button to move the claw)

	if ( pJoyDriver->GetBumperPressed(frc::GenericHID::kLeftHand) )
	{
		std::cout << "GripperControl::Open() called..." << std::endl;
		CommandBase::pGripper->OpenCompletely();
	}
	else if ( pJoyDriver->GetBumperPressed(frc::GenericHID::kRightHand) )
	{
		std::cout << "GripperControl::Close() called..." << std::endl;
		CommandBase::pGripper->CloseCompletely();
	}


//	NOW: A - intake in, B - intake out


	Gripper* pGripper = ::CommandBase::pGripper;

	if ( pJoyDriver->GetAButtonPressed() )
	{
		pGripper->PulseIntake( GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED, GRIPPER_INTAKE_PULSED_RUN_TIME );
	}
	else if ( pJoyDriver->GetBButtonPressed() )
	{
		pGripper->PulseIntake( -GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED, GRIPPER_INTAKE_PULSED_RUN_TIME );
	}

	// +++++++ MUST CALL EVERY UPDATE ++++++
	pGripper->UpdateState();

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


