#ifndef _AutoGripperOpen_HG_
#define _AutoGripperOpen_HG_

#include <Commands/Command.h>
#include <WPILib.h>
#include "../CommandBase.h"

class AutoGripperOpen : public frc::Command
{
public:
	// WARNING: THERE IS NO LIMIT OR SAFETY!!
	// ONLY PASS TINY VALUES TO THIS (like fractions of seconds)
	AutoGripperOpen(double secondsToOpen);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	// Can't call
	AutoGripperOpen() {};

	frc::Timer* m_pGripperOpenTimer;

	double m_secondsToOpen;
};

#endif

