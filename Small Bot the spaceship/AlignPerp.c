#include <kipr/botball.h>
#include <stdio.h>

#define LEFTWHEEL 0
#define RIGHTWHEEL 1
#define KPR 0.025
#define KPL 0.025
#define GRAYMAX 2300
#define GRAYMIN 1900

void align(int side, int lport, int rport, double ltarget, double rtarget);


void align(int side, int lport, int rport, double ltarget, double rtarget) 
{
    double currentleft = analog(lport);
    double currentright = analog(rport);
    double errorleft = currentleft-ltarget;
    double errorright = currentright-rtarget;
    double lproportional;
    double rproportional;
	printf("Hello\n");
    int start_time = seconds();
    int timer = seconds() - start_time;
    
    if(side == 1){
     printf("Yes\n");
     while(!((analog(lport) > (ltarget-50) && analog(lport) < (ltarget+50)) && (analog(rport) > (rtarget-50) && analog(rport) < (rtarget+50))))          
     {
     printf("Yes1\n");
	 currentleft = analog(lport);
	 currentright = analog(rport);
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
	 
         printf("Left: \t %i \n",analog(lport));
         printf("Right: \t %i \n",analog(rport));
     	
         timer = seconds() - start_time;
         if(timer>=5){break;} 
         }
     }

     if(side == 2){
         printf("No\n");
         while(!((analog(lport) > (ltarget-50) && analog(lport) < (ltarget+50)) && (analog(rport) > (rtarget-50) && analog(rport) < (rtarget+50))))                
             //not on grey
         {
	    currentleft = analog(lport);
	    currentright = analog(rport);
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
            if(timer>=5){break;} 
         }
    }
    ao();
}
