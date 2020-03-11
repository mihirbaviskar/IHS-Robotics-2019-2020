#include <kipr/botball.h>
#include <stdio.h>
#include <math.h>
#define LEFTMOTOR 0
#define RIGHTMOTOR 1
#define BUTTONSENSOR 3
#define SWEEPERCLAW 0 
#define SWEEPERRAISE 1
#define SPACESHIP 2
#define LEFTSIDE 0
#define RIGHTSIDE 1
#define LFLINE analog(0)
#define RTLINE analog(1)
/* Claw Bounds */
#define SWEEPMAX 1300
#define SWEEPMED 750
#define SWEEPMIN 250
#define SWEEPCLOSE 450
#define SWEEPDROP 975
#define SWEEPOPEN 1500
void forward(int speed, int time){ //in msleep time
    motor(LEFTMOTOR,speed); //mrp
    motor(RIGHTMOTOR,speed);
    msleep(time);
}
void back(int speed, int time){ //in msleep time
    motor(LEFTMOTOR,-speed); //mrp or motor
    motor(RIGHTMOTOR,-speed);
    msleep(time);
}
void move_servo(int port,int speed, int position){  // sweeper is a motor, negetive for down
    int curPos = get_servo_position(port);
    if(curPos<position){
        while (curPos < position){  //placement inequality
            curPos+=speed/10;
            set_servo_position(port, curPos);
            msleep(10);
        }
    }
    else{
        while (curPos > position){  //placement inequality
            curPos-=speed/10;
            set_servo_position(port, curPos);
            msleep(10);
        }
    }
}
void pipefollowSwitch(double time) {
    double initialTime = seconds();

    while (seconds() <= initialTime + time) {
        if (BUTTONSENSOR == 1) {
            motor(LEFTMOTOR, 100);
            motor(RIGHTMOTOR, 90);
        } 
        else {
            motor(LEFTMOTOR, 85);
            motor(RIGHTMOTOR, 100);        
        }
    }
}
void organize_cubes(){
    move_servo(SWEEPERRAISE, 50, SWEEPMIN); //lowers claw
    move_servo(SWEEPERCLAW, 50, SWEEPCLOSE); //closes claw
    move_servo(SWEEPERRAISE, 50, SWEEPMAX); //raises the claw up
    mav(LEFTMOTOR, -750);
    mav(RIGHTMOTOR, -550);
    msleep(2200); //moves forward to the large boxes
    ao();
    
    move_servo(SWEEPERRAISE, 50, SWEEPDROP);
    move_servo(SWEEPERCLAW, 50, SWEEPOPEN); //drops blocks
    msleep(500);
    move_servo(SWEEPERRAISE, 50, SWEEPMAX);
    move_servo(SWEEPERCLAW, 50, SWEEPOPEN+450); //lifts up and flattens claw
    msleep(500);
    mav(LEFTMOTOR, 750);
    mav(RIGHTMOTOR, 750);
    msleep(700);
    ao();
    move_servo(SWEEPERRAISE, 50, SWEEPMIN+500); //pushes claw on cubes
    //move_servo(SWEEPERRAISE, 50, SWEEPMED);
    msleep(500);
    
}
