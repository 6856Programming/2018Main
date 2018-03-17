#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

//Drive Train
const int DRIVETRAIN_RIGHT_FRONT_MOTOR_ID = 1;
const int DRIVETRAIN_RIGHT_REAR_MOTOR_ID = 2;
const int DRIVETRAIN_LEFT_FRONT_MOTOR_ID = 3;
const int DRIVETRAIN_LEFT_REAR_MOTOR_ID = 4;

const int LIFTER_MOTOR_ID = 5;
const double LIFT_MAST_SPEED_RATIO = 0.5;

const int GRIPPER_INTAKE_LEFT_MOTOR_ID = 6;
const int GRIPPER_INTAKE_RIGHT_MOTOR_ID = 7;
const int GRIPPER_CLAW_MOTOR_ID = 8;

const int GRIPPER_LIMIT_OPEN_DIO_ID = 0;
const int GRIPPER_LIMIT_CLOSED_DIO_ID = 1;

const double GRIPPER_INTAKE_PULSED_RUN_TIME = 1.0;


const int LIFT_MAST_CONTACT_SWITCH = 6;

const int FORK_WHEELS_CONTACT_INPUT = 2;


const double WHEEL_RADIUS = 3.0;

//XBox Controller
const int XBOX_CONTROLLER_DRIVE_PORT = 0;
const int XBOX_CONTROLLER_OPERATOR_PORT = 1;
//controller deadzone
const double XBOX_DEADZONE_LEFT_JOY=0.05;
const double XBOX_DEADZONE_RIGHT_JOY=0.05;

const double DRIVE_SLOW_SPEED_RATIO = 0.6;



// Claw is now electric, so no need for this
//const int COMPRESSOR_ID = 0;		// Is showing as device 0 on web dashboard
//const int PNEUMATIC_CONTROL_FORWARD_CHANNEL = 0;
//const int PNEUMATIC_CONTROL_REVERSE_CHANNEL = 1;



#endif

