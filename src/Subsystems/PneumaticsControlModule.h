#ifndef SRC_SUBSYSTEMS_PNEUMATICSCONTROLMODULE_H_
#define SRC_SUBSYSTEMS_PNEUMATICSCONTROLMODULE_H_

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

class PneumaticsControlModule : public frc::Subsystem
{
public:
	PneumaticsControlModule();				//constructer for pneumatic controller
	virtual ~PneumaticsControlModule();		//destructer for pneumatic controller

	void InitDefaultCommand() override;

	void CylinderRetract(void); //Solenoid is OFF, cylinder is in retracted position

	void CylinderExtend(void); //Solenoid is ON, cylinder is in extended position

	void CompressorOn(void);
	void CompressorOff(void);


private:
	frc::DoubleSolenoid* m_pGripperSolenoid;   //i am not sure about the declaration of this command

	Compressor* m_pCompressor;


};

#endif /* SRC_SUBSYSTEMS_PNEUMATICSCONTROLMODULE_H_ */



