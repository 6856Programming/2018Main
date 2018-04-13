/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "cRightStart_Switch_DontCrossField.h"

#include "../AutoDriveEncoder.h"
#include "../AutoTurnGyro.h"
#include "../AutonomousMast.h"
#include "../AutoGripperShoot.h"

// Global, so everyone can use it
#include "../../cGameState.h"
extern cGameState g_GameState;


cRightStart_Switch_DontCrossField::cRightStart_Switch_DontCrossField()
{

	Requires(::CommandBase::pDriveTrain);
	Requires(::CommandBase::pLiftMast);
	Requires(::CommandBase::pGripper);

	// 1. Serial: Forward 13'
	// **********************************************
	// ** If the switch isn't ours, then EXIT HERE **
	// **********************************************
	// 2. Serial: Lift at 100% for 0.7 seconds
	// 3. Parallel:
	// 	- Hold at 30%
	//  - We're RIGHT, to turn 90 degrees
	// 4. Parallel:
	//  - Hold at 30%
	//  - Drive forward (to bump into switch)
	// 5. Parallel:
	//	- Hold at 30%
	//	- Shoot
	// 6. Back away from the switch (and let lift fall, possibly)

	const double STAGE_1_DISTANCE_TO_DRIVE_FORWARD_IN_FEET = 13.0;	// 13.0 FEET
	const double STATE_4_DISTANCE_TO_DRIVE_FORWARD_IN_FEET = 2.0;	// 2.0 FEET
	const double STAGE_6_DISTANCE_TO_DRIVE_BACKWARD_IN_FEET = -2.0f;

	const double LIFT_HOLD_POSITION_POWER = 0.3;		// 30%


	// 1. Serial: Forward 13'
	{	// move forward x inches
		sMovementParamHelper driveState;

//		driveState.totalDistance = ::SmartDashboard::GetNumber("AutoDriveEncoder():Distance to drive",
//		                                                        STAGE_1_DISTANCE_TO_DRIVE_FORWARD_IN_FEET * 12.0);
//		::SmartDashboard::PutNumber("AutoDriveEncoder():Distance to drive", driveState.totalDistance);
//
//		driveState.maxSpeed = ::SmartDashboard::GetNumber("AutoDriveEncoder():maxDriveSpeed", 0.6);
//		::SmartDashboard::PutNumber("AutoDriveEncoder():maxDriveSpeed", driveState.maxSpeed);
//
//		driveState.accelPhasePercent = ::SmartDashboard::GetNumber("AutoDriveEncoder():accelPhasePercent", 0.1);
//		::SmartDashboard::PutNumber("AutoDriveEncoder():accelPhasePercent", driveState.accelPhasePercent);

		driveState.totalDistance = STAGE_1_DISTANCE_TO_DRIVE_FORWARD_IN_FEET * 12.0;
		driveState.maxSpeed = 0.6;

		driveState.RecalculateProfileFromDistances( driveState.totalDistance,
		                                            12.0, 			// Accel distance 1'
													12.0 );			// Decel distance 1'
//		driveState.accelPhasePercent = 0.10;
//		driveState.cruisePhasePercent = 0.80;
//		driveState.decelPhasePercent = 0.10;
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
	}// ENDOF: Stage 1


	// **********************************************
	// ** If the switch isn't ours, then EXIT HERE **
	cGameState::ePositions nearSwitchPos = ::g_GameState.getNearSwitchPosition();

	if ( nearSwitchPos != cGameState::RIGHT )
	{
		// Switch isn't on our side, so exit here
		return;
	}
	// **********************************************


	// 2. Serial: Lift at 100% for 0.7 seconds
	{
		Command* pLiftMast = new AutonomousMast( 0.7, 		// Lift time in seconds
		                                         1.0 );		// Lift speed (100%)

		this->AddSequential(pLiftMast);
	}// ENDOF: Stage 2

	// 3. Parallel:
	// 	- Hold at 30%
	//  - We're RIGHT, to turn 90 degrees
	{
		Command* pHoldMast = new AutonomousMast( 1.5, 								// Lift time in seconds
		                                         LIFT_HOLD_POSITION_POWER );		// Lift speed (30% to 'hold' mast)
		this->AddParallel(pHoldMast);

		sMovementParamHelper driveState;
		driveState.totalDistance = 90.0;		// Degrees
		driveState.maxSpeed = 0.65;
		driveState.minSpeed = 0.6;
		driveState.accelPhasePercent = 0.30;
		driveState.cruisePhasePercent = 0.40;
		driveState.decelPhasePercent = 0.30;		// At 10%, it overshot

		std::cout << driveState.getMemberStateString() << std::endl;

		Command* pTurnCCW90 = new AutoTurnGyro(driveState);
		this->AddParallel( pTurnCCW90 );

	}// ENDOF: Stage 3

	// 4. Parallel:
	//  - Hold at 30%
	//  - Drive forward (to bump into switch)
	{
		Command* pHoldMast = new AutonomousMast( 0.5, 								// Lift time in seconds
		                                         LIFT_HOLD_POSITION_POWER );		// Lift speed (30% to 'hold' mast)
		this->AddParallel(pHoldMast);


		sMovementParamHelper driveState;
		driveState.totalDistance = STATE_4_DISTANCE_TO_DRIVE_FORWARD_IN_FEET * 12.0;
		driveState.maxSpeed = 0.6;
		driveState.minSpeed = 0.4;

		Command* pDriveToSwitch = new AutoDriveEncoder(driveState, false);
		this->AddParallel( pDriveToSwitch );
	}


	// 5. Parallel:
	//	- Hold at 30%
	//	- Shoot
	{
		Command* pHoldMast = new AutonomousMast( 2.0, 								// Lift time in seconds
		                                         LIFT_HOLD_POSITION_POWER );		// Lift speed (30% to 'hold' mast)
		this->AddParallel(pHoldMast);

		Command* pShootCube = new AutoGripperShoot( 2.0, 	// Seconds to run
		                                            1.0 ); 	// Speed
		this->AddParallel( pShootCube );

	}// ENDOF: Stage 5

	// 6. Back away from the switch (and let lift fall, possibly)
	{
		sMovementParamHelper driveState;
		driveState.totalDistance = STAGE_6_DISTANCE_TO_DRIVE_BACKWARD_IN_FEET * 12.0;
		driveState.maxSpeed = 0.6;
		driveState.minSpeed = 0.4;

		Command* pBackAwayFromSwitch = new AutoDriveEncoder(driveState, false);
		this->AddSequential( pBackAwayFromSwitch );
	}// ENDOF: Stage 6



	return;
}
