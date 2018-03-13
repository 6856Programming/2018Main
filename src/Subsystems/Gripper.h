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

	void ClawOpen(void); //Madi- The motor will open the forks
	void ClawClose(void); //Madi - The motor will close the forks
	void ClawStop(void);	// Turns motor off

	void SetIntakeSpeed(double speed);

	void Reset(void);

//	void CompressorOn(void);
//	void CompressorOff(void);


private:
//	frc::DoubleSolenoid* m_pGripperSolenoid;   //i am not sure about the declaration of this command

//	Compressor* m_pCompressor;

	frc::DigitalInput*  m_pContact;		// On Rio PID pins, number 0 to ??

	//Looking at code from DriveTrain.h
	can::WPI_TalonSRX* m_pLeftIntakeMotor;
	can::WPI_TalonSRX* m_pRightIntakeMotor;

	can::WPI_TalonSRX* m_pClawMotor;
};

#endif /* SRC_SUBSYSTEMS_GRIPPER_H_ */



