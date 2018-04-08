#include "AutoDriveEncoder.h"



AutoDriveEncoder::AutoDriveEncoder(double inchesToDrive, double speed)
{
	this->m_MovementState = sMovementParamHelper(inchesToDrive, speed);

	std::string error = "";
	if ( ! this->m_MovementState.ValidateParameters(error) )
	{
		std::cout << "****************************************************" << std::endl;
		std::cout << "*** WARNING: AutoDriveEncoder() did NOT validate ***" << std::endl;
		std::cout << error << std::endl;
		std::cout << "****************************************************" << std::endl;
	}

	return;
}

AutoDriveEncoder::AutoDriveEncoder( sMovementParamHelper moveParams )
{
	std::string error = "";
	if ( ! this->m_MovementState.ValidateParameters(error) )
	{
		std::cout << "****************************************************" << std::endl;
		std::cout << "*** WARNING: AutoDriveEncoder() did NOT validate ***" << std::endl;
		std::cout << error << std::endl;
		std::cout << "****************************************************" << std::endl;

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

	this->m_MovementState.Start_ChangeStateToAccelerating();

	return;
}

void AutoDriveEncoder::Execute()
{
	// Get current encoder values
	double currentDistance = CommandBase::pDriveTrain->getAverageEncoderPositionInTicks();

	double speed = this->m_MovementState.CalculateSpeedAndUpdateState( currentDistance );

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
