#include <Commands/AutoBasicForwardTimerWithDelay.h>

#include <Commands/Waiter.h>
#include "Robot.h"

#include "Commands/AutonomousGripper.h"
#include "Commands/AutonomousRotateGyro.h"
#include "Commands/AutoDriveEncoder.h"


Robot::~Robot()
{
	delete this->pDriveWithJoystick;
//	delete this->pDefaultAutoCommand;
//	delete this->pMyAutoCommand;

	return;
}

/**
 *
 */

void Robot::RobotInit()
{
	std::cout << "[Robot] Initialized" << std::endl;

	// instantiate the commands
	this->pDriveWithJoystick = new DriveWithJoystick();

	//
	this->m_driverStationPosition = Robot::UNKNOWN;		// Left, Centre, or Right

	this->m_nearSwitchPosition = Robot::UNKNOWN;			// Left or Right
	this->m_scalePosition = Robot::UNKNOWN;				// Left or Right
	this->m_farSwitchPosition = Robot::UNKNOWN;			// Left or Right

	CommandBase::pDriveTrain->setWheelDiameterInches( 6.0 );
	CommandBase::pDriveTrain->setEncoderTicksPerRevolution( 1440.0 );

	this->ProcessGameStartUpState();


	return;
}

//	ePositions m_driverStationPosition;		// Left, Centre, or Right
//	// Note: the FMS sends sides based on aliance colour
//	// So these are 'our' positions, in other words...
//	ePositions m_nearSwitchPosition			// Left or Right
//	ePositions m_scalePosition;				// Left or Right
//	ePositions m_farSwitchPosition;			// Left or Right

// Will populate the positions based on init game state
// SHOULD BE CALLED ON AUTOINIT
void Robot::ProcessGameStartUpState(void)
{
//	int _RP = 10; // 10 = Left, 20 = Center, 30 = Right
//	int _SP =  1;  // 1 = Left, 2 = Right

	switch ( frc::DriverStation::GetInstance().GetLocation() )
	{
	case 1:
		this->m_driverStationPosition = Robot::LEFT;
		break;
	case 2:
		this->m_driverStationPosition = Robot::CENTRE;
		break;
	case 3:
		this->m_driverStationPosition = Robot::RIGHT;
	}

	std::string gameItemsString = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	// Near switch position?
	if ( gameItemsString[0] == 'L' )
	{
		this->m_nearSwitchPosition = Robot::LEFT;
	}
	else if ( gameItemsString[0] == 'R' )
	{
		this->m_nearSwitchPosition = Robot::RIGHT;
	}

	// Scale position?
	if ( gameItemsString[1] == 'L' )
	{
		this->m_scalePosition = Robot::LEFT;
	}
	else if ( gameItemsString[1] == 'R' )
	{
		this->m_scalePosition = Robot::RIGHT;
	}

	// Far switch position
	if ( gameItemsString[2] == 'L' )
	{
		this->m_farSwitchPosition = Robot::LEFT;
	}
	else if ( gameItemsString[2] == 'R' )
	{
		this->m_farSwitchPosition = Robot::RIGHT;
	}


	return;
}


Robot::ePositions Robot::getDirverStationPosition(void)
{
	return this->m_driverStationPosition;
}

Robot::ePositions Robot::getNearSwitchPosition(void)
{
	return this->m_nearSwitchPosition;
}

Robot::ePositions Robot::getScalePosition(void)
{
	return this->m_scalePosition;
}

Robot::ePositions Robot::getFarSwitchPositions(void)
{
	return this->m_farSwitchPosition;
}



/**
 *
 */

void Robot::DisabledInit()
{
	return;
}

/**
 *
 */

void Robot::DisabledPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}

/**
 *
 */

void Robot::AutonomousInit()
{
	std::cout << "[Robot] Autonomous Initialized" << std::endl;

//	std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
//	std::cout << "[Robot] Auto Selected: " << autoSelected << std::endl;


	//	this->pDefaultAutoCommand = new ExampleCommand();
	//	this->pMyAutoCommand = new MyAutoCommand();

		// Setup smartdashboard autonomous options
	//	m_chooser.AddDefault("Default Auto", pDefaultAutoCommand);
	//	m_chooser.AddObject("My Auto", pMyAutoCommand);

//	frc::SmartDashboard::PutData("Auto Modes", &(this->m_chooser) );
//
//	pAutonomousCommand = m_chooser.GetSelected();
//
//	if (pAutonomousCommand != nullptr)
//	{
//		std::cout << "[Robot] Starting autonomous" << std::endl;
//		pAutonomousCommand->Start();
//	}
//	else
//	{
//		std::cout << "Autonomous Command is null!" << std::endl;
//	}

	//::Scheduler::GetInstance()->AddCommand( new WaitCommand(5.0));

	// For now, use the Quick-n-Dirty AutoBasicForwardTimerWithDelay() command


	double autoWaitToStartTime = ::SmartDashboard::GetNumber("AUTO: seconds to wait to start driving", DEFAULT_WAIT_TO_START_TIME);
	double autoDriveSpeed = ::SmartDashboard::GetNumber("AUTO: drive speed", DEFAULT_DRIVE_SPEED);
	double autoDriveTime = ::SmartDashboard::GetNumber("AUTO: seconds to drive", DEFAULT_DRIVE_FORWARD_TIME);


	// *****************************************************************************
	// ********** THIS IS THE OG delay, then drive auto **********
	Command* pAuto = new AutoBasicForwardTimerWithDelay(autoWaitToStartTime, autoDriveSpeed, autoDriveTime);
	::Scheduler::GetInstance()->AddCommand( pAuto );	// double wait
	// *****************************************************************************



//	double inchesToDrive = 48.0;
//	double maxDriveSpeed = 0.5;
//
//	sMovementParamHelper driveState(inchesToDrive, maxDriveSpeed);
//	driveState.minSpeed = 0.5;
//	std::cout << "Robot::AutoInit()..." << std::endl;
//	std::cout << driveState.getMemberStateString() << std::endl;
//
//	//Command* pAuto = new AutoDriveEncoder(inchesToDrive, maxDriveSpeed);
//	Command* pAuto = new AutoDriveEncoder(driveState);
//	::Scheduler::GetInstance()->AddCommand( pAuto );


	return;
}

/**
 *
 */

void Robot::AutonomousPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}

/**
 *
 */

void Robot::TeleopInit()
{
	std::cout << "[Robot] Teleop Initialized" << std::endl;

	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (pAutonomousCommand != nullptr)
	{
		pAutonomousCommand->Cancel();
		pAutonomousCommand = nullptr;
	}

	if (pDriveWithJoystick != nullptr)
	{
		std::cout << "[Robot] Starting DriveWithJoystick" << std::endl;
		//pDriveWithJoystick->Start();
	}
	else
	{
		std::cout << "[Robot] DriveWithJoystick is null!" << std::endl;
	}

	return;
}

/**
 *
 */

void Robot::TeleopPeriodic()
{
	//std::cout << "[Robot] Running Scheduler" << std::endl;

	frc::Scheduler::GetInstance()->Run();

	return;
}

/**
 *
 */

void Robot::TestPeriodic()
{
	std::cout << "[Robot] TestPeriodic" << std::endl;

	return;
}

/**
 *
 */

START_ROBOT_CLASS(Robot)

