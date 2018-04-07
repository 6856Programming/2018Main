#include "Robot.h"

// Will place the default smart dashboard settings
void Robot::InitSmartDashboardDefaults(void)
{


	::SmartDashboard::PutNumber("AUTO: seconds to wait to start driving", DEFAULT_WAIT_TO_START_TIME);
	::SmartDashboard::PutNumber("AUTO: drive speed", DEFAULT_DRIVE_SPEED);
	::SmartDashboard::PutNumber("AUTO: seconds to drive", DEFAULT_DRIVE_FORWARD_TIME);


	return;
}
