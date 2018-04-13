#ifndef _AutoMastLiftToTopLimit_HG_
#define _AutoMastLiftToTopLimit_HG_

#include <WPILib.h>
#include <Commands/Command.h>

class AutoMastLiftToTopLimit : public frc::Command
{
public:
	AutoMastLiftToTopLimit(double speed);
	AutoMastLiftToTopLimit(double speed, double watchDogTimeOutInSeconds);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

public:
	// Can't call c'tor (what IS a default version of this command?)
	AutoMastLiftToTopLimit() {};

	void m_Init(void);
	frc::Timer* m_pWatchDogTimer;
	double m_WatchDogTimerTimeOut;
	const double m_DEFAULT_WATCH_DOG_TIME_OUT = 15.0f;	// ?? Reduce this ??

	double m_Speed;
};

#endif // AutoMastLiftToTopLimit
