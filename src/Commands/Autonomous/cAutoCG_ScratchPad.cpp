/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "cAutoCG_ScratchPad.h"

#include "../AutoDriveEncoder.h"
#include "../AutoTurnGyro.h"


cAutoCG_ScratchPad::cAutoCG_ScratchPad()
{

	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.

	Requires(::CommandBase::pDriveTrain);

	{	// move forward x inches
		// 48 inches actually moves it 70 inches (more or less)
		sMovementParamHelper driveState;

//		driveState.totalDistance = ::SmartDashboard::GetNumber("AutoDriveEncoder():Distance to drive", 48.0);
//		driveState.totalDistance = ::SmartDashboard::GetNumber("AutoDriveEncoder():Distance to drive", 21.5 * 12.0);
		driveState.totalDistance = ::SmartDashboard::GetNumber("AutoDriveEncoder():Distance to drive", 15.0 * 12.0);
		::SmartDashboard::PutNumber("AutoDriveEncoder():Distance to drive", driveState.totalDistance);

		driveState.maxSpeed = ::SmartDashboard::GetNumber("AutoDriveEncoder():maxDriveSpeed", 0.6);
		::SmartDashboard::PutNumber("AutoDriveEncoder():maxDriveSpeed", driveState.maxSpeed);

		driveState.accelPhasePercent = ::SmartDashboard::GetNumber("AutoDriveEncoder():accelPhasePercent", 0.1);
		::SmartDashboard::PutNumber("AutoDriveEncoder():accelPhasePercent", driveState.accelPhasePercent);
		driveState.accelPhasePercent = 0.10;
		driveState.cruisePhasePercent = 0.80;
		driveState.decelPhasePercent = 0.1;
		driveState.minSpeed = 0.4;

		std::cout << driveState.getMemberStateString() << std::endl;

		Command* pDriveForward = new AutoDriveEncoder(driveState, true);

		this->AddSequential(pDriveForward);
	}

	{	// Stop abruptly at the end
		sMovementParamHelper driveState;
		driveState.totalDistance = -1.0;
		driveState.maxSpeed = 1.0;
		driveState.accelPhasePercent = 0.0;
		driveState.cruisePhasePercent = 100.0;
		driveState.decelPhasePercent = 0.0f;


		std::cout << driveState.getMemberStateString() << std::endl;

		Command* pReverseAtEnd = new AutoDriveEncoder(driveState, true);

		this->AddSequential(pReverseAtEnd);
	}


	{	// Turn -45 degrees
		sMovementParamHelper driveState;
		driveState.totalDistance = 45.0;		// Degrees
		driveState.maxSpeed = 0.65;
		driveState.minSpeed = 0.6;
		driveState.accelPhasePercent = 0.30;
		driveState.cruisePhasePercent = 0.40;
		driveState.decelPhasePercent = 0.30;		// At 10%, it overshot

		std::cout << driveState.getMemberStateString() << std::endl;

		Command* pTurnLeft45 = new AutoTurnGyro(driveState);
		this->AddSequential( pTurnLeft45 );
	}



	return;
}
