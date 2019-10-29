#ifndef __CONFIG_H
#define __CONFIG_H

/** Locomotion-related constants */
#define MICROMETERS_PER_COUNT 8.32
#define SHIFT_AFTER_180_DEG_TURN 0.010

/** Time it takes for the robot to decide where to go next while searching */
#define SEARCH_REACTION_TIME 0.01

/** Calibration constants for sensors */
#define SENSOR_SIDE_LEFT_A 2.806
#define SENSOR_SIDE_LEFT_B 0.287
#define SENSOR_SIDE_RIGHT_A 2.327
#define SENSOR_SIDE_RIGHT_B 0.231
#define SENSOR_FRONT_LEFT_A 2.609
#define SENSOR_FRONT_LEFT_B 0.242
#define SENSOR_FRONT_RIGHT_A 2.713
#define SENSOR_FRONT_RIGHT_B 0.258

/** Feed-forward constants */
#define FEEDFORWARD_SPEED_LEFT_0 0.07503
#define FEEDFORWARD_SPEED_LEFT_1 2.8333
#define FEEDFORWARD_SPEED_RIGHT_0 0.09884
#define FEEDFORWARD_SPEED_RIGHT_1 3.0890
#define FEEDFORWARD_FORCE_LEFT 4.99588
#define FEEDFORWARD_FORCE_RIGHT 4.30160
#define FEEDFORWARD_TURN_LEFT_LEFT -0.27322
#define FEEDFORWARD_TURN_LEFT_RIGHT 0.59426
#define FEEDFORWARD_TURN_RIGHT_LEFT 0.57960
#define FEEDFORWARD_TURN_RIGHT_RIGHT -0.06865

/** Control constants */
#define KP_LINEAR 1.
#define KD_LINEAR 16.
#define KP_ANGULAR .02
#define KD_ANGULAR 1.
#define KP_ANGULAR_FRONT .1
#define KI_ANGULAR_FRONT .5
#define KP_ANGULAR_SIDE .5
#define KI_ANGULAR_SIDE 1.
#define KP_ANGULAR_DIAGONAL .5
#define KI_ANGULAR_DIAGONAL 1.

struct control_constants {
	float kp_linear;
	float kd_linear;
	float kp_angular;
	float kd_angular;
	float kp_angular_front;
	float ki_angular_front;
	float kp_angular_side;
	float ki_angular_side;
	float kp_angular_diagonal;
	float ki_angular_diagonal;
};

/** Speed constants */
#define LINEAR_SPEED_LIMIT 2.

float get_micrometers_per_count(void);
void set_micrometers_per_count(float value);
struct control_constants get_control_constants(void);
void set_control_constants(struct control_constants value);
float get_linear_speed_limit(void);
void set_linear_speed_limit(float value);

#endif /* _CONFIG_H */
