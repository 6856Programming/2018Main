#include "Subsystems/Gripper.h"
#include "../Commands/GripperControl.h"

//..\src\Subsystems\PneumaticsControlModule.cpp:10:50: error: no matching function for call to 'frc::Subsystem::Subsystem()'
// PneumaticsControlModule::PneumaticsControlModule() {

Gripper::Gripper() : frc::Subsystem("Gripper")
{
	// TODO Auto-generated constructor stub

//	this->m_pGripperSolenoid = new frc::DoubleSolenoid(PNEUMATIC_CONTROL_FORWARD_CHANNEL,
//	                                                   PNEUMATIC_CONTROL_REVERSE_CHANNEL);


//	this->m_pCompressor = new Compressor(COMPRESSOR_ID);

	this->m_pLeftIntakeMotor = new can::WPI_TalonSRX(GRIPPER_LEFT_INTAKE_MOTOR_ID);
	this->m_pRightIntakeMotor = new can::WPI_TalonSRX(GRIPPER_RIGHT_INTAKE_MOTOR_ID);


	this->m_pClawMotor = new can::WPI_TalonSRX(GRIPPER_CLAW_MOTOR_ID);


	this->m_pContact = new frc::DigitalInput(GRIPPER_DIGITAL_INPUT_1);

	return;
}

Gripper::~Gripper()
{
	// TODO Auto-generated destructor stub

	return;
}

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

void Gripper::InitDefaultCommand()
{
	SetDefaultCommand(new GripperControl());

	return;
}

void Gripper::SetIntakeSpeed(double speed)
{
	double leftSpeed = speed * GRIPPER_RIGHT_INTAKE_MOTOR_SPEED_RATIO;
	double rightSpeed = speed * GRIPPER_LEFT_INTAKE_MOTOR_SPEED_RATIO;

	::SmartDashboard::PutNumber("Gripper::L Intake Speed", leftSpeed);
	::SmartDashboard::PutNumber("Gripper::R Intake Speed", rightSpeed);

	this->m_pLeftIntakeMotor->Set(leftSpeed);
	this->m_pRightIntakeMotor->Set(rightSpeed);

	return;
}

void Gripper::ClawOpen(void) //Solenoid is OFF, cylinder is in retracted position
{
	//std::cout << "Gripper::Open()" << std::endl;
	::SmartDashboard::PutString("Gripper State:", "Open");

	this->m_pClawMotor->Set( GRIPPER_CLAW_MOTOR_MAX_SPEED );

//	this->m_pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);

	return;
}

void Gripper::ClawClose(void) //Solenoid is ON, cylinder is in extended position
{
	//std::cout << "Gripper::Close()" << std::endl;
	::SmartDashboard::PutString("Gripper State:", "Close");

	this->m_pClawMotor->Set( -GRIPPER_CLAW_MOTOR_MAX_SPEED );

//	this->m_pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);


	return;
}

void Gripper::ClawStop(void)	// Turns motor off
{
	//std::cout << "Gripper::Close()" << std::endl;
	::SmartDashboard::PutString("Gripper State:", "OFF");

	this->m_pClawMotor->Set(0.0);

	return;
}

void Gripper::Reset(void)
{
	CommandBase::pGripper->ClawStop();
	CommandBase::pGripper->SetIntakeSpeed(0.0);

	return;
}


