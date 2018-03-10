#ifndef _DEBUG_TALONSRX_TESTER_HG_
#define _DEBUG_TALONSRX_TESTER_HG_

#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */

class DebugTalonSRXTester: public CommandBase
{
public:
	DebugTalonSRXTester();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	unsigned int PickNextTalon(void);
	unsigned int PickPreviousTalon(void);
	unsigned int PickSpecificTalon(unsigned int talonID);
	unsigned int GetSelectedTalonID(void);
private:
	static const unsigned int NUMBEROFTALONS = 10;
	can::WPI_TalonSRX* m_pMotors[NUMBEROFTALONS];
	unsigned int m_selectedTalonID;
};


#endif
