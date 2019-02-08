#include "main.h"
#include "io.h"

extern int auton;

void autonomous() {
    pros::Motor cascade_left(CASCADE_LEFT);
    pros::Motor cascade_right(CASCADE_RIGHT);
    pros::Motor drive_left(DRIVE_LEFT);
    pros::Motor drive_right(DRIVE_RIGHT);
    pros::Motor drive_h(DRIVE_H);
    pros::Motor intake(INTAKE);
    pros::Motor launcher(LAUNCHER);
    pros::Motor arm(ARM);

    cascade_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    cascade_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);



    if(auton == 0 || auton == NULL) {
        pros::c::delay(3000);

        //fire at the flag
        launcher.move(-127);
        pros::c::delay(1400);
        launcher.move(0);

        //turn right toward the red unscored cap
        drive_right.move_relative(1100, 127);
        drive_left.move_relative(1100, 127);
        while ((drive_left.is_stopped() != 1) && (drive_right.is_stopped() != 1));

        //drive toward the red unscored cap
        intake.move(127);
        drive_right.move_relative(-5000, -127);
        drive_left.move_relative(5000, 127);
    }
}
