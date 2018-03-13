#include "GripperControl.h"


#include "../RobotMap.h"

#include <iostream>


GripperControl::GripperControl()
{
	std::cout << "[GripperControl] Constructed" << std::endl;

	if (CommandBase::pDriveTrain != nullptr)
	{
		Requires(CommandBase::pGripper);
	}
	else
	{
		std::cout << "[GripperControl] driveTrain is null!" << std::endl;
	}

	this->m_pClawOffTimer = new frc::Timer();

	this->m_pClawOffTimer->Reset();
	this->m_pClawOffTimer->Stop();


	return;
}


void GripperControl::Initialize()
{
	std::cout << "[GripperControl] Initialized" << std::endl;


	return;
}





void GripperControl::Execute()
{
//	::SmartDashboard::PutNumber("Selected TalonID:", this->m_selectedTalonID);
//	::SmartDashboard::PutString("Y+A = Select Talon", "Right Joy for +ve, -ve power");

	frc::XboxController* pJoyDriver = CommandBase::pOI->GetJoystickDrive();

	if ( pJoyDriver->GetBumperPressed(frc::GenericHID::kLeftHand) )
	{
		//std::cout << "GripperControl::ClawOpen() called..." << std::endl;
		CommandBase::pGripper->ClawOpen();
		// Start timer
		this->m_pClawOffTimer->Reset();
		this->m_pClawOffTimer->Start();
	}
	else if ( pJoyDriver->GetBumperPressed(frc::GenericHID::kRightHand) )
	{
		//std::cout << "GripperControl::ClawClose() called..." << std::endl;
		CommandBase::pGripper->ClawClose();
		// Start timer
		this->m_pClawOffTimer->Reset();
		this->m_pClawOffTimer->Start();
	}

	// Check the timer to see if the gripper motor has run to long
	if ( this->m_pClawOffTimer->Get() >= GRIPPER_CLAW_SHUT_OFF_TIME )
	{
		std::cout << "Gripper: Claw timer timeout - turning off claw" << std::endl;
		this->m_pClawOffTimer->Stop();
		CommandBase::pGripper->ClawStop();
	}

//	std::cout << this->m_pClawOffTimer->Get() << std::endl;

	// For some reason, this will "pulse" the motor on and off with this code
//	else
//	{
//		//std::cout << "GripperControl::ClawStop() called..." << std::endl;
//		CommandBase::pGripper->ClawStop();
//	}

	double intakeSpeed = pJoyDriver->GetY(frc::GenericHID::kLeftHand);

	// Check for deadzone on joystick
	if ( fabs(intakeSpeed) < XBOX_DEADZONE_LEFT_JOY )
	{
		intakeSpeed = 0.0;
	}

	CommandBase::pGripper->SetIntakeSpeed( -intakeSpeed );



//	if ( pJoyDriver->GetXButtonReleased() )
//	{
//		std::cout << "GripperControl::CompressorsOn() called..." << std::endl;
//		CommandBase::pGripper->CompressorOn();
//	}
//	else if ( pJoyDriver->GetYButtonReleased() )
//	{
//		std::cout << "GripperControl::CompressorOff() called..." << std::endl;
//		CommandBase::pGripper->CompressorOff();
//	}



	return;
}


bool GripperControl::IsFinished()
{
	return false;
}


void GripperControl::End()
{
	return;
}


void GripperControl::Interrupted()
{
	return;
}


