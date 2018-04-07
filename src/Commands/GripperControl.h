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
	// This is used to decode the commands from the operator,
	//  so that there's a clear command, before executing.
	// (because the new gripper can rip the machine to bits...)
	enum eGripperCommand
	{
		OPEN_GRIPPER,
		CLOSE_GRIPPER,
		STOP_GRIPPER
	};

	// Checks the state of the joystick and returns a "good" command.
	// If there is ANY worries, it returns STOP_GRIPPER
	eGripperCommand m_DecodeOperatorGripperCommand(void);

};



#endif /* SRC_COMMANDS_GRIPPERCONTROL_H_ */
