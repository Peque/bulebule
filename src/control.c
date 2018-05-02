#include "control.h"

/**
 * Maximum acceleration and deceleration.
 *
 * - Linear acceleration is defined in meters per second squared.
 * - Linear deceleration is defined in meters per second squared.
 * - Angular acceleration is defined in radians per second squared.
 */
static volatile float linear_acceleration = 5.;
static volatile float linear_deceleration = 5.;
static volatile float angular_acceleration = 32. * PI;

static volatile float target_linear_speed;
static volatile float target_angular_speed;
static volatile float ideal_linear_speed;
static volatile float ideal_angular_speed;

static volatile float kp_linear = 1600.;
static volatile float kd_linear = 100.;
static volatile float kp_angular = 60.;
static volatile float kd_angular = 50.;
static volatile float ki_angular_front = 30.;
static volatile float ki_angular_side = 10.;
static volatile float ki_distance_front = 0.;
static volatile float side_sensors_error_factor = 750.;
static volatile float front_sensors_error_factor = 100.;
static volatile float front_distance_error_factor = 0.;
static volatile float linear_error;
static volatile float angular_error;
static volatile float last_linear_error;
static volatile float last_angular_error;

static volatile int32_t pwm_left;
static volatile int32_t pwm_right;

static volatile bool collision_detected_signal;
static volatile bool motor_control_enabled_signal;
static volatile bool side_sensors_control_enabled;
static volatile bool front_sensors_control_enabled;
static volatile bool front_distance_control_enabled;
static volatile float side_sensors_integral;
static volatile float front_sensors_integral;
static volatile float front_distance_integral;

float get_linear_acceleration(void)
{
	return linear_acceleration;
}

void set_linear_acceleration(float value)
{
	linear_acceleration = value;
}

float get_linear_deceleration(void)
{
	return linear_deceleration;
}

void set_linear_deceleration(float value)
{
	linear_deceleration = value;
}

float get_angular_acceleration(void)
{
	return angular_acceleration;
}

void set_angular_acceleration(float value)
{
	angular_acceleration = value;
}

float get_side_sensors_error_factor(void)
{
	return side_sensors_error_factor;
}

void set_side_sensors_error_factor(float value)
{
	side_sensors_error_factor = value;
	reset_control_errors();
}

float get_front_sensors_error_factor(void)
{
	return front_sensors_error_factor;
}

void set_front_sensors_error_factor(float value)
{
	front_sensors_error_factor = value;
	reset_control_errors();
}

float get_front_distance_error_factor(void)
{
	return front_distance_error_factor;
}

void set_front_distance_error_factor(float value)
{
	front_distance_error_factor = value;
	reset_control_errors();
}

float get_kp_linear(void)
{
	return kp_linear;
}

void set_kp_linear(float value)
{
	kp_linear = value;
	reset_control_errors();
}

float get_kd_linear(void)
{
	return kd_linear;
}
void set_kd_linear(float value)
{
	kd_linear = value;
	reset_control_errors();
}

float get_kp_angular(void)
{
	return kp_angular;
}

void set_kp_angular(float value)
{
	kp_angular = value;
	reset_control_errors();
}

float get_kd_angular(void)
{
	return kd_angular;
}

void set_kd_angular(float value)
{
	kd_angular = value;
	reset_control_errors();
}

float get_ki_angular_side(void)
{
	return ki_angular_side;
}

void set_ki_angular_side(float value)
{
	ki_angular_side = value;
	reset_control_errors();
}

float get_ki_angular_front(void)
{
	return ki_angular_front;
}

void set_ki_angular_front(float value)
{
	ki_angular_front = value;
	reset_control_errors();
}

float get_ki_distance_front(void)
{
	return ki_distance_front;
}

void set_ki_distance_front(float value)
{
	ki_distance_front = value;
	reset_control_errors();
}

/**
 * @brief Enable or disable the side sensors control.
 */
void side_sensors_control(bool value)
{
	side_sensors_control_enabled = value;
}

/**
 * @brief Enable or disable the front sensors control.
 */
void front_sensors_control(bool value)
{
	front_sensors_control_enabled = value;
}

/**
 * @brief Enable or disable the front distance control.
 */
void front_distance_control(bool value)
{
	front_distance_control_enabled = value;
}

/**
 * @brief Set collision detected signal.
 *
 * It also automatically disables the motor control.
 */
static void set_collision_detected(void)
{
	collision_detected_signal = true;
	motor_control_enabled_signal = false;
}

/**
 * @brief Returns true if a collision was detected.
 */
bool collision_detected(void)
{
	return collision_detected_signal;
}

/**
 * @brief Reset the collision detection signal.
 *
 * This will also reset the PWM saturation counters, used for collision
 * detection.
 */
void reset_collision_detection(void)
{
	collision_detected_signal = false;
	reset_pwm_saturation();
}

/**
 * @brief Reset control error variables.
 */
void reset_control_errors(void)
{
	side_sensors_integral = 0;
	front_sensors_integral = 0;
	front_distance_integral = 0;
	linear_error = 0;
	angular_error = 0;
	last_linear_error = 0;
	last_angular_error = 0;
}

/**
 * @brief Reset control speed variables.
 */
void reset_control_speed(void)
{
	target_linear_speed = 0.;
	target_angular_speed = 0.;
	ideal_linear_speed = 0.;
	ideal_angular_speed = 0.;
}

/**
 * @brief Reset all control variables.
 *
 * In particular:
 *
 * - Reset control errors.
 * - Reset control speed.
 * - Reset collision detection.
 */
void reset_control_all(void)
{
	reset_control_errors();
	reset_control_speed();
	reset_collision_detection();
}

/**
 * @brief Enable the motor control.
 *
 * This means the motor control function will be executed the PWM output will be
 * generated.
 */
void enable_motor_control(void)
{
	motor_control_enabled_signal = true;
}

/**
 * @brief Disable the motor control.
 *
 * This means the motor control function will not be executed and no PWM output
 * will be generated.
 */
void disable_motor_control(void)
{
	motor_control_enabled_signal = false;
}

/**
 * @brief Return the current PWM duty for the left motor.
 */
float get_left_pwm(void)
{
	return pwm_left;
}

/**
 * @brief Return the current PWM duty for the right motor.
 */
float get_right_pwm(void)
{
	return pwm_right;
}

/**
 * @brief Return the current target linear speed in meters per second.
 */
float get_target_linear_speed(void)
{
	return target_linear_speed;
}

/**
 * @brief Return the current target angular speed in degrees per second.
 */
float get_target_angular_speed(void)
{
	return target_angular_speed;
}

/**
 * @brief Return the current ideal linear speed in meters per second.
 */
float get_ideal_linear_speed(void)
{
	return ideal_linear_speed;
}

/**
 * @brief Return the current ideal angular speed in degrees per second.
 */
float get_ideal_angular_speed(void)
{
	return ideal_angular_speed;
}

/**
 * @brief Set target linear speed in meters per second.
 */
void set_target_linear_speed(float speed)
{
	target_linear_speed = speed;
}

/**
 * @brief Set target angular speed in degrees per second.
 */
void set_target_angular_speed(float speed)
{
	target_angular_speed = speed;
}

/**
 * @brief Update ideal speed according to the defined speed profile.
 *
 * Current ideal speed is increased or decreased according to the target speed
 * and the defined maximum acceleration and deceleration.
 */
void update_ideal_speed(void)
{
	if (ideal_linear_speed < target_linear_speed) {
		ideal_linear_speed +=
		    linear_acceleration / SYSTICK_FREQUENCY_HZ;
		if (ideal_linear_speed > target_linear_speed)
			ideal_linear_speed = target_linear_speed;
	} else if (ideal_linear_speed > target_linear_speed) {
		ideal_linear_speed -=
		    linear_deceleration / SYSTICK_FREQUENCY_HZ;
		if (ideal_linear_speed < target_linear_speed)
			ideal_linear_speed = target_linear_speed;
	}
	if (ideal_angular_speed < target_angular_speed) {
		ideal_angular_speed +=
		    angular_acceleration / SYSTICK_FREQUENCY_HZ;
		if (ideal_angular_speed > target_angular_speed)
			ideal_angular_speed = target_angular_speed;
	} else if (ideal_angular_speed > target_angular_speed) {
		ideal_angular_speed -=
		    angular_acceleration / SYSTICK_FREQUENCY_HZ;
		if (ideal_angular_speed < target_angular_speed)
			ideal_angular_speed = target_angular_speed;
	}
}

/**
 * @brief Set PWM signals to power the motors.
 *
 * This function also implements collision detection by checking PWM output
 * saturation. If collision is detected it sets the `collision_detected_signal`
 * variable to `true`.
 *
 * @param[in] linear_pwm Linear PWM value, added to both motors.
 * @param[in] angular_pwm Angular PWM value, added to left motor, substracted
 * from right motor.
 */
static void set_pwm(float linear_pwm, float angular_pwm)
{
	pwm_left = (int32_t)(linear_pwm + angular_pwm);
	pwm_right = (int32_t)(linear_pwm - angular_pwm);

	power_left(pwm_left);
	power_right(pwm_right);

	if (pwm_saturation() > MAX_PWM_SATURATION_PERIOD * SYSTICK_FREQUENCY_HZ)
		set_collision_detected();
}

/**
 * @brief Execute a front wall distance control.
 *
 * Try to keep a defined distance from the front wall.
 *
 * This function also implements collision detection by checking PWM output
 * saturation. If collision is detected it sets the `collision_detected_signal`
 * variable to `true`.
 */
static void front_wall_distance_control(void)
{
	float linear_pwm;
	float angular_pwm;
	float front_sensors_feedback;
	float front_distance_feedback;

	front_sensors_feedback =
	    get_front_sensors_error() * front_sensors_error_factor;
	front_sensors_integral += front_sensors_feedback;

	front_distance_feedback =
	    (get_front_wall_distance() - CELL_DIMENSION / 2.) *
	    front_distance_error_factor;
	front_distance_integral += front_distance_feedback;

	linear_pwm = kp_linear * front_distance_feedback +
		     ki_distance_front * front_distance_integral;
	angular_pwm = kp_angular * front_sensors_feedback +
		      ki_angular_front * front_sensors_integral;

	set_pwm(linear_pwm, angular_pwm);
}

/**
 * @brief Execute the robot motor control.
 *
 * Set the motors power to try to follow a defined speed profile.
 */
void motor_control(void)
{
	float left_speed;
	float right_speed;
	float encoder_feedback_linear;
	float encoder_feedback_angular;
	float linear_pwm;
	float angular_pwm;
	float side_sensors_feedback;
	float front_sensors_feedback;

	if (!motor_control_enabled_signal)
		return;

	if (front_distance_control_enabled) {
		front_wall_distance_control();
		return;
	}

	left_speed = get_encoder_left_speed();
	right_speed = get_encoder_right_speed();
	encoder_feedback_linear = (left_speed + right_speed) / 2.;
	encoder_feedback_angular = get_encoder_angular_speed();

	if (side_sensors_control_enabled) {
		side_sensors_feedback =
		    get_side_sensors_error() * side_sensors_error_factor;
		side_sensors_integral += side_sensors_feedback;
	} else {
		side_sensors_feedback = 0;
	}

	if (front_sensors_control_enabled) {
		front_sensors_feedback =
		    get_front_sensors_error() * front_sensors_error_factor;
		front_sensors_integral += front_sensors_feedback;
	} else {
		front_sensors_feedback = 0;
	}

	linear_error += ideal_linear_speed - encoder_feedback_linear;
	angular_error += ideal_angular_speed - encoder_feedback_angular;

	linear_pwm = kp_linear * linear_error +
		     kd_linear * (linear_error - last_linear_error);
	angular_pwm = kp_angular * (angular_error + side_sensors_feedback +
				    front_sensors_feedback) +
		      kd_angular * (angular_error - last_angular_error) +
		      ki_angular_side * side_sensors_integral +
		      ki_angular_front * front_sensors_integral;

	set_pwm(linear_pwm, angular_pwm);

	last_linear_error = linear_error;
	last_angular_error = angular_error;
}
