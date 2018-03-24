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


	Gripper* pGripper = ::CommandBase::pGripper;


// For DRIVER xbox controller, was A - intake in, B - intake out
//	if ( pJoyDriver->GetAButtonPressed() )
//	{
//		pGripper->PulseIntake( GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED, GRIPPER_INTAKE_PULSED_RUN_TIME );
//	}
//	else if ( pJoyDriver->GetBButtonPressed() )
//	{
//		pGripper->PulseIntake( -GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED, GRIPPER_INTAKE_PULSED_RUN_TIME );
//	}
//
//
//	frc::XboxController* pJoyDriver = CommandBase::pOI->GetJoystickDrive();
//
//	// Gripper control:
//	// Push ONCE to do FULL close
//	// (i.e. They DON'T have to hold the button to move the claw)
//
//	if ( pJoyDriver->GetBumperPressed(frc::GenericHID::kLeftHand) )
//	{
//		std::cout << "GripperControl::Open() called..." << std::endl;
//		CommandBase::pGripper->OpenCompletely();
//	}
//	else if ( pJoyDriver->GetBumperPressed(frc::GenericHID::kRightHand) )
//	{
//		std::cout << "GripperControl::Close() called..." << std::endl;
//		CommandBase::pGripper->CloseCompletely();
//	}



// For OPERATOR joystick control:
// - trigger (button 1) = shoot out, "top" button (button 2) (lower thumb button) = intake

	frc::Joystick* pJoyOperator = ::CommandBase::pOI->GetJoystickOperator();

	if ( pJoyOperator->GetTriggerPressed() )
	{
		pGripper->PulseIntake( GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED, GRIPPER_INTAKE_PULSED_RUN_TIME );
	}
	else if ( pJoyOperator->GetTopPressed() )
	{
		pGripper->PulseIntake( -GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED, GRIPPER_INTAKE_PULSED_RUN_TIME );
	}

// For OPERATOR joystick control:
// - left top (button 4) = open claw, right top (button 5) = close claw

	// Gripper control:
	// Push ONCE to do FULL close
	// (i.e. They DON'T have to hold the button to move the claw)

		if ( pJoyOperator->GetRawButtonPressed(JOYSTICK_OPEN_BUTTON_ID) )
		{
			std::cout << "GripperControl::Open() called..." << std::endl;
			CommandBase::pGripper->OpenCompletely(false);
		}
		else if ( pJoyOperator->GetRawButtonPressed(JOYSTICK_IDLE_BUTTON_ID) )
		{
			std::cout << "GripperControl::Idle()..." << std::endl;
			pGripper->Idle();
		}

/*		else if ( pJoyOperator->GetRawButtonPressed(JOYSTICK_OPEN_AND_SHOOT_BUTTON_ID) )
		{
			std::cout << "GripperControl::OpenAndShoot()..." << std::endl;
			pGripper->OpenCompletely(true);
		}
*/
		else if ( pJoyOperator->GetRawButtonPressed(JOYSTICK_CLOSE_BUTTON_ID) )
		{
			std::cout << "GripperControl::Close() called..." << std::endl;
			CommandBase::pGripper->CloseCompletely();
		}
//		else if ( pJoyOperator->GetRawButtonPressed(3) )
//		{
//			std::cout << "GripperControl::Idle() called..." << std::endl;
//			CommandBase::pGripper->Idle();
//		}


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


