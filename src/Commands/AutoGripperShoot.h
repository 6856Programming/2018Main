#ifndef _AutoGripperShoot_HG_
#define _AutoGripperShoot_HG_

#include <WPILib.h>
#include <Commands/Command.h>
#include "../CommandBase.h"

class AutoGripperShoot : public frc::Command
{
public:
	AutoGripperShoot(double secondsToRun, double speed);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	// Can't call
	AutoGripperShoot() {};

	double m_secondsToRun;
	double m_speed;
};

#endif
