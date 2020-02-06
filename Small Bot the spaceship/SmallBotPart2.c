#include <stdio.h>
#include <botball.h>
#include <stdbool.h>
#include <math.h>
#include <PID.h>
#include <turn.h>

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

void forward(int speed, int time){ //in msleep time
    motor(LEFTMOTOR,speed); //mrp
    motor(RIGHTMOTOR,speed);
    msleep(time);
}
void back(int speed, int time){ //in msleep time
    motor(LEFTMOTOR,speed); //mrp or motor
    motor(LEFTMOTOR,speed);
    msleep(time);
}
void moveSpaceShip(int speed, int finalPos){ // negetive for down 
    curPos = get_servo_position(int port);
    while (curPos < finalPos){  //placement inequality
        set_servo_position(port, curPos+1);
        msleep(10);
    }
}
void moveSweeper(int speed, int time){  // sweeper is a motor, negetive for down
    motor(LEFTMOTOR,speed);
    motor(LEFTMOTOR,speed);
    msleep(time);
}

int main() {
    enable_servos();
    moveSpaceShip(speed, finalpos);// so that spaceship fits under bridge
    moveSweeper(port, pos); // sweeper fits under the bridge
    pid_one_sensor_forwards_till_black(int target, int speed, int milliseconds, int side);
    forward(speed, 20); // reaches the other side of the tape
    turnDegree(int degree); // stationary
    pid_one_sensor_forwards_timed(int speed, int milliseconds, int target, int side);// goes towards astronaut suits
    lowerSpaceShip(int finalPos); // slowly
    // open spaceship
    raiseSpaceShip(int finalPos); // lift spaceship a little bit
    forward(speed, 10);
    lowerSpaceShip(int finalPos);// lower spaceship so that it touches ground
    back(speed, time);
    raiseSpaceShip(int finalPos); // lift spaceship a little bit
    raiseSweeper(int time); // raise so that it is able to turn
    turnDegree(int degree); // turn to make space for the cube dropping has to be one wheel so turn on the spot
    forward(speed, time); 
    lowerSweeper(int time);
    //get out of the way according to how big bot needs it
    return 0;

}
