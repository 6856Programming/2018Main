#include "DriveTrain.h"
#include "../Commands/DriveWithJoystick.h"
#include "../Commands/DebugTalonSRXTester.h"
#include <iostream>
#include <math.h>

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain")
{
	std::cout << "[DriveTrain] Constructed" << std::endl;

	this->pLeftFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_FRONT_MOTOR_ID);
	this->pLeftRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_LEFT_REAR_MOTOR_ID);
	this->pLeftSpeedControllerGroup
	                = new frc::SpeedControllerGroup( *(this->pLeftFrontMotor),
			                                         *(this->pLeftRearMotor) );

	this->pLeftSpeedControllerGroup->SetInverted(true);

	//this->pLeftFrontMotor->SetInverted(true);
	this->pRightFrontMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_FRONT_MOTOR_ID);
	this->pRightRearMotor = new can::WPI_TalonSRX(DRIVETRAIN_RIGHT_REAR_MOTOR_ID);
	this->pRightSpeedControllerGroup
	                = new frc::SpeedControllerGroup( *(this->pRightFrontMotor),
                                                     *(this->pRightRearMotor) );

	this->pRightSpeedControllerGroup->SetInverted(true);


	this->pRobotDrive
	                = new frc::DifferentialDrive( *(this->pLeftSpeedControllerGroup),
                                                  *(this->pRightSpeedControllerGroup) );

	pRobotDrive->SetSafetyEnabled(false);

	this->m_wheelDiameterInches = this->m_DEFAULT_WHEEL_DIAMETER_INCHES;
	this->m_encoderTicksPerRevolution = this->m_DEFAULT_TICKS_PER_REVOLUTION;


	this->m_pGyro = new frc::ADXRS450_Gyro();

	this->m_pGyro->Reset();

	this->m_pGyroCalibrationTimer = new frc::Timer();
	this->m_pGyroCalibrationTimer->Reset();

	this->m_bGyroIsCalibrating = false;


	return;
}


/**
 *
 */

DriveTrain::~DriveTrain()
{
	delete this->pRobotDrive;
	delete this->pRightSpeedControllerGroup;
	delete this->pLeftSpeedControllerGroup;
	delete this->pRightFrontMotor;
	delete this->pRightRearMotor;
	delete this->pLeftFrontMotor;
	delete this->pLeftRearMotor;

	return;
}

/**
 *
 */

void DriveTrain::InitDefaultCommand()
{
	std::cout << "[DriveTrain] Initialized Default Command" << std::endl;

	SetDefaultCommand(new DriveWithJoystick());

	//SetDefaultCommand(new DebugTalonSRXTester());

	return;
}

/**
 *
 */

// Put methods for controlling this subsystem here.
// Call these from Commands.

//Madi - We only use the first one... ArcadeDrive(forwardSpeed, turnAngle) !!!

void DriveTrain::Drive(XboxController* pJoystick) //This needs to use the driver joystick
{
	double forwardSpeed = pJoystick->GetY(XboxController::kLeftHand);
	double turnAngle = pJoystick->GetX(XboxController::kLeftHand);

	this->pRobotDrive->ArcadeDrive(forwardSpeed, turnAngle);

	return;
}

void DriveTrain::ArcadeDrive( double xSpeed, double zRotation )
{
	// Taken from DriveTrain::Drive()
	::SmartDashboard::PutNumber("ArcadeDrive():speed", xSpeed);
	this->pRobotDrive->ArcadeDrive(xSpeed, -zRotation);

	return;
}

void DriveTrain::CurvatureDrive( double xSpeed, double zRotation, bool isQuickTurn )
{
	this->pRobotDrive->CurvatureDrive( xSpeed, zRotation, isQuickTurn );

	return;
}

void DriveTrain::TankDrive( double leftSpeed, double rightSpeed )
{
	this->pRobotDrive->TankDrive( leftSpeed, rightSpeed );

	return;
}


void DriveTrain::Reset()
{
	std::cout << "[DriveTrain] Resetting the motors" << std::endl;

	this->pLeftFrontMotor->Set(ControlMode::PercentOutput, 0.0);
	this->pLeftRearMotor->Set(ControlMode::PercentOutput, 0.0);
	this->pRightFrontMotor->Set(ControlMode::PercentOutput, 0.0);
	this->pRightRearMotor->Set(ControlMode::PercentOutput, 0.0);

	return;
}

void DriveTrain::getEncoderPositionInTicks(double &leftEncoder, double &rightEncoder)
{
	leftEncoder = this->pLeftFrontMotor->GetSelectedSensorPosition(0);
	rightEncoder = this->pRightFrontMotor->GetSelectedSensorPosition(0);

	// Inverted?
	leftEncoder = ( this->m_bLeftEncoderReturnValueIsInverted ? -leftEncoder : leftEncoder );
	rightEncoder = ( this->m_bRightEncoderReturnValueIsInverted ? -rightEncoder : rightEncoder );

	return;
}

void DriveTrain::getEncoderVelocityInTicks(double &leftEncoder, double &rightEncoder)
{
	leftEncoder = this->pLeftFrontMotor->GetSelectedSensorVelocity(0);
	rightEncoder = this->pRightFrontMotor->GetSelectedSensorVelocity(0);

	// Inverted?
	leftEncoder = ( this->m_bLeftEncoderReturnValueIsInverted ? -leftEncoder : leftEncoder );
	rightEncoder = ( this->m_bRightEncoderReturnValueIsInverted ? -rightEncoder : rightEncoder );

	return;
}

double DriveTrain::getAverageEncoderPositionInTicks(void)
{
	double leftEncoder = 0.0;
	double rightEncoder = 0.0;

	this->getEncoderPositionInTicks( leftEncoder, rightEncoder );

	return ( leftEncoder + rightEncoder ) / 2.0;
}

double DriveTrain::getAverageEncoderVelocityInTicks(void)
{
	double leftEncoder = 0.0;
	double rightEncoder = 0.0;

	this->getEncoderVelocityInTicks( leftEncoder, rightEncoder );

	return ( leftEncoder + rightEncoder ) / 2.0;
}


void DriveTrain::resetEncoder(bool bLeft, bool bRight)
{
	const int PID_LOOP_INDEX = 0;
	const int TIMEOUT_MS = 10;
	if (bLeft)
	{
		this->pLeftFrontMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMEOUT_MS);
	}
	if (bRight)
	{
		this->pRightFrontMotor->SetSelectedSensorPosition(0, PID_LOOP_INDEX, TIMEOUT_MS);
	}
	return;
}

void DriveTrain::setInvertLeftEncoderReturnValue(bool bInvertLeftEncoder)
{
	this->m_bLeftEncoderReturnValueIsInverted = bInvertLeftEncoder;
	return;
}

void DriveTrain::setInvertRightEncoderReturnValue(bool bInvertRightEncoder)
{
	this->m_bRightEncoderReturnValueIsInverted = bInvertRightEncoder;
	return;
}

bool DriveTrain::IsLeftEncoderReturnValueInverted(void)
{
	return this->m_bLeftEncoderReturnValueIsInverted;
}

bool DriveTrain::IsRightEncoderReturnValueInverted(void)
{
	return this->m_bRightEncoderReturnValueIsInverted;
}



enum eMotorID
{
	LEFT_FRONT,
	LEFT_REAR,
	RIGHT_FRONT,
	RIGHT_REAR
};
// This is used to get the information directly from the motor
double DriveTrain::DEBUG_getEncoderPositionFromMotorID( eMotorID motorID )
{
	switch ( motorID )
	{
	case DriveTrain::LEFT_FRONT:
		return this->pLeftFrontMotor->GetSelectedSensorPosition(0);
		break;
	case DriveTrain::LEFT_REAR:
		return this->pLeftRearMotor->GetSelectedSensorPosition(0);
		break;
	case DriveTrain::RIGHT_FRONT:
		return this->pRightFrontMotor->GetSelectedSensorPosition(0);
		break;
	case DriveTrain::RIGHT_REAR:
		return this->pRightRearMotor->GetSelectedSensorPosition(0);
		break;
	}

	return 0.0;
}

double DriveTrain::DEBUG_getEncoderVelocityFromMotorID( eMotorID motorID )
{
	switch ( motorID )
	{
	case DriveTrain::LEFT_FRONT:
		return this->pLeftFrontMotor->GetSelectedSensorVelocity(0);
		break;
	case DriveTrain::LEFT_REAR:
		return this->pLeftRearMotor->GetSelectedSensorVelocity(0);
		break;
	case DriveTrain::RIGHT_FRONT:
		return this->pRightFrontMotor->GetSelectedSensorVelocity(0);
		break;
	case DriveTrain::RIGHT_REAR:
		return this->pRightRearMotor->GetSelectedSensorVelocity(0);
		break;
	}

	return 0.0;
}


void DriveTrain::setWheelDiameter( double wheelDiameterInches )
{
	this->m_wheelDiameterInches = wheelDiameterInches;
	return;
}

double DriveTrain::getWheelDiameter(void)
{
	return this->m_wheelDiameterInches;
}

void DriveTrain::setEncoderTicksPerRevolution( double encoderTicksPerRevolution )
{
	this->m_encoderTicksPerRevolution = encoderTicksPerRevolution;
	return;
}

double DriveTrain::getEncoderTicksPerRevolution(void)
{
	return this->m_encoderTicksPerRevolution;
}

double DriveTrain::getWheelCircumference(void)
{
	return M_PI * this->m_wheelDiameterInches;
}

double DriveTrain::ConvertEncoderTicksToInches(double encoderTicks)
{
	return ( this->m_encoderTicksPerRevolution / this->getWheelCircumference() ) * encoderTicks;
}

double DriveTrain::ConvertInchesToEncoderTicks(double distanceInches)
{
	return ( distanceInches / this->getWheelCircumference() ) * this->m_encoderTicksPerRevolution;
}

void DriveTrain::getEncoderPositionInInches(double &leftEncoder, double &rightEncoder)
{
	// Get the number of ticks...
	this->getEncoderPositionInTicks( leftEncoder, rightEncoder );

	// ...convert to inches
	leftEncoder = this->ConvertEncoderTicksToInches(leftEncoder);
	rightEncoder = this->ConvertEncoderTicksToInches(rightEncoder);


	return;
}


void DriveTrain::getEncoderVelocityInInches(double &leftEncoder, double &rightEncoder)
{
	// Get the number of ticks...
	this->getEncoderVelocityInTicks( leftEncoder, rightEncoder );

	// ...convert to inches
	leftEncoder = this->ConvertEncoderTicksToInches( leftEncoder );
	rightEncoder = this->ConvertEncoderTicksToInches( rightEncoder );

	return;
}

double DriveTrain::Gyro_GetAngle()
{
	if ( this->IsGyroCalibrating() )
	{
		return 0.0;
	}

	return this->m_pGyro->GetAngle();
}

double DriveTrain::Gyro_GetRate()
{
	if ( this->IsGyroCalibrating() )
	{
		return 0.0;
	}
	return this->m_pGyro->GetRate();
}

void DriveTrain::Gyro_Reset()
{
	if ( this->IsGyroCalibrating() )
	{
		return;
	}

	this->m_pGyro->Reset();

	return;
}

void DriveTrain::Gyro_Calibrate()
{
	// Starts a timer for x seconds to allow the gyro to calibrate
	this->m_pGyroCalibrationTimer->Reset();
	this->m_pGyroCalibrationTimer->Start();
	this->m_bGyroIsCalibrating = true;

	std::cout << "*********************************************************" << std::endl;
	std::cout << "    BEGIN GYRO CALIBRATION. Don't move robot, please.    " << std::endl;
	std::cout << "(calibration will take " << this->m_GYRO_CALIBRATION_COUNTDOWN_TIME << " seconds)" << std::endl;
	std::cout << "*********************************************************" << std::endl;


	this->m_pGyro->Calibrate();
	return;
}

// Returns true if timer is running and time is
bool DriveTrain::IsGyroCalibrating(void)
{
	if ( this->m_bGyroIsCalibrating )
	{
		// Done?
		if ( this->m_pGyroCalibrationTimer->Get() >= this->m_GYRO_CALIBRATION_COUNTDOWN_TIME )
		{
			std::cout << "**********************************" << std::endl;
			std::cout << "    GYRO CALIBRATION COMPLETE.    " << std::endl;
			std::cout << "**********************************" << std::endl;

			this->m_bGyroIsCalibrating = false;
		}
	}

	return this->m_bGyroIsCalibrating;
}


// You aren't really supposed to call this...
frc::ADXRS450_Gyro* DriveTrain::pGetGyroRawPointer(void)
{
	return this->m_pGyro;
}


















