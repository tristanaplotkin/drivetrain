#include "okapi/api.hpp"

using namespace okapi;

ChassisController chassis;
Controller masterController;

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	// nothing needed yet
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	const double kP = 1.0;
	const double kI = 0.001;
	const double kD = 0.1;
	const int DRIVE_LEFT_FRONT_PORT = 0;
	const int DRIVE_RIGHT_FRONT_PORT = 1; // add more as needed for testing

	chassis = ChassisControllerPID().withMotors(DRIVE_LEFT_FRONT_PORT, DRIVE_RIGHT_FRONT_PORT).withGains({kP, kI, kD}, {kP, kI, kD}, {kP, kI, kD}).withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR}).withOdometry().buildOdometry();
	chassis->setState({0_in, 0_in, 0_deg});
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	chassis->driveToPoint({1_ft, 1_ft});
	chassis->turnToPoint({5_ft, 0_ft});
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	while(true) {
		chassis->getModel()->tank(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightX));
		pros::delay(10);
	}
}
