#include "LiftControl.h"

#include "../RobotMap.h"

#include <iostream>


LiftControl::LiftControl()
{
	std::cout << "[LiftControl] Constructed" << std::endl;

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pLiftMast);
	}
	else
	{
		std::cout << "[LiftControl] driveTrain is null!" << std::endl;
	}


	return;
}


void LiftControl::Initialize()
{
	std::cout << "[LiftControl] Initialized" << std::endl;


	return;
}





void LiftControl::Execute()
{
//	::SmartDashboard::PutNumber("Selected TalonID:", this->m_selectedTalonID);
//	::SmartDashboard::PutString("Y+A = Select Talon", "Right Joy for +ve, -ve power");

// **********************************
// Now the operator is using the Joystick (not the xbox controller
// **********************************
//	frc::XboxController* pJoyDriver = CommandBase::pOI->GetJoystickDrive();
//	double trigLeft = pJoyDriver->GetTriggerAxis(frc::GenericHID::kLeftHand);
//	double trigRight = pJoyDriver->GetTriggerAxis(frc::GenericHID::kRightHand);
//	double liftSpeedAndDirection = (trigRight - trigLeft) * LIFT_MAST_SPEED_RATIO;
//	CommandBase::pLiftMast->DEBUG_SetMotorSpeed(liftSpeedAndDirection);
// **********************************

	frc::Joystick* pJoyOperator = CommandBase::pOI->GetJoystickOperator();

	double liftSpeedAndDirection = pJoyOperator->GetY();		// is "right" hand, even though there is only 1 joystick

	liftSpeedAndDirection *= -1;

	if ( fabs(liftSpeedAndDirection) < JOYSTICK_DEADZONE )
	{
		liftSpeedAndDirection = 0.0;
	}

	::SmartDashboard::PutNumber("LiftControl LiftSpeed:", liftSpeedAndDirection);

	::CommandBase::pLiftMast->DEBUG_SetMotorSpeed(liftSpeedAndDirection);


	// Show limit switch state
//	::SmartDashboard::PutString("Upper Limit Switch",
//	                            ::CommandBase::pLiftMast->getUpperLimitSwitchStatus() ? "OPEN" : "CLOSED" );
	::SmartDashboard::PutString("Upper Limit Switch is:",
	                            ::CommandBase::pLiftMast->isUpperLimitSwitchClosed() ? "CLOSED" : "OPEN" );

	return;
}


bool LiftControl::IsFinished()
{
	return false;
}


void LiftControl::End()
{
	return;
}


void LiftControl::Interrupted()
{
	return;
}


