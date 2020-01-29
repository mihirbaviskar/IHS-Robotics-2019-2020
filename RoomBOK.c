#include<kipr/botball.h>
#include<stdio.h>
#include<math.h>

#define BLACK 2000
#define WHITE 4000

void moveForward(int s, int t) {
  create_drive_direct(s, s);
  msleep(t*1000);
}

void go_until_black(int sensor, int speed) {
  if(sensor == LCLIFF) {
    while(get_create_lcliff_amt() > BLACK) {
      moveForward(100, .001);
    }
  }
  else if(sensor == LFCLIFF) {
    while(get_create_lfcliff_amt() > BLACK) {
      moveForward(100, .001);
    }
  }  
  else if(sensor == RFCLIFF) {
    while(get_create_rfcliff_amt() > BLACK) {
      moveForward(100, .001);
    }
  }
  else {
    while(get_create_rcliff_amt() > BLACK) {
      moveForward(100, .001);
    }
  }
}

void back_until_black(int sensor, int speed) {
  if(sensor == LCLIFF) {
    while(get_create_lcliff_amt() > BLACK) {
      moveForward(-100, .001);
    }
  }
  else if(sensor == LFCLIFF) {
    while(get_create_lfcliff_amt() > BLACK) {
      moveForward(-100, .001);
    }
  }  
  else if(sensor == RFCLIFF) {
    while(get_create_rfcliff_amt() > BLACK) {
      moveForward(-100, .001);
    }
  }
  else {
    while(get_create_rcliff_amt() > BLACK) {
      moveForward(-100, .001);
    }
  }
}

void go_until_white(int sensor, int speed) {
  if(sensor == LCLIFF) {
    while(get_create_lcliff_amt() < WHITE) {
      moveForward(100, .001);
    }
  }
  else if(sensor == LFCLIFF) {
    while(get_create_lfcliff_amt() < WHITE) {
      moveForward(100, .001);
    }
  }  
  else if(sensor == RFCLIFF) {
    while(get_create_rfcliff_amt() < WHITE) {
      moveForward(100, .001);
    }
  }
  else {
    while(get_create_rcliff_amt() < WHITE) {
      moveForward(100, .001);
    }
  }
}

void back_until_white(int sensor, int speed) {
  if(sensor == LCLIFF) {
    while(get_create_lcliff_amt() < WHITE) {
      moveForward(-100, .001);
    }
  }
  else if(sensor == LFCLIFF) {
    while(get_create_lfcliff_amt() < WHITE) {
      moveForward(-100, .001);
    }
  }  
  else if(sensor == RFCLIFF) {
    while(get_create_rfcliff_amt() < WHITE) {
      moveForward(-100, .001);
    }
  }
  else {
    while(get_create_rcliff_amt() < WHITE) {
      moveForward(-100, .001);
    }
  }
}
