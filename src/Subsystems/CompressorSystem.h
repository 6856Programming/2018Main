#ifndef SRC_SUBSYSTEMS_COMPRESSORSYSTEM_H_
#define SRC_SUBSYSTEMS_COMPRESSORSYSTEM_H_
/*
 * Compressor.h
 *
 *  Created on: Feb 25, 2018
 *      Author: Robotics, WaderGater
 */

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>
#include "../RobotMap.h"

class CompressorSystem : public frc::Subsystem
{
private:
	int po;
	int pf;

	frc::Compressor* m_pCompressor;

public:
	CompressorSystem(int o,int f);
	virtual ~CompressorSystem();
	int SetClosedLoopControl();
};


#endif /* SRC_SUBSYSTEMS_COMPRESSORSYSTEM_H_ */
