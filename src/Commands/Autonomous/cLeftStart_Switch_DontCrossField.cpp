/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "cLeftStart_Switch_DontCrossField.h"

#include "../AutoDriveEncoder.h"
#include "../AutoTurnGyro.h"
#include "../AutonomousMast.h"
#include "../AutoGripperShoot.h"

// S: Forward 13'
// S: Lift at 100% for 0.7 seconds
// P: Hold at 30%
//    We're LEFT, to turn -90 degrees
// S: Shoot and release

cLeftStart_Switch_DontCrossField::cLeftStart_Switch_DontCrossField()
{

	Requires(::CommandBase::pDriveTrain);
	Requires(::CommandBase::pGripper);
	Requires(::CommandBase::pLiftMast);

	{	// S: Drive forward 13'
		sMovementParamHelper driveState;

		// Accel and Decel for 12", move a total of 13.0'
		driveState.RecalculateProfileFromDistances( 13.0 * 12.0, 12.0, 12.0 );

		driveState.maxSpeed = 0.6;					// 60%

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

	// S: Lift at 100% for 0.7 seconds
	{
		//Command* pLiftMast = new AutonomousMast()
	}

	{	// Turn -45 degrees
		sMovementParamHelper driveState;
		driveState.totalDistance = 45.0;		// Degrees
		driveState.maxSpeed = 0.65;
		driveState.minSpeed = 0.6;
		driveState.accelPhasePercent = 0.10;
		driveState.cruisePhasePercent = 0.70;
		driveState.decelPhasePercent = 0.20;		// At 10%, it overshot

		std::cout << driveState.getMemberStateString() << std::endl;

		Command* pTurnLeft45 = new AutoTurnGyro(driveState);
		this->AddSequential( pTurnLeft45 );
	}



	return;
}

