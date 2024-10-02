#include <reg51.h>
#include <math.h>
#include "ds1302.h"

const unsigned char DIGIT[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

//Define button pin
sbit K1 = P3^1;
sbit K2 = P3^0;
bit buttonPressed = 0;  // Flag to indicate if the button was pressed
bit latchState = 0;     // State of the latch (0 or 1)


//Define 7-segment PIN
#define LED P0
sbit A = P2^2;
sbit D = P2^3;
sbit C = P2^4;


//Delay func
void delay(long time) {
    while (time--) {;}
}



//Since ds1302 use BCD, we have to convert it into Decimal

//Hour, min, sec display
void Display1() {
    // Show hour
    C = 1; D = 1; A = 1;
    LED = DIGIT[hour / 10];
    delay(50);
    A = 0;
    LED = DIGIT[hour % 10];
    delay(50);
		// '|' split
		C = 1; D = 0; A = 1;
		LED = 0x5c;
		delay(50);
    // Show min
    C = 1; D = 0; A = 0;
    LED = DIGIT[min/ 10];
    delay(50);
    C = 0; D = 1; A = 1;
    LED = DIGIT[min% 10];
    delay(50);
		// '|' split
		A = 0;
		LED = 0x5c;
		delay(50);
    // Show sec
    C = 0; D = 0; A = 1;
    LED = DIGIT[sec / 10];
    delay(50);
    A = 0;
    LED = DIGIT[sec % 10];
    delay(50);
}

//Year, month,day display
void Display2(){
    // Show year
    C = 1; D = 1; A = 1;
    LED = DIGIT[year / 10];
    delay(50);
    A = 0;
    LED = DIGIT[year % 10];
    delay(30);
		// '|' split
		C = 1; D = 0; A = 1;
		LED = 0x40;
		delay(50);
    // Show month
    C = 1; D = 0; A = 0;
    LED = DIGIT[month/ 10];
    delay(50);
    C = 0; D = 1; A = 1;
    LED = DIGIT[month% 10];
    delay(50);
		// '|' split
		A = 0;
		LED = 0x40;
		delay(50);
    // Show date
    C = 0; D = 0; A = 1;
    LED = DIGIT[date / 10];
    delay(50);
    A = 0;
    LED = DIGIT[date % 10];
    delay(50);
}




// Main 
void main() {
    K1 = 1;  // Set button pin as input
		DS1302_SetTime(00,00,11,1,10,24); //11h00m00s 1/10/2024
		//SetCompileTime();
    DS1302_Init();  // Initialize DS1302

    while (1) {
        DS1302_GetTime();			// Get time from DS1302

        if (K1 == 0) {  // Check if button is pressed
            delay(5);  // Debounce the button
            if (K1 == 0 && !buttonPressed) {  // Confirm button press and check if it was not already pressed
                buttonPressed = 1;  // Set button pressed flag
                latchState = !latchState;  // Toggle latch state
            }
        } 
				else {
            buttonPressed = 0;  // Reset button pressed flag when button is released
        }

        if (latchState == 0) {
            Display1();  // Display time
        } 
				else {
            Display2(); //Display date
        }
    }
}