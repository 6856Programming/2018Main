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

// NOTE: There was some talk of having pre-set positions for the lift.
//       These methods would move the lift to those positions.
//       For now, we aren't going to do that (and there's a top and bottom switch, anyway)
//	void Bottom(); //Wade - Lift will be in lowest position
//	void SwitchHeight(); //Wade - Lift will assume height of 2 feet from floor for switch placement
//	void ScaleLowHeight(); //Wade - Lift will assume height of 5 feet from floor for scale placement if scale is in low position
//	void ScaleNeutral(); //Wade - Lift will assume height of 5.8 feet from floor for scale placement at neutral level
//	void Highest(); //Wade - Lift will assume highest height position for scale placement and the rung climb
//	void BottomPosition(void);
//	void TopPosition(void);

	// This really isn't supposed to be called, but is in here
	//	so that we can have direct control of the motor...
	void DEBUG_SetMotorSpeed(double speed);



//	bool getBottomLimitSwitch(void);
//	bool getTopLimitSwitchStatus(void);

private:
//	frc::DigitalInput* m_pLimitSwitchBottom;	// On DIO pins 2 & 3
//	frc::DigitalInput*m_pLimitSwitchTop;


	can::WPI_TalonSRX* m_pLiftMotor;



};

#endif /* SRC_SUBSYSTEMS_LIFTMAST_H_ */

