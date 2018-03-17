#ifndef SRC_SUBSYSTEMS_GRIPPER_H_
#define SRC_SUBSYSTEMS_GRIPPER_H_

/*
 * PneumaticsControlModule.h
 *
 *  Created on: Feb 25, 2018
 *      Author: Robotics - Hand-Grenade Wade 'cause I'm just that Explosive
*/

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include <DigitalInput.h>
#include "../RobotMap.h"

class Gripper : public frc::Subsystem
{
public:
	Gripper();				//constructer for pneumatic controller
	virtual ~Gripper();		//destructer for pneumatic controller

	void InitDefaultCommand() override;

	void Open(void); //Madi- The motor will open the forks

	void Close(void); //Madi - The motor will close the forks


	void SetIntakeSpeed(double speed);

	// This will run the intake for the desired speed.
	// Each time it's called, the timer resets.
	void PulseIntake(double speed, double time);

	bool getGripperOpenLimitSwitchStatus(void);
	bool getGripperClosedLimitSwitchStatus(void);

private:

	// Limit switches on the "claw" portion
	frc::DigitalInput* m_pClawOpenLimitSwitch;		// On Rio PID pins, number 0 and 1
	frc::DigitalInput* m_pClawClosedLimitSwitch;

	// Fail-safe timer in case the limit switches fail
	frc::Timer* m_pClawMotorWatchDogTimer;

	// Motor to open and close the "claw"
	can::WPI_TalonSRX* m_pClawMotor;


	// Motors for the speed of the star shaped rubber wheels
	can::WPI_TalonSRX* m_pLeftIntakeMotor;
	can::WPI_TalonSRX* m_pRightIntakeMotor;

	// "Pulse" timer for the intake motors
	// (i.e. they will run for this length of time, then stop)
	frc::Timer* m_pIntakeMotorPusledModeCountdownTimer;




//  Gripper now electric, now, so no compressor
//	void CompressorOn(void);					// public
//	void CompressorOff(void);					// public
//	frc::DoubleSolenoid* m_pGripperSolenoid;	// private
//	Compressor* m_pCompressor;					// private



};

#endif /* SRC_SUBSYSTEMS_GRIPPER_H_ */



