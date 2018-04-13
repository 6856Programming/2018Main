#include <Commands/AutoBasicForwardTimerWithDelay.h>

#include "Robot.h"

//#include "Commands/AutonomousGripper.h"
//#include "Commands/AutonomousRotateGyro.h"
#include "Commands/AutoDriveEncoder.h"
#include "Commands/AutoTurnGyro.h"

// Auto command groups
#include "Commands/Autonomous/cAutoCG_ScratchPad.h"	// Quick-n-Dirty test command group

#include "Commands/AutoBasicForwardTimerWithDelay.h"
#include "Commands/Autonomous/cRightStart_Switch_DontCrossField.h"
#include "Commands/Autonomous/cLeftStart_Switch_DontCrossField.h"


// Global, so everyone can use it
cGameState g_GameState;


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

//	//
//	this->m_driverStationPosition = Robot::UNKNOWN;		// Left, Centre, or Right
//
//	this->m_nearSwitchPosition = Robot::UNKNOWN;			// Left or Right
//	this->m_scalePosition = Robot::UNKNOWN;				// Left or Right
//	this->m_farSwitchPosition = Robot::UNKNOWN;			// Left or Right

	CommandBase::pDriveTrain->setWheelDiameterInches( 6.0 );
	CommandBase::pDriveTrain->setEncoderTicksPerRevolution( 1440.0 );

	CommandBase::pDriveTrain->setInvertLeftEncoderReturnValue(false);
	CommandBase::pDriveTrain->setInvertRightEncoderReturnValue(true);

//	this->ProcessGameStartUpState();
	::g_GameState.ProcessGameStartUpState();

	std::cout << "Robot::RobotInit(): Resetting Gyro" << std::endl;
	CommandBase::pDriveTrain->get_pGyroHelper()->ResetGyro();

	return;
}


void Robot::DisabledInit()
{
	return;
}


void Robot::DisabledPeriodic()
{
	frc::Scheduler::GetInstance()->Run();

	return;
}


void Robot::AutonomousInit()
{
	std::cout << "[Robot] Autonomous Initialized" << std::endl;

//	std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
//	std::cout << "[Robot] Auto Selected: " << autoSelected << std::endl;


	//	this->pDefaultAutoCommand = new ExampleCommand();
	//	this->pMyAutoCommand = new MyAutoCommand();

	// Setup smartdashboard autonomous options

	double autoWaitToStartTime = ::SmartDashboard::GetNumber("AUTO: seconds to wait to start driving", DEFAULT_WAIT_TO_START_TIME);
	double autoDriveSpeed = ::SmartDashboard::GetNumber("AUTO: drive speed", DEFAULT_DRIVE_SPEED);
	double autoDriveTime = ::SmartDashboard::GetNumber("AUTO: seconds to drive", DEFAULT_DRIVE_FORWARD_TIME);
	Command* pDefaultAuto = new AutoBasicForwardTimerWithDelay(autoWaitToStartTime, autoDriveSpeed, autoDriveTime);

	m_chooser.AddDefault("Default Auto", pDefaultAuto );

	m_chooser.AddObject("Right Switch (don't cross)", new cRightStart_Switch_DontCrossField() );
	m_chooser.AddObject("Left Switch (don't cross)", new cLeftStart_Switch_DontCrossField() );

	frc::SmartDashboard::PutData("Auto Modes", &(this->m_chooser) );

	pAutonomousCommand = m_chooser.GetSelected();

	if (pAutonomousCommand != nullptr)
	{
		std::cout << "[Robot] Starting autonomous" << std::endl;
		pAutonomousCommand->Start();
	}
	else
	{
		std::cout << "Autonomous Command is null!" << std::endl;
		std::cout << "Using the Good Old AutoBasicForwardTimerWithDelay() Command";
		pAutonomousCommand = pDefaultAuto;
	}


//	// *****************************************************************************
//	// ********** THIS IS THE OG delay, then drive auto **********
//
//	double autoWaitToStartTime = ::SmartDashboard::GetNumber("AUTO: seconds to wait to start driving", DEFAULT_WAIT_TO_START_TIME);
//	double autoDriveSpeed = ::SmartDashboard::GetNumber("AUTO: drive speed", DEFAULT_DRIVE_SPEED);
//	double autoDriveTime = ::SmartDashboard::GetNumber("AUTO: seconds to drive", DEFAULT_DRIVE_FORWARD_TIME);
//
//	Command* pAuto = new AutoBasicForwardTimerWithDelay(autoWaitToStartTime, autoDriveSpeed, autoDriveTime);
//	::Scheduler::GetInstance()->AddCommand( pAuto );	// double wait
//	// *****************************************************************************


//	::Scheduler::GetInstance()->AddCommand( new cAutoCG_ScratchPad() );

	::Scheduler::GetInstance()->AddCommand( pAutonomousCommand );


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


void Robot::TeleopPeriodic()
{
	//std::cout << "[Robot] Running Scheduler" << std::endl;

	frc::Scheduler::GetInstance()->Run();

	return;
}


void Robot::TestPeriodic()
{
	std::cout << "[Robot] TestPeriodic" << std::endl;

	return;
}

/**
 *
 */

START_ROBOT_CLASS(Robot)

