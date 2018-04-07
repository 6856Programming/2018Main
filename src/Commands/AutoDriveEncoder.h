#ifndef _AutoDriveEncoder_HG_
#define _AutoDriveEncoder_HG_

#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"
#include "MyAutoCommand.h"

/**
 *
 */

class AutoDriveEncoder: public CommandBase
{
public:
	AutoDriveEncoder(double inchesToDrive, double speed);
	virtual ~AutoDriveEncoder();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;

private:

	double m_speed;
	double m_inchesToDrive;

	// Can't call c'tor
	AutoDriveEncoder();

};


#endif /* _AutoDriveEncoder_HG_ */




