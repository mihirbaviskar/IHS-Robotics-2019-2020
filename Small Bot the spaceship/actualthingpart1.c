//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <stdio.h>
#include <kipr/botball.h>
#include <stdbool.h>
#include <movement.h>
#include <Claw.h>
#include <FloorPlan.h>

#define FORWARD true
#define BACKWARD false

int main() {
    enable_servos();
    //startPos();
    goingOnATrip();
    inOurFavoriteRocketShip();
    zoomingThroughTheSky();
    disable_servos();
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FloorPlan ~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <kipr/botball.h>
#include <AlignPerp.h>
#define TOPHAT analog(0)
#define FORWARD true
#define BACKWARD false
#define BLACK 2000
#define WHITE 200
#define SWEEPERCLAW 0
#define SWEEPERARM 1
#define SPACESHIPARM 2
#define SPACESHIPHEAD 3

void startPos(){
    moveSweeper(70,1400); //UP
    moveSpaceShip(70,100); //UP
    set_servo_position(SWEEPERCLAW,1250); //OPEN
    thePeopleFork(10, 970); //TILT DOWN
}

void animalCrossing(int tape, bool direction){
    int counter = 0;
    while(counter < tape){
        if(direction){
            while(TOPHAT < BLACK){
                move_to(100,71,1);
                ao();
                printf("%d\n",counter);
            }
            while(TOPHAT > WHITE){
                move_to(100,71,1);
                ao();
                printf("%d\n",counter);
            }
        }
        else{
            while(TOPHAT < BLACK){
                motor(RIGHTMOTOR, -51);
                motor(LEFTMOTOR, -50);
                msleep(10);
            }
            while(TOPHAT > WHITE){
                motor(RIGHTMOTOR, -51);
                motor(LEFTMOTOR, -50);
                msleep(10);
            }
        }
        counter++;
    }
}

void goingOnATrip(){
    startPos();
    move_to(30,-60,2060);
    set_servo_position(0,900);
    msleep(500);
    moveSweeper(70,465);
    move_to(-50,-50,1000);
    clapClaw(15,1500);
    move_to(-50,-50,1000);
    align(1, 2000 , 2000);
    animalCrossing(2,BACKWARD);
    align(2, 1600, 3000);
    move_to(50, 50, 180);
    clapClaw(20,600);
    clapClaw(20,1500);
    msleep(1000);
    theWholeShebang();
}

void inOurFavoriteRocketShip(){
    move_to(60, 60, 1500);
    align(2, 1600, 1600);
    msleep(1000);
    move_to(-60, -60, 700);
    move_to(0, 80, 2400);
    move_to(60, 60, 3400);
    move_to(-60, 60, 1700);
	set_servo_position(SPACESHIPARM,95);
    thePeopleFork(20, 970);
    pid_one_sensor_forwards(1600, 800, 2000, 'R', 0, 0.25);
    pid_one_sensor_forwards(2500, 500, 2200, 'R', 0, 0.1);
    thePeopleFork(20, 1300);
}

void zoomingThroughTheSky(){
    move_to(-50, -50, 1000);
    move_to(50, -50, 1500);
    while(analog(3) < 2000) {
        motor(RIGHTMOTOR, -50);
        motor(LEFTMOTOR, 50);
        msleep(10);
    }
    ao();
    while(analog(3) > 1500) {
        motor(RIGHTMOTOR, -30);
        motor(LEFTMOTOR, 30);
        msleep(1);
    }
    ao();
    moveSpaceShip(20,920);
    moveSweeper(20,690); //lower sweeper
    msleep(3000);
    pid_one_sensor_backwards(2500, 30, 7, 0);
    pid_one_sensor_backwards(2500, 30, 2, 0);
    pid_one_sensor_backwards(2500, 30, 5, 0);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Claw ~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <kipr/botball.h>

#define SWEEPERCLAW 0
#define SWEEPERARM 1

void clapClaw(int speed, int finalClaw){
    int curClaw;
    curClaw = get_servo_position(SWEEPERCLAW);
    if((curClaw - finalClaw) > 0){
        while(curClaw > finalClaw){
        set_servo_position(SWEEPERCLAW, curClaw - 5);
    	curClaw = get_servo_position(SWEEPERCLAW);
        msleep(speed);
        }
    }
    if((curClaw - finalClaw) < 0){
        while(curClaw < finalClaw){
        set_servo_position(SWEEPERCLAW, curClaw + 5);
    	curClaw = get_servo_position(SWEEPERCLAW);
        msleep(speed);
        }
    }
    msleep(2000);
}

void thePeopleFork(int speed, int finalClaw){
    int curClaw;
    curClaw = get_servo_position(3);
    if((curClaw - finalClaw) > 0){
        while(curClaw > finalClaw){
        set_servo_position(3, curClaw - 5);
    	curClaw = get_servo_position(3);
        msleep(speed);
        }
    }
    if((curClaw - finalClaw) < 0){
        while(curClaw < finalClaw){
        set_servo_position(3, curClaw + 5);
    	curClaw = get_servo_position(3);
        msleep(speed);
        }
    }
    msleep(2000);
}


void theActualThing(){
    clapClaw(20,500);
}

void theWholeShebang(){
    moveSweeper(70,400);//DOWN
  	msleep(500);
    thread sweeperPickUp;
	sweeperPickUp = thread_create(theActualThing);
	thread_start(sweeperPickUp);
    msleep(3000);
    moveSweeper(25,1200);
    thread_destroy(sweeperPickUp);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ All Servo Values ~~~~~~~~~~~~~~~~~~~~~~~~~~//
//OPEN claw: 1250 (reset)
//CLOSE claw: 550
//Sweeper UP: 1400 (reset), 690 (final)
//Sweeper DOWN: 400

//TILT Spaceship: 0 (reset), 700 (straight), 100 (slanted)
//Spaceship UP: 100 (reset)
//Spaceship DOWN: 900
