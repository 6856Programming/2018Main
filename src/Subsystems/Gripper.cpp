#include "Subsystems/Gripper.h"
#include "../Commands/GripperControl.h"


Gripper::Gripper() : frc::Subsystem("Gripper")
{

//	this->m_pGripperSolenoid = new frc::DoubleSolenoid(PNEUMATIC_CONTROL_FORWARD_CHANNEL,
//	                                                   PNEUMATIC_CONTROL_REVERSE_CHANNEL);
//	this->m_pCompressor = new Compressor(COMPRESSOR_ID);

	this->m_pLeftIntakeMotor = new can::WPI_TalonSRX(GRIPPER_INTAKE_LEFT_MOTOR_ID);
	this->m_pRightIntakeMotor = new can::WPI_TalonSRX(GRIPPER_INTAKE_RIGHT_MOTOR_ID);

	this->m_pClawMotor = new can::WPI_TalonSRX(GRIPPER_CLAW_MOTOR_ID);

	this->m_pClawOpenLimitSwitch = new frc::DigitalInput(GRIPPER_LIMIT_OPEN_DIO_ID);		// On Rio PID pins, number 0 to ??
	this->m_pClawClosedLimitSwitch = new frc::DigitalInput(GRIPPER_LIMIT_CLOSED_DIO_ID);

	this->m_pClawMotorWatchDogTimer = new frc::Timer();

	return;
}

bool Gripper::getGripperOpenLimitSwitchStatus(void)
{
	// Are NO, so invert this
	return ( ! this->m_pClawOpenLimitSwitch->Get() );
}

bool Gripper::getGripperClosedLimitSwitchStatus(void)
{
	// Are NO, so invert this
	return ( ! this->m_pClawClosedLimitSwitch->Get() );
}


Gripper::~Gripper()
{
	delete this->m_pLeftIntakeMotor;
	delete this->m_pRightIntakeMotor;
	delete this->m_pClawMotor;
	delete this->m_pClawMotorWatchDogTimer;

	return;
}



void Gripper::InitDefaultCommand()
{
	SetDefaultCommand(new GripperControl());

	return;
}

void Gripper::OpenCompletely(void) //Solenoid is OFF, cylinder is in retracted position
{
	std::cout << "Gripper::Open()" << std::endl;

	//this->m_pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);

	return;
}

void Gripper::CloseCompletely(void) //Solenoid is ON, cylinder is in extended position
{
	std::cout << "Gripper::Close()" << std::endl;

	//this->m_pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);

	return;
}

// Gripper claw now electric, so no need for compressor control
//void Gripper::CompressorOn(void)
//{
//	std::cout << "Compressor on" << std::endl;
//	this->m_pCompressor->SetClosedLoopControl(true);
//	return;
//}
//
//void Gripper::CompressorOff(void)
//{
//	std::cout << "Compressor off" << std::endl;
//	this->m_pCompressor->SetClosedLoopControl(false);
//	return;
//}
