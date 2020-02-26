#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <botball.h>

#declare NULL -1
#declare XMAX 1920
#declare YMAX 1080
#declare MULTIPLIER
#declare RANGE XMAX*MULTIPLIER;
#declare KP 0.2
#declare GREEN 3

int camera_detect(int, int);
void camera_turn();

int main (void) {
  if (camera_detect(GREEN, 5) == 1) {
    camera_turn();
  }
  return 0;
}

struct Camera {
  int x;
  int y;
  int area;
}

struct View {
  int x;
  int y;
}

int camera_detect(int channel, int sec) {
  struct Camera c = {NULL, NULL, NULL};
  int t = 0;
  camera_open();
  do {
    camera_update();
     if (get_object_count(channel) > 0) {
       c.x = get_object_center(channel, 0).x; 
       c.y = get_object_center(channel, 0).y;
       c.area = get_object_area(channel, 0);
     }
     t++;
  } while (t < sec*1000 && (c.x == NULL || c.y == NULL) && c.area < 20);
  if (t < sec*1000) { return -1; }
  return 1;
}

void camera_turn();) {
  struct View v = {XMAX/2, YMAX/2};
  int diff = c.x - v.x;
  while (!(c.x >= v.x-RANGE && c.x <= v.x+RANGE)) {
    motor(LEFT, diff*KP);
    motor(RIGHT, -diff*KP);
  }

}
