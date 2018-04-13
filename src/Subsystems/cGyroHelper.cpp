#include "cGyroHelper.h"
#include <iostream>
#include <algorithm>

cGyroHelper::cGyroHelper( frc::ADXRS450_Gyro* pTheGyro )
{
	this->m_pGyro = pTheGyro;
	this->m_Init();
	return;
}

cGyroHelper::cGyroHelper()
{
	this->m_pGyro = new frc::ADXRS450_Gyro();
	this->m_Init();
	return;
}

void cGyroHelper::m_Init(void)
{
	this->m_pTimeSinceStartTimer = new frc::Timer();
	this->m_pTimeSinceStartTimer->Reset();
	this->m_pTimeSinceStartTimer->Start();

	this->m_pGyroCalibrationTimer = new frc::Timer();
	this->m_pGyroCalibrationTimer->Reset();

	this->m_bGyroIsCalibrating = false;

	return;
}


// Returns true if timer is running and time is
bool cGyroHelper::IsGyroCalibrating(void)
{
	if ( this->m_bGyroIsCalibrating )
	{
		// Done?
		if ( this->m_pGyroCalibrationTimer->Get() >= this->m_GYRO_CALIBRATION_COUNTDOWN_TIME )
		{
			std::cout << "**********************************" << std::endl;
			std::cout << "    GYRO CALIBRATION COMPLETE.    " << std::endl;
			std::cout << "**********************************" << std::endl;

			this->m_bGyroIsCalibrating = false;
		}
	}

	return this->m_bGyroIsCalibrating;
}

void cGyroHelper::CalibrateGyro()
{
	if ( this->m_bGyroIsCalibrating )
	{
		return;
	}

	this->m_pGyroCalibrationTimer->Start();
	this->m_bGyroIsCalibrating = true;
	std::cout << "**********************************" << std::endl;
	std::cout << "   GYRO CALIBRATION STARTING...   " << std::endl;
	std::cout << "**********************************" << std::endl;
	return;
}

double cGyroHelper::GetGyroAngleImmediate()
{
	if ( this->m_bGyroIsCalibrating )	{	return 0.0; }

	sSample curSample;
	curSample.angle = this->m_pGyro->GetAngle();
	curSample.timeStamp = this->m_pTimeSinceStartTimer->Get();

	this->m_AddSampleToBuffer(curSample);

	return curSample.angle;
}

double cGyroHelper::GetGyroRateImmediate()
{
	if ( this->m_bGyroIsCalibrating )	{ return 0.0; }

	return this->m_pGyro->GetRate();
}

void cGyroHelper::ResetGyro()
{
	if ( this->m_bGyroIsCalibrating )	{ return; }

	this->m_pGyro->Reset();

	return;
}

//// This allows only periodic sampling of the gyro, rather than spamming it
//void setMinSampleTime(double minSampleTimeSeconds);
//// Each time the gyro is sampled, it will store the value in a buffer.
//// The is for the need for gradual changing values, like driving straight.
//void setSampleLowPassFilterSize(int numberOfSamples);
//double getGetAngleAverage(void);

// You aren't really supposed to call this...
frc::ADXRS450_Gyro* cGyroHelper::pGetGyroRawPointer(void)
{
	return this->m_pGyro;
}

void cGyroHelper::m_AddSampleToBuffer(sSample gyroSample)
{
	this->m_vecGyroSamples.push_back(gyroSample);
	return;
}


double cGyroHelper::getGetGyroAngleAverage(void)
{
	if ( this->m_bGyroIsCalibrating )	{	return 0.0; }

	// Add current sample
	sSample curSample;
	curSample.angle = this->m_pGyro->GetAngle();
	curSample.timeStamp = this->m_pTimeSinceStartTimer->Get();
	this->m_AddSampleToBuffer(curSample);

	unsigned int sizeOfVec = (unsigned int)this->m_vecGyroSamples.size();
	double total = 0.0;
	for ( unsigned int index = 0; index != sizeOfVec; index++ )
	{
		total += this->m_vecGyroSamples[index].angle;
	}
	double average = total / (double)sizeOfVec;
	return average;
}

// Clears any samples older than value, then returns average
double cGyroHelper::getGetGyroAngleAverage(double maxSampleAgeSeconds)
{
	this->m_clearSamplesOlderThan(maxSampleAgeSeconds);

	return this->getGetGyroAngleAverage();
}

void cGyroHelper::m_clearSamplesOlderThan(double ageInSeconds)
{
	double minTimeStampToSave = this->m_pTimeSinceStartTimer->Get() - ageInSeconds;

	std::vector<sSample> vecKeep;
	vecKeep.reserve(100);

	unsigned int sizeOfVec = (unsigned int)this->m_vecGyroSamples.size();

	for ( unsigned int index = 0; index != sizeOfVec; index++ )
	{
		// If time is OK, copy  it
		sSample& curSample = this->m_vecGyroSamples[index];
		if ( curSample.timeStamp >= minTimeStampToSave )
		{
			vecKeep.push_back(curSample);
		}
	}
	this->m_vecGyroSamples.clear();
	std::copy(vecKeep.begin(), vecKeep.end(), this->m_vecGyroSamples.begin());

	return;
}





















