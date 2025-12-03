#include "main.h"
#include "lemlib/api.hpp"

#include "pot_auton_selector.hpp"
#include "autons.hpp"
#include "intake.hpp"
#include "drive.hpp"
#include "catapult.hpp"
#include "pistons.hpp"

/*
             U _____ u        _       ____    U _____ u       ____   _   _      _       ____      _                U _____ u      ____              _   _       
 __        __\| ___"|/    U  /"\  uU |  _"\ u \| ___"|/    U /"___| |'| |'| U  /"\  uU |  _"\ u  |"|        ___    \| ___"|/     |  _"\    ___     |'| |'|      
 \"\      /"/ |  _|"       \/ _ \/  \| |_) |/  |  _|"      \| | u  /| |_| |\ \/ _ \/  \| |_) |/U | | u     |_"_|    |  _|"      /| | | |  |_"_|   /| |_| |\     
 /\ \ /\ / /\ | |___       / ___ \   |  _ <    | |___       | |/__ U|  _  |u / ___ \   |  _ <   \| |/__     | |     | |___      U| |_| |\  | |    U|  _  |u     
U  \ V  V /  U|_____|     /_/   \_\  |_| \_\   |_____|       \____| |_| |_| /_/   \_\  |_| \_\   |_____|  U/| |\u   |_____|      |____/ uU/| |\u   |_| |_|      
.-,_\ /\ /_,-.<<   >>      \\    >>  //   \\_  <<   >>      _// \\  //   \\  \\    >>  //   \\_  //  \\.-,_|___|_,-.<<   >>       |||_.-,_|___|_,-.//   \\      
 \_)-'  '-(_/(__) (__)    (__)  (__)(__)  (__)(__) (__)    (__)(__)(_") ("_)(__)  (__)(__)  (__)(_")("_)\_)-' '-(_/(__) (__)     (__)_)\_)-' '-(_/(_") ("_)     
             U _____ u       ____     _       ____      ____     __   __      _____    _   _  U _____ u       ____   _   _  U _____ uU _____ u ____   U _____ u 
 __        __\| ___"|/    U /"___|U  /"\  uU |  _"\ uU |  _"\ u  \ \ / /     |_ " _|  |'| |'| \| ___"|/    U /"___| |'| |'| \| ___"|/\| ___"|// __"| u\| ___"|/ 
 \"\      /"/ |  _|"      \| | u   \/ _ \/  \| |_) |/ \| |_) |/   \ V /        | |   /| |_| |\ |  _|"      \| | u  /| |_| |\ |  _|"   |  _|" <\___ \/  |  _|"   
 /\ \ /\ / /\ | |___       | |/__  / ___ \   |  _ <    |  _ <    U_|"|_u      /| |\  U|  _  |u | |___       | |/__ U|  _  |u | |___   | |___  u___) |  | |___   
U  \ V  V /  U|_____|       \____|/_/   \_\  |_| \_\   |_| \_\     |_|       u |_|U   |_| |_|  |_____|       \____| |_| |_|  |_____|  |_____| |____/>> |_____|  
.-,_\ /\ /_,-.<<   >>      _// \\  \\    >>  //   \\_  //   \\_.-,//|(_      _// \\_  //   \\  <<   >>      _// \\  //   \\  <<   >>  <<   >>  )(  (__)<<   >>  
 \_)-'  '-(_/(__) (__)    (__)(__)(__)  (__)(__)  (__)(__)  (__)\_) (__)    (__) (__)(_") ("_)(__) (__)    (__)(__)(_") ("_)(__) (__)(__) (__)(__)    (__) (__) 
 */

#define UPPER_INTAKE_MOTOR_PORT 10
#define LOWER_INTAKE_MOTOR_PORT 14
#define MIDDLE_INTAKE_MOTOR_PORT 1

#define DRIVE_LB_PORT 13
#define DRIVE_LM_PORT 12
#define DRIVE_LF_PORT 11

#define DRIVE_RB_PORT 20
#define DRIVE_RM_PORT 19
#define DRIVE_RF_PORT 18

#define IMU_PORT 15

#define LEFT_ENCODER_PORT 5
#define RIGHT_ENCODER_PORT 4
#define BACK_ENCODER_PORT 9

#define TUNG_SAHUR_ACTUATOR_PORT 'A'
#define WING_ACTUATOR_PORT 'B'

#define AUTON_SELECT_BUTTON pros::E_CONTROLLER_DIGITAL_UP

#define CATA_LAUNCH_BUTTON pros::E_CONTROLLER_DIGITAL_R1
#define CATA_HANG_BUTTON pros::E_CONTROLLER_DIGITAL_R2

#define INTAKE_INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L1
#define INTAKE_OUTTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L2

#define ACTUATE_INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_Y

#define RIGHT_BACK_WING_BUTTON pros::E_CONTROLLER_DIGITAL_B
#define LEFT_BACK_WING_BUTTON pros::E_CONTROLLER_DIGITAL_DOWN

// #define UP_MATCH_LOAD_SPEED_BUTTON pros::E_CONTROLLER_DIGITAL_LEFT
// #define DOWN_MATCH_LOAD_SPEED_BUTTON pros::E_CONTROLLER_DIGITAL_DOWN

#define LIMIT_DRIVE_SPEED_BUTTON pros::E_CONTROLLER_DIGITAL_RIGHT

pros::Controller Controller (pros::E_CONTROLLER_MASTER);
pros::Motor UpperIntake(UPPER_INTAKE_MOTOR_PORT, MOTOR_GEARSET_6, false);
pros::Motor MiddleIntake(MIDDLE_INTAKE_MOTOR_PORT, MOTOR_GEARSET_18, true);
pros::Motor LowerIntake(LOWER_INTAKE_MOTOR_PORT, MOTOR_GEARSET_18, false);

pros::ADIDigitalOut wingPiston(WING_ACTUATOR_PORT);
pros::ADIDigitalOut tonguePiston(TUNG_SAHUR_ACTUATOR_PORT);

////////////////////////////////////////////
// LemLib Drive definitions
///////////////////

pros::Motor drive_lb(DRIVE_LB_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor drive_lm(DRIVE_LM_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor drive_lf(DRIVE_LF_PORT, pros::E_MOTOR_GEARSET_06, false);

pros::Motor drive_rb(DRIVE_RB_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor drive_rm(DRIVE_RM_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor drive_rf(DRIVE_RF_PORT, pros::E_MOTOR_GEARSET_06, true);

pros::MotorGroup drive_left({drive_lb, drive_lm, drive_lf});
pros::MotorGroup drive_right({drive_rb, drive_rm, drive_rf});

pros::Imu inertial_sensor(IMU_PORT);

pros::Rotation left_encoder(LEFT_ENCODER_PORT);
pros::Rotation right_encoder(RIGHT_ENCODER_PORT);
pros::Rotation back_encoder(BACK_ENCODER_PORT);

lemlib::TrackingWheel left_tracking_wheel(&left_encoder,2.75, 5.+5./16.);
lemlib::TrackingWheel right_tracking_wheel(&right_encoder,2.75,5.+5./16.);
lemlib::TrackingWheel back_tracking_wheel(&back_encoder,2,4.25);



lemlib::Drivetrain_t drivetrain {
    &drive_left, // left drivetrain motors
    &drive_right, // right drivetrain motors
    10.+5./8., // track width
    2.75, // wheel diameter // 3.175
    360 // wheel rpm
};

lemlib::OdomSensors_t sensors {
    &left_tracking_wheel, // vertical tracking wheel 1
    &right_tracking_wheel, // vertical tracking wheel 2
    &back_tracking_wheel, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralPIDController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularPIDController {
    4.2, // kP
    40, // kD
    3, // smallErrorRange
    100, // smallErrorTimeout
    10, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};

lemlib::Chassis chassis(drivetrain, lateralPIDController, angularPIDController, sensors);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

pros::Distance distance_sensor(15);

void screen() {
    // loop forever
    while (true) {

        // // pros::lcd::print(1, "auton: %i", get_selected_auton(AutonPot.get_value())); // print the x position
        // controller.print(0, 0, "auton: %i   ", get_selected_auton(AutonPot.get_value()));
        // controller.clear();

        // lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        // pros::lcd::print(0, "x: %f", pose.x); // print the x position
        // pros::lcd::print(1, "y: %f", pose.y); // print the y position
        // pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}
 
void initialize() {
  pros::delay(1000);
    chassis.calibrate(); // calibrate the chassis
    pros::delay(200);

    printf("%b\n", pros::lcd::is_initialized());
    pros::delay(10);

    pros::lcd::initialize(); // initialize brain screen

    printf("what the heck\n");
    pros::delay(200);

    // chassis.setPose(-11, 60, 90);
    Catapult.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

     // create a task to print the position to the screen

    pros::lcd::set_text(2,"1 - Far 5 Ball\n" );
    pros::delay(100);
    pros::lcd::print(3,"2 - Near 4 Ball" );
    pros::lcd::print(4,"3 - Skills" );
    pros::lcd::print(5,"4 - Near Safe AWP" );
    pros::lcd::print(6,"5 - Far Safe AWP" );
    pros::Task screenTask(screen);
    pros::delay(50);


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  pros::delay(10);
}

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

/*
  1 - Far 5 Ball
  2 - Near 4 Ball
  3 - Skills
  4 - Near Safe AWP
  5 - Far Safe AWP
*/
void autonomous() {
  
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

bool actuate_intake_pressed = false;
bool actuate_intake_pressed_last = actuate_intake_pressed;

bool actuate_wings_pressed = false;
bool actuate_wings_pressed_last = actuate_wings_pressed;

bool up_match_load_speed_pressed = false;
bool up_match_load_speed_pressed_last = up_match_load_speed_pressed;

bool down_match_load_speed_pressed = false;
bool down_match_load_speed_pressed_last = down_match_load_speed_pressed;

int cata_shoot_velocity = 100;

int drive_ceiling_speed = 80;

/*
1 - Far 5 Ball
2 - Near 4 Ball
3 - Skills
4 - Near Safe AWP
5 - Far Safe AWP
*/


int wingState=0;
int tongueState=0;

void opcontrol() {
  



	while (true) {

            // pros::lcd::print(3,"%i", distance_sensor.get()); // print the x position

      // printf("hello %d\n", AutonPot.get_value());

      // pros::lcd::print(1,"hello %d" , AutonPot.get_value());

      // pros::lcd::print(5,"test %i" , get_selected_auton(AutonPot.get_value()));
    if(Controller.get_digital_new_press(DIGITAL_Y)){wingPiston.set_value(wingState++%2);}
		if(Controller.get_digital_new_press(DIGITAL_B)){tonguePiston.set_value(tongueState++%2);}
		
		float j1=0.5*Controller.get_analog(ANALOG_RIGHT_X);
		float j3=0.5*Controller.get_analog(ANALOG_LEFT_Y);

		drive_left.move(j3+j1);
		drive_right.move(j3-j1);

		//storage
		if(Controller.get_digital(DIGITAL_R1)){
			LowerIntake.move(94*0.5);
			MiddleIntake.move(63*0.5);
			UpperIntake.move(63);
		}
	
		if(Controller.get_digital_new_press(DIGITAL_R1)){
			MiddleIntake.brake();
			UpperIntake.brake();
		}

		//move blocks up
		if(Controller.get_digital(DIGITAL_L1)){
			LowerIntake.move(94*0.5);
			MiddleIntake.move(127*0.5);
			UpperIntake.move(127);
		}

		//move blocks down
		if(Controller.get_digital(DIGITAL_R2)){
			LowerIntake.move(-31*0.5);
			MiddleIntake.move(-63*0.5);
			UpperIntake.move(-63);
		}

		//middle goal
		if(Controller.get_digital(DIGITAL_L2)){
			LowerIntake.move(63*0.5);
			MiddleIntake.move(94*0.5);
			UpperIntake.move(-106);
		}

		//un-middle goal
		if(Controller.get_digital(DIGITAL_X)){
			LowerIntake.move(-63*0.5);
			MiddleIntake.move(-94*0.5);
			UpperIntake.move(106);
		}

		//unstucky
		if(Controller.get_digital(DIGITAL_DOWN)){
			LowerIntake.move(-127*0.5);
			MiddleIntake.move(127*0.5);
		}

		if(Controller.get_digital(DIGITAL_RIGHT)){
			MiddleIntake.brake();
			LowerIntake.brake();
			UpperIntake.brake();
		}

    pros::delay(5);

	}

}
