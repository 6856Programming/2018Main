#include "DebugTalonSRXTester.h"

#include "../RobotMap.h"

#include <iostream>

/**
 *		THIS IS NOT REALLY TO BE USED ON THE ACTUAL ROBOT.
 *		IT WAS JUST HERE TO QUICKLY TEST THE TALON MOTOR CONTROLLERS.
 */

DebugTalonSRXTester::DebugTalonSRXTester()
{
	std::cout << "[DebugTalonSRXTester] Constructed" << std::endl;

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pDriveTrain);
	}
	else
	{
		std::cout << "[DebugTalonSRXTester] driveTrain is null!" << std::endl;
	}

	this->m_selectedTalonID = 1;

	return;
}


void DebugTalonSRXTester::Initialize()
{
	std::cout << "[DebugTalonSRXTester] Initialized" << std::endl;

	for ( int index = 0; index != DebugTalonSRXTester::NUMBEROFTALONS; index++ )
	{
		// Create a talon with this PID
		std::cout << "Attempting to create Talon at ID: " << index << "..." << std::endl;
		this->m_pMotors[index] = new can::WPI_TalonSRX(index);
	}



	return;
}

unsigned int DebugTalonSRXTester::PickNextTalon(void)
{
	this->m_selectedTalonID++;
	if ( this->m_selectedTalonID > DebugTalonSRXTester::NUMBEROFTALONS )
	{
		this->m_selectedTalonID = 0;
	}
	return this->m_selectedTalonID;
}


unsigned int DebugTalonSRXTester::PickPreviousTalon(void)
{
	if ( this->m_selectedTalonID == 0 )
	{
		this->m_selectedTalonID = DebugTalonSRXTester::NUMBEROFTALONS;
	}
	else
	{
		this->m_selectedTalonID--;
	}
	return this->m_selectedTalonID;
}


unsigned int DebugTalonSRXTester::PickSpecificTalon(unsigned int talonID)
{
	if ( talonID > DebugTalonSRXTester::NUMBEROFTALONS )
	{
		talonID = DebugTalonSRXTester::NUMBEROFTALONS;
	}
	this->m_selectedTalonID = talonID;
	return this->m_selectedTalonID;
}


unsigned int DebugTalonSRXTester::GetSelectedTalonID(void)
{
	return this->m_selectedTalonID;
}


void DebugTalonSRXTester::Execute()
{
	::SmartDashboard::PutNumber("Selected TalonID:", this->m_selectedTalonID);
	::SmartDashboard::PutString("Y+A = Select Talon", "Right Joy for +ve, -ve power");

	frc::XboxController* pJoyDriver = CommandBase::pOI->GetJoystickDrive();

	if ( pJoyDriver->GetAButtonPressed() )
	{
		this->PickPreviousTalon();
	}
	else if ( pJoyDriver->GetYButtonReleased() )
	{
		this->PickNextTalon();
	}

	double motorPower = pJoyDriver->GetX(XboxController::kRightHand);

	const double POWERRATIO = 1.0;

	motorPower *= POWERRATIO;

	::SmartDashboard::PutNumber("Talon power:", motorPower);

	this->m_pMotors[this->m_selectedTalonID]->Set(motorPower);


	return;
}


bool DebugTalonSRXTester::IsFinished()
{
	return false;
}


void DebugTalonSRXTester::End()
{
	return;
}


void DebugTalonSRXTester::Interrupted()
{
	return;
}


