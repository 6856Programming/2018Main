#include "Subsystems/Gripper.h"
#include "../Commands/GripperControl.h"

//..\src\Subsystems\PneumaticsControlModule.cpp:10:50: error: no matching function for call to 'frc::Subsystem::Subsystem()'
// PneumaticsControlModule::PneumaticsControlModule() {

Gripper::Gripper() : frc::Subsystem("Gripper")
{
	// TODO Auto-generated constructor stub

	this->m_pGripperSolenoid = new frc::DoubleSolenoid(PNEUMATIC_CONTROL_FORWARD_CHANNEL,
	                                                   PNEUMATIC_CONTROL_REVERSE_CHANNEL);


	this->m_pCompressor = new Compressor(COMPRESSOR_ID);

	this->m_pLeftGripperMotor = new can::WPI_TalonSRX(GRIPPER_WHEEL_LEFT_MOTOR_ID);
	this->m_pRightGripperMotor = new can::WPI_TalonSRX(GRIPPER_WHEEL_RIGHT_MOTOR_ID);

	this->m_pContact = new frc::DigitalInput(GRIPPER_DIGITAL_INPUT_1);

	return;
}

Gripper::~Gripper()
{
	// TODO Auto-generated destructor stub

	return;
}

void Gripper::CompressorOn(void)
{
	std::cout << "Compressor on" << std::endl;
	this->m_pCompressor->SetClosedLoopControl(true);
	return;
}

void Gripper::CompressorOff(void)
{
	std::cout << "Compressor off" << std::endl;
	this->m_pCompressor->SetClosedLoopControl(false);
	return;
}

void Gripper::InitDefaultCommand()
{
	SetDefaultCommand(new GripperControl());

	return;
}

void Gripper::Open(void) //Solenoid is OFF, cylinder is in retracted position
{
	std::cout << "Gripper::Open()" << std::endl;

	this->m_pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);

	return;
}

void Gripper::Close(void) //Solenoid is ON, cylinder is in extended position
{
	std::cout << "Gripper::Close()" << std::endl;

	this->m_pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);

	return;
}
