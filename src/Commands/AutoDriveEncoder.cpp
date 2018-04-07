#include "AutoDriveEncoder.h"



AutoDriveEncoder::AutoDriveEncoder(double inchesToDrive, double speed)
{
	this->m_speed = speed;
	this->m_inchesToDrive = inchesToDrive;

	return;
}


AutoDriveEncoder::~AutoDriveEncoder()
{
	return;
}

void AutoDriveEncoder::Initialize()
{
	return;
}

void AutoDriveEncoder::Execute()
{
	return;
}

bool AutoDriveEncoder::IsFinished()
{
	//TODO: Change this
	return true;
}

void AutoDriveEncoder::End()
{

	return;
}
void AutoDriveEncoder::Interrupted()
{
	return;
}

// Can't call c'tor
AutoDriveEncoder::AutoDriveEncoder()
{
	return;
}
