#ifndef _sMovementParamHelper_HG_
#define _sMovementParamHelper_HG_

#include <WPILib.h>	// frc::Timer
#include <string>

// Uses to control auto movement.
// Used by both the auto drive and auto turn
class sMovementParamHelper
{
public:
	sMovementParamHelper();
	// maxSpeed is ALWAYS positive,
	// but totalDistance will indicate direction (+ve or -ve)
	sMovementParamHelper(double totalDistance, double maxSpeed);

	// This is called by Init()
	void Start_ChangeStateToAccelerating(void);
	// This is called during Execute()
	// NOTE: currentDistance can be -ve, i.e. it is the REAL encoder-gyro reading.
	// Returned speed is the ACTUAL motor speed (i.e. is -ve or +ve)
	double CalculateSpeedAndUpdateState(double currentDistance);


	double totalDistance;
	double maxSpeed;
	// NOTE: This can be zero, but the robot will never actually reach
	//	the target. Set this speed to the "slowest speed" that actually
	//  moves the robot, but doesn't overshoot (much).
	double minSpeed;

	// The command will run up to this time, then quit
	// Default is 15.0 seconds (the entire time for auto)
	double watchDogKillTimeSeconds;

	// +ve or -ve
	double overallDirection;

	// These are based on distances
	double accelPhasePercent;
	double decelPhasePercent;
	double cruisePhasePercent;

	static const double DEFAULT_ACCEL_PHASE_PERCENT;	// = 0.1;
	static const double DEFAULT_DECEL_PHASE_PERCENT;	// = 0.1;
	static const double DEFAULT_CRUISE_PHASE_PERCENT;	// = 0.8;
	static const double DEFAULT_MIN_SPEED;	// = 0.1;
	static const double DEFAULT_WATCHDOG_KILL_TIME_SECONDS;	// = 15.0;

	enum eMoveState
	{
		INVALID_STATE,			// If validate doesn't pass, is in this state
		IS_WAITING_TO_START,	// Initial state
		IS_ACCELERATING,
		IS_CRUISING,
		IS_DECELERATING,
		IS_DONE,
		WATCH_DOG_TIMED_OUT
	};

	eMoveState getCurrentState(void);

	// Returns if IS_DONE is the state
	bool IsDone(void);
	// Returns if invalid, watch dog, or anything else 'bad' happened
	bool IsStateInvalid(void);

private:
	eMoveState m_currentState;
	// This also checks the timer
	void m_ChangeState(eMoveState newState, bool bLogToConsole = true);
public:

	std::string TranslateStringState(eMoveState theState);


	// Makes sure the parameters "make sense"
	// min speed LT max, percents all add up, etc.
	// Called by all constructors
	bool ValidateParameters(void);
	bool ValidateParameters(std::string &error);
	double getAccelPhaseEndDistance(void);
	double getDecelPhaseStartDistance(void);
	double getDecelPhaseDistance(void);
	double getCruizePhaseDistance(void);


	frc::Timer* m_pWatchDogKillTimer;
};



#endif /* SRC_COMMANDS_SMOVEMENTPARAMS_H_ */
