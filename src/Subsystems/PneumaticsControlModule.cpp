/*
 * PneumaticsControlModule.cpp
 *
 *  Created on: Feb 25, 2018
 *      Author: Robotics
 */

#include "PneumaticsControlModule.h"

//..\src\Subsystems\PneumaticsControlModule.cpp:10:50: error: no matching function for call to 'frc::Subsystem::Subsystem()'
// PneumaticsControlModule::PneumaticsControlModule() {

PneumaticsControlModule::PneumaticsControlModule() : frc::Subsystem("PneumaticsControlModule")
{
	// TODO Auto-generated constructor stub

	return;
}

PneumaticsControlModule::~PneumaticsControlModule()
{
	// TODO Auto-generated destructor stub

	return;
}


void PneumaticsControlModule::InitDefaultCommand()
{

	return;
}

void PneumaticsControlModule::CylinderRetract(void) //Solenoid is OFF, cylinder is in retracted position
{

	return;
}

void PneumaticsControlModule::CylinderExtend(void) //Solenoid is ON, cylinder is in extended position
{

	return;
}
