#ifndef _cRightStart_Switch_DontCrossField_HG_
#define _cRightStart_Switch_DontCrossField_HG_

#include <Commands/CommandGroup.h>

// Start from RIGHT side.
// Go for RIGHT SWITCH (DON'T cross field)
// Drop on switch if it's correct side,
//  otherwise, just drive forward

class cRightStart_Switch_DontCrossField : public frc::CommandGroup
{
public:
	cRightStart_Switch_DontCrossField();
};

#endif // cRightStart_Switch_DontCrossField

