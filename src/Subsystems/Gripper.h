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

	void OpenCompletely(void); //Madi- The motor will open the forks

	void CloseCompletely(void); //Madi - The motor will close the forks


	void SetIntakeSpeed(double speed);

	// This will run the intake for the desired speed.
	// Each time it's called, the timer resets.
	void PulseIntake(double speed, double time);

	bool isClawOpenLimitSwitchPushed(void);
	bool isClawClosedLimitSwitchPushed(void);
	bool areEitherClawLimitSwitchesPushed(void);


	// This MUST be called repeatedly by whatever command is using this.
	// (i.e. call this in the command Execute() or IsFinished() methods)
	// +++++++++++++++++++ WARNING +++++++++++++++++++
	// If you DON'T call this, the limit switches and pulsed
	// mode operation WON'T WORK.
	void UpdateState(void);

private:

	enum eClawState
	{
		IS_IDLE,
		IS_OPENNING,
		IS_CLOSING
	};
	double m_ClawMovementSpeed;
	eClawState m_CurrentClawState;

	// Limit switches on the "claw" portion
	frc::DigitalInput* m_pClawOpenLimitSwitch;		// On Rio PID pins, number 0 and 1
	frc::DigitalInput* m_pClawClosedLimitSwitch;

	// Motor to open and close the "claw"
	can::WPI_TalonSRX* m_pClawMotor;

	// Fail-safe timer in case the limit switches fail
	frc::Timer* m_pClawMotorWatchDogTimer;




	// Motors for the speed of the star shaped rubber wheels
	can::WPI_TalonSRX* m_pLeftIntakeMotor;
	can::WPI_TalonSRX* m_pRightIntakeMotor;

	// "Pulse" timer for the intake motors
	// (i.e. they will run for this length of time, then stop)
	frc::Timer* m_pPulsedIntakeCountdownTimer;
	// The speed the intake will go when in pulsed mode
	double m_PulsedIntakeSpeed;
	double m_PulsedIntakePulseTimeInSeconds;
	bool m_bPulsedIntakeModeOn;




//  Gripper now electric, now, so no compressor
//	void CompressorOn(void);					// public
//	void CompressorOff(void);					// public
//	frc::DoubleSolenoid* m_pGripperSolenoid;	// private
//	Compressor* m_pCompressor;					// private



};

#endif /* SRC_SUBSYSTEMS_GRIPPER_H_ */



