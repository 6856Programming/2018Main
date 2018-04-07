
#ifndef SRC_COMMANDS_AUTONOMOUSROTATEGYRO_H_
#define SRC_COMMANDS_AUTONOMOUSROTATEGYRO_H_

#include <WPILib.h>
#include "../CommandBase.h"
//#include "MyAutoCommand.h"
#include <iostream>
#include <ADXRS450_Gyro.h>

/**
 *
 */

class AutonomousRotateGyro: public CommandBase
{
public:
	// Zero degrees is "forward"
	AutonomousRotateGyro(double direction);
    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End() override;
    void Interrupted() override;


private:

    double m_direction;

    frc::ADXRS450_Gyro* m_pGyro;


    AutonomousRotateGyro();
};




#endif /* SRC_COMMANDS_AUTONOMOUSROTATEGYRO_H_ */
