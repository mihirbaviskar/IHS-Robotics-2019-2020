#include <kipr/botball.h>
#include <movement.h>
#include <PID.h>
#include <AlignPerp.h>
/* Ports */
#define LEFTMOTOR 0
#define RIGHTMOTOR 1
//#define BUTTONSENSOR 3
#define SWEEPERCLAW 0 
#define SWEEPERRAISE 1
#define SPACESHIP 2
/* PID */
#define LEFTSIDE 0
#define RIGHTSIDE 1
/* Align */
#define OVERLINE 1
#define UNDERLINE 2
/* Claw Bounds */
#define SWEEPMAX 1300
#define SWEEPMED 750
#define SWEEPMIN 250
#define SWEEPCLOSE 450
#define SWEEPDROP 975
#define SWEEPOPEN 1500

#define LFLINE analog(0)
#define RTLINE analog(1)
#define TARGET 1900
#define WHITE analog(3) < TARGET
#define BLACK analog(3) > TARGET
int main() {
    enable_servos();
    
    move_servo(SWEEPERRAISE, 50, SWEEPMIN); //lowers claw
    move_servo(SWEEPERCLAW, 50, SWEEPCLOSE); //closes claw
    move_servo(SWEEPERRAISE, 50, SWEEPMAX); //raises the claw up
    
    mav(LEFTMOTOR, -750);
    mav(RIGHTMOTOR, -750);
    msleep(1800); //moves forward to the large boxes
    ao();
    move_servo(SWEEPERRAISE, 50, SWEEPDROP);
    move_servo(SWEEPERCLAW, 50, SWEEPOPEN); //drops blocks
    msleep(500);
    move_servo(SWEEPERRAISE, 50, SWEEPMAX);
    move_servo(SWEEPERCLAW, 50, SWEEPOPEN+200); //lifts up and flattens claw
    msleep(500);
    mav(LEFTMOTOR, 750);
    mav(RIGHTMOTOR, 750);
    msleep(700);
    ao();
   
    move_servo(SWEEPERRAISE, 50, SWEEPMIN+500); //pushes claw on cubes
    //move_servo(SWEEPERRAISE, 50, SWEEPMED);
    msleep(500);
    
    while(analog(1)<TARGET){
    	pid_one_sensor_backwards(TARGET, 50, 0.01, RIGHTSIDE);
    }
    
   	msleep(250);
    mav(LEFTMOTOR, -500); //tilt robot left to fit the cubes in the zone
    mav(RIGHTMOTOR, -1000);
    msleep(1800);
    ao();
    
    /*
    while (analog(3) < TARGET) { //moves back until front sensor touches black
    	mav(LEFTMOTOR, 750);
    	mav(RIGHTMOTOR, 750);
    }
    */
   	mav(LEFTMOTOR, 750);
    mav(RIGHTMOTOR, 750);
    msleep(500);
    ao();
   
    move_servo(SWEEPERRAISE, 50, SWEEPMAX+200); //raises claw to go over ramp
    while (WHITE) {
        mav(LEFTMOTOR, -750); 
        mav(RIGHTMOTOR, 750);
    }
    ao();
    while (BLACK) {
        mav(LEFTMOTOR, -750); 
        mav(RIGHTMOTOR, 750);
    }
    ao();
    
    mav(LEFTMOTOR, -750); 
    mav(RIGHTMOTOR, 750);
    msleep(1000);
    ao();
    
    align(OVERLINE, 1, 0, TARGET, TARGET); //align robot parallel to black line
    ao();
    //pid_one_sensor_backwards(TARGET, 50, 1.8, RIGHTSIDE); //change distance
    /*while(analog(1)<TARGET){
        mav(LEFTMOTOR,-750);    
        mav(RIGHTMOTOR,-750);
        msleep(10);
    }
    while(analog(1)>TARGET){
        mav(LEFTMOTOR,-750);    
        mav(RIGHTMOTOR,-750);
        msleep(10);
    }*/

    disable_servos();
    return 0;

}
