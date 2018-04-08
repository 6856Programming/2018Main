#include "sMovementParamHelper.h"
#include <math.h>
#include <float.h>
#include <sstream>
#include <iostream>


/*static*/ const double sMovementParamHelper::DEFAULT_ACCEL_PHASE_PERCENT = 0.1;
/*static*/ const double sMovementParamHelper::DEFAULT_DECEL_PHASE_PERCENT = 0.1;
/*static*/ const double sMovementParamHelper::DEFAULT_CRUISE_PHASE_PERCENT = 0.8;
/*static*/ const double sMovementParamHelper::DEFAULT_MIN_SPEED = 0.1;
/*static*/ const double sMovementParamHelper::DEFAULT_WATCHDOG_KILL_TIME_SECONDS = 15.0;


sMovementParamHelper::sMovementParamHelper()
{
	// Set to zero... assume we are setting these somewhere else
	this->totalDistance = 0.0;
	this->maxSpeed = 0.0;

	this->minSpeed = sMovementParamHelper::DEFAULT_MIN_SPEED;

	this->accelPhasePercent = sMovementParamHelper::DEFAULT_ACCEL_PHASE_PERCENT;
	this->decelPhasePercent = sMovementParamHelper::DEFAULT_DECEL_PHASE_PERCENT;
	this->cruisePhasePercent = sMovementParamHelper::DEFAULT_CRUISE_PHASE_PERCENT;

	this->watchDogKillTimeSeconds = sMovementParamHelper::DEFAULT_WATCHDOG_KILL_TIME_SECONDS;

	this->m_currentState = sMovementParamHelper::IS_WAITING_TO_START;

	this->m_pWatchDogKillTimer = new frc::Timer();
	this->m_pWatchDogKillTimer->Reset();

	this->ValidateParameters();


	return;
}


sMovementParamHelper::sMovementParamHelper(double totalDistance, double maxSpeed)
{
	this->totalDistance = totalDistance;
	this->maxSpeed = maxSpeed;

	this->minSpeed = sMovementParamHelper::DEFAULT_MIN_SPEED;

	this->accelPhasePercent = sMovementParamHelper::DEFAULT_ACCEL_PHASE_PERCENT;
	this->decelPhasePercent = sMovementParamHelper::DEFAULT_DECEL_PHASE_PERCENT;
	this->cruisePhasePercent = sMovementParamHelper::DEFAULT_CRUISE_PHASE_PERCENT;

	this->watchDogKillTimeSeconds = sMovementParamHelper::DEFAULT_WATCHDOG_KILL_TIME_SECONDS;

	this->m_currentState = sMovementParamHelper::IS_WAITING_TO_START;

	this->m_pWatchDogKillTimer = new frc::Timer();
	this->m_pWatchDogKillTimer->Reset();

	this->ValidateParameters();

	return;
}


double sMovementParamHelper::getAccelPhaseEndDistance(void)
{
	return this->totalDistance * this->accelPhasePercent;
}

double sMovementParamHelper::getDecelPhaseStartDistance(void)
{
	double decStart = this->totalDistance * ( 1.0 - this->decelPhasePercent );
	return decStart;
}

double sMovementParamHelper::getDecelPhaseDistance(void)
{
	double descDistance = this->totalDistance * this->decelPhasePercent;
	return descDistance;
}


double sMovementParamHelper::getCruizePhaseDistance(void)
{
	double cruiseDistance = this->totalDistance * ( 1.0 - (this->decelPhasePercent + this->accelPhasePercent) );
	return cruiseDistance;
}


bool sMovementParamHelper::ValidateParameters(void)
{
	std::string error = "";
	return this->ValidateParameters(error);
}

// Makes sure the parameters "make sense"
// min speed LT max, percents all add up, etc.
bool sMovementParamHelper::ValidateParameters(std::string &error)
{
	if (this->minSpeed >= this->maxSpeed)
	{
		error = "ERROR: min cruise speed is GTE max drive speed";
		return false;
	}

	double phasePercentTotal = this->accelPhasePercent + this->cruisePhasePercent + this->decelPhasePercent;

	// Does this add to 1.0 (with 2x epsilon)?
	if (( fabs(phasePercentTotal) - 1.0 ) > ( FLT_EPSILON * 2.0 ))
	{
		std::stringstream ssError;
		ssError << "ERROR: Drive phases add to " << phasePercentTotal << " but should add up to 1.0";
		error = ssError.str();
		return false;
	}

	// Set the overall direction
	this->overallDirection = 1.0;
	if (this->totalDistance < 0.0)
	{
		this->overallDirection = -1.0;
	}

	if (this->watchDogKillTimeSeconds < 0.0)
	{
		this->watchDogKillTimeSeconds = sMovementParamHelper::DEFAULT_WATCHDOG_KILL_TIME_SECONDS;
	}

	// We're good to go
	return true;
}

std::string sMovementParamHelper::TranslateStringState(sMovementParamHelper::eMoveState theState)
{
	switch (theState)
	{
	case sMovementParamHelper::IS_WAITING_TO_START:
		return "IS_WAITING_TO_START";
		break;

	case sMovementParamHelper::IS_ACCELERATING:
		return "IS_ACCELERATING";
		break;

	case sMovementParamHelper::IS_CRUISING:
		return "IS_CRUISING";
		break;

	case sMovementParamHelper::IS_DECELERATING:
		return "IS_DECELERATING";
		break;

	case sMovementParamHelper::IS_DONE:
		return "IS_DONE";
		break;

	case sMovementParamHelper::WATCH_DOG_TIMED_OUT:
		return "WATCH_DOG_TIMED_OUT";
		break;

	case sMovementParamHelper::INVALID_STATE:
		return "INVALID_STATE";
		break;

	default:
		return "Unknown State: Re-evaluate your life choices and learn to program. Geeze.";
		break;
	}

	//
	return "Unknown State: Re-evaluate your life choices and learn to program. Geeze.";
}

std::string sMovementParamHelper::getCurrentStateString(void)
{
	return this->TranslateStringState(this->m_currentState);
}


// This is called by Init()
void sMovementParamHelper::Start_ChangeStateToAccelerating(void)
{
	// This can only be called when we are waiting to start
	if (this->m_currentState == IS_WAITING_TO_START)
	{
		this->m_currentState = IS_ACCELERATING;
	}

	this->ValidateParameters();

	this->m_pWatchDogKillTimer->Start();

	return;
}

sMovementParamHelper::eMoveState sMovementParamHelper::getCurrentState(void)
{
	return this->m_currentState;
}

// This is called during Execute()
double sMovementParamHelper::CalculateSpeedAndUpdateState(double currentDistance)
{
//	std::cout << "[sMovementParamHelper::CalculateSpeedAndUpdateState(" << currentDistance << ")] called" << std::endl;

	// maxSpeed is ALWAYS positive,
	// but totalDistance will indicate direction (+ve or -ve)

	// Check watchdog...
	if ( this->m_pWatchDogKillTimer->Get() >= this->watchDogKillTimeSeconds )
	{
		// Sorry, you took too long, son.
		std::cout << "WARNING: Watch dog timer timed out." << std::endl;
		this->m_ChangeState(sMovementParamHelper::WATCH_DOG_TIMED_OUT);
		return 0.0;
	}

	switch (this->m_currentState)
	{
	case sMovementParamHelper::IS_WAITING_TO_START:
		return 0.0;
		break;

	case sMovementParamHelper::IS_ACCELERATING:
	{
		// What is the speed ratio at this point?
		double percentThroughPhase = fabs(currentDistance / this->getAccelPhaseEndDistance());
		if (percentThroughPhase > 1.0)
		{
			// We are done accelerating
			this->m_ChangeState(IS_CRUISING);

			// Clamp the value
			percentThroughPhase = 1.0;
		}
		double calculatedSpeed = percentThroughPhase * this->maxSpeed;
		// Is speed too low?
		if (calculatedSpeed < this->minSpeed)
		{
			calculatedSpeed = this->minSpeed;
		}

		return calculatedSpeed * this->overallDirection;
	}
	break;

	case sMovementParamHelper::IS_CRUISING:
	{
		double distanceThroughCruise = currentDistance - this->getAccelPhaseEndDistance();
		double percentThroughPhase = fabs( distanceThroughCruise / this->getCruizePhaseDistance() );

		if (percentThroughPhase > 1.0)
		{
			// We are done cruising
			this->m_ChangeState(IS_DECELERATING);
		}

		return this->maxSpeed * this->overallDirection;
	}
	break;

	case sMovementParamHelper::IS_DECELERATING:
	{
		double distanceThroughDecel = currentDistance - this->getDecelPhaseStartDistance();
		double percentThroughPhase = fabs( distanceThroughDecel / this->getDecelPhaseDistance() );

		if ( percentThroughPhase > 1.0 )
		{
			// Done decelerating
			this->m_ChangeState(IS_DONE);
		}

		double calculatedSpeed = (1.0 - percentThroughPhase) * this->maxSpeed;
		// Is speed too low?
		if (calculatedSpeed < this->minSpeed)
		{
			calculatedSpeed = this->minSpeed;
		}

		return calculatedSpeed * this->overallDirection;
	}
	break;

	case sMovementParamHelper::IS_DONE:
		return 0.0;
		break;

	case sMovementParamHelper::WATCH_DOG_TIMED_OUT:
		return 0.0;
		break;

	case sMovementParamHelper::INVALID_STATE:
	default:
		return 0.0;
		break;
	}

	// Should never get here...
	return 0.0;
}

// This is really so that something will print out to the console
void sMovementParamHelper::m_ChangeState(sMovementParamHelper::eMoveState newState, bool bLogToConsole /*=true*/)
{
	this->m_currentState = newState;

	if ( bLogToConsole )
	{
		std::stringstream ssMessage;
		ssMessage << "AutoDriveEncoder() changing state to " << this->TranslateStringState(this->m_currentState);
		std::cout << ssMessage.str() << std::endl;
	}
	return;
}

// Returns if IS_DONE is the state
bool sMovementParamHelper::IsDone(void)
{
	if ( this->m_currentState == sMovementParamHelper::IS_DONE )
	{
		return true;
	}
	return false;
}

// Returns if invalid, watch dog, or anything else 'bad' happened
bool sMovementParamHelper::IsStateInvalid(void)
{
	if ( (this->m_currentState == sMovementParamHelper::WATCH_DOG_TIMED_OUT) ||
	     (this->m_currentState == sMovementParamHelper::INVALID_STATE) )
	{
		return true;
	}
	return false;
}

std::string sMovementParamHelper::getMemberStateString(void)
{
	std::stringstream ssOut;

	ssOut << "--------------------------------------------------------" << std::endl;
	ssOut << "totalDistance = " << this->totalDistance << std::endl;
	ssOut << "maxSpeed = " << this->maxSpeed << std::endl;
	ssOut << "minSpeed = " << this->minSpeed << std::endl;
	ssOut << "watchDogKillTimeSeconds = " << this->watchDogKillTimeSeconds << std::endl;
	ssOut << "overallDirection = " << this->overallDirection << std::endl;
	ssOut << "accelPhasePercent = " << this->accelPhasePercent << std::endl;
	ssOut << "decelPhasePercent = " << this->decelPhasePercent << std::endl;
	ssOut << "cruisePhasePercent = " << this->cruisePhasePercent << std::endl;
	ssOut << "current state = " << this->getCurrentStateString() << std::endl;
	ssOut << "IsDone() = " << (this->IsDone() ? "TRUE" : "FALSE" ) << std::endl;
	ssOut << "IsStateInvalid() = " << (this->IsStateInvalid() ? "TRUE" : "FALSE" ) << std::endl;
	ssOut << "--Calculated values--" << std::endl;
	ssOut << "getAccelPhaseEndDistance() = " << this->getAccelPhaseEndDistance() << std::endl;
	ssOut << "getDecelPhaseStartDistance() = " << this->getDecelPhaseStartDistance() << std::endl;
	ssOut << "getDecelPhaseDistance() = " << this->getDecelPhaseDistance() << std::endl;
	ssOut << "getCruizePhaseDistance() = " << this->getCruizePhaseDistance() << std::endl;
	ssOut << "--------------------------------------------------------" << std::endl;

	return ssOut.str();
}




