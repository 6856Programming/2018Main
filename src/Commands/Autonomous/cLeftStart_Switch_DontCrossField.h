#ifndef _cLeftStart_Switch_DontCrossField_HG_
#define _cLeftStart_Switch_DontCrossField_HG_

#include <Commands/CommandGroup.h>

// Start from LEFT side.
// Go for LEFT SWITCH (DON'T cross field)
// Drop on switch if it's correct side,
//  otherwise, just drive forward

class cLeftStart_Switch_DontCrossField : public frc::CommandGroup
{
public:
	cLeftStart_Switch_DontCrossField();
};

#endif // cLeftStart_Switch_DontCrossField

