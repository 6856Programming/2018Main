#include "CompressorSystem.h"

CompressorSystem::CompressorSystem(int o,int f) : frc::Subsystem("CompressorSystem")
{
//	int ClosedLoopControl;

	this->m_pCompressor = new frc::Compressor(PNEUMATIC_CONTROL_MODULE_ID);

	return;
}


CompressorSystem::~CompressorSystem()
{

	return;
}


