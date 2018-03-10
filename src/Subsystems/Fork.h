#ifndef SRC_SUBSYSTEMS_FORK_H_
#define SRC_SUBSYSTEMS_FORK_H_
/*
 * Fork.h
 *
 *  Created on: Feb 18, 2018
 *      Author: Robotics
 */

//One of these should supply can::
#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include <DigitalInput.h>
#include <Spark.h>
#include "../RobotMap.h"

/**
 * The claw subsystem is a simple system with a motor for opening and closing.
 * If using stronger motors, you should probably use a sensor so that the
 * motors don't stall.
 */
class Fork : public frc::Subsystem
{
public:
	Fork();

	~Fork();

	void InitDefaultCommand() override;

	void Open(); //Madi- The motor will open the forks

	void Close(); //Madi - The motor will close the forks

	void Stop(); //Stolen Code- Makes the forks stop moving


	//bool IsGripping(); //This is Stolen but sensors are used to test if the grips are tight enough


private:
	frc::Spark m_motor{7}; //I have no clue what these are for - MADI
	frc::DigitalInput m_contact{5};

	//Looking at code from DriveTrain.h
	can::WPI_TalonSRX* pForkMotor;


};



#endif /* SRC_SUBSYSTEMS_FORK_H_ */
