#include <kipr/botball.h>
#include <stdio.h>

#define LEFTWHEEL 3
#define RIGHTWHEEL 2
#define KPR 0.01
#define KPL 0.01
#define GRAYMAX 2300
#define GRAYMIN 1900
#declare OVERLINE 1
#declare UNDERLINE 2

void align(int side, double ltarget, double rtarget);


void align(int side, double ltarget, double rtarget) 
{
    double currentleft = analog(1);
    double currentright = analog(2);
    double errorleft = currentleft-ltarget;
    double errorright = currentright-rtarget;
    double lproportional;
    double rproportional;

    int start_time = seconds();
    int timer = seconds() - start_time;
    
    if(side == OVERLINE){
        
     while(!((analog(1) > (ltarget-50) && analog(1) < (ltarget+50)) && (analog(2) > (rtarget-50) && analog(2) < (ltarget+50))))                 
		//not on grey
     {
	 currentleft = analog(1);
	 currentright = analog(2);
	 errorleft = currentleft-ltarget;
     	 errorright = currentright-rtarget;
	 lproportional = KPL * errorleft;
	 rproportional = KPR * errorright;
         
	 /*
	 printf("lproportional: %lf\n",lproportional);
	 printf("rproportional: %lf\n",rproportional);
	 */
	 motor(LEFTWHEEL,lproportional);
         motor(RIGHTWHEEL,rproportional);
         msleep(10);
	 /*
         printf("Left: \t %i \n",analog(1));
         printf("Right: \t %i \n",analog(2));
     	*/
         timer = seconds() - start_time;
         if(timer>=10){break;} 
         }
     }

     if(side == UNDERLINE){
        
         while(!((analog(1) > (ltarget-50) && analog(1) < (ltarget+50)) && (analog(2) > (rtarget-50) && analog(2) < (ltarget+50))))                
             //not on grey
         {
	    currentleft = analog(1);
	    currentright = analog(2);
            errorleft = ltarget-currentleft;
            errorright = rtarget-currentright;
            lproportional = KPL * errorleft;
            rproportional = KPR * errorright;
	    /*
            printf("lproportional: %lf\n",lproportional);
            printf("rproportional: %lf\n",rproportional);
	    */
		 
            motor(LEFTWHEEL, lproportional);
            motor(RIGHTWHEEL, rproportional);
            msleep(10);
            /*
            printf("Left: \t %i \n",analog(1));
            printf("Right: \t %i \n",analog(2));
	    */
            timer = seconds()-start_time;
            //printf("\t TIEMPOOOOO: %i\n",tiempo);
            if(timer>=10){break;} 
         }
    }
    ao();
}
