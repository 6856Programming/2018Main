/*
 * GripperHold.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: Robotics
 */

#include "GripperHold.h"


GripperHold::GripperHold() : frc::Subsystem("GripperHold")
{
	// TODO Auto-generated constructor stub

	this->m_pLeftGripperMotor = new can::WPI_TalonSRX(GRIPPER_WHEEL_LEFT_MOTOR_ID);
	this->m_pRightGripperMotor = new can::WPI_TalonSRX(GRIPPER_WHEEL_RIGHT_MOTOR_ID);

	this->m_pContact = new frc::DigitalInput(GRIPPER_DIGITAL_INPUT_1);

	return;
}

GripperHold::~GripperHold()
{
	// TODO Auto-generated destructor stub
}

void GripperHold::InitDefaultCommand()
{
	return;
}

void GripperHold::Extend() //Wade - Solenoid is energized, extending cylinder and raising gripper.
{

	return;
}

void GripperHold::Retract() //Wade - Solenoid is de-energized, retracting cyclinder and lowering gripper.
{
	return;
}
