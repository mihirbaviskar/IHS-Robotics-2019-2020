//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <stdio.h>
#include <kipr/botball.h>
#include <stdbool.h>
#include <movement.h>
#include <Claw.h>
#include <FloorPlan.h>

#define FORWARD true
#define BACKWARD false

/* March 11th Plan
** - Run hella trials for everything in main()
** - Fix whatever
*/

int main() {
    enable_servos();
    //inOurFavoriteRocketShip();
    startPos();
    /*moveSweeper(70,465);
    clapClaw(20,800);
    set_servo_position(0,1500);
    msleep(1000);
    theWholeShebang();
    move_to(-100,-100,2000);*/
    move_to(30,-60,2070);
    set_servo_position(0,900);
    msleep(500);
    moveSweeper(70,465);
    move_to(-50,-50,1000);
    clapClaw(15,1500);
    move_to(-50,-50,1000);
    msleep(5000);
    align(1, 2000 , 2000);
    animalCrossing(2,BACKWARD);
    align(2, 1500, 2800);
    move_to(50, 50, 180);
    clapClaw(20,600);
    clapClaw(20,1500);
    msleep(1000);
    theWholeShebang();
    inOurFavoriteRocketShip();
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
    set_servo_position(SPACESHIPHEAD,50); //TILT DOWN
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
                motor(RIGHTMOTOR, -52);
                motor(LEFTMOTOR, -50);
                msleep(10);
            }
            while(TOPHAT > WHITE){
                motor(RIGHTMOTOR, -52);
                motor(LEFTMOTOR, -50);
                msleep(10);
            }
        }
        counter++;
    }
}

void goingOnATrip(){
    
}

void inOurFavoriteRocketShip(){
    move_to(60, 60, 1500);
    align(2, 1600, 1600);
    msleep(1000);
    move_to(-60, -60, 700);
    move_to(0, 80, 2400);
    move_to(60, 60, 3400);
    move_to(-60, 60, 1500);
	set_servo_position(SPACESHIPARM,95);
    set_servo_position(SPACESHIPHEAD,700);
    pid_one_sensor_forwards(1600, 800, 2000, 'R', 0, 0.1);
    pid_one_sensor_forwards(1600, 500, 2700, 'R', 0, 0.1);
    /*pid_one_sensor_forwards_till_black(BLACK,75,5000,1); //!! wrong analog !!
    move_to(50,100,90*8.5); //turn left, TEST VAL
    pid_one_sensor_forwards(BLACK,75,3000,1,0,0); //into the astronauts*/
}

/*void zoomingThroughTheSky(){
    set_servo_position(SPACESHIPHEAD, 100); //tilt head
    move_to(-100,-100,1000);//TEST VAL
    set_servo_position(SPACESHIPARM, 900); //lower spaceship
    moveSweeper(70,690); //lower sweeper
    pid_one_sensor_forwards(BLACK,75,3000,1,0,0); //TEST VAL
}*/

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

void theActualThing(){
    clapClaw(20,600);
}

void theWholeShebang(){
    moveSweeper(70,400);//DOWN
  	msleep(500);
    thread sweeperPickUp;
	sweeperPickUp = thread_create(theActualThing);
	thread_start(sweeperPickUp);
    msleep(3000);
    moveSweeper(30,1200);
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
