#include <kipr/botball.h>
#include<stdbool.h>

void clock_set();

int main()
{	
	clock_set();
	return 0;
}

void clock_set() {
	int min = 0; int hour = 0;
	while (!digital(0)) {
		if (left_button() || right_button()) { //if any button is pressed
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
}
