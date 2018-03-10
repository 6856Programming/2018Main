#ifndef SRC_SUBSYSTEMS_FORKWHEELS_H_
#define SRC_SUBSYSTEMS_FORKWHEELS_H_

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include <DigitalInput.h>
#include <AnalogPotentiometer.h>
#include <Commands/Subsystem.h>
#include <Commands/PIDSubsystem.h>
#include "../RobotMap.h"

class ForkWheels : public frc::Subsystem
{
public:
	ForkWheels();
	~ForkWheels();

	void InitDefaultCommand() override;

	void WheelsIn();

	void WheelsOut();

	void Stop();

private:
	frc::DigitalInput*  m_pContact;

	//Looking at code from DriveTrain.h
	can::WPI_TalonSRX* pLeftWheelMotor;
	can::WPI_TalonSRX* pRightWheelMotor;

};




#endif /* SRC_SUBSYSTEMS_FORKWHEELS_H_ */
