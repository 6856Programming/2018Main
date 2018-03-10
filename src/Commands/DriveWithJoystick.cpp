#include "DriveWithJoystick.h"
#include <math.h>
#include "../RobotMap.h"

/**
 *
 */

DriveWithJoystick::DriveWithJoystick()
{
	std::cout << "[DriveWithJoystick] Constructed" << std::endl;

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
	}
	else
	{
		std::cout << "[DriveWithJoystick] driveTrain is null!" << std::endl;
	}

	return;
}

/**
 *
 */

void DriveWithJoystick::Initialize()
{
	std::cout << "[DriveWithJoystick] Initialized" << std::endl;

	return;
}

/**
 *
 */

void DriveWithJoystick::Execute()
{
	// Right joystick Y axis = forward, backward
	// Left joystic X axis = steering
	// Right trigger = drive speed

	frc::XboxController* pJoyDriver = CommandBase::pOI->GetJoystickDrive();
//	frc::XboxController* pJoyOperator = CommandBase::pOI->GetJoystickOperator();


	//double forwardSpeed = pJoyDriver->GetY(XboxController::kRightHand);
	double turnAngle = pJoyDriver->GetX(XboxController::kLeftHand);

	// Reverse the direction of the steering
	turnAngle = -turnAngle;

	double throttleLeft = pJoyDriver->GetTriggerAxis(frc::GenericHID::kLeftHand);
	double throttleRight = pJoyDriver->GetTriggerAxis(frc::GenericHID::kRightHand);
	double forwardSpeed = throttleLeft-throttleRight;

	SmartDashboard::PutNumber("Driver Right Y axis:", forwardSpeed);
	SmartDashboard::PutNumber("Driver Left X axis:", turnAngle);
	SmartDashboard::PutNumber("Driver Right Trigger:", forwardSpeed);

	if (fabs(forwardSpeed) <= XBOX_DEADZONE_LEFT_JOY)
	{
		forwardSpeed = 0.0;
	}

	if (fabs(turnAngle) <= XBOX_DEADZONE_LEFT_JOY)
	{
		turnAngle = 0.0;
	}

	CommandBase::pDriveTrain->ArcadeDrive( forwardSpeed, turnAngle );

	return;
}

/**
 *
 */

bool DriveWithJoystick::IsFinished()
{
	return false;
}

/**
 *
 */

void DriveWithJoystick::End()
{
	return;
}

/**
 *
 */

void DriveWithJoystick::Interrupted()
{
	return;
}

