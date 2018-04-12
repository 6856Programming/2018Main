
#ifndef _AutoBasicForwardTimerWithDelay_HG_
#define _AutoBasicForwardTimerWithDelay_HG_

#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */

class AutoBasicForwardTimerWithDelay: public CommandBase
{
public:

	enum eState
	{
		COMMAND_NOT_STARTED,	// c'tor called, but Initialize() not called, yet
		IS_WAITING_TO_START_DRIVING,
		IS_DRIVING,
		IS_DONE,
		UNKNOWN					// WTF? (should never happen)
	};

	// NOTE: secondsToRun is time AFTER delay has finished (NOT total time)
	AutoBasicForwardTimerWithDelay( double secondsToWaitToStart, double speed, double secondsToRun );
	virtual ~AutoBasicForwardTimerWithDelay();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	std::string GetCurrentStateString(void);

private:

	double m_secondsToWaitToStart;
	double m_secondsToRun;
	double m_speed;


	eState m_currentState;

	// Can't call c'tor
	AutoBasicForwardTimerWithDelay();

	frc::Timer* m_pTimerWaitToStart;	// Time to wait until drive starts
	frc::Timer* m_pTimerDrive;		// Time to drive AFTER wait is done
};


#endif /* SRC_COMMANDS_AUTONOMOUSFORWARD_H_ */
