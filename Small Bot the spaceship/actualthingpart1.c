//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <stdio.h>
#include <kipr/botball.h>
#include <stdbool.h>
#include <movement.h>
#include <Claw.h>
#include <FloorPlan.h>

/* February 27 Plan
** - Test values for:
**   - startPos()
**   - WHITE
**   - zoomingThroughTheSky()
**   - theWholeShebang()
** - Split into two teams for:
**   - Test goingOnATrip() w/o theWholeShebang()
**   - Update theWholeShebang()
*/

int main() {
    pid_one_sensor_forwards(1600, 600, 20000, 'R', 0, 0.15);
    /*enable_servos();
    moveSweeper(70,400);
    msleep(500);
    theWholeShebang();
    disable_servos();*/
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FloorPlan ~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <kipr/botball.h>

#define TOPHAT analog(0)
#define FORWARD true
#define BACKWARD false
#define BLACK 2000
#define WHITE
#define SWEEPERCLAW 0
#define SWEEPERARM 1
#define SPACESHIPARM 2
#define SPACESHIPHEAD 3

void startPos(){
    moveSweeper(70,1200); //UP???
    moveSpaceShip(70,0); //UP (change val; adjust to astronaut height)
    set_servo_position(SWEEPERCLAW,1350); //OPEN
    set_servo_position(SPACESHIPHEAD,); //original tilt position
}

void animalCrossing(int tape, bool direction){
    int counter = 0;
    while(counter < tape){
        if(direction){
            while(TOPHAT < BLACK){
                move_to(100,100,1);
                ao();
            }
            ao();
            while(TOPHAT > WHITE){
                move_to(100,100,1);
                ao();
            }
            ao();
        }else{
            while(TOPHAT < BLACK){
                move_to(-100,-100,1);
                ao();
                
            }
            ao();
            while(TOPHAT > WHITE){
                move_to(-100,-100,1);
                ao();
            }
            ao();
        }
    }
    counter++;
}

void goingOnATrip(){
    while(TOPHAT < BLACK){ //move forward
        move_to(100,100,1);
    }
    ao();
    move_to(-100,-100,100); //adjust
    while(TOPHAT < BLACK){ //turn
        move_to(-25,-50,1);
    }
    ao();
    move_to(100,100,2000); //move forward to go against pipe
    moveSweeper(70,400);
    msleep(100);
    animalCrossing(2, BACKWARD); //backup & push boxes together
    move_to(100,100,500); //adjust
    theWholeShebang();
}

void inOurFavoriteRocketShip(){
    animalCrossing(1, FORWARD); //foward
    move_to(50,100,90*8.5); //turn left
    pid_one_sensor_forwards_till_black(BLACK,75,5000,1); //!! wrong analog !!
    move_to(50,100,90*8.5); //turn left
    pid_one_sensor_forwards(BLACK,75,3000,1); //into the astronauts
}

void zoomingThroughTheSky(){
    set_servo_position(SPACESHIPHEAD, ?); //tilt head
    move_to(-100,-100,1000)
    set_servo_position(SPACESHIPARM, ?); //lower spaceship
    pid_one_sensor_forwards(BLACK,75,3000,1); //go under bridge
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Claw ~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include <kipr/botball.h>

#define SWEEPERCLAW 0
#define SWEEPERARM 1

void clapClaw(int speed, int finalClaw){
    int curClaw = get_servo_position(SWEEPERCLAW)
    while(curClaw > finalClaw){
        set_servo_position(SWEEPERCLAW, curClaw - 5);
    	curClaw = get_servo_position(SWEEPERCLAW);
        msleep(speed);
    }
}

void theActualThing(){
    clapClaw(1,525);
}

void theWholeShebang(){
    /*clapClaw(1,1000);
    set_servo_position(SWEEPERCLAW,1350);
    moveSweeper(70,400);
    msleep(200);*/
    thread sweeperPickUp;
    sweeperPickUp = thread_create(theActualThing);
    thread_start(sweeperPickUp);
    msleep(500);
    moveSweeper(50,1200); //make it lower
    thread_destroy(sweeperPickUp);
}
