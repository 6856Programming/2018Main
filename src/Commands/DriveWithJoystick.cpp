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
	// Rigth stick DOWN = FASTER mode

	frc::XboxController* pJoyDriver = CommandBase::pOI->GetJoystickDrive();
//	frc::XboxController* pJoyOperator = CommandBase::pOI->GetJoystickOperator();


	double forwardSpeed = pJoyDriver->GetY(XboxController::kRightHand);
	double turnAngle = pJoyDriver->GetX(XboxController::kRightHand);

	// If right joystick push button is UP, we drive SLOWLY
	// If right joystick push button is DOWN, we drive QUICKLY

	if( ! pJoyDriver->GetStickButton(XboxController::kRightHand) )
	{
		forwardSpeed *= DRIVE_SLOW_SPEED_RATIO;
	}

	// Reverse the direction of the steering
	turnAngle = -turnAngle;

// We tried this "throttle based" thing, but nobody liked it
//	double throttleLeft = pJoyDriver->GetTriggerAxis(frc::GenericHID::kLeftHand);
//	double throttleRight = pJoyDriver->GetTriggerAxis(frc::GenericHID::kRightHand);
//	double forwardSpeed = throttleLeft - throttleRight;

	SmartDashboard::PutNumber("Driver Forward Speed:", forwardSpeed);
	SmartDashboard::PutNumber("Driver Turn angle:", turnAngle);
//	SmartDashboard::PutNumber("Driver Right Trigger:", forwardSpeed);

	if (fabs(forwardSpeed) <= XBOX_DEADZONE_LEFT_JOY)
	{
		forwardSpeed = 0.0;
	}

	if (fabs(turnAngle) <= XBOX_DEADZONE_LEFT_JOY)
	{
		turnAngle = 0.0;
	}

	CommandBase::pDriveTrain->ArcadeDrive( forwardSpeed, turnAngle );

	// Display the encoder positions of the left and right motor
	double leftEncoder = 0.0;
	double rightEncoder = 0.0;

	::CommandBase::pDriveTrain->getEncoderPosition( leftEncoder, rightEncoder );

	::SmartDashboard::PutNumber("Left Encoder", leftEncoder);
	::SmartDashboard::PutNumber("Right Encoder", rightEncoder);

	// In case the encoders are connected to the wrong Talons...
	DriveTrain* pDT = ::CommandBase::pDriveTrain;

	::SmartDashboard::PutNumber( "DEBUG: LeftFront Position", pDT->DEBUG_getEncoderPositionFromMotorID(DriveTrain::LEFT_FRONT) );
	::SmartDashboard::PutNumber( "DEBUG: RightFront Position", pDT->DEBUG_getEncoderPositionFromMotorID(DriveTrain::RIGHT_FRONT) );
	::SmartDashboard::PutNumber( "DEBUG: LeftRear Position", pDT->DEBUG_getEncoderPositionFromMotorID(DriveTrain::LEFT_REAR) );
	::SmartDashboard::PutNumber( "DEBUG: RightRear Position", pDT->DEBUG_getEncoderPositionFromMotorID(DriveTrain::RIGHT_REAR) );

	::SmartDashboard::PutNumber( "DEBUG: LeftFront Velocity", pDT->DEBUG_getEncoderVelocityFromMotorID(DriveTrain::LEFT_FRONT) );
	::SmartDashboard::PutNumber( "DEBUG: RightFront Velocity", pDT->DEBUG_getEncoderVelocityFromMotorID(DriveTrain::RIGHT_FRONT) );
	::SmartDashboard::PutNumber( "DEBUG: LeftRear Velocity", pDT->DEBUG_getEncoderVelocityFromMotorID(DriveTrain::LEFT_REAR) );
	::SmartDashboard::PutNumber( "DEBUG: RightRear Velocity", pDT->DEBUG_getEncoderVelocityFromMotorID(DriveTrain::RIGHT_REAR) );

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

