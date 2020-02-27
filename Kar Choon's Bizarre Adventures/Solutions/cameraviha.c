#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <botball.h>
void cameraViha(){
// ideal area > 3000
    camera_open();
    msleep(1000);
    printf("Camera opened\n");
   /* int counter = 0;
	while(counter<=20){
        camera_update();
        if (get_object_area(3,0) != -1){
    		printf("detected\n");
        	printf(" x: %d\n", get_object_center(3, 0).x );
    		printf(" y: %d\n", get_object_center(3, 0).y );
            printf(" area: %d\n", get_object_area(3,0));
        	ao();
    	}
        counter++;
    }*/
  if (get_object_area(3,0) > 3000){
    	printf("detected\n");
        
        ao();
    }
    double current = seconds();
    double amount = current + 50;
    while(get_object_area(3,0) < 3000 && current < amount){
        current = seconds();
        printf("in the while loop \n");
    	camera_update();
        printf(" %d\n ", camera_update());
    	printf(" %d\n  ",get_object_area(3, 0));
        motor(LEFT, -20);
    	motor(RIGHT, 20);
        msleep(10);
    }
    printf("outside the while loop\n");
    msleep(100);
   	while(( get_object_center(3, 0).x <= 70 ||  get_object_center(3, 0).x >= 75) && (get_object_center(3, 0).y <= 33 ||  get_object_center(3, 0).y >= 37) ){
        printf("in the first conditional while loop\n");
        motor(0,-10);
		motor(1,-10);
        msleep(10);
        printf("x: %d\n",  get_object_center(3, 0).x);
        printf("y: %d\n",  get_object_center(3, 0).y);
        camera_update();
		/*while (get_object_center(3,0).y < 40){
            printf("in the second conditional while loop and y is lower than required range");
            motor(0,-10);
            motor(1,-10);
            msleep(10);
        	printf("x: %d\n",  get_object_center(3, 0).y);
        	camera_update();
        	counterx++;
        }
        while(get_object_center(3,0).x > 55){
            printf("in the second conditional while loop and y is higher than required range");
            motor(0,10);
            motor(1,10);
            msleep(10);
        	printf("x: %d\n",  get_object_center(3, 0).y);
        	camera_update();
        	counterx++;
            
        }*/
    }
    ao();
    camera_close();
    printf("camera closed\n");
}
int main(void) {
  
  return 0;
}
