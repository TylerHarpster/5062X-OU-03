#include "catapult.hpp"
#include "main.h"
#include "lemlib/api.hpp"

#include "intake.hpp"
#include "pistons.hpp"

#include "autons.hpp"
#include <array>

void far_auton() {
    chassis.setPose(-11, 60, 90);
    // -11, 60
    // actuate_intake(true);
    spin_intake_auto(true, 600);
    pros::delay(400);

    // move into centerline ball

	chassis.moveTo(-7, 60, 1000);

    // 

    // Pos2
    chassis.moveTo(-45, 61, 1000, 160); 

    actuate_back_wings(true); //wings out for corner

    // chassis.turnTo(-22, 70, 1000, false, 100);

    // Pos3
    chassis.moveTo(-63, 48, 1000, 70);

    chassis.turnTo(-66, 18, 1000, true);

    // pros::delay(50);

    // drive_left.move_relative(-15000, 500);
    // drive_right.move_relative(-15000, 500);

    // pros::delay(800);

    // drive_left.move_velocity(0);
    // drive_right.move_velocity(0);

    // pros::delay(100);

    // chassis.setPose(-66, 24, inertial_sensor.get_heading());

    // pros::delay(50);

    actuate_left_back_wing(false);

    chassis.moveTo(-69, 18, 750, 180); // back into side of goal

    actuate_back_wings(false);


    // chassis.turnTo(-59.5, 38, 1000);

    // chassis.moveTo(-59.5, 38, 1000, 150);

    chassis.turnTo(-39, 35, 700);

    chassis.moveTo(-39, 35, 1000, 150);

    chassis.turnTo(-44, 18, 700);

    stop_intake_auto();

    spin_intake_auto(false, 250);

    pros::delay(400);

    chassis.turnTo(-4, 30, 700);

    spin_intake_auto(true, 600);

    // chassis.moveTo(-13, 31.6, 1000, 150);

    chassis.moveTo(-11, 28, 1000, 150);
    
    chassis.turnTo(-16, 12, 700, true);

    chassis.moveTo(-16, 12, 1000, 150);

    chassis.turnTo(0, 12, 700);

    actuate_back_wings(true);

    chassis.moveTo(-48, 12, 1000, 150); //into goal with wings

    chassis.moveTo(-34, 12, 1000, 150);

    actuate_back_wings(false);

    chassis.turnTo(-42, 12, 700);

    spin_intake_auto(false, 600);

    chassis.moveTo(-46, 12, 1000, 150);

    actuate_intake(false);

    chassis.moveTo(-34, 12, 1000, 150);

}

void skills() {
    // chassis.moveTo(-50, -56, 400, );-

    // actuate_intake(true);

    cata_limit_shoot = true;
    pros::delay(1000); // 39500
    cata_limit_shoot = false;

    chassis.turnTo(-34, -63, 1500, true); // turn to move to center
    
    chassis.moveTo(-34, -63, 1500); 

    chassis.turnTo(40, -61, 1500, true); // turn to move to center

    chassis.moveTo(40, -61, 1500); // move into offensive zone

    chassis.turnTo(56, -44, 600, true); // turn to diagonal

    actuate_back_wings(true);

    chassis.moveTo(56, -44, 1500, 180);

    chassis.turnTo(58, 0, 600, true);

    actuate_back_wings(false);

    chassis.moveTo(58, -26, 1500, 200); // side push??

    chassis.moveTo(58,-40, 950, 160);

    chassis.turnTo(22, -24, 600, true);

    chassis.moveTo(22, -24, 1500, 150); //go to line

    chassis.turnTo(22, 0, 600, true);

    chassis.moveTo(22,-14,700,160);


    chassis.turnTo(36, -14, 600, true);

    actuate_back_wings(true);

    // chassis.moveTo(43, -8, 1500, 300); // first push

    drive_left.move_relative(-15000, 500);
    drive_right.move_relative(-15000, 500);

    pros::delay(900);

    drive_left.move_voltage(0);
    drive_right.move_voltage(0);

    pros::delay(100);

    chassis.setPose(36,-18, 270);

    actuate_back_wings(false);

    chassis.turnTo(22, -18, 600, true);

    chassis.moveTo(22, -18, 1500, 160);

    chassis.turnTo(22, 22, 600, true);

    chassis.moveTo(22, 22, 1500, 160);

    actuate_back_wings(true);

    chassis.turnTo(39, 6, 600, true);


    // chassis.moveTo(43, 15, 1500, 300); // second push

    drive_left.move_relative(-15000, 500);
    drive_right.move_relative(-15000, 500);

    pros::delay(900);

    drive_left.move_voltage(0);
    drive_right.move_voltage(0);

    chassis.setPose(36,11, 270);

    chassis.moveTo(10, 15, 1500, 160);

    actuate_back_wings(false);

    chassis.turnTo(44, 50, 600, true);

    chassis.moveTo(44, 50, 700);

    chassis.turnTo(60, 24, 600, true);

    actuate_back_wings(true);

    chassis.moveTo(60, 18, 700, 200);

    chassis.moveTo(51, 42, 700, 200);

    actuate_back_wings(false);

    chassis.turnTo(60, 18, 1500);


    // chassis.moveTo(60, 18, 700, 200);

    drive_left.move_relative(-15000, 600);
    drive_right.move_relative(-15000, 600);

    pros::delay(1100);

    drive_left.move_voltage(0);
    drive_right.move_voltage(0);

    spin_intake_auto(false, 600);

    chassis.setPose(60, 32, 0);

    chassis.moveTo(51, 42, 700, 200);
    


    // chassis.moveTo(48, 15, 1500, 300); // third push

    // chassis.moveTo(10,15,120); // final backup

}

void near_elims_auton() {

}

void near_auton() {

    // chassis.moveTo(5, 60, 1000);
    // pros::delay(1500);
    
    //     spin_intake_auto(true, 600);

    // actuate_intake(true);

    chassis.moveTo(57,49,1500,120); // move backwards

    actuate_back_wings(true);

    pros::delay(250);

    chassis.moveTo(48,57,1500,120); // move back to start

    chassis.moveTo(33,60,1500,120); // push triballs into alley

    actuate_back_wings(false);

    pros::delay(500);

    spin_intake_auto(true,600);

    chassis.turnTo(24,12,1500);

    chassis.moveTo(24, 24, 1500, 120); // setup for middle triball

    chassis.turnTo(24,0,1500); // turn to middle triball

    chassis.moveTo(24,14,1500,80); // go to middle triball

    chassis.moveTo(40,64,1500,80); // head back

    chassis.turnTo(10,64,1500, false, 120);

    spin_intake_auto(false,600);

    chassis.moveTo(10,64,1500,200);

    actuate_intake(true);

    // chassis.moveTo(4,62,1500,200);


    pros::delay(100000);

}

void near_auton_safe() {
    // chassis.moveTo(5, 60, 1000);
    // pros::delay(1500);
    
    //     spin_intake_auto(true, 600);

    // actuate_intake(true);

    chassis.moveTo(57,49,1500,120); // move backwards

    actuate_back_wings(true);

    pros::delay(250);

    chassis.moveTo(40,62,1500,120); // move back to start

    actuate_back_wings(false);


    chassis.turnTo(8,62,1500,true); // push triballs into alley

    chassis.moveTo(8,62,1500,120); // push triballs into alley


    chassis.turnTo(46, 42, 1000);

    actuate_back_wings(true);

    // chassis.turnTo(10,66,1500, false, 120);

    // chassis.moveTo(10,66,1500,200);

    // actuate_intake(true);

    // chassis.moveTo(4,62,1500,200);


    pros::delay(100000);

}

void far_auton_safe() {
    spin_intake_auto(true, 600);
    // actuate_intake(true);

    pros::delay(300);

    chassis.moveTo(-36, 12, 2000);

    chassis.turnTo(-60, 12, 1000);

    spin_intake_auto(false, 600);

    pros::delay(1000);

    stop_intake_auto();

    chassis.turnTo(60, 12, 1000);

    chassis.moveTo(-48, 12, 1000, 200);

    chassis.moveTo(-54, 12, 1000, 200);


    chassis.turnTo(-36, 35, 1000, true);

    chassis.moveTo(-36, 35, 1000);

    chassis.turnTo(-12, 35, 1000, true);

    actuate_back_wings(true);

    chassis.moveTo(-11, 35, 1000);

    chassis.turnTo(-48, 56, 1000);

    // actuate_intake(true);

    pros::delay(10000);



}

void skills2() {

    // Pos2
    chassis.moveTo(-46, -44, 1000);

    // Pos3
    chassis.turnTo(-60, -52, 1000);
    chassis.moveTo(-60, -52, 1000);

    cata_limit_shoot = true;
    pros::delay(36000);

    cata_limit_shoot = false;

    chassis.setPose(-61, -52, inertial_sensor.get_heading());
    pros::delay(150);

    // Pos4
    chassis.moveTo(-56, -52, 1000, 150);

    // Pos5
    chassis.turnTo(-34, -67, 1000, true, 100);
    chassis.moveTo(-34, -67, 1500, 150);

    actuate_back_wings(true);

    // Pos6
    chassis.turnTo(36, -67, 1000, true);
    actuate_right_back_wing(false);
    chassis.moveTo(36, -67, 1500);

    // Pos7
    // chassis.turnTo(52, -53, 1000, true);
    // chassis.moveTo(52, -53, 1500);

    // chassis.turnTo(60, -37, 1000, true);

    // drive_left.move_relative(-15000, 500);
    // drive_right.move_relative(-15000, 500);

    // pros::delay(1500);

    // drive_left.move_velocity(0);
    // drive_right.move_velocity(0);

    // pros::delay(200);

    // Pos8
    // chassis.setPose(60, -30, inertial_sensor.get_heading());

    // chassis.moveTo(61, -33, 1500);

    actuate_back_wings(false);

    // Pos9
    chassis.turnTo(48, -49, 1500,true);
    chassis.moveTo(48, -49  , 1500);

    // Pos10
    chassis.turnTo(16, -27, 1500, true);
    chassis.moveTo(16, -27, 1000);

    // Pos11
    chassis.turnTo(16, -20, 1500, true);
    chassis.moveTo(16, -20, 1000);

    chassis.turnTo(40, -12, 1500, true);

    actuate_back_wings(true);

    drive_left.move_relative(-15000, 360);
    drive_right.move_relative(-15000, 400);

    pros::delay(900);

    drive_left.move_velocity(0);
    drive_right.move_velocity(0);

    pros::delay(200);

    // Pos12
    chassis.setPose(40, -12, inertial_sensor.get_heading());

    actuate_back_wings(false);

    // chassis.moveTo(39, -12, 1000);

    // Pos13
    chassis.moveTo(16, -12, 1000);

    // Pos14
    chassis.turnTo(16, 20, 1000, true);
    chassis.moveTo(16, 20, 1000);

    // Pos15
    chassis.turnTo(41, 2, 1000, true); 

    actuate_back_wings(true);

    drive_left.move_relative(-15000, 400);
    drive_right.move_relative(-15000, 400);

    pros::delay(1500);

    drive_left.move_velocity(0);
    drive_right.move_velocity(0);

    pros::delay(200);

    chassis.setPose(41, 2, inertial_sensor.get_heading());

    actuate_back_wings(false);

    // Pos16
    chassis.moveTo(14, 2, 1000, true);


    // // PosNA
    // chassis.turnTo(27, 33, 1000, true);
    // chassis.moveTo(27, 33, 1000);

    // Pos17
    chassis.turnTo(44, 55, 1000, true);
    actuate_left_back_wing(true);
    chassis.moveTo(44, 55, 1000);

    // Pos18
    chassis.turnTo(59, 41, 1000, true);
    actuate_back_wings(true);   

    drive_left.move_relative(-15000, 400);
    drive_right.move_relative(-15000, 400);

    pros::delay(1500);

    drive_left.move_velocity(0);
    drive_right.move_velocity(0);

    pros::delay(200);

    chassis.setPose(59,41, inertial_sensor.get_heading());

    // Pos19
    chassis.turnTo(59, 32, 1000, true);

    drive_left.move_relative(-15000, 400);
    drive_right.move_relative(-15000, 400);

    pros::delay(1500);

    drive_left.move_velocity(0);
    drive_right.move_velocity(0);

    pros::delay(200);

    chassis.setPose(59, 32, inertial_sensor.get_heading());
    
    // Pos20
    chassis.moveTo(59, 46, 1000);
    actuate_back_wings(false);

}