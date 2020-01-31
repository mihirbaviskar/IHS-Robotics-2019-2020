/*---------------------------------------------------------------------------------------
             ___   ___   ___   ___   ___   ___     _     _____   ___    ___    _  _     Segregation
            | _ \ | _ \ | __| | _ \ | __| | _ \   /_\   |_   _| |_ _|  / _ \  | \| |    Federation
            |  _/ |   / | _|  |  _/ | _|  |   /  / Δ \    | |    | |  | (_) | | .` |    Cremation
            |_|   |_|_\ |___| |_|   |___| |_|_\ /_/ \_\   |_|   |___|  \___/  |_|\_|    -Pepper Nation                                                                                                                                                    
//--------------------------------------------------------------------------------------- */

//-----------------------------Prep and #Includes-------------------------------tinyurl.com/svyvqaf "Small"
#include <stdio.h>
#include <kipr/botball.h>
#include <math.h>
#include <Roombackend.h>

//Clapper Mechanism
  #define clapperCloser 0
  #define clapperRotator 0

//Titanium Oxide Mechanism   WIP
  #define tioSucker 1
  #define tioLifter 2
  
//Number
  #define OPEN 0
  #define CLOSED 1
  #define OUT 0
  #define IN 1
  #define DOWN 0
  #define UP 1000
   double dannyhasagooglepixelstopwatch = seconds();
   double dannyhaselapsed = seconds() - dannyhasagooglepixelstopwatch;

//-----------------------------Function Declarations----------------------------
void clapper(int b); //b = boolean where 0 = open and 1 = close
void suck(int b, double t); //t = seconds and b = boolean where 0 = out and 1 = in
void piedpiper();

/*---------------------------------------------------------------------------------------
                                __  __   _   ___ _  _ 
                               |  \/  | /_\ |_ _| \| |
                               | |\/| |/ Δ \ | || .` |
                               |_|  |_/_/ \_|___|_|\_|                   
---------------------------------------------------------------------------------------*/
int main () {
    create_connect();

    /* Starting position */
    shut_down_in(120);
    printf("Start\n");
    
    /* Start timer */
    thread timer;
    timer = thread_create(dannywilltime);
    thread_start(timer);
    
    /* Make sure clapper is open */
    clapper(OPEN);

    /* Start moving and grab cubes */
    forward_until_black(LFSENSOR, 100);
    forward_until_white(LFSENSOR, 100);
    forwardMove(100, 2000); // move to red and green cube position
    clapper(CLOSED);
    msleep(500);
    clapper(OPEN);

    /* Move to titanium oxide */
    gyroTurn(20, 15);
    forwardMove(100, 3000);

    /* Start loading procedure */
        // im sure there will be some claw adjustments at this stage
    piedpiper();
    
    

    thread_destroy(timer);
    create_disconnect();
    return 2147483647;
}

/*---------------------------------------------------------------------------------------
                        _   _ _____ ___ _    ___ _______   __
                        | | | |_   _|_ _| |  |_ _|_   _\ \ / /
                        | |_| | | |  | || |__ | |  | |  \ V / 
                         \___/  |_| |___|____|___| |_|   |_|                                                      
---------------------------------------------------------------------------------------*/

/*
clapper: Move red and blue rectangular things into "clapper"
int b: Determines if open or closed movement should be made
*/
void clapper(int b) {
    if (b) {
        while (gmpc(clapperCloser < OUT)) {
            motor(clapperCloser, 100);
        }
    } else {
        while (gmpc(clapperCloser > IN)) {
                motor(clapperCloser, -100);
        }
    }
}

/*
suck: move treads on main claw to grab the titanium oxide poms (aka sucking)
int b: reverse movement on treads
double t: time in seconds
*/
void suck(int b, double t) {
    double zawarudo = seconds();
    if (b) {                                        //IN
        while(seconds() - zawarudo < t) {
            motor(tioSucker, 100); 
        }
    } else {                                        //OUT
        while (seconds() - zawarudo < t) {
            motor(tioSucker, -100);
        }
    }
}

/*
piedpiper: repeats the up-down motion to suck poms, and after certain seconds, move back and forth to suck poms for certain seconds
*/
void piedpiper() {
    int i = 0;
    int enoughTime = 0;
    if(dannyhaselapsed < 50) {
        enoughTime = 1;
    }
    //Start the sequence for up-down movement to suck poms
    while(dannyhaselapsed < 60) {                               //might not make it time-based, sequence
        for(i = 0; i < 3; i++) {
            set_servo_position(tioLifter, DOWN);
            suck(OPEN, 500);
            set_servo_position(tioLifter, UP);
            move_forward(100, 10);
        }
        move_forward(-100, 30);
    }
    
    //Start the sequence for forward-back movement to suck poms
    if(enoughTime) {                                            //if there is enough time to do this part, then do it
        set_servo_position(tioLifter, DOWN);
        while(dannyhaselapsed < 65) {
            motor(tioSucker, 100);
            move_forward(100, 50);
            create_stop();
            move_forward(-100, 50);
            create_stop();
        }
    }
    set_servo_position(tioLifter, UP);
}

/*
timer: times
*/
void dannywilltime() {
    while(1) {
        dannyhaselapsed = seconds() - dannyhasagooglepixelstopwatch;
    }
}
          
          
          
          
          
          
          
          
