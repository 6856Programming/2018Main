#ifndef _cGameState_HG_
#define _cGameState_HG_

// Gets the game state

#include <string>

class cGameState
{
public:
	cGameState();
// These are the positions of the driver stations, switch, and scale
	enum ePositions
	{
		LEFT, CENTRE, RIGHT, UNKNOWN
	};
private:
	ePositions m_driverStationPosition;		// Left, Centre, or Right
	// Note: the FMS sends sides based on aliance colour
	// So these are 'our' positions, in other words...
	ePositions m_nearSwitchPosition;			// Left or Right
	ePositions m_scalePosition;				// Left or Right
	ePositions m_farSwitchPosition;			// Left or Right
public:
	// Will populate the positions based on init game state
	void ProcessGameStartUpState(void);

	ePositions getDirverStationPosition(void);
	ePositions getNearSwitchPosition(void);
	ePositions getScalePosition(void);
	ePositions getFarSwitchPositions(void);

	std::string DecodePositionEnumString( ePositions position );
};



#endif /* _iRobot_GameState_HG_ */
