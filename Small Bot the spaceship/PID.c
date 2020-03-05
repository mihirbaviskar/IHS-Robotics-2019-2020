#include <stdio.h>
#include <math.h>
#include <kipr/botball.h>

//define statements for camera
#define LEFTWHEEL 0
#define RIGHTWHEEL 1
#define KPB 0.01
#define KDB 0.000
#define Kp 0.03
#define DISTANCE_THRESHOLD 1300 // when pid begins to work
#define BLACK analog(0) > 80
#define WHITE analog(0) < 30
//define statements for backwards pid
#define ls analog(4) //left sensor
#define rs analog(5) //right sensor
void pied_piper(int sensor, int target);
void stop_at_black_line();
void pid_two_sensors_forwards_timed(int, int, int);
void move_to(int left_power, int right_power, int milliseconds);
void mav_to(int left_power, int right_power, int milliseconds);
void pid_one_sensor_forwards_till_black(int target, int speed, int milliseconds, int side);
void pid_one_sensor_forwards(int target, int speed, int milliseconds, int side, int sensor);

int flag = 0;
int counter = 0;
void bang_pid_back(int speed, int target, int time){
    int init_seconds = seconds();
    while((seconds()-init_seconds)<time){
        if(analog(0)<target){ //WHITE
            mav(LEFTWHEEL, -(speed+200));
        	mav(RIGHTWHEEL, -(speed-200));
        	msleep(5);
        }
        else{
            mav(LEFTWHEEL, -(speed-200));
        	mav(RIGHTWHEEL, -(speed+200));
        	msleep(5);
        } 
    }   
}
void pied_piper(int sensor, int target)	//0 1100
{
    int position = analog(0);
    msleep(500);
    while(analog(sensor) < target){
        position = analog(0); //current sensor value
        int difference = position - 900;
        int correction = Kp*difference;
        int left_speed = 600 + correction;
        int right_speed = 600 - correction;
        mav(LEFTWHEEL, left_speed);
        mav(RIGHTWHEEL, right_speed);
        msleep(75);
        printf("ET: %i\n", position);
        if(analog(0) >= 1100) { break; }
        //printf("left_speed = %i, right_speed = %i,difference = %i\n", left_speed, right_speed, difference); 
    }
}



void stop_at_black_line() {
	if(BLACK) { //on black
        printf("it is on black\n");
        flag=1;
    }
    if(WHITE) { //on white again	   
    	if(flag==1){
        	printf("passed black\n");
            counter++;
            flag=0; 
	    }
    }
}

void move_to(int left_power, int right_power, int milliseconds)
{
    motor(LEFTWHEEL, left_power);
    motor(RIGHTWHEEL, right_power);
    msleep(milliseconds);
    ao();
}
void pid_right_sensor_forwards(int target, int speed, int seconds, int side){
    int milliseconds = seconds * 1000;
    int counter = 0;
    if(side == 1){ //right side
    while(counter < milliseconds) {
        int position = analog(2);
        int difference = target-position;
        int correction = Kp* difference;
        printf("pos_val: %i, diff_val: %i, correction: %i\n", position, difference, correction);
        int lspeed = speed - correction;
        int rspeed = speed + correction;
        mav(RIGHTWHEEL,rspeed);
        mav(LEFTWHEEL,lspeed);
        msleep(100);
        
        counter+= 100;
    }   
    ao();
    }
    if(side == 0){ //left side
        while(counter < milliseconds) {
        int position = analog(2);
        int difference = target-position;
        int correction = Kp* difference;
        int lspeed = speed + correction;
        int rspeed = speed - correction;
        mav(RIGHTWHEEL,rspeed);
        mav(LEFTWHEEL,lspeed);
        msleep(100);
        
        counter+= 100;
    }   
    ao();
    }
}
void pid_one_sensor_backwards(int target, int speed, double seconds, int side){
    double milliseconds = seconds*1000;
    int counter = 0;
    int last_diff = 0;
    if(side == 1){
    while(counter < milliseconds) {
        int position = analog(2);
        int difference = target-position;
        int correction = KPB* difference + KDB*last_diff;
        printf("%d\n", correction);
        int lspeed = speed + correction;
        int rspeed = speed - correction;
        motor(RIGHTWHEEL,-rspeed);
        motor(LEFTWHEEL,-lspeed);
        msleep(100);
        counter+= 100;
        last_diff = last_diff-difference;
    }   
  }
    if(side == 0){
        while(counter < milliseconds) {
            int position = analog(2);
            int difference = target-position;
            int correction = KPB* difference + KDB*last_diff;
            printf("%d", correction);
            int lspeed = speed - correction;
            int rspeed = speed + correction;
            motor(RIGHTWHEEL,-rspeed);
            motor(LEFTWHEEL,-lspeed);
            msleep(100);
            counter+= 100;
            last_diff = last_diff-difference;
    	}   
    }
}


void pid_two_sensors_forwards_timed(int speed, int seconds, int target){
   int counter = 0;
   int milliseconds = seconds * 1000;
    while(counter < milliseconds) {
        //int rs = analog(2);
        //int ls = analog();
        int right_difference = rs - target;
        int left_difference = ls - target;
        int right_correction = -right_difference * Kp;
        int left_correction = -left_difference * Kp;
        mav(LEFTWHEEL, -speed + left_correction);
        mav(RIGHTWHEEL, -speed + right_correction);
        /*int correction = Kp* difference;
        int lspeed = speed - correction;
        int rspeed = speed + correction;
        mav(RIGHTWHEEL,rspeed);
        mav(LEFTWHEEL,lspeed);*/
        msleep(100);
        
        counter+= 100;
    }   
  
    ao();
}
void pid_one_sensor_forwards_timed(int speed, int seconds, int target, int side){
   int counter = 0;   
   int milliseconds = seconds * 1000;
   while(counter < milliseconds) {
        //int rs = analog(2);
        //int ls = analog();
        int right_difference = rs - target;
        int left_difference = ls - target;
        int right_correction = -right_difference * Kp;
        int left_correction = -left_difference * Kp;
        mav(LEFTWHEEL, -speed + left_correction);
        mav(RIGHTWHEEL, -speed + right_correction);
        /*int correction = Kp* difference;
        int lspeed = speed - correction;
        int rspeed = speed + correction;
        mav(RIGHTWHEEL,rspeed);
        mav(LEFTWHEEL,lspeed);*/
        msleep(100);
        
        counter+= 100;
    }   
  
    ao();
}


void pid_one_sensor_forwards_till_black(int target, int speed, int seconds, int side){
    int counter = 0;
    int milliseconds = seconds * 1000;
    while (analog(2) < 4000)
    {
        if(side == 1){ //right side
            while(counter < milliseconds) {
                int position = analog(2);
                int difference = target-position;
                int correction = Kp * difference;
                printf("pos_val: %i, diff_val: %i, correction: %i\n", position, difference, correction);
                int lspeed = speed - correction;
                int rspeed = speed + correction;
                mav(RIGHTWHEEL, rspeed);
                mav(LEFTWHEEL, lspeed);
                msleep(100);
                
                counter+= 100;
            }   
            ao();
        }
        if(side == 0){ //left side
            while(counter < milliseconds) {
                int position = analog(2);
                int difference = target-position;
                int correction = Kp* difference;
                int lspeed = speed + correction;
                int rspeed = speed - correction;
                mav(RIGHTWHEEL, rspeed);
                mav(LEFTWHEEL, lspeed);
                msleep(100);
                
                counter+= 100;
            }   
            ao();
        }
    }
}


void pid_one_sensor_forwards(int target, int speed, int seconds, int side, int sensor){
    // parameter side: 0 for left; 1 for right      parameter sensor : 1 for left; 2 or right
    int counter = 0;
    int milliseconds = seconds * 1000;
    
    if(side == 1){ //right side
        while(counter < milliseconds) {
            int position = analog(sensor);
            int difference = target-position;
            double correction = Kp* difference;
            printf("pos_val: %i, diff_val: %i, correction: %lf\n", position, difference, correction);
            double lspeed = speed - correction;
            double rspeed = speed + correction;
            mav(RIGHTWHEEL, rspeed);
            mav(LEFTWHEEL, lspeed);
            msleep(100);
            
            counter+= 100;
        }   
        ao();
    }

    if(side == 0){ //left side
        while(counter < milliseconds) {
        int position = analog(sensor);
        int difference = target-position;
        double correction = Kp * difference;
        printf("pos_val: %i, diff_val: %i, correction: %lf\n", position, difference, correction);
        double lspeed = speed + correction;
        double rspeed = speed - correction;
        mav(RIGHTWHEEL, rspeed);
        mav(LEFTWHEEL, lspeed);
        msleep(100);
        
        counter+= 100;
        }   
        ao();
    }
}

void gradual_move(int leftpower, int rightpower, double time) {
    double rate = 0.1;
    int i;
    double rightspeed = rightpower * rate;
    double leftspeed = leftpower * rate;
    for(i = 0; i < 10; i++) {
        motor(LEFTWHEEL, leftspeed*1.04);
        motor(RIGHTWHEEL, rightspeed);
        msleep(time/10);
        rightspeed = rightpower * rate;
        leftspeed = leftpower * rate;
        rate += 0.1;
        }
    ao();
}

void distance_pid_one_sensor_forwards(int target, int speed, int seconds, int side, int sensor,  int distance){
  while (analog(3) < distance) {
    int counter = 0;
    int milliseconds = seconds * 1000;
    if(side == 1){ //right side
    	while(counter < milliseconds) {
            int position = analog(sensor);
            int difference = target-position;
            double correction = Kp* difference;
            //printf("pos_val: %i, diff_val: %i, correction: %lf\n", position, difference, correction);
            printf("distance; %i\n", analog(3));
            double lspeed = speed - correction;
            double rspeed = speed + correction;
            mav(RIGHTWHEEL, rspeed);
            mav(LEFTWHEEL, lspeed);
            msleep(1);
            
            counter+= 1;
        }   
        ao();
    }
	if(side == 0){ //left side
        while(counter < milliseconds) {
            int position = analog(sensor);
            int difference = target-position;
            double correction = Kp * difference;
            //printf("pos_val: %i, diff_val: %i, correction: %lf\n", position, difference, correction);
            printf("distance; %i\n", analog(3));
            double lspeed = speed + correction;
            double rspeed = speed - correction;
            mav(RIGHTWHEEL, rspeed);
            mav(LEFTWHEEL, lspeed);
            msleep(1);

            counter+= 1;
        }   
    	ao();
	}	
  }
}
      

   
    
    
