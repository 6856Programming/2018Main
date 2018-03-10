#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

//Drive Train
const int DRIVETRAIN_RIGHT_FRONT_MOTOR_ID = 1;
const int DRIVETRAIN_RIGHT_REAR_MOTOR_ID = 2;
const int DRIVETRAIN_LEFT_FRONT_MOTOR_ID = 3;
const int DRIVETRAIN_LEFT_REAR_MOTOR_ID = 4;

const int DRIVETRAIN_LIFTER_MOTOR_ID = 5;
const int DRIVETRAIN_GRIPPER_WHEEL_RIGHT_MOTOR_ID = 6;
const int DRIVETRAIN_GRIPPER_ARMS_MOTOR_ID = 7;
const int DRIVETRAIN_WINCH_MOTOR_ID = 8;

// Compressor
const int COMPRESSOR_ID = 0;		// Is showing as device 0 on web dashboard


const int GRIPPER_WHEEL_LEFT_MOTOR_ID = 9; //Added Feb 18/2018
const int GRIPPER_WHEEL_RIGHT_MOTOR_ID = 10; //Added Feb 18/2018

const int FORKED_WHEEL_LEFT_MOTOR_ID = 11;
const int FORKED_WHEEL_RIGHT_MOTOR_ID = 12;

const int PNEUMATIC_CONTROL_FORWARD_CHANNEL = 0;
const int PNEUMATIC_CONTROL_REVERSE_CHANNEL = 1;

//TODO: The gripper has a digital input, but I'm not sure what it's for...
const int GRIPPER_DIGITAL_INPUT_1 = 1;

const int LIFT_MAST_CONTACT_SWITCH = 6;

const int FORK_WHEELS_CONTACT_INPUT = 2;


const double WHEEL_RADIUS = 3.0;

//XBox Controller
const int XBOX_CONTROLLER_DRIVE_PORT = 0;
const int XBOX_CONTROLLER_OPERATOR_PORT = 1;
//controller deadzone
const double XBOX_DEADZONE_LEFT_JOY=0.05;
const double XBOX_DEADZONE_RIGHT_JOY=0.05;


#endif

