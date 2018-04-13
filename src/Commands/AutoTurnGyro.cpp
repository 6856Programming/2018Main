#include "AutoTurnGyro.h"



AutoTurnGyro::AutoTurnGyro( double turnAngle, double speed )
{
	std::cout << "[AutoTurnGyro() constructed" << std::endl;
//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;
	this->m_MovementState = sMovementParamHelper(turnAngle, speed);
//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;

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

AutoTurnGyro::AutoTurnGyro( sMovementParamHelper moveParams )
{
//	std::cout << "AutoDriveEncoder..." << std::endl;
//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;
	this->m_MovementState = moveParams;
//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;


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



AutoTurnGyro::~AutoTurnGyro()
{
	return;
}

void AutoTurnGyro::Initialize()
{
	std::cout << "[AutoTurnGyro::Initialize()] called" << std::endl;
	std::cout << "[AutoTurnGyro::Initialize()] calling: Start_ChangeStateToAccelerating()" << std::endl;

	CommandBase::pDriveTrain->get_pGyroHelper()->ResetGyro();

	this->m_MovementState.Start_ChangeStateToAccelerating();

//	std::cout << this->m_MovementState.getMemberStateString() << std::endl;

	return;
}

void AutoTurnGyro::Execute()
{
//	std::cout << "[AutoDriveEncoder::Execute()] called..." << std::endl;

	// Get current encoder values
	double currentAngle = CommandBase::pDriveTrain->get_pGyroHelper()->GetGyroAngleImmediate();

	double speed = this->m_MovementState.CalculateSpeedAndUpdateState( currentAngle );

	double remainingDegrees = this->m_MovementState.totalDistance - currentAngle;

	::SmartDashboard::PutNumber("AutoTurnGyro: Remaining degrees", remainingDegrees );
	::SmartDashboard::PutNumber("AutoTurnGyro: currentSpeed", speed );

	std::cout
		<< "AutoTurnGyro: remaining degrees: " << remainingDegrees
		<< " current speed L, R:" << speed << ", " << -speed << std::endl;


	CommandBase::pDriveTrain->TankDrive( speed, -speed );

	return;
}

bool AutoTurnGyro::IsFinished()
{
	if ( this->m_MovementState.IsDone() || this->m_MovementState.IsStateInvalid() )
	{
		// Either we're done or all is lost, forever lost...
		return true;
	}

	// Still have work to do, Holmes.
	return false;
}

void AutoTurnGyro::End()
{

	return;
}
void AutoTurnGyro::Interrupted()
{
	return;
}

// Can't call c'tor
AutoTurnGyro::AutoTurnGyro()
{
	return;
}

