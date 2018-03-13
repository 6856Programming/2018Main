/*
 * LiftMast.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: Robotics - Wade Wilson
 */
#include "LiftMast.h"
#include "../Commands/LiftControl.h"
#include <iostream>

LiftMast::LiftMast() : frc::Subsystem("LiftMast")
{
	// TODO Auto-generated constructor stub
	std::cout << "[LiftMast] constructed" << std::endl;

	this->m_pLiftMotor = new can::WPI_TalonSRX(LIFTER_WINCH_MOTOR_ID);


	this->m_pContactSwitch = new frc::DigitalInput(LIFT_MAST_CONTACT_SWITCH);

	return;
}

void LiftMast::DEBUG_SetMotorSpeed(double speed)
{
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

//Wade - Lift will be in lowest position
void LiftMast::Bottom()
{

	return;
}

//Wade - Lift will assume height of 2 feet from floor for switch placement
void LiftMast::SwitchHeight()
{

	return;
}

//Wade - Lift will assume height of 5 feet from floor for scale placement if scale is in low position
void LiftMast::ScaleLowHeight()
{

	return;
}

//Wade - Lift will assume height of 5.8 feet from floor for scale placement at neutral level
void LiftMast::ScaleNeutral()
{

	return;
}

 //Wade - Lift will assume highest height position for scale placement and the rung climb
void LiftMast::Highest()
{

	return;
}













