#ifndef _AutoDriveEncoder_HG_
#define _AutoDriveEncoder_HG_

#include <Commands/sMovementParamHelper.h>
#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"


class AutoDriveEncoder: public CommandBase
{
public:

	AutoDriveEncoder( double inchesToDrive, double speed, bool bUseGyroToDriveStraight = true );
	AutoDriveEncoder( sMovementParamHelper moveParams, bool bUseGyroToDriveStraight = true );
	virtual ~AutoDriveEncoder();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:

	// This has all the 'brains' of the movement
	sMovementParamHelper m_MovementState;

	bool m_bUseGyroToDriveStraight;

	// Can't call c'tor
	AutoDriveEncoder();

};


#endif /* _AutoDriveEncoder_HG_ */




