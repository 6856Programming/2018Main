#ifndef _DRIVETRAIN_HG_
#define _DRIVETRAIN_HG_

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include "cGyroHelper.h"
#include "../RobotMap.h"
#include <vector>

#include <iostream>


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
	double getAverageEncoderPositionInInches(void);
	double getAverageEncoderVelocityInInches(void);

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

	void setEncoderTicksPerRevolution( double encoderTicksPerRevolution );
	double getEncoderTicksPerRevolution(void);

	double getWheelCircumference(void);
	double getEncoderTicksPerInch(void);

	void setWheelDiameterInches(double wheelDiameterInInches);
	double getWheelDiameterInches(void);

	cGyroHelper* get_pGyroHelper(void);


private:
	can::WPI_TalonSRX* pLeftFrontMotor;
	can::WPI_TalonSRX* pLeftRearMotor;
	can::WPI_TalonSRX* pRightFrontMotor;
	can::WPI_TalonSRX* pRightRearMotor;

	frc::SpeedControllerGroup* pLeftSpeedControllerGroup;
	frc::SpeedControllerGroup* pRightSpeedControllerGroup;

	frc::DifferentialDrive* pRobotDrive;

	cGyroHelper* m_pGyroHelper;


	double m_wheelDiameterInches;			// Is explicitly set
	double m_encoderTicksPerRevolution;		// Is explicitly set

	double m_DEFAULT_WHEEL_DIAMETER_INCHES = 6.0;
	// With a ticks per revolution of 1440.0, asking for 48", we really drove 70"
	double m_DEFAULT_TICKS_PER_REVOLUTION = 1440.0 * (48.0/70.0);

	bool m_bLeftEncoderReturnValueIsInverted;	// = false
	bool m_bRightEncoderReturnValueIsInverted;	// = false

};

#endif


