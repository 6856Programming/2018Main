/*
 * LiftMast.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: Robotics - Wade Wilson
 */
#include "LiftMast.h"
#include "../Commands/LiftControl.h"
#include <iostream>

// Enable: button 6
// Up: 11
// Down: 10

LiftMast::LiftMast() : frc::Subsystem("LiftMast")
{
	// TODO Auto-generated constructor stub
	std::cout << "[LiftMast] constructed" << std::endl;

	this->m_pLiftMotor = new can::WPI_TalonSRX(LIFTER_MOTOR_ID);

	this->m_pLimitSwitchUpper = new frc::DigitalInput(LIFT_MAST_UPPER_LIMIT_SWITCH_READY_TO_SHOOT_SCALE_POSITION);

//	this->m_pLimitSwitchTop = new frc::DigitalInput(LIFT_MAST_UPPER_CONTACT_SWITCH);
//	this->m_pLimitSwitchBottom = new frc::DigitalInput(LIFT_MAST_LOWER_CONTACT_SWITCH);

	this->m_bMastIsBeingHold = false;

	return;
}

//bool LiftMast::getBottomLimitSwitch(void)
//{
//	return this->m_pLimitSwitchBottom->Get();
//}


bool LiftMast::isUpperLimitSwitchClosed(void)
{
	// Original state (from ditital switch):
	// - false = Open
	// - true = Closed
	return ! this->m_pLimitSwitchUpper->Get();
}
//

void LiftMast::DEBUG_SetMotorSpeed(double speed)
{
	// Disable mast lift hold (as it'e being set by something)
	this->m_bMastIsBeingHold = false;

	this->m_pLiftMotor->Set(speed);

	return;
}


LiftMast::~LiftMast()
{
	// TODO Auto-generated destructor stub

	return;
}

void LiftMast::InitDefaultCommand()
{
	SetDefaultCommand(new LiftControl());

	return;
}

void LiftMast::EnableMastHold(void)
{
	this->m_bMastIsBeingHold = true;

	this->m_pLiftMotor->Set(this->m_MastHoldPower);

	return;
}

void LiftMast::DisableMastHold(void)
{
	this->m_bMastIsBeingHold = false;

	this->m_pLiftMotor->Set(0.0);

	return;
}

void LiftMast::setMastHoldPower(double holdPowerSpeed) // 30% is default
{
	// Should not be negative
	if ( holdPowerSpeed < 0.0 )
	{
		this->m_MastHoldPower = this->m_DEFAULT_MAST_HOLD_POWER;
	}
	// Should not be GT 1.0
	if ( holdPowerSpeed > 1.0 )
	{
		this->m_MastHoldPower = 1.0;
	}

	this->m_MastHoldPower = holdPowerSpeed;

	return;
}

double LiftMast::getMastHoldPower(void)
{
	return this->m_MastHoldPower;
}



// NOTE: There was some talk of having pre-set positions for the lift.
//       These methods would move the lift to those positions.
//       For now, we aren't going to do that (and there's a top and bottom switch, anyway)
//
//Wade - Lift will be in lowest position
//void LiftMast::Bottom()
//{
//
//	return;
//}

//Wade - Lift will assume height of 2 feet from floor for switch placement
//void LiftMast::SwitchHeight()
//{
//
//	return;
//}

//Wade - Lift will assume height of 5 feet from floor for scale placement if scale is in low position
//void LiftMast::ScaleLowHeight()
//{
//
//	return;
//}

//Wade - Lift will assume height of 5.8 feet from floor for scale placement at neutral level
//void LiftMast::ScaleNeutral()
//{
//
//	return;
//}

//Wade - Lift will assume highest height position for scale placement and the rung climb
//void LiftMast::Highest()
//{
//
//	return;
//}













