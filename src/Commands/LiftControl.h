#ifndef SRC_COMMANDS_LIFTCONTROL_H_
#define SRC_COMMANDS_LIFTCONTROL_H_


#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"

/**
 *
 */

class LiftControl: public CommandBase
{
public:
	LiftControl();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;


private:
};


#endif /* SRC_COMMANDS_LIFTCONTROL_H_ */
