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


// For OPERATOR joystick control:
// - trigger (button 1) = shoot out, "top" button (button 2) (lower thumb button) = intake

	frc::Joystick* pJoyOperator = ::CommandBase::pOI->GetJoystickOperator();

	if ( pJoyOperator->GetTriggerPressed() )
	{
		std::cout << "Gripper: Trigger pressed: PulseIntake(" << GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED << ")" << std::endl;
		pGripper->PulseIntake( GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED, GRIPPER_INTAKE_PULSED_RUN_TIME );
	}
	else if ( pJoyOperator->GetTopPressed() )
	{
		std::cout << "Gripper: Top pressed: PulsedIntake(" << -GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED << ")" << std::endl;
		pGripper->PulseIntake( -GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED, GRIPPER_INTAKE_PULSED_RUN_TIME );
	}

//	if ( pJoyOperator->GetTrigger() )
//	{
//		pGripper->SetIntakeSpeed( GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED );
//	}
//	else if ( pJoyOperator->GetTop() )
//	{
//		pGripper->SetIntakeSpeed( -GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED );
//	}
//	else
//	{
//		pGripper->SetIntakeSpeed(0.0);
//	}

// For OPERATOR joystick control:
// - left top (button 4) = open claw, right top (button 5) = close claw

	switch ( this->m_DecodeOperatorGripperCommand() )
	{
	case GripperControl::OPEN_GRIPPER:
//		std::cout << "GripperControl::Open() called..." << std::endl;
		CommandBase::pGripper->ClawOpen();
		break;

	case GripperControl::CLOSE_GRIPPER:
//		std::cout << "GripperControl::Close() called..." << std::endl;
		CommandBase::pGripper->ClawClose();
		break;

	case GripperControl::STOP_GRIPPER:
	default:
		CommandBase::pGripper->ClawStop();

	}// switch ( this->m_DecodeOperatorGripperCommand() )


	// +++++++ MUST CALL EVERY UPDATE ++++++
	pGripper->UpdateState();

	return;
}

GripperControl::eGripperCommand GripperControl::m_DecodeOperatorGripperCommand(void)
{
	frc::Joystick* pJoyOperator = ::CommandBase::pOI->GetJoystickOperator();

	// Open pressed and closed NOT pressed?
	if ( pJoyOperator->GetRawButton(JOYSTICK_OPEN_BUTTON_ID) &&
	     ! pJoyOperator->GetRawButton(JOYSTICK_CLOSE_BUTTON_ID) )
	{
		return GripperControl::OPEN_GRIPPER;
	}

	// Closed pressed and open NOT pressed?
	if ( pJoyOperator->GetRawButton(JOYSTICK_CLOSE_BUTTON_ID) &&
	     ! pJoyOperator->GetRawButton(JOYSTICK_OPEN_BUTTON_ID) )
	{
		return GripperControl::CLOSE_GRIPPER;
	}



	// No idea what's happening, so return stop (safest situation)
	return GripperControl::STOP_GRIPPER;
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


