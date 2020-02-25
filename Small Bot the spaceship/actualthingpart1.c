#include <PID.h>
#include <stdio.h>
#include <stdio.bool>
#include <movement.h>

#define sweeper 0
#define sweeperClaw 1
#define spaceshipJoint 2
#define TOPHATL 0
#define TOPHATR 1
#define black
#define white
#define forward true
#define backward false

void animalCrossing(int tape, boolean direction);
void woopTyWoo(int degrees);
void goingOnATrip();
void inOurFavoriteRocketShip();
void zoomingThroughTheSky();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ reference ~~~~~~~~~~~~~~~~~~~~~~~~~~//
/* @function - 
** @param1 -
** @param2 -
*/
//void simultaneous();
/*thread nameHere;
  nameHere = thread_create(simultaneous);
  thread_start(nameHere);*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

int main{
  goingOnATrip();
  inOurFavoriteRocketShip();
  zoomingThroughTheSky();
  return 0;
}

/* @function - cross a certain # of black lines
** @param1 - how many tape to cross
** @param2 - which direction is it going
** note - values must be tested
*/
void animalCrossing(int tape, boolean direction){
  int counter = 0;
  while(counter<tape){
    if(direction){
      while(TOPHATR < black){
        forward(?,?);
        ao();
      }
      ao();
      while(TOPHATR > white){
        forward(?,?);
        ao();
      }
      ao();
    }else{
      while(TOPHATR < black){
        back(?,?);
        ao();
      }
      ao();
      while(TOPHATR > white){
        back(?,?);
        ao();
      }
      ao();
    }
  }
  counter++;
}
  
/* @function - turns left a certain degree
** @param1 - degrees you want to turn
*/
void woopTyWoo(int degrees) {
  double conversion = degrees * 8.5;
  motor(left, -100);
  motor(right, 100);
  msleep(conversion);
}

/* @function - get in position, go backward and pick up cubes
** note - values must be tested
*/
void goingOnATrip(){
  move_to(100,100,???);
  //turn
  enable_servos();
  set_servo_postion(sweeperClaw,1175); //open sweeper
  disable_servos();
  moveSweeper(?,?); //bring sweeper down
  animalCrossing(2, backward); //backup
  move_to(100,100,???); //adjust
  //theWholeShabang function
}

/* @function - going forward and turn before going to astronauts
** note - values must be tested
*/
void inOurFavoriteRocketShip(){
  animalCrossing(1, forward); //foward
  woopTyWoo(90); //turn left
  pid_one_sensor_forwards_till_black(black,75,5000,1); //line follow till black
  woopTyWoo(90); //turn left
  pid_one_sensor_forwards(black,75,3000,1); //line follow until in front of astronauts
}

/* @function - picking up astronauts
** note - values must be tested
*/
void zoomingThroughTheSky(){
  enable_servos();
  set_servo_position(spaceshipJoint, ?); //adjust height of spaceship arm
  disable_servos();
  forward(?,?); //move forward to "fork" the astronauts
  enable_servos();
  set_servo_position(spaceshipJoint, ?); //lift arm slightly to secure the astronauts
  disable_servos();
  back(?,?); //back up a little
  enable_servos();
  set_servo_position(spaceshipJoint, ?); //bring spaceship down
  disable_servos();
  pid_one_sensor_forwards(black,75,3000,1); //line follow with sensor under the bridge
}