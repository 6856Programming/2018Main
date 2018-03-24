/*
 * Wait.h
 *
 *  Created on: Mar 23, 2018
 *      Author: Robotics
 */


#pragma once

#include <iostream>
#include <Commands/Command.h>
#include <WPILib.h>

class Waiter : public frc::Command {
public:
	Waiter();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	frc::Timer* timer;
};



