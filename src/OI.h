#ifndef _OI_HG_
#define _OI_HG_

#include <iostream>
#include <WPILib.h>
#include <XboxController.h>

/**
 *
 */

class OI
{
public:
	OI();
	~OI();

	frc::XboxController* GetJoystickDrive();
	//frc::XboxController* GetJoystickOperator();
	frc::Joystick* GetJoystickOperator();


private:
	frc::XboxController* pJoystickDrive;
	//frc::XboxController* pJoystickOperator;

	frc::Joystick* pJoystickOperator;
};

#endif
