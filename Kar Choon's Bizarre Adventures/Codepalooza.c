#include <kipr/botball.h>
#include<stdbool.h>

//void moveSeconds(int);
//void turnDegrees(int);
//void moveSeconds(int);
//void clock_set();
//void button_turn(int);
//void button_move();
# define LEFT 0 
# define RIGHT 1
int KarChoon(int);

int main(){
    camera_open();
    msleep(3000);
    //int camera;
    while(1){
        camera_update();
        //camera = get_object_center_x(0,0);
        //printf("Center: %i\n",camera);
        if(get_object_count(0)>0 && get_object_area(0,0)>1000 && get_object_center_x(0,0)>50 && get_object_center_x(0,0)<110
         ){
            int angle = 80 - get_object_center_x(0,0);
            double speed = angle * 150;
            //printf("%lf\n",speed);
            if(speed<200){
                speed = 200;
            }
            if(get_object_center_x(0,0)<80){
            	mav(1,speed);
                mav(0,100);
                //printf("%lf\n",speed);
            }
            else if(get_object_center_x(0,0)>80){
                mav(0,speed);
                mav(1,100);
                printf("%lf\n",speed);
            }
            else if(get_object_center_x(0,0)==80){
            /*int count = get_object_count(0);
        	int area = get_object_area(0,0);
            printf("Center: %i\n",camera);
       		printf("Count: %i\n",count);
       		printf("Area: %i\n",area);
            printf("yes\n");*/
            mav(0,200);
            mav(1,200);
            }
            if(get_object_area(0,0)>=6000){
                break;
            }
        }
        else {
            mav(0,70);
            mav(1,-70);
        }
    }
    	//ao();
        camera_close();
		return 0;
}
   
    /* Sween's Embarassment
    clock_set();*/
    
    //Challenge 1: Move Forward for 10 seconds
    
    //1 sec is 260 ticks
    /*int sec = 5;
    int duration = sec * 270;
    
    mrp(0,250,duration);
    mrp(1,250,duration);
	bmd(0);
	bmd(1);*/
    
    //Challenge 2:
    //moveSeconds(5);
    //return 0;
    
    //Chalenge 3/1: Type in # degrees and it turns that much MAKE IT A FUNCTIUONAOKDNOKPANGLKJBPKAWNFJ
    /*turnDegrees(90);
    return 0;*/
    
    //Challenge 2: Be able to turn CW/Counter
    /*turnDegrees(-90);
    return 0;*/
    
    //Challenge 3: Skip Black Stop on 2nd
    /*int x=0;
    while (x==0) {
    	while (analog(0)<3200) {
        	motor(0,50);
        	motor(1,50);
    	}
        while (analog(0)>3200) {
            x = x+1;
        }
    }
    mrp(0,250,500);
    mrp(1,250,500);
    bmd(0);
    bmd(1);
    while (analog(0)<3200) {
        motor(0,50);
        motor(1,50);
    }
    return 0;*/
    
    //Challenge 5: Stay in Box, Move within Box until Time
    /*moveSeconds(20);
    return 0;*/
    
    //Challenge 6: Line Following (Backwards)
    /*
    int x = 0;
    while (x<10000) {
    	while (analog(0)<3000) {
            motor(1,-10);
            motor(0,40);
            int sensor = analog(0);
            msleep(100);
            //int curr = analog(0) - sensor;
            int curr = 3000 - sensor;
            int speed = curr * 0.12;
        	if (speed<10) { 
                motor(1,-10);
            	motor(0,40);
                //printf("The speed right now is 40. \n");
            }
            else {
                motor(1,-10);
                motor(0,speed);
                //printf("The speed right now is %i. \n", speed);
            }
            	//int sensor = analog(0);
	        	//msleep(100);
    	    	//int curr = analog(0) - sensor;
            	//int curr = 3000 - sensor;
        		//printf("The value right now is %i \n", curr);
    	}
    	while (analog(0)>3300) {
        	motor(0,-10);
            motor(1,-40);*/
            	/*int sensor = analog(0);
	        	msleep(100);
    		    int curr = analog(0) - sensor;
        		printf("The value right now is %i \n", curr);*/
    	/*}
        while (analog(0)>3000 && analog(0)<3300) {
        	motor(0,-20);
            motor(1,-20);*/
            	/*int sensor = analog(0);
        		msleep(100);
        		int curr = analog(0) - sensor;
        		printf("The value right now is %i \n", curr);*/
    	//}
    //}
    
    //Challenge 4: Button Sensors
    /*int x = 0;
    int y = 0;
    while (x==0) {
        if (digital(0)==1 && y==0) {
            printf("Kar Choon is cool.\n");
            y=y+1;
        }
        else if (digital(0)==0) {
            y=0;
        }
    }*/
    
    //Make Clock
    
    /*int x = 0;
    int y = 0;
    int hour = 0;
    int minute = 0;
    printf("Your Time Now:\n00:00\n");
    while (1) {
        if (left_button() && x==0) {
            if (hour<9 && minute<10) {
            	console_clear();
            	hour++;
                printf("Your Time Now:\n0%i:0%i\n",hour,minute);
                x++;
            }
            else if (hour>8 && hour<12 && minute<10) {
                console_clear();
                hour++;
                printf("Your Time Now:\n%i:0%i\n",hour,minute);
                x++;
            }
            else if (hour==12 && minute<10) {
                console_clear();
                hour = hour - 11;
                printf("Your Time Now:\n0%i:0%i\n",hour,minute);
                x++;
            }
            else if (hour<9 && minute>9 && minute<60) {
            	console_clear();
            	hour++;
                printf("Your Time Now:\n0%i:%i\n",hour,minute);
                x++;
            }
            else if (hour>8 && hour<12 && minute>9 && minute<60) {
                console_clear();
                hour++;
                printf("Your Time Now:\n%i:%i\n",hour,minute);
                x++;
            }
            else if (hour==12 && minute>9 && minute<60) {
                console_clear();
                hour = hour - 11;
                printf("Your Time Now:\n0%i:%i\n",hour,minute);
                x++;
            }
        }
        if (right_button() && y==0) {
            if (hour<10 && minute<9) {
            	console_clear();
            	minute++;
                printf("Your Time Now:\n0%i:0%i\n",hour,minute);
                y++;
            }
            else if (hour>9 && hour<13 && minute<9) {
                console_clear();
                minute++;
                printf("Your Time Now:\n%i:0%i\n",hour,minute);
                y++;
            }
            else if (hour<10 && minute>8 && minute<59) {
            	console_clear();
            	minute++;
                printf("Your Time Now:\n0%i:%i\n",hour,minute);
                y++;
            }
            else if (hour>9 && hour<13 && minute>8 && minute<59) {
                console_clear();
                minute++;
                printf("Your Time Now:\n%i:%i\n",hour,minute);
                y++;
            }
            else if (hour<10 && minute==59) {
                console_clear();
                hour = hour + 1;
                minute = minute - 59;
                printf("Your Time Now:\n0%i:0%i\n",hour,minute);
                y++;
            }
            else if (hour>9 && hour<12 && minute==59) {
                console_clear();
                hour = hour + 1;
                minute = minute - 59;
                printf("Your Time Now:\n%i:0%i\n",hour,minute);
                y++;
            }
            else if (hour==12 && minute==59) {
                console_clear();
                hour = hour - 11;
                minute = minute - 59;
                printf("Your Time Now:\n0%i:0%i\n",hour,minute);
                y++;
            }
        }
        if (left_button()==0) {
            x=0;
        }
        if (right_button()==0) {
            y=0;
        }
    }*/
    
    //Challenge 5: RENEGADE turn
    /*
    thread 
    while (timer<sec) {
        if (!digital(0)) {
            mav(0,10);
            mav(1,10);
        }
        else if (digital(0)) {
            mav(0,10);
            mav(1,-10);
        }
    }
    return 0;
    */
    //button_turn(5);
    //KarChoon(10);


/*
int KarChoon(int start){
    int end=10;
    int math=0;
    while(1){
            math = end * start;
        	return KarChoon(start-1);
        }
        if (start==0){
            printf("%i",math);
            return 0;
        }
    }*/

/*void clock_set() {
    printf("00:00");
	int min = 0; int hour = 0;
	while (!digital(0)) {
		if (left_button() || right_button()) { //if any button is pressed
            console_clear();
			if (left_button()) { //if left button is pressed
				while (left_button()) { msleep(1); } //breaks when the button isn't pressed anymore
				hour++; //add an hour
				if(hour>12) { hour = 0; } //if the hour is greater than 12, reset back to 0
			}
			if (right_button()) { //if right button is pressed
				while (right_button()) { msleep(1); } //breaks when the button isn't pressed anymore
				min++; //add a minute
				if(min>59) { 
					min = 0;
					hour++;
					if (hour > 12) { hour = 0; }
				} //if minute is greater than 59, reset back to 0
			}
			console_clear(); //clear the screen
			if (hour<10) { printf("0"); } //print out values
			printf("%i:", hour);
			if (min<10) { printf("0");}
			printf("%i", min);
		}
	} // continues loop
	printf("\nYour time is now set."); 
}*/
/*
void moveSeconds (int sec) {
    int timer = 0;
    int curr = seconds();
    while (timer<sec) {
        motor(1,20);
        motor(0,20);
        msleep(1000);
    	timer = seconds() - curr;
    }
    printf("%i", timer);
}
void turnDegrees(int degree) {
    if (degree>0){
    	double calculate = degree * 14.5;
    	mrp(0,150,calculate);
    	mrp(1,150,-calculate);
    	bmd(0);
    	bmd(1);
    }
    else {
        double calculate = degree * 14.2;
    	mrp(0,150,calculate);
    	mrp(1,150,-calculate);
    	bmd(0);
    	bmd(1);
    }
}*/
/*void moveSeconds (int sec) {
    int timer = 0;
    int curr = seconds();
    while (timer<sec) {
    	while (analog(0)<3200) {
        	motor(0,50);
        	motor(1,50);
    	}
        while (analog(0)>3200) {
            motor(0,100);
            motor(1,-100);
        }
        msleep(1000);
        timer = seconds()-curr;
    }
    mrp(0,800,8000);
    mrp(1,800,8000);
    bmd(0);
    bmd(1);
}*/
/*void button_turn (int sec) {
    thread move;
    move = thread_create(button_move);
    thread_start(move);
    int elapsed = 0;
    int curr = seconds();
   	while (elapsed < sec) {
        msleep(1000);
        elapsed = seconds() - curr;
    }
    thread_destroy(move);
}

void button_move () {
    while (1) {
        if (!digital(0)) {
            mav(0,50);
            mav(1,50);
        }
        else if (digital(0)) {
            mav(0,50);
            mav(1,-50);
        }
    }
}*/
