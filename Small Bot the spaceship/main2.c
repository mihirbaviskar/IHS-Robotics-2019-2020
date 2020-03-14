#include <kipr/botball.h>
#include <Movement.h>
#include <PID.h>
#include <AlignPerp.h>
/* Ports */
#define LEFTMOTOR 0
#define RIGHTMOTOR 1
//#define BUTTONSENSOR 3
#define SWEEPERCLAW 0 
#define SWEEPERRAISE 1
#define SPACESHIP 2
#define ATILT 3
/* PID */
#define LEFTSIDE 0
#define RIGHTSIDE 1
/* Align */
#define OVERLINE 1
#define UNDERLINE 2
/* Claw Bounds */
#define SWEEPMAX 1300

#define SWEEPMIN 250
#define SWEEPCLOSE 450
#define SWEEPDROP 975
#define SWEEPOPEN 1500
// ANALOGS
#define LFLINE analog(0)
#define RTLINE analog(1)
#define TARGET 1900
#define WHITE analog(3) < 3200
#define BLACK analog(3) > 3200
// ET sensor
#define THRESHOLD 2900
int main() {
    enable_servos();
    move_servo(ATILT, 50, 1600); // 1156 with astronauts
    organize_cubes();
    while(analog(1)<TARGET+1000){
    	pid_one_sensor_backwards(TARGET, 50, 0.01, LEFTSIDE);
    }
    ao();
   	msleep(250);
    mav(LEFTMOTOR, -500); //tilt robot left to fit the cubes in the zone
    mav(RIGHTMOTOR, -1000);
    msleep(2000);
    ao();
    
    
  /* while (analog(3) < TARGET) { //moves back until front sensor touches black
    	mav(LEFTMOTOR, 750);  //stuff to comment later on
    	mav(RIGHTMOTOR, 750);
    }*/
    
   	mav(LEFTMOTOR, 400);  // going 'back' to 
    mav(RIGHTMOTOR, 950);
    msleep(650);
    ao();
    
    move_servo(SWEEPERRAISE, 50, SWEEPMAX+200); //raises claw to go over ramp
    while (WHITE) {
        printf("Moving from white to black.\n");
        mav(LEFTMOTOR, -750); 
        mav(RIGHTMOTOR, 750);
    }
    ao();
    msleep(2000);
    while (BLACK) {
        printf("Moving from black to white, forward.\n");
		mav(LEFTMOTOR,  750); 
        mav(RIGHTMOTOR, 750);
    }
    ao();
	msleep(2000);

    
    while (WHITE) {
        printf("Moving from white to black.\n");
        mav(LEFTMOTOR, -750); 
        mav(RIGHTMOTOR, 750);
    }
    ao();
    msleep(2000);
    while (BLACK) {
        printf("Moving from black to white, turn.\n");
        mav(LEFTMOTOR, -750); 
        mav(RIGHTMOTOR, 750);
    }
    ao();
    align(OVERLINE, 1, 0, TARGET, TARGET); //align robot parallel to black line
    ao(); 
    mav(LEFTMOTOR, -750); 
    mav(RIGHTMOTOR, -750);
    msleep(300);
    ao();
    align(UNDERLINE, 1, 0, TARGET, TARGET); //align robot parallel to black line
    move_servo(SPACESHIP,50, 500);
    while(analog(4) < THRESHOLD){
    pid_one_sensor_forwards(2900, 600, 0.001, LEFTSIDE, 3);
    }
    ao();
    move_servo(ATILT,50, 1500);
    msleep(2000);
    move_servo(SPACESHIP, 20, 1450);
    msleep(2000);
    move_servo(ATILT,50, 1100);
    msleep(2000);
    ao();
    mav(LEFTMOTOR, -450); 
    mav(RIGHTMOTOR, 250);
    msleep(550);
    ao();
    mav(LEFTMOTOR, 300); 
    mav(RIGHTMOTOR, 300);
    msleep(150);
    int i;
    for (i = 0; i<=4; i++){
        mav(LEFTMOTOR, -400); 
        mav(RIGHTMOTOR, 200);
        msleep(640);
        ao();
        mav(LEFTMOTOR, 300); 
        mav(RIGHTMOTOR, 300);
        msleep(475);
        ao();
    }
    move_servo(ATILT,50, 700);
    msleep(2000);
    mav(LEFTMOTOR, -1000);  // go back after pulling them in
    mav(RIGHTMOTOR, -1000);
    msleep(900);
    ao();
    msleep(2000);
    move_servo(SPACESHIP, 80, 700);
    msleep(2000);
    move_servo(ATILT,50, 750);
    msleep(2000);
    ao();
    mav(LEFTMOTOR, -1000);  // go back after dropping them
    mav(RIGHTMOTOR, -1000);
    msleep(700);
    ao();
    align(OVERLINE, 1, 0, TARGET, TARGET); //align robot parallel to black line
	move_servo(ATILT,50, 1600);
    move_servo(SPACESHIP,50, 1200);
    move_servo(SWEEPERRAISE,80,550);
    move_servo(SWEEPERCLAW,80,1000);
    msleep(100);
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
