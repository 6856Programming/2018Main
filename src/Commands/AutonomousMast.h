#ifndef SRC_COMMANDS_AUTONOMOUSMAST_H_
#define SRC_COMMANDS_AUTONOMOUSMAST_H_

#include <iostream>
#include <WPILib.h>
#include "../CommandBase.h"

class AutonomousMast: public CommandBase
{
public:
	AutonomousMast(double SecondsToRun, double SpeedAndDirection);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;

    double m_secondsToRun;
    double m_speed;
    frc::Timer* pTimer;

private:
    AutonomousMast();
};



#endif /* SRC_COMMANDS_AUTONOMOUSMAST_H_ */
