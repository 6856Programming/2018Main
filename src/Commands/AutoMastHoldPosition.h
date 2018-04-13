#ifndef _AutoMastHoldPosition_HG_
#define _AutoMastHoldPosition_HG_

#include <Commands/Command.h>

class AutoMastHoldPosition : public frc::Command
{
public:
	AutoMastHoldPosition(bool bEnableHold);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:
	void m_Init(void);
	// Can't call c'tor
	// (Because: you'll need to set if this is being held or not)
	AutoMastHoldPosition() {};
	bool m_bEnableHold;
};

#endif // AutoMastHoldPosition
