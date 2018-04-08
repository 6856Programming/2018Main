#include "AutoDriveEncoder.h"



AutoDriveEncoder::AutoDriveEncoder(double inchesToDrive, double speed)
{
//	std::cout << "AutoDriveEncoder..." << std::endl;
//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;
	this->m_MovementState = sMovementParamHelper(inchesToDrive, speed);
//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;

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

	return;
}

AutoDriveEncoder::AutoDriveEncoder( sMovementParamHelper moveParams )
{
//	std::cout << "AutoDriveEncoder..." << std::endl;
//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;
	this->m_MovementState = moveParams;
//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;


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
	std::cout << "Whell cir = " << CommandBase::pDriveTrain->getWheelCircumference() << std::endl;
	std::cout << "EncoderTicksPerInch: " << CommandBase::pDriveTrain->getEncoderTicksPerInch() << std::endl;
	std::cout << "EncoderTicksPerRev: " << CommandBase::pDriveTrain->getEncoderTicksPerRevolution() << std::endl;

	return;
}

void AutoDriveEncoder::Execute()
{
//	std::cout << "[AutoDriveEncoder::Execute()] called..." << std::endl;

	// Get current encoder values
	double currentDistance = CommandBase::pDriveTrain->getAverageEncoderPositionInInches();

	double speed = this->m_MovementState.CalculateSpeedAndUpdateState( currentDistance );

	double leftEncoder = 0.0;
	double rightEncoder = 0.0;

	CommandBase::pDriveTrain->getEncoderPositionInInches( leftEncoder, rightEncoder );

	std::cout
		<< "AutoDriveEncoder:Current state = " << this->m_MovementState.getCurrentStateString()
		<< ", speed calculated = " << speed
		<< ", L,R enc = " << leftEncoder << ", " << rightEncoder << std::endl;

	CommandBase::pDriveTrain->ArcadeDrive( speed, 0.0 );

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
