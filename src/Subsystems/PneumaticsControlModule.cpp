#include "PneumaticsControlModule.h"
#include "../Commands/GripperControl.h"

//..\src\Subsystems\PneumaticsControlModule.cpp:10:50: error: no matching function for call to 'frc::Subsystem::Subsystem()'
// PneumaticsControlModule::PneumaticsControlModule() {

PneumaticsControlModule::PneumaticsControlModule() : frc::Subsystem("PneumaticsControlModule")
{
	// TODO Auto-generated constructor stub

	this->m_pGripperSolenoid = new frc::DoubleSolenoid(PNEUMATIC_CONTROL_FORWARD_CHANNEL,
	                                                   PNEUMATIC_CONTROL_REVERSE_CHANNEL);


	this->m_pCompressor = new Compressor(COMPRESSOR_ID);


	return;
}

PneumaticsControlModule::~PneumaticsControlModule()
{
	// TODO Auto-generated destructor stub

	return;
}

void PneumaticsControlModule::CompressorOn(void)
{
	std::cout << "Compressor on" << std::endl;
	this->m_pCompressor->SetClosedLoopControl(true);
	return;
}

void PneumaticsControlModule::CompressorOff(void)
{
	std::cout << "Compressor off" << std::endl;
	this->m_pCompressor->SetClosedLoopControl(false);
	return;
}

void PneumaticsControlModule::InitDefaultCommand()
{
	SetDefaultCommand(new GripperControl());

	return;
}

void PneumaticsControlModule::CylinderRetract(void) //Solenoid is OFF, cylinder is in retracted position
{
	std::cout << "CylinderRetract()" << std::endl;

	this->m_pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);

	return;
}

void PneumaticsControlModule::CylinderExtend(void) //Solenoid is ON, cylinder is in extended position
{
	std::cout << "CylinderExtend()" << std::endl;

	this->m_pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);

	return;
}
