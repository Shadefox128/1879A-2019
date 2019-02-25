#include "main.h"
#include "io.h"

void opcontrol() {    
    int joy_left_x, joy_left_y, joy_right_x, joy_right_y;
    pros::Controller master(CONTROLLER_MASTER);

    pros::Motor cascade(CASCADE);
    pros::Motor drive_front_left(DRIVE_FRONT_LEFT);
    pros::Motor drive_back_left(DRIVE_BACK_LEFT);
    pros::Motor drive_front_right(DRIVE_FRONT_RIGHT);
    pros::Motor drive_back_right(DRIVE_BACK_RIGHT);
    pros::Motor intake(INTAKE);
    pros::Motor launcher(LAUNCHER);
    pros::Motor arm(ARM);

    cascade.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    while(true) {
        joy_left_x = master.get_analog(ANALOG_LEFT_X);
        joy_left_y = master.get_analog(ANALOG_LEFT_Y);
        joy_right_x = -master.get_analog(ANALOG_RIGHT_X);
        joy_right_y = -master.get_analog(ANALOG_RIGHT_Y);

        if(abs(joy_right_x) > 3 | abs(joy_right_y) > 3 |
            abs(joy_left_x) > 3 | abs(joy_left_y) > 3) {
            drive_front_left.move(joy_left_y - joy_left_x);
            drive_back_left.move(joy_left_y + joy_left_x);
            drive_front_right.move(joy_right_y + joy_right_x);
            drive_back_right.move(joy_right_y - joy_right_x);
        } else {
            drive_front_left.move(0);
            drive_back_left.move(0);
            drive_front_right.move(0);
            drive_back_right.move(0);
        }

        //---CASCADE---
        if(master.get_digital(DIGITAL_L1)) {
            cascade.move(-127);
        } else if(master.get_digital(DIGITAL_L2)) {
            cascade.move(127);
        } else {
            cascade.move(0);
        }

        //---ARM---
        if(master.get_digital(DIGITAL_R1)) {
            arm.move(127);
        } else if(master.get_digital(DIGITAL_R2)) {
            arm.move(-127);
        } else {
            arm.move(0);
        }

        //---INTAKE---
        if(master.get_digital(DIGITAL_DOWN)) {
            intake.move(-127);
        } else if(master.get_digital(DIGITAL_UP)) {
            intake.move(127);
        } else {
            intake.move(0);
        }

        //---LAUNCHER---
        if(master.get_digital(DIGITAL_X)) {
            launcher.move(127);
        } else if(master.get_digital(DIGITAL_B)) {
            launcher.move(-127);
        } else {
            launcher.move(0);
        }
    }
}
