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

	this->m_pClawOpenLimitSwitch = new frc::DigitalInput(GRIPPER_CLAW_LIMIT_OPEN_DIO_ID);		// On Rio PID pins, number 0 to ??
	this->m_pClawClosedLimitSwitch = new frc::DigitalInput(GRIPPER_CLAW_LIMIT_CLOSED_DIO_ID);

	this->m_pClawMotorWatchDogTimer = new frc::Timer();

	this->m_pPulsedIntakeCountdownTimer = new frc::Timer();

	this->m_PulsedIntakeSpeed = 0.0;
	this->m_PulsedIntakePulseTimeInSeconds = 0.0;
	this->m_bPulsedIntakeModeOn = false;


	this->m_ClawMovementSpeed = 0.0;
	this->m_CurrentClawState = Gripper::IS_IDLE;


	return;
}

bool Gripper::isClawOpenLimitSwitchPushed(void)
{
	// Are NO, so invert this
	return ( ! this->m_pClawOpenLimitSwitch->Get() );
}

bool Gripper::isClawClosedLimitSwitchPushed(void)
{
	// Are NO, so invert this
	return ( ! this->m_pClawClosedLimitSwitch->Get() );
}

bool Gripper::areEitherClawLimitSwitchesPushed(void)
{
	return ( this->isClawOpenLimitSwitchPushed() || this->isClawClosedLimitSwitchPushed() );
}


Gripper::~Gripper()
{
	delete this->m_pLeftIntakeMotor;
	delete this->m_pRightIntakeMotor;
	delete this->m_pPulsedIntakeCountdownTimer;

	delete this->m_pClawMotor;
	delete this->m_pClawMotorWatchDogTimer;
	delete this->m_pClawOpenLimitSwitch;
	delete this->m_pClawClosedLimitSwitch;

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

	// Is the claw already fully open, already?
	if ( ! this->isClawOpenLimitSwitchPushed() )
	{
		// If the claw is idle now, reset the watchdog timer
		// (but if it's NOT idle, then the claw is ALREADY moving,
		//  so we DON'T want to reset it, as it's supposed to keep
		//  track of how long the motor has continuously run)
		if ( this->m_CurrentClawState == Gripper::IS_IDLE )
		{
			this->m_pClawMotorWatchDogTimer->Reset();
			this->m_pClawMotorWatchDogTimer->Start();
		}

		this->m_ClawMovementSpeed = CLAW_MOVEMENT_SPEED_MAX;
		this->m_CurrentClawState = Gripper::IS_OPENNING;
	}

	return;
}

void Gripper::CloseCompletely(void) //Solenoid is ON, cylinder is in extended position
{
	std::cout << "Gripper::Close()" << std::endl;

	//this->m_pGripperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);

	// Is the claw fully closed, already?
	if ( ! this->isClawClosedLimitSwitchPushed() )
	{
		// If the claw is idle now, reset the watchdog timer
		// (but if it's NOT idle, then the claw is ALREADY moving,
		//  so we DON'T want to reset it, as it's supposed to keep
		//  track of how long the motor has continuously run)
		if ( this->m_CurrentClawState == Gripper::IS_IDLE )
		{
			this->m_pClawMotorWatchDogTimer->Reset();
			this->m_pClawMotorWatchDogTimer->Start();
		}

		this->m_ClawMovementSpeed = CLAW_MOVEMENT_SPEED_MAX;
		this->m_CurrentClawState = Gripper::IS_CLOSING;
	}

	return;
}

void Gripper::SetIntakeSpeed(double speed)
{
	this->m_pLeftIntakeMotor->Set(speed);
	this->m_pRightIntakeMotor->Set(speed);
	return;
}

// This will run the intake for the desired speed.
// Each time it's called, the timer resets.
void Gripper::PulseIntake(double speed, double time)
{
	// Reset the timer & save the speed of the intake
	this->m_PulsedIntakeSpeed = speed;
	this->m_PulsedIntakePulseTimeInSeconds = time;

	this->m_pPulsedIntakeCountdownTimer->Reset();
	this->m_pPulsedIntakeCountdownTimer->Start();

	this->m_bPulsedIntakeModeOn = true;

	return;
}

// MUST be called repeatedly by the default (or any) command.
// (i.e. call from Execute() or IsFinished())
void Gripper::UpdateState(void)
{
	::SmartDashboard::PutBoolean( "Gripper Open Limit", this->isClawOpenLimitSwitchPushed() );
	::SmartDashboard::PutBoolean( "Gripper Closed Limit",this->isClawClosedLimitSwitchPushed() );

	// Are we in "Pulsed Intake" mode?
	if ( this->m_bPulsedIntakeModeOn )
	{
		// Intake is being pulsed for x seconds
		double secondsRemaining = this->m_PulsedIntakePulseTimeInSeconds - this->m_pPulsedIntakeCountdownTimer->Get();

		if ( secondsRemaining > 0.0 )
		{
			// We are still pulsing the intake
			this->SetIntakeSpeed(this->m_PulsedIntakeSpeed);
			::SmartDashboard::PutNumber("Pulsed Intake Remaining (sec)", secondsRemaining);
		}
		else
		{
			// Intake pulse is completed
			this->m_bPulsedIntakeModeOn = false;
			::SmartDashboard::PutNumber("Pulsed Intake Remaining (sec)", 0.0);
			this->m_pPulsedIntakeCountdownTimer->Stop();
			this->m_pPulsedIntakeCountdownTimer->Reset();
			this->SetIntakeSpeed(0.0);
		}// if ( secondsRemaining > 0.0 )
	}// if ( this->m_bPulsedIntakeModeOn )


	// See what state the claw is supposed to be in
	switch ( this->m_CurrentClawState )
	{
	case Gripper::IS_IDLE:
		::SmartDashboard::PutString("Claw state", "IS_IDLE");
		this->m_pClawMotor->Set(0.0);
		break;
	case Gripper::IS_OPENNING:
		::SmartDashboard::PutString("Claw state", "IS_OPENNING");

		if ( ! this->areEitherClawLimitSwitchesPushed() )
		{
			// Claw is opening
			this->m_pClawMotor->Set(this->m_ClawMovementSpeed);
		}
		else
		{
			// Claw is fully opened, so stop
			this->m_pClawMotor->Set(0.0);
			this->m_CurrentClawState = Gripper::IS_IDLE;
		}// if ( this->getGripperOpenLimitSwitchStatus() )

		break;

	case Gripper::IS_CLOSING:
		::SmartDashboard::PutString("Claw state", "IS_CLOSING");

		if ( ! this->areEitherClawLimitSwitchesPushed() )
		{
			// Claw is closing
			this->m_pClawMotor->Set( -this->m_ClawMovementSpeed );
			// Claw is fully closed, so stop
		}
		else
		{
			this->m_pClawMotor->Set(0.0);
			this->m_CurrentClawState = Gripper::IS_IDLE;
		}// if ( this->getGripperClosedLimitSwitchStatus() )

		break;
	}

	// Has the claw motor been running too long?
	if ( this->m_pClawMotorWatchDogTimer->Get() >= GRIPPER_CLAW_MOVEMENT_WATCHDOG_TIMER_TIME )
	{
		// The motor has been running too long, so shut it off!
		this->m_pClawMotor->Set(0.0);
		this->m_CurrentClawState = Gripper::IS_IDLE;

		std::cout << "WARNING: Claw watchdog timer fired! Claw was running for more than "
				<< GRIPPER_CLAW_MOVEMENT_WATCHDOG_TIMER_TIME << " seconds." << std::endl;
	}


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
