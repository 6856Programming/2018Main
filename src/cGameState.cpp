#include "cGameState.h"
#include <WPILib.h>

cGameState::cGameState()
{
	//
	this->m_driverStationPosition = cGameState::UNKNOWN;		// Left, Centre, or Right

	this->m_nearSwitchPosition = cGameState::UNKNOWN;			// Left or Right
	this->m_scalePosition = cGameState::UNKNOWN;				// Left or Right
	this->m_farSwitchPosition = cGameState::UNKNOWN;			// Left or Right

	return;
}


// Will populate the positions based on init game state
// SHOULD BE CALLED ON AUTOINIT
void cGameState::ProcessGameStartUpState(void)
{
//	int _RP = 10; // 10 = Left, 20 = Center, 30 = Right
//	int _SP =  1;  // 1 = Left, 2 = Right

	switch ( frc::DriverStation::GetInstance().GetLocation() )
	{
	case 1:
		this->m_driverStationPosition = cGameState::LEFT;
		break;
	case 2:
		this->m_driverStationPosition = cGameState::CENTRE;
		break;
	case 3:
		this->m_driverStationPosition = cGameState::RIGHT;
	}

	std::string gameItemsString = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	// Near switch position?
	if ( gameItemsString[0] == 'L' )
	{
		this->m_nearSwitchPosition = cGameState::LEFT;
	}
	else if ( gameItemsString[0] == 'R' )
	{
		this->m_nearSwitchPosition = cGameState::RIGHT;
	}

	// Scale position?
	if ( gameItemsString[1] == 'L' )
	{
		this->m_scalePosition = cGameState::LEFT;
	}
	else if ( gameItemsString[1] == 'R' )
	{
		this->m_scalePosition = cGameState::RIGHT;
	}

	// Far switch position
	if ( gameItemsString[2] == 'L' )
	{
		this->m_farSwitchPosition = cGameState::LEFT;
	}
	else if ( gameItemsString[2] == 'R' )
	{
		this->m_farSwitchPosition = cGameState::RIGHT;
	}


	return;
}

cGameState::ePositions cGameState::getDirverStationPosition(void)
{
	return this->m_driverStationPosition;
}

cGameState::ePositions cGameState::getNearSwitchPosition(void)
{
	return this->m_nearSwitchPosition;
}

cGameState::ePositions cGameState::getScalePosition(void)
{
	return this->m_scalePosition;
}

cGameState::ePositions cGameState::getFarSwitchPositions(void)
{
	return this->m_farSwitchPosition;
}







