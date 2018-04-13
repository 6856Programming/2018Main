#ifndef _cGyroHelper_HG_
#define _cGyroHelper_HG_

// This is a thin wrapper around the gyro that adds
//  features like limiting the sample frequency,
//  getting the average of the last X samples (Low pass filter),
//  etc.
// It was made on the off-chance the the "drive straight" was
//  spamming the gyro too often, and over-reacting to the
//  return values, causing instability over longer drive distances

#include <WPILib.h>
#include <ADXRS450_Gyro.h>
#include <vector>

class cGyroHelper
{
public:
	cGyroHelper( frc::ADXRS450_Gyro* pTheGyro );
	cGyroHelper();

	double GetGyroAngleImmediate();
	double GetGyroRateImmediate();
	void ResetGyro();
	void CalibrateGyro();

	// This allows only periodic sampling of the gyro, rather than spamming it
	void setMinSampleTime(double minSampleTimeSeconds);
	// Each time the gyro is sampled, it will store the value in a buffer.
	// The is for the need for gradual changing values, like driving straight.
	void setSampleLowPassFilterSize(int numberOfSamples);
	// Returns average of all samples in buffers
	double getGetGyroAngleAverage(void);
	// Clears any samples older than value, then returns average
	double getGetGyroAngleAverage(double maxSampleAgeSeconds);

	// You aren't really supposed to call this...
	frc::ADXRS450_Gyro* pGetGyroRawPointer(void);

	// Returns true if timer is running and time is
	bool IsGyroCalibrating(void);

private:
	// Called by all c'tors
	void m_Init(void);

//	// Gyro can't be sampled until this amount of time has elapsed
//	double m_GyroMinSampleFrequency;_
//	const double m_DEFAULT_GYRO_MIN_SAMPLE_FREQUENCY = 0.1;		// 100 ms max
//	frc::Timer* m_GyroSampleCountDownTimer;
//	// This is the last actual gyro sample

	struct sSample
	{
		sSample() : timeStamp(0.0), angle(0.0) {};
		double timeStamp;
		double angle;
	};
	std::vector<sSample> m_vecGyroSamples;
	void m_clearSamplesOlderThan(double ageInSeconds);
	void m_AddSampleToBuffer(sSample gyroSample);

	// This will alow a few seconds to calibrate the gyro.
	// When it's calibrating, you can't call anything on the gyro
	frc::Timer* m_pGyroCalibrationTimer;
	const double m_GYRO_CALIBRATION_COUNTDOWN_TIME = 5.0;
	bool m_bGyroIsCalibrating;	// = false

	frc::ADXRS450_Gyro* m_pGyro;

	// Keeps track of time since we started.
	// Used for time stamps
	frc::Timer* m_pTimeSinceStartTimer;

};



#endif /* SRC_SUBSYSTEMS_CGYROHELPER_H_ */
