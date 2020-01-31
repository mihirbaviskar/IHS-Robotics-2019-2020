#include<kipr/botball.h>
#include<stdio.h>
#include<math.h>
#include<stdbool.h>

/*PID MOVEMENT--------------------------------------------------------------------------------------*/
#define RIGHTSIDE 1
#define LEFTSIDE 2
#define KP 5    //a       vvv
#define KI 0.25 //b, b<a  Must be guess and checked. We got this from our testing. Changing these values will change Distance Incrementation.
#define KD 0.1 //c, c~a   ^^^

/*OFFSETS/SCALARS------------------------------------------------------------------------------------*/
#define move_offset 1
//Movement Offset
    //Due to gyro oscillation, take average of Gyro Readings, about 100 iterations whilst stationary
    //Subtract an offset from the average Gyro Readings
#define angle_offset 1000 //old: 986
 //Offset 2 (Angle Scalar) 
    //Convert given angle into a more suitable value that lines up with gyro readings
#define CCW_offset 1
//Offset 3 (Clockwise vs Counterclockwise, Scalar)
    //Convert Counterclockwise turn value to work for 90 degrees

/*WHEELS------------------------------------------------------------------------------------*/
#define LWHEEL 1
#define RWHEEL 2

/*TURN------------------------------------------------------------------------------------*/
#define rbTurn 40 //roomba reverse turn constant
#define sbTurn 40 //small bot reverse turn constant
/*ARRAY INDEXES------------------------------------------------------------------------------------*/
#define CURRENT_ANGLE 0
#define PREV_ANGLE 1
#define PREV_VELOCITY 2
#define CURRENT_VELOCITY 3
#define CHANGE_IN_VELOCITY 4

double angle_arr[] = {0.0, 0.0, 0.0, 0.0, 0.0};  //{CURRENT_ANGLE, PREV_ANGLE, PREV_VELOCITY, CURRENT_VELOCITY, CHANGE_IN_VELOCITY}

/*DEFINES-----------------------------------------------------------------------------------*/
#define BLACK 2000
#define WHITE 4000
#define LCLIFF 0
#define LFCLIFF 1
#define RFCLIFF 2
#define RCLIFF 3


void moveForward(int s, int t) {
  create_drive_direct(s, s);
  msleep(t);
}

/*-------------------------------------------------------------------------------------------------
			     _____ ______ _   _  _____  ____  _____  
			    / ____|  ____| \ | |/ ____|/ __ \|  __ \ 
			   | (___ | |__  |  \| | (___ | |  | | |__) |
			    \___ \|  __| | . ` |\___ \| |  | |  _  / 
			    ____) | |____| |\  |____) | |__| | | \ \ 
			   |_____/|______|_| \_|_____/ \____/|_|  \_\
sensor movement
--------------------------------------------------------------------------------------------------*/

void go_until_black(int sensor, int s) {
  if(sensor == LCLIFF) {
    while(get_create_lcliff_amt() > BLACK) {
      moveForward(s, .001);
    }
  }
  else if(sensor == LFCLIFF) {
    while(get_create_lfcliff_amt() > BLACK) {
      moveForward(s, .001);
    }
  }  
  else if(sensor == RFCLIFF) {
    while(get_create_rfcliff_amt() > BLACK) {
      moveForward(s, .001);
    }
  }
  else {
    while(get_create_rcliff_amt() > BLACK) {
      moveForward(s, .001);
    }
  }
}

void back_until_black(int sensor, int s) {
  if(sensor == LCLIFF) {
    while(get_create_lcliff_amt() > BLACK) {
      moveForward(-s, .001);
    }
  }
  else if(sensor == LFCLIFF) {
    while(get_create_lfcliff_amt() > BLACK) {
      moveForward(-s, .001);
    }
  }  
  else if(sensor == RFCLIFF) {
    while(get_create_rfcliff_amt() > BLACK) {
      moveForward(-s, .001);
    }
  }
  else {
    while(get_create_rcliff_amt() > BLACK) {
      moveForward(-s, .001);
    }
  }
}

void go_until_white(int sensor, int s) {
  if(sensor == LCLIFF) {
    while(get_create_lcliff_amt() < WHITE) {
      moveForward(s, .001);
    }
  }
  else if(sensor == LFCLIFF) {
    while(get_create_lfcliff_amt() < WHITE) {
      moveForward(s, .001);
    }
  }  
  else if(sensor == RFCLIFF) {
    while(get_create_rfcliff_amt() < WHITE) {
      moveForward(s, .001);
    }
  }
  else {
    while(get_create_rcliff_amt() < WHITE) {
      moveForward(s, .001);
    }
  }
}

void back_until_white(int sensor, int s) {
  if(sensor == LCLIFF) {
    while(get_create_lcliff_amt() < WHITE) {
      moveForward(-s, .001);
    }
  }
  else if(sensor == LFCLIFF) {
    while(get_create_lfcliff_amt() < WHITE) {
      moveForward(-s, .001);
    }
  }  
  else if(sensor == RFCLIFF) {
    while(get_create_rfcliff_amt() < WHITE) {
      moveForward(-s, .001);
    }
  }
  else {
    while(get_create_rcliff_amt() < WHITE) {
      moveForward(-s, .001);
    }
  }
}

void move_until_black(int sensor, int ls, int rs) {
  if(sensor == LCLIFF) {
    while(get_create_lcliff_amt() > BLACK) {
      create_drive_direct(ls, rs);
      msleep(1);        
    }
  }
  else if(sensor == LFCLIFF) {
    while(get_create_lfcliff_amt() > BLACK) {
      create_drive_direct(ls, rs);
      msleep(1);        
    }
  }  
  else if(sensor == RFCLIFF) {
    while(get_create_rfcliff_amt() > BLACK) {
      create_drive_direct(ls, rs);
      msleep(1);        
    }
  }
  else {
    while(get_create_rcliff_amt() > BLACK) {
      create_drive_direct(ls, rs);
      msleep(1);        
    }
  }
}

void move_until_white(int sensor, int ls, int rs) {
  if(sensor == LCLIFF) {
    while(get_create_lcliff_amt() < WHITE) {
      create_drive_direct(ls, rs);
      msleep(1);
    }
  }
  else if(sensor == LFCLIFF) {
    while(get_create_lfcliff_amt() < WHITE) {
      create_drive_direct(ls, rs);
      msleep(1);    
    }
  }  
  else if(sensor == RFCLIFF) {
    while(get_create_rfcliff_amt() < WHITE) {
      create_drive_direct(ls, rs);
      msleep(1);        
    }
  }
  else {
    while(get_create_rcliff_amt() < WHITE) {
      create_drive_direct(ls, rs);
      msleep(1);        
    }
  }
}

/*-------------------------------------------------------------------------------------------------
                                            _____ _____ _____  
                                           |  __ \_   _|  __ \ 
                                           | |__) || | | |  | |
                                           |  ___/ | | | |  | |
                                           | |    _| |_| |__| |
                                           |_|   |_____|_____/ 
 PID Line following
 -------------------------------------------------------------------------------------------------*/

void forwards_pid_right(int side, double target, double position, int speed)
{
    set_create_distance(0);
    double current = get_create_rfcliff_amt();
    double error = target - current;
    double proportional;
    double integral;
    double integration;
    double last_error;
    double derivative;
    double derivation;
    double right;
    double left;
    double correction;
    if(side == 1){		//RIGHTSIDE
		while(get_create_distance() < position)
        {
            current = get_create_rfcliff_amt();
            error = target - current;
            integral=integral+error;
            //Sum of all errors(integral) should approach zero.
            //If integral is mostly positive then you are mostly on white and straying to the left
            //If integral is mostly negative then you are mostly on black and straying to the right
            integration=KI*integral;
            //Ki is some arbitrary value, Ki should most likely be lower than Kd and Kp
            proportional = KP * error;
            //increasing Kp makes it more drastic decreasing it makes it smoother
             derivative=last_error-error;
             derivation=KD * derivative;
            
			if(integration<-10){
                    integral=0;
                    integration=0;
                    //printf("\tIntegration cleared");
                    //integration=abs(integration)*-1
                    //you have to use a certain header file to use abs
                    //this may make it too drastic
                }
            
          	correction = proportional + integration + derivation;
            //printf("proportional: %lf   integration: %lf  derivation: %lf\n",proportional,integration,derivation);
            right = speed - correction;
            left = speed + correction;
            //printf("right: %lf\n",right);
            //printf("left: %lf\n",left);
            
            //printf("%i\n",get_create_distance());
            
			//create_drive_straight(1000)
			//msleep(1000)
            create_drive_direct(left,right);
            msleep(1);	//was one
            //printf("%i , %lfa , %lfb , %lfc , %i,  %lfa + %lfb + %lfc\n",counter,error, integral, derivative,counter,error, integral, derivative);
            //use to figure out define constants by pasting list in excel and the pasting that in desmos.Use slider to adjust values till graph matches sin(x)/x
            last_error=error;
            //used to find previous error
		}
    }
    
        if(side == 2){		//LEFTSIDE
        
            while(get_create_distance() < position)
            {
                /*KD = (get_create_lcliff_amt()>2500) ? 0.4: 0.05;
            	printf("%lf\n",KD);*/
                current = get_create_rfcliff_amt();
                error = target - current;
                integral=integral+error;
                //Sum of all errors(integral) should approach zero.
                //If integral is mostly positive then you are mostly on white and straying to the left
                //If integral is mostly negative then you are mostly on black and straying to the right
                integration=KI*integral;
                //Ki is some arbitrary value, Ki should most likely be lower than Kd and Kp
                proportional = KP * error;
                //increasing Kp makes it more drastic decreasing it makes it smoother
                 derivative=last_error-error;
                 derivation=KD * derivative;                
                 if(integration<-10){
                 	integral=0;
                 	integration=0;
                   	//printf("\tIntegration cleared");
                }

                correction = proportional + integration + derivation;
                //printf("proportional: %lf   integration: %lf  derivation: %lf\n",proportional,integration,derivation);
                //printf("%lf\n",derivative);
                right = speed + correction;
                left = speed - correction;
                //printf("Rightside: %lf\n",right);
                //printf("Leftside: %lf\n",left);
                
                //printf("%i\n",get_create_distance());
                
            	create_drive_direct(left,right);
                msleep(7);	//was twenty
                
                //printf("%i , %lfa , %lfb , %lfc , %i,  %lfa + %lfb + %lfc\n",counter,error, integral, derivative,counter,error, integral, derivative);
                //use to figure out define constants by pasting list in excel and the pasting that in desmos.Use slider to adjust values till graph matches sin(x)/x
                last_error=error;
                //used to find previous error
                }
        	
        }
	}	

void forwards_pid_left(int side, double target, double position, int speed)
{
    set_create_distance(0);
    double current = get_create_lfcliff_amt();
    double error = target - current;
    double proportional;
    double integral;
    double integration;
    double last_error;
    double derivative;
    double derivation;
    double right;
    double left;
    double correction;
    if(side == 1){		//RIGHTSIDE
		while(get_create_distance()<position){
            current = get_create_lfcliff_amt();
            error = target - current;
            integral=integral+error;
            //Sum of all errors(integral) should approach zero.
            //If integral is mostly positive then you are mostly on white and straying to the left
            //If integral is mostly negative then you are mostly on black and straying to the right
            integration=KI*integral;
            //Ki is some arbitrary value, Ki should most likely be lower than Kd and Kp
            proportional = PROP * error;
            //increasing Kp makes it more drastic decreasing it makes it smoother
             derivative=last_error-error;
             derivation=KD * derivative*0.05;
            
			if(integration<-10){
            	integral=0;
            	integration=0;
            	//printf("\tIntegration cleared");
            	//integration=abs(integration)*-1
            	//you have to use a certain header file to use abs
            	//this may make it too drastic
            }
            
          	correction = proportional + integration + derivation;
            //printf("proportional: %lf   integration: %lf  derivation: %lf\n",proportional,integration,derivation);
            right = speed - correction;
            left = speed + correction;
            
            /*
            printf("right: %lf\n",right);
            printf("left: %lf\n",left);
            printf("correction: %lf\n", correction);
            printf("%lf\n",current);
            */
            
			//create_drive_straight(1000)
			//msleep(1000)
            create_drive_direct(left,right);
            msleep(7); //was one
            //printf("%i , %lfa , %lfb , %lfc , %i,  %lfa + %lfb + %lfc\n",counter,error, integral, derivative,counter,error, integral, derivative);
            //use to figure out define constants by pasting list in excel and the pasting that in desmos.Use slider to adjust values till graph matches sin(x)/x
            last_error=error;
            //used to find previous error
		}
        }
    
        if(side == 2){		//LEFTSIDE
        
            while(get_create_distance()<position)
            {
                /*KD = (get_create_lcliff_amt()>2500) ? 0.4: 0.05;
            	printf("%lf\n",KD);*/
                current = get_create_lfcliff_amt();
                error = target - current;
                integral=integral+error;
                //Sum of all errors(integral) should approach zero.
                //If integral is mostly positive then you are mostly on white and straying to the left
                //If integral is mostly negative then you are mostly on black and straying to the right
                integration=KI*integral;
                //Ki is some arbitrary value, Ki should most likely be lower than Kd and Kp
                proportional = KP * error;
                //increasing Kp makes it more drastic decreasing it makes it smoother
                 derivative=last_error-error;
                 derivation=KD * derivative;                
                 if(integration<-10){
              	 	integral=0;
                 	integration=0;    
                   	//printf("\tIntegration cleared");    
                 }

                correction = proportional + integration + derivation;
                //printf("proportional: %lf   integration: %lf  derivation: %lf\n",proportional,integration,derivation);
                //printf("%lf\n",derivative);
                right = speed + correction;
                left = speed - correction;
                //printf("Rightside: %lf\n",right);
                //printf("Leftside: %lf\n",left);
                
                //printf("%lf\n",current);
                
            	create_drive_direct(left,right);
                msleep(7);
                
                //printf("%i , %lfa , %lfb , %lfc , %i,  %lfa + %lfb + %lfc\n",counter,error, integral, derivative,counter,error, integral, derivative);
                //use to figure out define constants by pasting list in excel and the pasting that in desmos.Use slider to adjust values till graph matches sin(x)/x
                last_error=error;
                //used to find previous error
                }
        	
        }
	}	

void topHat_pid(int side, double target, double position, int speed)
{
    set_create_distance(0);
    double current = analog(0);
    double error = target - current;
    double proportional=0;
    double integral=0;
    double integration=0;
    double last_error=0;
    double derivative=0;
    double derivation=0;
    double right=0;
    double left=0;
    double correction;
    if(side == 1){		//RIGHTSIDE        
		while(get_create_distance() > -position){
        current = analog(0);
        error = target - current;
        integral=integral+error;
        //Sum of all errors(integral) should approach zero.
        //If integral is mostly positive then you are mostly on white and straying to the left
        //If integral is mostly negative then you are mostly on black and straying to the right
        integration=KI*integral;
        //Ki is some arbitrary value, Ki should most likely be lower than Kd and Kp
        proportional = KP * error;
        //increasing Kp makes it more drastic decreasing it makes it smoother
        derivative=last_error-error;
        derivation=KD * derivative;
            
		if(integration<-10){
            //integral=0;
            integration=0;
                
             // printf("\tIntegration cleared");
                
             //integration=abs(integration)*-1
             //you have to use a certain header file to use abs
             //this may make it too drastic
        }

        correction = proportional + derivation;	//had a + integration
        right = -speed + correction;
        left = -speed - correction;
        //printf("proportional: %lf   integration: %lf  derivation: %lf\n",proportional,integration,derivation);
        printf("right: %lf",right);
        printf("left: %lf\n",left);
            
        printf("analog(zero): %i\n",analog(0));
        // printf("%lf\n",current);
            
	    //create_drive_straight(1000)
		//msleep(1000)
            
        // printf("left:%lf  right:%lf\n",left,right);
        create_drive_direct(left,right);
        msleep(50);
        //printf("%i , %lfa , %lfb , %lfc , %i,  %lfa + %lfb + %lfc\n",counter,error, integral, derivative,counter,error, integral, derivative);
        //use to figure out define constants by pasting list in excel and the pasting that in desmos.Use slider to adjust values till graph matches sin(x)/x
        last_error=error;
        //used to find previous error
		}
   }
    
        if(side == 2){		//LEFTSIDE
        
            while(get_create_distance() > -position)
            {
                printf("analog(zero): %lf\n", current);
                /*KD = (get_create_lcliff_amt()>2500) ? 0.4: 0.05;
            	  printf("%lf\n",KD);*/
                current = analog(0);
                error = target - current;
                integral=integral+error;
                //Sum of all errors(integral) should approach zero.
                //If integral is mostly positive then you are mostly on white and straying to the left
                //If integral is mostly negative then you are mostly on black and straying to the right
                integration=KI*integral;
                //Ki is some arbitrary value, Ki should most likely be lower than Kd and Kp
                proportional = KP * error;
                //increasing Kp makes it more drastic decreasing it makes it smoother
                 derivative=last_error-error;
                 derivation=KD * derivative;

                
                    if(integration<-10){
                        integral=0;
                        integration=0;
                        
                       // printf("\tIntegration cleared");
                    }

                correction = proportional + derivation;	//had a + integration
                //printf("proportional: %lf   integration: %lf  derivation: %lf\n",proportional,integration,derivation);
                //printf("%lf\n",derivative);
                right = -speed - correction;
                left = -speed + correction;
                //printf("Rightside: %lf\n",right);
                //printf("Leftside: %lf\n",left);
                
                /*
                printf("current: %lf\t correct: %lf\n",current, correction);
                printf("right: %lf\t left: %lf\n", right, left);
                */
            	create_drive_direct(left,right);
                msleep(10);
                //printf("%i , %lfa , %lfb , %lfc , %i,  %lfa + %lfb + %lfc\n",counter,error, integral, derivative,counter,error, integral, derivative);
                //use to figure out define constants by pasting list in excel and the pasting that in desmos.Use slider to adjust values till graph matches sin(x)/x
                last_error=error;
                //used to find previous error
                }
        	
        }
}






void topHat_pid_backwards(int side, double target, double position, int speed)
{
    set_create_distance(0);
    double current = analog(0);
    double error = target - current;
    double proportional;
    double integral;
    double integration;
    double last_error;
    double derivative;
    double derivation;
    double right;
    double left;
    double correction;
    if(side == 1){		//RIGHTSIDE        
		while(get_create_distance() < position){
            current = analog(0);
            error = target - current;
            integral=integral+error;
            //Sum of all errors(integral) should approach zero.
            //If integral is mostly positive then you are mostly on white and straying to the left
            //If integral is mostly negative then you are mostly on black and straying to the right
            integration=KI*integral;
            //Ki is some arbitrary value, Ki should most likely be lower than Kd and Kp
            proportional = KP * error;
            //increasing Kp makes it more drastic decreasing it makes it smoother
             derivative=last_error-error;
             derivation=KD * derivative;
            
			if(integration<-10){
            	integral=0;
       			integration=0;
                
                //printf("\tIntegration cleared");
                
                //integration=abs(integration)*-1
                //you have to use a certain header file to use abs
                //this may make it too drastic
           }

            correction = proportional + integration + derivation;
            right = speed + correction;
            left = speed - correction;
            //printf("proportional: %lf   integration: %lf  derivation: %lf\n",proportional,integration,derivation);
            //printf("right: %lf\n",right);
            //printf("left: %lf\n",left);
            
           // printf("%lf\n",current);
            
			//create_drive_straight(1000)
			//msleep(1000)
            
            //printf("left:%lf  right:%lf\n",left,right);
            create_drive_direct(left,right);
            msleep(50);
            //printf("%i , %lfa , %lfb , %lfc , %i,  %lfa + %lfb + %lfc\n",counter,error, integral, derivative,counter,error, integral, derivative);
            //use to figure out define constants by pasting list in excel and the pasting that in desmos.Use slider to adjust values till graph matches sin(x)/x
            last_error=error;
            //used to find previous error
		}
    }
    
        if(side == 2){		//LEFTSIDE
        
            while(get_create_distance() < position)
            {
                /*KD = (get_create_lcliff_amt()>2500) ? 0.4: 0.05;
            	printf("%lf\n",KD);*/
                current = analog(0);
                error = target - current;
                integral=integral+error;
                //Sum of all errors(integral) should approach zero.
                //If integral is mostly positive then you are mostly on white and straying to the left
                //If integral is mostly negative then you are mostly on black and straying to the right
                integration=KI*integral;
                //Ki is some arbitrary value, Ki should most likely be lower than Kd and Kp
                proportional = KP * error;
                //increasing Kp makes it more drastic decreasing it makes it smoother
                 derivative=last_error-error;
                 derivation=KD * derivative;

                
                    if(integration<-10){
                        integral=0;
                        integration=0;
                        
                       // printf("\tIntegration cleared");
                    }

                correction = proportional + integration + derivation;
                //printf("proportional: %lf   integration: %lf  derivation: %lf\n",proportional,integration,derivation);
                //printf("%lf\n",derivative);
                right = speed - correction;
                left = speed + correction;
                //printf("Rightside: %lf\n",right);
                //printf("Leftside: %lf\n",left);
                
                //printf("%lf\n",current);
            	create_drive_direct(left,right);
                msleep(20);
                
                //printf("%i , %lfa , %lfb , %lfc , %i,  %lfa + %lfb + %lfc\n",counter,error, integral, derivative,counter,error, integral, derivative);
                //use to figure out define constants by pasting list in excel and the pasting that in desmos.Use slider to adjust values till graph matches sin(x)/x
                last_error=error;
                //used to find previous error
                }
        	
        }
}

/*-------------------------------------------------------------------------------------------------
                                           _      _____ _____ _   _ 
                                     /\   | |    |_   _/ ____| \ | |
                                    /  \  | |      | || |  __|  \| |
                                   / /\ \ | |      | || | |_ | . ` |
                                  / ____ \| |____ _| || |__| | |\  |
                                 /_/    \_\______|_____\_____|_| \_|
 Align
 -------------------------------------------------------------------------------------------------*/

void align(int side, double target)   //aligns the roomba perpendicular to the tape
{
    double currentleft = get_create_lcliff_amt();
    double currentright = get_create_rcliff_amt();
    double errorleft = currentleft-target;
    double errorright = currentright-target;
    double lproportional;
    double rproportional;
	  double lintegral;
	  double rintegral;
    double lintegration;
	  double rintegration;
    double lderivative;
	  double rderivative;
    double ldifferentiation;
	  double rdifferentiation;
    int last_error_left;
    int last_error_right;
    double lcorrection;
    double rcorrection;
    int start_time = seconds();
    int tiempo = seconds() - start_time;
    if(side == 1){		//UNDERLINE
        
        while(!((get_create_lcliff_amt()>GRAYMIN && get_create_lcliff_amt()<GRAYMAX) &&  
	        (get_create_rcliff_amt()>GRAYMIN && get_create_rcliff_amt()<GRAYMAX)))                 
		//not on grey
        {
	 	      currentleft = get_create_lcliff_amt();
	 	      currentright = get_create_rcliff_amt();
	 	      errorleft = currentleft-target;
          errorright = currentright-target;
	 	      lproportional = KPL * errorleft;
	 	      rproportional = KPR * errorright;
          lintegral += errorleft;
          rintegral += errorright;
          lintegration = lintegral*KIL;
          rintegration = rintegral*KIR;   
          lderivative =last_error_left-errorleft;
          rderivative =last_error_right-errorright;
          ldifferentiation = lderivative*KDL;
	        rdifferentiation = rderivative*KDR;
          lcorrection = lproportional+lintegration+ldifferentiation;
          rcorrection = rproportional+rintegration+rdifferentiation;
          if((get_create_lcliff_amt()>GRAYMIN && get_create_lcliff_amt()<GRAYMAX)){lproportional = 0; printf("\t LEFT CLEARED\n");}
          if((get_create_rcliff_amt()>GRAYMIN && get_create_rcliff_amt()<GRAYMAX)){rproportional = 0; printf("\t RIGHT CLEARED\n");}
          if(lproportional<10 && lproportional>-10 && rproportional<10 && rproportional>-10){printf("\t NOT IN RANGE\n"); break;}
         
         /*
         printf("lproportional: %lf\n",lproportional);
	 	 printf("rproportional: %lf\n",rproportional);
         */
          create_drive_direct(lcorrection,rcorrection);
	 	      msleep(6);
          printf("Left: \t %i \n",get_create_lcliff_amt());
     	    printf("Right: \t %i \n",get_create_rcliff_amt()); 
          last_error_left = errorleft;
          last_error_right = errorright;
          tiempo = seconds() - start_time;
          if(tiempo>=3){break;} 
        }
     }

     if(side == 2){		//OVERLINE
        
        while(!((get_create_lcliff_amt()>GRAYMIN && get_create_lcliff_amt()<GRAYMAX) && 
	        (get_create_rcliff_amt()>GRAYMIN && get_create_rcliff_amt()<GRAYMAX)))                 
			//not on grey
       {
	 	      currentleft = get_create_lcliff_amt();
	 	      currentright = get_create_rcliff_amt();
	 	      errorleft = target-currentleft;
    	    errorright = target-currentright;
	 	      lproportional = KPL * errorleft;
	        rproportional = KPR * errorright;
          lintegral += errorleft;
          rintegral += errorright;
          lintegration = lintegral* KIL;
          rintegration = rintegral* KIR;   
          lderivative =last_error_left-errorleft;
          rderivative =last_error_right-errorright;
          ldifferentiation = lderivative*KDL;
	        rdifferentiation = rderivative*KDR;
          lcorrection = lproportional+lintegration+ldifferentiation;
          rcorrection = rproportional+rintegration+rdifferentiation;
          if((get_create_lcliff_amt()>GRAYMIN && get_create_lcliff_amt()<GRAYMAX)){lproportional = 0; printf("\t LEFT CLEARED\n");}
          if((get_create_rcliff_amt()>GRAYMIN && get_create_rcliff_amt()<GRAYMAX)){rproportional = 0; printf("\t RIGHT CLEARED\n");}
          if(lproportional<10 && lproportional>-10 && rproportional<10 && rproportional>-10){printf("\t NOT IN RANGE\n"); break;}
	     /*
         printf("lproportional: %lf\n",lcorrection);
	 	 printf("rproportional: %lf\n",rcorrection);
         */
          create_drive_direct(lcorrection,rcorrection);
          msleep(6);
          printf("Left: \t %i \n",get_create_lcliff_amt());
     	    printf("Right: \t %i \n",get_create_rcliff_amt());
          last_error_left = errorleft;
          last_error_right = errorright;
          tiempo = seconds() - start_time;
          if(tiempo>=3){break;} 
		}
     }
}

void alignfront(int side, double target)
{
    double currentleft = get_create_lfcliff_amt();
    double currentright = get_create_rfcliff_amt();
    double errorleft = currentleft-target;
    double errorright = currentright-target;
    double lproportional;
    double rproportional;
	  double lintegral;
	  double rintegral;
    double lintegration;
	  double rintegration;
    double lderivative;
	  double rderivative;
    double ldifferentiation;
	  double rdifferentiation;
    int last_error_left;
    int last_error_right;
    double lcorrection;
    double rcorrection;
    int start_time = seconds();
    int tiempo = seconds() - start_time;
    if(side == 1){		//UNDERLINE
        
        while(!((get_create_lfcliff_amt()>GRAYMIN && get_create_lfcliff_amt()<GRAYMAX) &&  
	        (get_create_rfcliff_amt()>GRAYMIN && get_create_rfcliff_amt()<GRAYMAX)))                 
		//not on grey
        {
	 	      currentleft = get_create_lfcliff_amt();
	 	      currentright = get_create_rfcliff_amt();
	 	      errorleft = currentleft-target;
          errorright = currentright-target;
	 	      lproportional = KPL * errorleft;
	 	      rproportional = KPR * errorright;
          lintegral += errorleft;
          rintegral += errorright;
          lintegration = lintegral*KIL;
          rintegration = rintegral*KIR;   
          lderivative =last_error_left-errorleft;
          rderivative =last_error_right-errorright;
          ldifferentiation = lderivative*KDL;
	        rdifferentiation = rderivative*KDR;
          lcorrection = lproportional+lintegration+ldifferentiation;
          rcorrection = rproportional+rintegration+rdifferentiation;
          if((get_create_lfcliff_amt()>GRAYMIN && get_create_lfcliff_amt()<GRAYMAX)){lproportional = 0; printf("\t LEFT CLEARED\n");}
          if((get_create_rfcliff_amt()>GRAYMIN && get_create_rfcliff_amt()<GRAYMAX)){rproportional = 0; printf("\t RIGHT CLEARED\n");}
          if(lproportional<10 && lproportional>-10 && rproportional<10 && rproportional>-10){printf("\t NOT IN RANGE\n"); break;}
         
         /*
         printf("lproportional: %lf\n",lproportional);
	 	 printf("rproportional: %lf\n",rproportional);
         */
            if(wheelratio == 0)
            {
            	create_drive_direct(lcorrection,rcorrection);
            }
            else {
            	create_drive_direct(lcorrection,rcorrection*1.5);
            }
	 	 
     	    msleep(10);
          printf("Left: \t %i \n",get_create_lfcliff_amt());
     	    printf("Right: \t %i \n",get_create_rfcliff_amt()); 
          last_error_left = errorleft;
          last_error_right = errorright;
          tiempo = seconds() - start_time;
          if(tiempo>=6){break;} 
        }
     }

     if(side == 2){		//OVERLINE
        
        while(!((get_create_lfcliff_amt()>GRAYMIN && get_create_lfcliff_amt()<GRAYMAX) && 
	        (get_create_rfcliff_amt()>GRAYMIN && get_create_rfcliff_amt()<GRAYMAX)))                 
			//not on grey
       {
	 	      currentleft = get_create_lfcliff_amt();
	 	      currentright = get_create_rfcliff_amt();
	 	      errorleft = target-currentleft;
    	    errorright = target-currentright;
	 	      lproportional = KPL * errorleft;
	        rproportional = KPR * errorright;
          lintegral += errorleft;
          rintegral += errorright;
          lintegration = lintegral* KIL;
          rintegration = rintegral* KIR;   
          lderivative =last_error_left-errorleft;
          rderivative =last_error_right-errorright;
          ldifferentiation = lderivative*KDL;
	        rdifferentiation = rderivative*KDR;
          lcorrection = lproportional+lintegration+ldifferentiation;
          rcorrection = rproportional+rintegration+rdifferentiation;
          if((get_create_lfcliff_amt()>GRAYMIN && get_create_lfcliff_amt()<GRAYMAX)){lproportional = 0; printf("\t LEFT CLEARED\n");}
          if((get_create_rfcliff_amt()>GRAYMIN && get_create_rfcliff_amt()<GRAYMAX)){rproportional = 0; printf("\t RIGHT CLEARED\n");}
          if(lproportional<10 && lproportional>-10 && rproportional<10 && rproportional>-10){printf("\t NOT IN RANGE\n"); break;}
	     /*
         printf("lproportional: %lf\n",lcorrection);
	 	 printf("rproportional: %lf\n",rcorrection);
         */
	 	      if(wheelratio == 0)
            {
            	create_drive_direct(lcorrection,rcorrection);
            }
            else {
            	create_drive_direct(lcorrection,rcorrection*1.5);
            }
          msleep(10);
          printf("Left: \t %i \n",get_create_lfcliff_amt());
     	    printf("Right: \t %i \n",get_create_rfcliff_amt());
          last_error_left = errorleft;
          last_error_right = errorright;
          tiempo = seconds() - start_time;
          if(tiempo>=6){break;} 
		}
     }
}

/*-------------------------------------------------------------------------------------------------
                   _______     _______   ____    _______ _    _ _____  _   _ 
                  / ____\ \   / /  __ \ / __ \  |__   __| |  | |  __ \| \ | |
                 | |  __ \ \_/ /| |__) | |  | |    | |  | |  | | |__) |  \| |
                 | | |_ | \   / |  _  /| |  | |    | |  | |  | |  _  /| . ` |
                 | |__| |  | |  | | \ \| |__| |    | |  | |__| | | \ \| |\  |
                  \_____|  |_|  |_|  \_\\____/     |_|   \____/|_|  \_\_| \_|
gyro turn
--------------------------------------------------------------------------------------------------*/


	int gyroVal() {
        int currentAngle = 0;
        int avg = averageGyro(); 
        int t0 = seconds();
        while(digital(0) == 0){
            create_drive_direct(40,-40);
         	currentAngle -= (int)(gyro_z()-avg)*(seconds()-t0); //increase currentAngle by each offset gyro_z value
            t0 = seconds();
        }
        return currentAngle/90;
    }
    

// -------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------gyroVal Function Above----------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------


    int rotate(double angle, int speed) {  //Bot turns by a given set degree relative to its position //speed cap might be 70
        //speed +=(int)(abs(angle)/5);
        //int max = -1;
        speed = 50;
        angle = angle*angle_offset; //convert angle -> suitable form for gyro
        printf("\nThe desired angle is: %lf\n", angle);
        printf("\nThe desired speed is %i\n", speed);
        
        int avg = averageGyro() - move_offset; //compute new average w/o offset
        int currentAngle = 0; //set our relative angle to 0

        int t0 = seconds(); //set current time to variable
        //double speed_offset; //declare movement offset commented out so compile looks beautiful

        /* PID Constants */
       //double pid_P = 0; //test valuecommented out so compile looks beautiful
        //double pid_I = 0; commented out so compile looks beautiful
        //double pid_D = 0;commented out so compile looks beautiful

        //bool zero_reached = false;
        while(1) {
            if (angle > 0) { //clockwise turn
            	currentAngle -= (int)(gyro_z()-avg)*(seconds()-t0); //increase currentAngle by avg of each gyro_z value
                //printf("This is a current angle that u have n want: %i\t%lf\n", currentAngle, angle);
                //restate array values
                /*
                angle_arr[PREV_ANGLE] = angle_arr[CURRENT_ANGLE]; //set previous angle 
                angle_arr[CURRENT_ANGLE] = currentAngle; //update new angle
                angle_arr[CHANGE_IN_ANGLE] = angle_arr[CURRENT_ANGLE] - angle_arr[PREV_ANGLE]; //calculate difference between the two angles
*				*/
                //calculate new speed
                //speed_offset = (pid_P)*(angle_arr[CURRENT_ANGLE]) + (pid_D)*(angle_arr[CHANGE_IN_ANGLE]); //compute offset using pid_P and pid_D

                //adjust motor
                //motor(LWHEEL, speed+speed_offset); //move stationary CW
                //motor(RWHEEL, speed-speed_offset);
                
                //adjust motor Create
                create_drive_direct(speed, -speed);
                msleep(1);
                
                if (currentAngle >= angle) { //if the currentAngle reaches the final angle
                    printf("Final ANGLE HAS BEEN REACHED\n");
                    //reverse speed CCW for 10ms   
                /*
                if (!(zero_reached)) {
                	currentAngle -= (int)(gyro_z()-avg)*(seconds()-t0);
                    //printf("ZERO_NOT_REACHED, %i\n", (int)(gyro_z()-avg)*(seconds()-t0));
                }
                else if (zero_reached) {
                    printf("ZERO_REACHED, MAX: %i\n", max/2);
                    currentAngle += (int)(max/2)*(seconds()-t0);
                }
                //increase currentAngle by each offset gyro_z value
                //restate array values
                angle_arr[PREV_ANGLE] = angle_arr[CURRENT_ANGLE]; //set previous angle 
                angle_arr[CURRENT_ANGLE] = currentAngle; //update new angle
                angle_arr[PREV_VELOCITY] = angle_arr[CURRENT_VELOCITY];
                angle_arr[CURRENT_VELOCITY] = angle_arr[CURRENT_ANGLE] - angle_arr[PREV_ANGLE]; //calculate difference between the two angles(velocity)
                angle_arr[CHANGE_IN_VELOCITY] = angle_arr[CURRENT_VELOCITY] - angle_arr[PREV_VELOCITY];
                if (zero_reached == false && angle_arr[CURRENT_VELOCITY] > max) { max = angle_arr[CURRENT_VELOCITY]; }
                if ((angle_arr[CHANGE_IN_VELOCITY] < -50)) { 
                    zero_reached = true;
                }
				//printf("Prev Angle: %lf\n" ,angle_arr[PREV_ANGLE]);
                printf("Current_Angle: %lf\n" ,currentAngle);
                //printf("Change in Velocity: %lf\n" ,angle_arr[CHANGE_IN_VELOCITY]); 
                //calculate new speed
                //speed_offset = (pid_P)*(angle_arr[CURRENT_ANGLE]) + (pid_D)*(angle_arr[CHANGE_IN_ANGLE]); //compute offset using pid_P and pid_D
                //adjust motor
                //motor(LWHEEL, speed+speed_offset); //move stationary CW
                //motor(RWHEEL, speed-speed_offset);
                
                //adjust motor Create
                //if (currentAngle >= angle*0.95) { speed = 11; }
                create_drive_direct(speed, -speed);
                msleep(1);
                
                if (currentAngle >= angle) { //if the currentAngle reaches the final angle
                    //reverse speed CCW for 10ms
                */
                    /* Small bot reverse turn
                    motor(LWHEEL, -40);
                    motor(RWHEEL, 40);
                    */
                    
                    create_drive_direct(-rbTurn,rbTurn);
                    msleep(10);
                    /* Small bot reverse turn stop
                    motor(LWHEEL, 0);
                    motor(RWHEEL, 0);
                    */
                    create_drive_direct(0,0);
                    break; 
                } 
            }
            
             if (angle < 0 ) { //counterclockwise turn
                
                currentAngle -= (int)(gyro_z()-avg)*(seconds()-t0); //increase currentAngle by avg of each gyro_z value
                //printf("This is a current angle that u have n want: %i\t%lf\n", currentAngle, angle);
                //restate array values
                /*
                angle_arr[PREV_ANGLE] = angle_arr[CURRENT_ANGLE]; //set previous angle 
                angle_arr[CURRENT_ANGLE] = currentAngle; //update new angle
                angle_arr[CHANGE_IN_ANGLE] = angle_arr[CURRENT_ANGLE] - angle_arr[PREV_ANGLE]; //calculate difference between the two angles
*				*/
                //calculate new speed
                //speed_offset = (pid_P)*(angle_arr[CURRENT_ANGLE]) + (pid_D)*(angle_arr[CHANGE_IN_ANGLE]); //compute offset using pid_P and pid_D

                //adjust motor
                //motor(LWHEEL, speed+speed_offset); //move stationary CW
                //motor(RWHEEL, speed-speed_offset);
                
                //adjust motor Create
                create_drive_direct(-speed, speed);
                msleep(1);
                
                if (currentAngle <= angle) { //if the currentAngle reaches the final angle
                    printf("Final ANGLE HAS BEEN REACHED\n");
                    //reverse speed CCW for 10ms
                    
                    /* Small bot reverse turn
                    motor(LWHEEL, -40);
                    motor(RWHEEL, 40);
                    */
                    
                    create_drive_direct(rbTurn,-rbTurn);
                    msleep(10);
                    /* Small bot reverse turn stop
                    motor(LWHEEL, 0);
                    motor(RWHEEL, 0);
                    */
                    create_drive_direct(0,0);
                    break; 
                } 
            }
            t0 = seconds(); //resets time -> will always be 1ms difference
        }
        //if(zero_reached) { printf("WE DID IT! ZERO_REACHED = TRUE! \n"); }
        printf("Current Angle: %i\tFinal Angle: %lf\n", currentAngle, angle);
        return currentAngle; //records the final angle after finishing (NOTE: in gyromode not in degrees!)
    }

// -------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------Turn Function Above----------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------
        
    int averageGyro() { //takes the average of gyro values and returns the average

        int total = 0; //total gyro count
        int reps = 1000; //iterations
        int gyro_val; //gyro value
        int i; //for loop
        
        msleep(1000);
        for (i=0; i<reps; i++) {

            gyro_val = (int)(round(gyro_z())); //gets the rounded gyro_val
            total = total + gyro_val; //adds to total val
        }
        
		printf("Average Gyro Value: %i", total/reps);
        return total/reps; //returns the average
        
    }

// -------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------averageGyro Function Above----------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------

    void gyro_test () { //prints out gyro values to test

        while (1) {

            int x = gyro_x();
            int y = gyro_y();
            int z = gyro_z();

            console_clear(); //clears console after every iteration

            printf("x: %i      |   y: %i        |   z: %i      |\n",x,y,z);
            msleep(10);
         }
    }

// -------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------gyroTest Function Above----------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------

	void print_array(double array[]) {
        int i;
        for (i=0; i<3;i++) {
            printf("%lf\n",array[i]);
        }
        
        
    }
// -------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------print_array Function Above----------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------
	/*
    double buttonPress(int interval, int mode) { 
        int sec = seconds();
        int timer = seconds() - sec;
        int c = 1;
        int i = 0;
        double angle = 0.0;
        int prev = c;
        printf("Welcome to the Gyro Turn Clan! Press the button to adjust your angle: \n");
        printf("Angle: %i\n", 360/mode*c);
        while (timer < interval) {
            if (digital(0) == 1) { 
                while (digital(0) == 1) {
                    msleep(1);
                }
                c++;
            }
            if (c > mode){ c = 1; }
            if (c != prev) {
            	printf("Angle: %i\n", 360/mode*c);
                prev = c;
            }
            timer = seconds() - sec;
        }
        
        for (i = 1; i <=mode; i++) {
            if (c == i) { 
            	angle = 45*i;
            }
        }
        return angle;
    }*/

    double buttonPress(int interval, int mode) { //think about doing a 0-9 for increment (adjust your tens, adjust your ones)
        int sec = seconds();
        int timer = seconds() - sec;
        int c = 0;
        int angle = 0;
        int prev = c; 
        printf("Press the button to adjust your angle: \n");
        printf("Angle: %i\n", angle);
        while (timer < interval) {
            if (left_button() == 1) { //left button is going to increase the angle
                while (left_button() == 1) { msleep(1); }
     			c--;
            }
            if (right_button() == 1) { //right button is going to decrease the angle
                while (right_button() == 1) { msleep(1); }
                c++;
            }
            
            if (c > mode){ c = -mode; }
            if (c < -mode) { c = mode; }
            if (c != prev) {
                angle = 360/mode*c;
            	printf("Angle: %i\n", angle);
                prev = c;
            }
            timer = seconds() - sec;
        }
        return angle;
    }
	void turn_incr_test() { //speed is not consistent with value, jolts in random values (not in the tens!)
        int speed;
        for (speed=10; speed<=100; speed++) {
			printf("Speed: %i\n", speed);
           	create_drive_direct(speed, -speed);
            msleep(1000);
        }
        ao();
    }
