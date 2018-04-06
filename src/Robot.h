#ifndef _ROBOT_HG_
#define _ROBOT_HG_

#include <iostream>
#include <WPILib.h>
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <Commands/WaitCommand.h>
#include "Commands/DriveWithJoystick.h"
#include "Commands/ExampleCommand.h"
#include "Commands/MyAutoCommand.h"
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>



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

	// These are the positions of the driver stations, switch, and scale
	enum ePositions
	{
		LEFT, CENTRE, RIGHT, UNKNOWN
	};
private:
	ePositions m_driverStationPosition;		// Left, Centre, or Right
	// Note: the FMS sends sides based on aliance colour
	// So these are 'our' positions, in other words...
	ePositions m_nearSwitchPosition;			// Left or Right
	ePositions m_scalePosition;				// Left or Right
	ePositions m_farSwitchPosition;			// Left or Right
public:
	// Will populate the positions based on init game state
	void ProcessGameStartUpState(void);

	ePositions getDirverStationPosition(void);
	ePositions getNearSwitchPosition(void);
	ePositions getScalePosition(void);
	ePositions getFarSwitchPositions(void);



	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	frc::Command* pAutonomousCommand = nullptr;

	frc::SendableChooser<frc::Command*> m_chooser;

	// declare the commands
	DriveWithJoystick* pDriveWithJoystick;
	ExampleCommand* pDefaultAutoCommand;
	MyAutoCommand* pMyAutoCommand;

private:

};

#endif
