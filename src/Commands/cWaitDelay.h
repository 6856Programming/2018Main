#pragma once

#include <WPILib.h>
#include <Commands/Command.h>

class cWaitDelay : public frc::Command
{
public:
	cWaitDelay(double secondsToWait);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	// Don't call
	cWaitDelay() {};
	frc::Timer* m_pTimer;
	double m_secondsToWait;
};

