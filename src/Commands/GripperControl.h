#ifndef SRC_COMMANDS_GRIPPERCONTROL_H_
#define SRC_COMMANDS_GRIPPERCONTROL_H_

#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */

class GripperControl: public CommandBase
{
public:
	GripperControl();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;


private:
};



#endif /* SRC_COMMANDS_GRIPPERCONTROL_H_ */
