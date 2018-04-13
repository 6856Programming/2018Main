#ifndef _cRightStart_Scale_DontCrossField_HG_
#define _cRightStart_Scale_DontCrossField_HG_

#include <Commands/CommandGroup.h>

// Start from RIGHT side.
// Go for RIGHT SCALE (DON'T cross field)
// Drop on switch if it's correct side,
//  otherwise, just drive forward

class cRightStart_Scale_DontCrossField : public frc::CommandGroup
{
public:
	cRightStart_Scale_DontCrossField();
};

#endif // cRightStart_Switch_DontCrossField

