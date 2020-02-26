#include <PID.h>
#include <stdio.h>
#include <stdio.bool>
#include <movement.h>

#define sweeper 0
#define sweeperClaw 1
#define spaceshipJoint 2
#define TOPHAT 0
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
  while(TOPHAT < black){ //move forward
    move_to(100,100,1);
  }
  ao();
  move_to(-100,-100,100); //adjust
  while(TOPHAT < black){ //turn
    move_to(-25,-50,1);
  }
  ao();
  move_to(100,100,2000); //move forward to go against pipe
  enable_servos();
  set_servo_position(sweeperClaw,1350);
  moveSweeper(70,400);
  msleep(100);
  animalCrossing(2, backward); //backup & push boxes together
  move_to(100,100,500); //adjust
  theWholeShabang();
}

/* @function - going forward and turn before going to astronauts
** note - values must be tested
*/
void inOurFavoriteRocketShip(){
  animalCrossing(1, forward); //foward
  move_to(-100,100,765); //turn left
  pid_one_sensor_forwards_till_black(black,75,5000,1); //line follow till black
  move_to(-100,100,765); //turn left
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
