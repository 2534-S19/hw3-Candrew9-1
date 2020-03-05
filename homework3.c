#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework3.h"
#include "myGPIO.h"
#include "myTimer.h"





int main(void)
{
    button_enum boardButton = Released;
    // Count variables to control the LEDs.
    unsigned int count0 = 0;
    unsigned int count1 = 0;

    // TODO: Declare the variables that main uses to interact with your state machine.


    // Stops the Watchdog timer.
    initBoard();
    // Initialize the GPIO.

    initGPIO();
    // Initialize Timer0 to provide a one second count interval for updating LED2.

    initTimer(TIMER32_0_BASE, TIMER0_PRESCALER, TIMER0_COUNT);
    // Initialize Timer1 to provide a one millisecond count interval for updating the button history.

    initTimer(TIMER32_1_BASE, TIMER1_PRESCALER, TIMER1_COUNT);

    while(1)
    {
        // Update the color of LED2 using count0 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeLaunchpadLED2(count0);
        // Update the color of the Boosterpack LED using count1 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeBoosterpackLED(count1);


        // YOU MUST WRITE timer0expired IN myTimer.c
        if (timer0Expired()) {
            count0++;
        }


        // YOU MUST WRITE timer1expired IN myTimer.c
        if (timer1Expired()) {
            count1++;
        }


        // TODO: Call the button state machine function to check for a completed, debounced button press.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        fsmBoosterpackButtonS1(boardButton);


        // TODO: If a completed, debounced button press has occurred, increment count1.



    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);

    //initialize LEDs
}

//change to

// TODO: Map the value of a count variable to a color for LED2.
// Since count is an unsigned integer, you can mask the value in some way.
void changeLaunchpadLED2(unsigned int count)
{

    switch(count)
    {
    case 1: //change color to red
        turnOn_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Green();
        turnOff_LaunchpadLED2Blue();
        break;
    case 2: //change color to red + green
        turnOn_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Green();
        turnOff_LaunchpadLED2Blue();
        break;
    case 3: //change color to green
        turnOff_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Green();
        turnOff_LaunchpadLED2Blue();
        break;
    case 4: //change color to green + blue
        turnOff_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Blue();
        break;
    case 5: //change color to blue
        turnOff_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Blue();
        break;
    case 6: //change color to blue + red
        turnOn_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Blue();
        break;
    case 7: //change color to red + green + blue
        turnOn_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Blue();
        break;
    default: //no color
        turnOff_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Green();
        turnOff_LaunchpadLED2Blue();
        break;
    }
}

// TODO: Maybe the value of a count variable to a color for the Boosterpack LED
// This is essentially a copy of the previous function, using a different LED
void changeBoosterpackLED(unsigned int count)
{
    switch(count)
        {
        case 1: //change color to red
            turnOn_BoosterpackLEDRed();
            turnOff_BoosterpackLEDGreen();
            turnOff_BoosterpackLEDBlue();
            break;
        case 2: //change color to red + green
            turnOn_BoosterpackLEDRed();
            turnOn_BoosterpackLEDGreen();
            turnOff_BoosterpackLEDBlue();
            break;
        case 3: //change color to green
            turnOff_BoosterpackLEDRed();
            turnOn_BoosterpackLEDGreen();
            turnOff_BoosterpackLEDBlue();
            break;
        case 4: //change color to green + blue
            turnOff_BoosterpackLEDRed();
            turnOn_BoosterpackLEDGreen();
            turnOn_BoosterpackLEDBlue();
            break;
        case 5: //change color to blue
            turnOff_BoosterpackLEDRed();
            turnOff_BoosterpackLEDGreen();
            turnOn_BoosterpackLEDBlue();
            break;
        case 6: //change color to blue + red
            turnOn_BoosterpackLEDRed();
            turnOff_BoosterpackLEDGreen();
            turnOn_BoosterpackLEDBlue();
            break;
        case 7: //change color to red + green + blue
            turnOn_BoosterpackLEDRed();
            turnOn_BoosterpackLEDGreen();
            turnOn_BoosterpackLEDBlue();
            break;
        default: //no color
            turnOff_BoosterpackLEDRed();
            turnOff_BoosterpackLEDGreen();
            turnOff_BoosterpackLEDBlue();
            break;
        }
}

// TODO: Create a button state machine.
// The button state machine should return true or false to indicate a completed, debounced button press.
bool fsmBoosterpackButtonS1(button_enum buttonState) {
    bool pressed = false;


    //determine the current state
    unsigned char currentState = GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN1);
    //unsigned char nextState = 0x00;


    switch (buttonState) {
        case Pressed: //pressed
            if (currentState == 0) {
                //button is pressed
                pressed = true;
            }
            else {
                buttonState = PressedtoReleased;
            }
            break;
        case Released: //released
            if (currentState == 1) {
                //button is pressed
                pressed = false;
            }
            else {
                buttonState = ReleasedtoPressed;
            }

            break;
        case PressedtoReleased:
            //check for timer
            if (timer1Expired) {
                if (currentState == 0) {
                    buttonState = Pressed;

                }
                else {
                    buttonState = Released;
                }
            }
            break;
        case ReleasedtoPressed:
            //check for timer
            if (timer1Expired) {
                if (currentState == 0) {
                    buttonState = Pressed;
                }
                else {
                    buttonState = Released;
                }
            }
            break;

        }






    return pressed;
}


