#include "ForkWheels.h"

ForkWheels::ForkWheels() : frc::Subsystem("ForkWheels")
{
	this->m_pContact = new frc::DigitalInput(FORK_WHEELS_CONTACT_INPUT);

	//Looking at code from DriveTrain.h
	this->pLeftWheelMotor = new can::WPI_TalonSRX(FORKED_WHEEL_LEFT_MOTOR_ID);
	this->pRightWheelMotor = new can::WPI_TalonSRX(FORKED_WHEEL_RIGHT_MOTOR_ID);

	return;
}

ForkWheels::~ForkWheels()
{

	return;
}

void ForkWheels::InitDefaultCommand()
{

	return;
}

void ForkWheels::WheelsIn()
{

	return;
}

void ForkWheels::WheelsOut()
{

	return;
}

void ForkWheels::Stop()
{

	return;
}
