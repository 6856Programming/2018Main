#ifndef _DRIVETRAIN_HG_
#define _DRIVETRAIN_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include <ADXRS450_Gyro.h>
#include "../RobotMap.h"

#include <iostream>

/**
 *
 */

class DriveTrain: public frc::Subsystem
{
public:
	DriveTrain();
	~DriveTrain();
	void InitDefaultCommand() override;

	// Original basic example drive, passing joystick. Calls ArcadeDrive()
	void Drive(XboxController* joystick);
	// These are the same as the DifferentialDrive class:
	void ArcadeDrive( double xSpeed, double zRotation );
	void CurvatureDrive( double xSpeed, double zRotation, bool isQuickTurn );
	void TankDrive( double leftSpeed, double rightSpeed );

	void Reset();

	void getEncoderPositionInTicks(double &leftEncoder, double &rightEncoder);
	void getEncoderVelocityInTicks(double &leftEncoder, double &rightEncoder);
	double getAverageEncoderPositionInTicks(void);
	double getAverageEncoderVelocityInTicks(void);

	void getEncoderPositionInInches(double &leftEncoder, double &rightEncoder);
	void getEncoderVelocityInInches(double &leftEncoder, double &rightEncoder);

	void setInvertLeftEncoderReturnValue(bool bInvertLeftEncoder);
	void setInvertRightEncoderReturnValue(bool bInvertRightEncoder);

	bool IsLeftEncoderReturnValueInverted(void);
	bool IsRightEncoderReturnValueInverted(void);

	double ConvertEncoderTicksToInches(double encoderTicks);
	double ConvertInchesToEncoderTicks(double distanceInches);

	void resetEncoder(bool bLeft, bool bRight);

	enum eMotorID
	{
		LEFT_FRONT,
		LEFT_REAR,
		RIGHT_FRONT,
		RIGHT_REAR
	};


	// This is used to get the information directly from the motor
	double DEBUG_getEncoderPositionFromMotorID( eMotorID motorID );
	double DEBUG_getEncoderVelocityFromMotorID( eMotorID motorID );

	void setWheelDiameter( double wheelDiameterInches );
	double getWheelDiameter(void);
	void setEncoderTicksPerRevolution( double encoderTicksPerRevolution );
	double getEncoderTicksPerRevolution(void);

	double getWheelCircumference(void);
	double getEncoderTicksPerInch(void);

	double Gyro_GetAngle();
	double Gyro_GetRate();
	void Gyro_Reset();
	void Gyro_Calibrate();

	// You aren't really supposed to call this...
	frc::ADXRS450_Gyro* pGetGyroRawPointer(void);

	// Returns true if timer is running and time is
	bool IsGyroCalibrating(void);


private:
	can::WPI_TalonSRX* pLeftFrontMotor;
	can::WPI_TalonSRX* pLeftRearMotor;
	can::WPI_TalonSRX* pRightFrontMotor;
	can::WPI_TalonSRX* pRightRearMotor;

	frc::SpeedControllerGroup* pLeftSpeedControllerGroup;
	frc::SpeedControllerGroup* pRightSpeedControllerGroup;

	frc::DifferentialDrive* pRobotDrive;

	frc::ADXRS450_Gyro* m_pGyro;

	// This will alow a few seconds to calibrate the gyro.
	// When it's calibrating, you can't call anything on the gyro
	frc::Timer* m_pGyroCalibrationTimer;
	const double m_GYRO_CALIBRATION_COUNTDOWN_TIME = 5.0;
	bool m_bGyroIsCalibrating;	// = false

	double m_wheelDiameterInches;			// Is explicitly set
	double m_encoderTicksPerRevolution;		// Is explicitly set

	double m_DEFAULT_WHEEL_DIAMETER_INCHES = 6.0;
	double m_DEFAULT_TICKS_PER_REVOLUTION = 1440.0;

	bool m_bLeftEncoderReturnValueIsInverted;	// = false
	bool m_bRightEncoderReturnValueIsInverted;	// = false

};

#endif


