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

//Clapper Mechanism
  #define clapperCloser 0
  #define clapperRotator 0

//Titanium Oxide Mechanism   WIP
  #define tioSucker 1
  #define tioLifter 2
  
//Number
  #define OPEN 0
  #define CLOSED 1

//-----------------------------Function Declarations----------------------------
void forwardMove(int s, double t); //s = speed in roomba degrees, t = time in seconds
void gyroTurn(int s, int ang); //s = speed in roomba degrees, ang = angle from 0-360
void clapper(int b); //b = boolean where 0 = open and 1 = close
void suck(int b, double t); //t = seconds and b = boolean where 0 = out and 1 = in

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

    /* Make sure clapper is open */
    clapper(OPEN);

    /* Start moving and grab cubes */
    forwardMove(100, 2); // move to red and green cube position
    clapper(CLOSED);
    msleep(500);
    clapper(OPEN);

    /* Move to titanium oxide */
    gyroTurn(20, 15);
    forwardMove(100, 3);

    /* Start loading procedure */
        // im sure there will be some claw adjustments at this stage
    suck(1, 5.5);

    create_disconnect();
    return 2147483647;
}

/*---------------------------------------------------------------------------------------
                      __  __  _____   _____ __  __ ___ _  _ _____ 
                     |  \/  |/ _ \ \ / | __|  \/  | __| \| |_   _|
                     | |\/| | (_) \ V /| _|| |\/| | _|| .` | | |  
                     |_|  |_|\___/ \_/ |___|_|  |_|___|_|\_| |_|                                 
---------------------------------------------------------------------------------------*/
/*
forwardMove: move forward
int s: speed
double t: time to move in seconds
*/
void forwardMove(int s, double t) {
    create_drive_direct(s, s);
    msleep(t*1000);
}

//PUT GYRO TURN HERE

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
        while (gmpc(clapperCloser < CLOSED)) {
            motor(clapperCloser, 100);
        }
    } else {
        while (gmpc(clapperCloser > OPEN)) {
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
    if (b) {
        motor(clapperCloser, 100);  
    } else {
        while (gmpc(clapperCloser > OPEN)) {
            motor(clapperCloser, -100);
        }
    }
}
