#include <stdio.h>
#include <botball.h>
#include <stdbool.h>
#include <math.h>
#include <PIDMovement.h>
#include <turn.h>
#include <movement.h>
// SWEEPER IS BACK AND SPACESHIP IS FRONT 
/*
BASIC STEPS
linefollow for certain amount of time till hits pipe
turn right
follow pipe using button stop after certain amount of time in front of astronauts
lower arm to put astronauts in their suits
open spaceship
raise arm
close spaceship
go forward a little
completely lower arm
backup to pull astronauts in
lift spaceship (put down sweeper)
back up a little
put spaceship down a little (lift sweeper)
backward turn
put sweeper down
open the sweeper
back up
some sort of line follow to get the hell out some how
*/
#define LEFTMOTOR 0
#define RIGHTMOTOR 1
#define BUTTONSENSOR ? 
#define SWEEPERMOTOR ?

void forward(int speed, int time);
void back(int speed, int time);
void moveSpaceShip(int speed, int finalPos);
void moveSweeper(int speed, int time);
void pipefollowSwitch(double time);

int main() {
    enable_servos();
    moveSpaceShip(speed, finalpos);// so that spaceship fits under bridge
    moveSweeper(port, pos); // sweeper fits under the bridge
    pid_one_sensor_forwards(int target, int speed, int milliseconds, int side); // moves till pipe
    turnDegree(int degree); // stationary turn right
    pipefollowSwitch(double time); // until astronauts
    moveSpaceShip(int speed, int finalPos); // lower spaceship (-) speed 
    // open spaceship dont know how it works yet
    moveSpaceShip(speed, int finalPos); // raise spaceship speed should be pretty slow
    forward(speed, 10);
    moveSpaceShip(speed, int finalPos);// lower spaceship so that it touches ground
    back(speed, time);
    moveSpaceShip(speed, int finalPos);// lift spaceship a little bit
    moveSweeper(speed, int time); // raise so that it is able to turn
    turnDegree(int degree); // turn to make space for the cube dropping has to be one wheel so turn on the spot
    forward(speed, time); 
    moveSweeper(speed, int time); // lower sweeper to place blocks
    //get out of the way according to how big bot needs it
    return 0;

}
