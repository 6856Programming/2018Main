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

	std::cout << "DriveWithJoystick::Initialize(): Resetting Gyro" << std::endl;
	CommandBase::pDriveTrain->get_pGyroHelper()->ResetGyro();

	return;
}



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
		turnAngle *= TURN_SLOW_SPEED_RATIO;
	}


//	// ***************************************************************
//
//	this->DEBUG_ControllerTestMotors();
//	this->CheckForGyroCalibration();
//
//	// ***************************************************************



	// Reverse the direction of the steering
	turnAngle = -turnAngle;

// We tried this "throttle based" thing, but nobody liked it
//	double throttleLeft = pJoyDriver->GetTriggerAxis(frc::GenericHID::kLeftHand);
//	double throttleRight = pJoyDriver->GetTriggerAxis(frc::GenericHID::kRightHand);
//	double forwardSpeed = throttleLeft - throttleRight;


	if (fabs(forwardSpeed) <= XBOX_DEADZONE_LEFT_JOY)
	{
		forwardSpeed = 0.0;
	}

	if (fabs(turnAngle) <= XBOX_DEADZONE_LEFT_JOY)
	{
		turnAngle = 0.0;
	}

	SmartDashboard::PutNumber("Driver Forward Speed:", -forwardSpeed);
	SmartDashboard::PutNumber("Driver Turn angle:", -turnAngle);
//	SmartDashboard::PutNumber("Driver Right Trigger:", forwardSpeed);

	CommandBase::pDriveTrain->ArcadeDrive( -forwardSpeed, -turnAngle );

	// Display the encoder positions of the left and right motor
	double leftEncoder = 0.0;
	double rightEncoder = 0.0;

	::CommandBase::pDriveTrain->getEncoderPositionInTicks( leftEncoder, rightEncoder );

	::SmartDashboard::PutNumber("Left Encoder", leftEncoder);
	::SmartDashboard::PutNumber("Right Encoder", rightEncoder);


	// In case the encoders are connected to the wrong Talons...
//	DriveTrain* pDT = ::CommandBase::pDriveTrain;

//	::SmartDashboard::PutNumber( "DEBUG: LeftFront Position", pDT->DEBUG_getEncoderPositionFromMotorID(DriveTrain::LEFT_FRONT) );
//	::SmartDashboard::PutNumber( "DEBUG: RightFront Position", pDT->DEBUG_getEncoderPositionFromMotorID(DriveTrain::RIGHT_FRONT) );
//	::SmartDashboard::PutNumber( "DEBUG: LeftRear Position", pDT->DEBUG_getEncoderPositionFromMotorID(DriveTrain::LEFT_REAR) );
//	::SmartDashboard::PutNumber( "DEBUG: RightRear Position", pDT->DEBUG_getEncoderPositionFromMotorID(DriveTrain::RIGHT_REAR) );
//
//	::SmartDashboard::PutNumber( "DEBUG: LeftFront Velocity", pDT->DEBUG_getEncoderVelocityFromMotorID(DriveTrain::LEFT_FRONT) );
//	::SmartDashboard::PutNumber( "DEBUG: RightFront Velocity", pDT->DEBUG_getEncoderVelocityFromMotorID(DriveTrain::RIGHT_FRONT) );
//	::SmartDashboard::PutNumber( "DEBUG: LeftRear Velocity", pDT->DEBUG_getEncoderVelocityFromMotorID(DriveTrain::LEFT_REAR) );
//	::SmartDashboard::PutNumber( "DEBUG: RightRear Velocity", pDT->DEBUG_getEncoderVelocityFromMotorID(DriveTrain::RIGHT_REAR) );


	double currentDirection = CommandBase::pDriveTrain->get_pGyroHelper()->GetGyroAngleImmediate();
	::SmartDashboard::PutNumber("Gyro Angle", currentDirection);

	double currentDirAvg = CommandBase::pDriveTrain->get_pGyroHelper()->getGetGyroAngleAverage(1.0);
	::SmartDashboard::PutNumber("Gyro Angle (avg 1 second)", currentDirAvg);


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


int DEBUG_selectedMotorID = 0;
can::WPI_TalonSRX* DEBUG_pTalon[8] = {0};

// Added as a Q-n-D test the various motors Hail Mary pass at UWO
void DriveWithJoystick::DEBUG_ControllerTestMotors(void)
{
	frc::XboxController* pJoyDriver = CommandBase::pOI->GetJoystickDrive();

	if ( pJoyDriver->GetBButtonPressed() )
	{
		DEBUG_selectedMotorID++;
	}
	if ( pJoyDriver->GetAButtonPressed() )
	{
		DEBUG_selectedMotorID--;
	}
	if ( DEBUG_selectedMotorID > 8 )	{ DEBUG_selectedMotorID = 1; }
	if ( DEBUG_selectedMotorID < 1 )	{ DEBUG_selectedMotorID = 8; }


	// Created yet?
	if ( DEBUG_pTalon[DEBUG_selectedMotorID] == 0 )
	{
		DEBUG_pTalon[DEBUG_selectedMotorID] = new can::WPI_TalonSRX(DEBUG_selectedMotorID);
	}

	double testMotorSpeed = pJoyDriver->GetTriggerAxis(XboxController::kLeftHand) - pJoyDriver->GetTriggerAxis(XboxController::kRightHand);

	double leftTrigger = pJoyDriver->GetTriggerAxis(XboxController::kLeftHand);
	double rightTrigger = pJoyDriver->GetTriggerAxis(XboxController::kRightHand);

	::SmartDashboard::PutNumber("DEBUG Left Trigger", leftTrigger);
	::SmartDashboard::PutNumber("DEBUG Right Trigger", rightTrigger);

	// Clamp down the speed
	testMotorSpeed *= 0.5;


	::SmartDashboard::PutNumber("DEBUG Selected Motor ID", DEBUG_selectedMotorID);
	::SmartDashboard::PutNumber("DEBUG Selected Motor speed", testMotorSpeed);


	DEBUG_pTalon[DEBUG_selectedMotorID]->Set(testMotorSpeed);

	return;
}

// If the driver A, B, X, AND Y are pressed AT THE SAME TIME, the gyro calibrates
// *** WARNING: This will isolate the gyro for 5 seconds!! ***
void DriveWithJoystick::CheckForGyroCalibration(void)
{
	frc::XboxController* pJoyDriver = CommandBase::pOI->GetJoystickDrive();

	if ( pJoyDriver->GetAButton() && pJoyDriver->GetBButton() &&
	     pJoyDriver->GetXButton() && pJoyDriver->GetYButton() )
	{
		CommandBase::pDriveTrain->get_pGyroHelper()->CalibrateGyro();
	}

	return;
}

