#ifndef _ROBOTMAP_HG_
#define _ROBOTMAP_HG_

//Drive Train
const int DRIVETRAIN_RIGHT_FRONT_MOTOR_ID = 1;		// DriveRightFront
const int DRIVETRAIN_RIGHT_REAR_MOTOR_ID = 2;		// DriveRightRear
const int DRIVETRAIN_LEFT_FRONT_MOTOR_ID = 3;		// DriveLeftFront
const int DRIVETRAIN_LEFT_REAR_MOTOR_ID = 4;		// DriveLeftRear

const int LIFTER_MOTOR_ID = 5;						// LiftMotor
const double LIFT_MAST_SPEED_RATIO = 0.5;

const int GRIPPER_INTAKE_LEFT_MOTOR_ID = 6;			// GripperIntakeLeft
const int GRIPPER_INTAKE_RIGHT_MOTOR_ID = 8;		// GripperIntakeRight
const int GRIPPER_CLAW_MOTOR_ID = 7;				// GripperClaw

const int GRIPPER_CLAW_LIMIT_OPEN_DIO_ID = 0;
const int GRIPPER_CLAW_LIMIT_CLOSED_DIO_ID = 1;

const int LIFT_MAST_UPPER_LIMIT_SWITCH_READY_TO_SHOOT_SCALE_POSITION = 9;

// This is how long the gripper claw can move before it's turned off.
// This is just in case the switches are not working, or there is something
//  jamming the gripper claw - so the motor won't run when jammed.
//const double GRIPPER_CLAW_MOVEMENT_WATCHDOG_TIMER_TIME = 0.5;

// For the AutoBasicForwardTimerWithDelay() command
const double DEFAULT_WAIT_TO_START_TIME = 0.0;
const double DEFAULT_DRIVE_SPEED = 0.6;
const double DEFAULT_DRIVE_FORWARD_TIME = 4.0;


// Now long the "pulse" of the "pulsed mode" of the intake lasts (in seconds)
const double GRIPPER_INTAKE_PULSED_RUN_TIME = 1.0;
// Now fast the intake motors go when in pulsed mode
const double GRIPPER_INTAKE_PLUSED_MODE_MOTOR_SPEED = 0.90;
// How fast the intake motors spin when shooting
const double GRIPPER_SHOOT_PLUSED_MODE_MOTOR_SPEED = 0.80;


const int JOYSTICK_OPEN_BUTTON_ID = 4;
//const int JOYSTICK_OPEN_AND_SHOOT_BUTTON_ID = 3;
const int JOYSTICK_IDLE_BUTTON_ID = 3;
const int JOYSTICK_CLOSE_BUTTON_ID = 5;



//XBox Controller
const int XBOX_CONTROLLER_DRIVE_PORT = 0;
const int XBOX_CONTROLLER_OPERATOR_PORT = 1;
//controller deadzone
const double XBOX_DEADZONE_LEFT_JOY=0.05;
const double XBOX_DEADZONE_RIGHT_JOY=0.05;
const double JOYSTICK_DEADZONE = 0.05;

const double DRIVE_SLOW_SPEED_RATIO = 0.6;
const double TURN_SLOW_SPEED_RATIO = .55;


// Claw is now electric, so no need for this
//const int COMPRESSOR_ID = 0;		// Is showing as device 0 on web dashboard
//const int PNEUMATIC_CONTROL_FORWARD_CHANNEL = 0;
//const int PNEUMATIC_CONTROL_REVERSE_CHANNEL = 1;

//const int LIFT_MAST_UPPER_CONTACT_SWITCH = 2;
//const int LIFT_MAST_LOWER_CONTACT_SWITCH = 3;
//const int FORK_WHEELS_CONTACT_INPUT = 2;
//const double WHEEL_RADIUS = 3.0;

// The maximum speed the claw can move
//const double CLAW_MOVEMENT_SPEED_MAX = 0.3;
//const double CLAW_CLOSE_SPEED = 0.05;
//
//const double CLAW_OPEN_SHUT_OFF_TIME = 1;
//
//const double CLAW_OPEN_SPEED = 0.05;
//const double CLAW_OPEN_AND_SHOOT_SPEED = 0.1;

#endif

