#ifndef SRC_SUBSYSTEMS_LIFTMAST_H_
#define SRC_SUBSYSTEMS_LIFTMAST_H_
/*
 * LiftMast.h
 *
 *  Created on: Feb 24, 2018
 *      Author: Robotics
 */


#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include <DigitalInput.h>
#include <Spark.h>
#include "../RobotMap.h"

/**
 * The lift mechanism consists of five pre-set raise positions, which will allow
 * for operator to rapidly set the gripper mechanism to pre-determined heights.
 */
class LiftMast : public frc::Subsystem
{
public:
	LiftMast();

	~LiftMast();

	void InitDefaultCommand() override;

	void Bottom(); //Wade - Lift will be in lowest position

	void SwitchHeight(); //Wade - Lift will assume height of 2 feet from floor for switch placement

	void ScaleLowHeight(); //Wade - Lift will assume height of 5 feet from floor for scale placement if scale is in low position

	void ScaleNeutral(); //Wade - Lift will assume height of 5.8 feet from floor for scale placement at neutral level

	void Highest(); //Wade - Lift will assume highest height position for scale placement and the rung climb



private:
	frc::DigitalInput* m_pContactSwitch;

	//Looking at code from DriveTrain.h
	can::WPI_TalonSRX* m_pLiftMotor;



};

#endif /* SRC_SUBSYSTEMS_LIFTMAST_H_ */

