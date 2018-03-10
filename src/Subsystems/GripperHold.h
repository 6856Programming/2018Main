#ifndef SRC_SUBSYSTEMS_GRIPPERHOLD_H_
#define SRC_SUBSYSTEMS_GRIPPERHOLD_H_

/*
 * GripperHold.h
 *
 *  Created on: Feb 24, 2018
 *      Author: Robotics
 */

//Stolen Code, unknown use for the next 3 lines
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
 * The gripper assembly must be held within the confines of the robot at
 * the start of the match. A solenoid valve will extend a pneumatic
 * cylinder that will hold the gripper inside the frame until permitted to
 * lower it.
 */
class GripperHold : public frc::Subsystem
{
public:
	GripperHold();

	~GripperHold();

	void InitDefaultCommand() override;

	void Extend(); //Wade - Solenoid is energized, extending cylinder and raising gripper.

	void Retract(); //Wade - Solenoid is de-energized, retracting cyclinder and lowering gripper.



private:
	can::WPI_TalonSRX* m_pLeftGripperMotor;
	can::WPI_TalonSRX* m_pRightGripperMotor;
	frc::DigitalInput* m_pContact;

	//Looking at code from DriveTrain.h

};

#endif /* SRC_SUBSYSTEMS_GRIPPERHOLD_H_ */
