/*
 * Fork.cpp
 *
 *  Created on: Feb 18, 2018
 *      Author: Robotics
 */

//One of these should supply can::
#include <WPILib.h>
//#include <Commands/Subsystems.h>
#include <ctre/Phoenix.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>

#include "Fork.h"

//const int DRIVETRAIN_GRIPPER_WHEEL_RIGHT_MOTOR_ID = 6; //Madi- Source RobotMap.h
//const int DRIVETRAIN_GRIPPER_WHEEL_LEFT_MOTOR_ID = 9;
	//Looking at code from DriveTrain.h
	//can::WPI_TalonSRX* pLeftWheelMotor;
	//can::WPI_TalonSRX* pRightWheelMotor;



	//Madi - This shows it on LiveWindow
Fork::Fork() : frc::Subsystem("Fork")
{
	//AddChild("Motor", m_motor); //Original Code

	this->pForkMotor = new can::WPI_TalonSRX(DRIVETRAIN_GRIPPER_ARMS_MOTOR_ID);

}

Fork::~Fork()
{
	delete this->pForkMotor;
}


void Fork::InitDefaultCommand()
{
//We will eventually need to push the forks out when init
	this->pForkMotor->Set(0);
}

//Madi - All below is stolen from the Ex. Claw.cpp with "Claw" changed for "Fork"
void Fork::Open()
{
	this->pForkMotor->Set(-0.1);
	//Madi - We need to make a limit on opening (and closing)
}

void Fork::Close()
{

	this->pForkMotor->Set(0.1);
}

void Fork::Stop()
{
	this->pForkMotor->Set(0);

}

//Madi - We would use this if we had grip sensors
//bool Fork::IsGripping() {
//	return m_contact.Get();
//}


