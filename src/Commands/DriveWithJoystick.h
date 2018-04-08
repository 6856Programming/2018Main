#ifndef _DRIVEWITHJOYSTICK_HG_
#define _DRIVEWITHJOYSTICK_HG_

#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */

class DriveWithJoystick: public CommandBase
{
public:
	DriveWithJoystick();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

	// Added as a Q-n-D test the various motors Hail Mary pass at UWO
	void DEBUG_ControllerTestMotors(void);

	// If the driver A, B, X, AND Y are pressed AT THE SAME TIME, the gyro calibrates
	void CheckForGyroCalibration(void);

};

#endif
