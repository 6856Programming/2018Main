#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <cGameState.h>
#include <iostream>
#include <WPILib.h>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <Commands/WaitCommand.h>
#include "Commands/DriveWithJoystick.h"
//#include "Commands/ExampleCommand.h"
//#include "Commands/MyAutoCommand.h"
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "cGameState.h"


// Global, so everyone can use it
extern cGameState g_GameState;

//#include "S"


class Robot : public frc::TimedRobot
{
public:
	~Robot();
	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;



	// Will place the default smart dashboard settings
	void InitSmartDashboardDefaults(void);


	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	frc::Command* pAutonomousCommand = nullptr;

	frc::SendableChooser<frc::Command*> m_chooser;

	// declare the commands
	DriveWithJoystick* pDriveWithJoystick;
//	ExampleCommand* pDefaultAutoCommand;
//	MyAutoCommand* pMyAutoCommand;

private:

};

#endif
