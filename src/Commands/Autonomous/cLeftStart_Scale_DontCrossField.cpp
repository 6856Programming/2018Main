#include "cLeftStart_Scale_DontCrossField.h"

#include "../AutoDriveEncoder.h"
#include "../AutoTurnGyro.h"
#include "../AutonomousMast.h"
#include "../AutoGripperShoot.h"
#include "../AutoGripperOpen.h"
#include "../cWaitDelay.h"
#include "../AutoMastHoldPosition.h"
#include "../AutoMastLiftToTopLimit.h"

// Global, so everyone can use it
#include "../../cGameState.h"
extern cGameState g_GameState;


cLeftStart_Scale_DontCrossField::cLeftStart_Scale_DontCrossField()
{

	Requires(::CommandBase::pDriveTrain);
	Requires(::CommandBase::pLiftMast);
	Requires(::CommandBase::pGripper);

	// 1. Serial: Forward 21'
	// **********************************************
	// ** If the scale isn't ours, then EXIT HERE **
	// **********************************************
	// 2. Serial: Lift until limit switch is set
	// 3. Hold lift
	// 4. We're LEFT, to turn -45 degrees (CLOCKWISE)
	// 5. Move forward X feet (1? 2?)
	// 6. Shoot
	// 7. Back away from the switch
	// 8. Release lift

	const double STAGE_1_DISTANCE_TO_SCALE = 21.0;	// 21.0 FEET
	const double STATE_5_DISTANCE_AFTER_TURN = 2.0;	// 2.0 FEET


	// 1. Serial: Forward 21'
	{
		sMovementParamHelper driveState;

		driveState.totalDistance = STAGE_1_DISTANCE_TO_SCALE * 12.0;
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
	// ** If the scale isn't ours, then EXIT HERE **
	::g_GameState.ProcessGameStartUpState();
	cGameState::ePositions nearScaleLocation = ::g_GameState.getScalePosition();

//	::SmartDashboard::PutString("Scale Location", ::g_GameState.DecodePositionEnumString(nearScaleLocation) );

	if ( nearScaleLocation != cGameState::LEFT )
	{
		// Scale isn't on our side, so exit here
		::SmartDashboard::PutString("Scale", "Scale is on the RIGHT, so not dropping");

		return;
	}
	// **********************************************

	::SmartDashboard::PutString("Scale", "Scale is on the LEFT, so DROPPING");


	// 2. Serial: Lift until limit switch is set
	{
		Command* pLiftMastToTop = new AutoMastLiftToTopLimit(1.0, 5.0);
		this->AddSequential(pLiftMastToTop);
	}
	// 3. Hold lift
	{
		Command* pHoldMastLift = new AutoMastHoldPosition(true);
		this->AddSequential(pHoldMastLift);
	}

	// 4. We're LEFT, to turn -45 degrees (CLOCKWISE)
	{
		sMovementParamHelper driveState;
		driveState.totalDistance = -45.0;		// NEGATIVE, so CLOCKWISE
		driveState.maxSpeed = 0.75;
		driveState.minSpeed = 0.7;
		driveState.accelPhasePercent = 0.10;
		driveState.cruisePhasePercent = 0.80;
		driveState.decelPhasePercent = 0.10;		// At 10%, it overshot

		std::cout << driveState.getMemberStateString() << std::endl;

		Command* pTurn = new AutoTurnGyro(driveState);
		this->AddSequential( pTurn );
	}

	// 5. Move forward X feet (1? 2?)
	{
		sMovementParamHelper driveState;
		driveState.totalDistance = STATE_5_DISTANCE_AFTER_TURN * 12.0;
		driveState.maxSpeed = 0.6;
		driveState.minSpeed = 0.4;
		driveState.watchDogKillTimeSeconds = 3.0;

		Command* pDriveToSwitch = new AutoDriveEncoder(driveState, false);
		this->AddSequential( pDriveToSwitch );
	}

	// 6. Shoot
	{
		Command* pShootCube = new AutoGripperShoot( 2.0, 	// Seconds to run
		                                            1.0 ); 	// Speed
		this->AddSequential( pShootCube );
	}

	// 7. Back away from the scale
	{
		sMovementParamHelper driveState;
		driveState.totalDistance = -STATE_5_DISTANCE_AFTER_TURN * 12.0;
		driveState.maxSpeed = 0.6;
		driveState.minSpeed = 0.4;

		Command* pBackAway = new AutoDriveEncoder(driveState, false);
		this->AddSequential( pBackAway );
	}// ENDOF: Stage 6


	// 8. Release lift
	{
		this->AddSequential( new AutoMastHoldPosition(false) );
	}


	return;
}
