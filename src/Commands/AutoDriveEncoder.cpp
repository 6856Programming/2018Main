#include "AutoDriveEncoder.h"



AutoDriveEncoder::AutoDriveEncoder(double inchesToDrive, double speed, bool bUseGyroToDriveStraight)
{
	std::cout << "[AutoDriveEncoder()]"
		<< " distance = " << inchesToDrive
		<< ", speed = " << speed
		<< (bUseGyroToDriveStraight ? " (using gyro to assist)" : "" ) << std::endl;
//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;
	this->m_MovementState = sMovementParamHelper(inchesToDrive, speed);
//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;

	this->m_bUseGyroToDriveStraight = bUseGyroToDriveStraight;

	if ( this->m_bUseGyroToDriveStraight )
	{
		CommandBase::pDriveTrain->Gyro_Reset();
	}
/*
	std::string error = "";
	if ( ! this->m_MovementState.ValidateParameters(error) )
	{
		std::cout << "****************************************************" << std::endl;
		std::cout << "*** WARNING: AutoDriveEncoder() did NOT validate ***" << std::endl;
		std::cout << error << std::endl;
		std::cout << "****************************************************" << std::endl;
	}
	else
	{
		std::cout << "[AutoDriveEncoder] created. Values are OK." << std::endl;
	}
*/
	return;
}

AutoDriveEncoder::AutoDriveEncoder( sMovementParamHelper moveParams, bool bUseGyroToDriveStraight )
{
	std::cout << "[AutoDriveEncoder()]"
		<< " distance = " << moveParams.totalDistance
		<< ", speed = " << moveParams.maxSpeed
		<< (bUseGyroToDriveStraight ? " (using gyro to assist)" : "" ) << std::endl;

	//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;
	this->m_MovementState = moveParams;
//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;

	this->m_bUseGyroToDriveStraight = bUseGyroToDriveStraight;

	if ( this->m_bUseGyroToDriveStraight )
	{
		CommandBase::pDriveTrain->Gyro_Reset();
	}
/*
	std::string error = "";
	if ( ! this->m_MovementState.ValidateParameters(error) )
	{
		std::cout << "****************************************************" << std::endl;
		std::cout << "*** WARNING: AutoDriveEncoder() did NOT validate ***" << std::endl;
		std::cout << error << std::endl;
		std::cout << "****************************************************" << std::endl;
	}
	else
	{
		std::cout << "[AutoDriveEncoder] created. Values are OK." << std::endl;
	}
*/

	return;
}



AutoDriveEncoder::~AutoDriveEncoder()
{
	return;
}

void AutoDriveEncoder::Initialize()
{
	std::cout << "[AutoDriveEncoder::Initialize()] called" << std::endl;
	std::cout << "[AutoDriveEncoder::Initialize()] calling: Start_ChangeStateToAccelerating()" << std::endl;

	CommandBase::pDriveTrain->resetEncoder(true, true);

	this->m_MovementState.Start_ChangeStateToAccelerating();

//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;

	std::cout << "Wheel diam = " << CommandBase::pDriveTrain->getWheelDiameterInches() << std::endl;
	std::cout << "Wheel cir = " << CommandBase::pDriveTrain->getWheelCircumference() << std::endl;
	std::cout << "EncoderTicksPerInch: " << CommandBase::pDriveTrain->getEncoderTicksPerInch() << std::endl;
	std::cout << "EncoderTicksPerRev: " << CommandBase::pDriveTrain->getEncoderTicksPerRevolution() << std::endl;

	return;
}

void AutoDriveEncoder::Execute()
{
//	std::cout << "[AutoDriveEncoder::Execute()] called..." << std::endl;

	// Get current encoder values
	double currentDistance = CommandBase::pDriveTrain->getAverageEncoderPositionInInches();

	// Using the ArcadeDrive (as suggested by the FRC example), caused the robot
	//  to violently jerk right and left, so we are using TankDrive, instead
	double leftSpeed = this->m_MovementState.CalculateSpeedAndUpdateState( currentDistance );
	double rightSpeed = leftSpeed;

	{
		double leftEncoder = 0.0;
		double rightEncoder = 0.0;

		CommandBase::pDriveTrain->getEncoderPositionInInches( leftEncoder, rightEncoder );
		std::cout
			<< "AutoDriveEncoder:Current state = " << this->m_MovementState.getCurrentStateString()
			<< ", speed L:R = " << leftSpeed << ":" << rightSpeed
			<< ", L,R, avg enc = " << leftEncoder << ", " << rightEncoder << ", " << currentDistance << std::endl;
	}



	if ( this->m_bUseGyroToDriveStraight )
	{
		double angleAdjust = CommandBase::pDriveTrain->Gyro_GetAngle();

		// The angle that is returned could be very large,
		//  particularly since the max speed range is [-1.0, +1.0]
		// These two variables:
		// - Clamp the max angle to something sensible
		//   (remember that the robot is more or less straight,
		//    to the angles SHOULD be small; if not, something
		//    is very wrong with the world... gyro broken?)
		// - The speed is slightly adjusted based on this returned
		//    angle, but even small angles, like 3 degrees, are
		//    WAY larger than the maximum speed.
		//
		// NOTE: We have to invert the values if the robot
		//   overall direction is -ve vs +ve.

		const double MAX_CLAMP_ANGLE_FROM_GRYRO = 5.0;

		if ( angleAdjust > MAX_CLAMP_ANGLE_FROM_GRYRO )	{ angleAdjust = MAX_CLAMP_ANGLE_FROM_GRYRO; }
		if ( angleAdjust < -MAX_CLAMP_ANGLE_FROM_GRYRO )	{ angleAdjust = -MAX_CLAMP_ANGLE_FROM_GRYRO;}


		const double CRAPPY_ANGLE_TO_SPEED_ADJUST_RATIO = 0.1;

		angleAdjust *= CRAPPY_ANGLE_TO_SPEED_ADJUST_RATIO;

		if ( this->m_MovementState.overallDirection > 0 )
		{
			// Moving "forward"
			leftSpeed += angleAdjust;
			rightSpeed -= angleAdjust;
		}
		else if ( this->m_MovementState.overallDirection < 0 )
		{
			// Moving "backward"
			leftSpeed += angleAdjust;
			rightSpeed -= angleAdjust;
		}
		// Else: this shouldn't happen (overallDirection == 0)

	}// if ( this->m_bUseGyroToDriveStraight )

	// Using the ArcadeDrive (as suggested by the FRC example), caused the robot
	//  to violently jerk right and left, so we are using TankDrive, instead
//	CommandBase::pDriveTrain->ArcadeDrive( speed, -angleAdjust );
	CommandBase::pDriveTrain->TankDrive( leftSpeed, rightSpeed );

	return;
}

bool AutoDriveEncoder::IsFinished()
{
	if ( this->m_MovementState.IsDone() || this->m_MovementState.IsStateInvalid() )
	{
		// Either we're done or all is lost, forever lost...
		return true;
	}

	// Still have work to do, Holmes.
	return false;
}

void AutoDriveEncoder::End()
{

	return;
}
void AutoDriveEncoder::Interrupted()
{
	return;
}

// Can't call c'tor
AutoDriveEncoder::AutoDriveEncoder()
{
	return;
}
