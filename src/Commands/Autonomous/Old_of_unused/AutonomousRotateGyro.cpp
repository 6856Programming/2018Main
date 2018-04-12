//#include "AutonomousRotateGyro.h"
//#include "../RobotMap.h"
//#include <iostream>
//#define FORWARDSPEED 1
//
//#include <ADXRS450_Gyro.h>
//
//AutonomousRotateGyro::AutonomousRotateGyro(double direction)
//{
//
//    //this->m_pGyro = new frc::ADRS450_Gyro();
//
//    std::cout << "[AutonomousRotate] Constructed" << std::endl;
//
//    if (CommandBase::pDriveTrain != nullptr)
//    {
//   	 Requires(CommandBase::pDriveTrain);
//    }
//    else
//    {
//   	 std::cout << "[AutonomousRotate] driveTrain is null!" << std::endl;
//    }
//
//    this->m_direction = direction;
//
//    return;
//}
//
//AutonomousRotateGyro::AutonomousRotateGyro()
//{
//    this->m_direction = 0.0;
//    return;
//}
//
//void AutonomousRotateGyro::Initialize()
//{
//    std::cout << "[AutonomousRotate] Initialized" << std::endl;
//    CommandBase::pDriveTrain->Gyro_Reset(); //Used to construct the original direction of the robot
//    //gyro->SetSensitivity(SENSITIVITY); //In the brackets represent  volts/1000 Default 0.25
//    return;
//}
//
//
//void AutonomousRotateGyro::Execute()
//{
//	double currentDirection = CommandBase::pDriveTrain->Gyro_GetAngle();
//	::SmartDashboard::PutNumber("Gyro Angle", currentDirection);
//
//	{
//		double angleDifference = m_direction - currentDirection;
//		std::cout << "AutonomousRotate(): " << angleDifference << " units to go" << std::endl;
//	}
//
//	if ( currentDirection < this->m_direction )
//	{
//		double turnAngle = 1;
//		if ( this->m_direction < 0)
//		{
//			turnAngle *= -1;
//		}
//
//		CommandBase::pDriveTrain->ArcadeDrive(FORWARDSPEED, turnAngle); //Use tankdrive
//	}
//
//	return;
//}
//
//bool AutonomousRotateGyro::IsFinished()
//{
//	double gyroAngle = CommandBase::pDriveTrain->Gyro_GetAngle();
//
//	if (gyroAngle >= this->m_direction && gyroAngle > 0)
//	{
//		return true;
//	}
//	else if (gyroAngle <= this->m_direction && gyroAngle < 0)
//	{
//		return true;
//	}
//
//	return false;
//}
//
//void AutonomousRotateGyro::End()
//{
//    return;
//}
//
//void AutonomousRotateGyro::Interrupted()
//{
//    //We really shouldn't interrupt this b/c then we wouldn't know where the heading is
//    return;
//}

