#ifndef _AutoTurnGyro_HG_
#define _AutoTurnGyro_HG_

#include <Commands/sMovementParamHelper.h>
#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"


class AutoTurnGyro: public CommandBase
{
public:
	// For turnAngle is passed into move parameters as "distance"
	//  and "speed" is the turning speed, but it's NOT degrees per sec.,
	//  but is the value we pass into the TankDrive().
	//  So a speed of 1.0 means it would turn at 100% speed!
	AutoTurnGyro( double turnAngle, double speed );
	AutoTurnGyro( sMovementParamHelper moveParams );
	virtual ~AutoTurnGyro();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:

	// This has all the 'brains' of the movement
	sMovementParamHelper m_MovementState;


	// Can't call c'tor
	AutoTurnGyro();

};



#endif /* _AutoTurnGyro_HG_ */
