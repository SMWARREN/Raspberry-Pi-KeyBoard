/*


Sean Warren
12/3/2014

    Part of the Raspberry-Pi Bare Metal Tutorials
    Copyright (c) 2013, Brian Sidebotham
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
        this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
        this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.

*/

/*
    C-Library stubs introduced for newlib
*/

#include <string.h>
#include <stdlib.h>
#include "rpi-gpio.h"
#include "assembly.h"
#include <types.h>
#include <device/hid/keyboard.h>
#include <usbd/usbd.h>

/** GPIO Register set */
volatile unsigned int* gpio = (unsigned int*)GPIO_BASE;

//variables to be used in my program
int KeyboardCount1 = 0;
u32 KeyboardAdress1 = 0;
int Address = 0;
u32 KDs = 0;
int KDD[5];
bool modDown = false;

//function structures
void checkKeys(u32 Address,u32 KDs);
void checkMod(u32 Address,u32 KDs);
void blink4();
void blink3();
void blink43();
void blink43s();
void BothKeys();


/*Query the keyboard
if a letter or one of the symbols from the number row over the letters is pressed: blink the ok LED 4 times rapidly (4 'dots' to use the tutorial's terminology)
if one of the 8 special keys are pressed, blink the ok LED 3 times slowly (3 dashes)
if both of the above are pressed, blink 4 dots followed by 3 dashes
if any other key is pressed, blink dash-dot-dash-dot-dash-dot.*/

void checkKeys(u32 Address,u32 KDs){
    //checks if Keysdown is greater than zero and that none of the modifiers are pressed.
    while (KDs > 0 && KeyboardGetModifiers(Address).LeftControl == false || KeyboardGetModifiers(Address).LeftShift == false || KeyboardGetModifiers(Address).LeftAlt == false || KeyboardGetModifiers(Address).LeftGui == false || KeyboardGetModifiers(Address).RightControl  == false || KeyboardGetModifiers(Address).RightShift == false || KeyboardGetModifiers(Address).RightAlt == false || KeyboardGetModifiers(Address).RightGui == false){

        int i;
        // I created a loop that goes through all of the keys that are not a letter key, or one of the symbols of the numbers row
        for (i = 40; i < 129; i++) {
        //if any other key is pressed, blink dash-dot-dash-dot-dash-dot.*/
        if (KeyboadGetKeyIsDown(Address,i)){
        blink43s();
            }
        }
        // checks if a letter or one of the symbols from the number row over the letters is pressed: blink the ok LED 4 times rapidly (4 'dots' to use the tutorial's terminology)
        int k;
        for (k = 4; k < 39; k++) {
                //i check the boolean if the modifer key has been pressed
        if (KeyboadGetKeyIsDown(Address,k) && modDown == false){
        blink4();}
        }
        break;
    }

}


void checkMod(u32 Address,u32 KDs){
// i check if any of the keyboardgetmodifers are set to true
  if(KeyboardGetModifiers(Address).LeftControl == true || KeyboardGetModifiers(Address).LeftShift == true || KeyboardGetModifiers(Address).LeftAlt == true || KeyboardGetModifiers(Address).LeftGui == true || KeyboardGetModifiers(Address).RightControl  == true || KeyboardGetModifiers(Address).RightShift == true || KeyboardGetModifiers(Address).RightAlt == true || KeyboardGetModifiers(Address).RightGui == true){
                KeyboardPoll(Address);
                modDown = true;
                //i set a boolean so when i press both keys, it will do my checkKeys function.
                if (KDs > 0){
                        //if both of the above are pressed, blink 4 dots followed by 3 dashes

                    BothKeys(Address);
                    }
                else{
              //if one of the 8 special keys are pressed, blink the ok LED 3 times slowly (3 dashes)
                blink3();
                }
            }
}

void blink43s(){

    int i;
    for (i = 0; i < 3; i++) {
		//BLINK ONCE SLOW
        Wait(800000);
		SetGpio(16, 0);
		Wait(800000);
		SetGpio(16, 1);
		// BLINK ONCE FAST
        Wait(500000);
		SetGpio(16, 0);
		Wait(250000);
		SetGpio(16, 1);
    }
}
void blink4(){
    int i;
    for (i = 0; i < 4; i++) {
		Wait(500000);
		SetGpio(16, 0);
		Wait(250000);
		SetGpio(16, 1);
	}
}

void blink3(){
    int i;
    for (i = 0; i < 3; i++) {
		Wait(800000);
		SetGpio(16, 0);
		Wait(800000);
		SetGpio(16, 1);
    }
}


void blink43(){
    blink4();
	blink3();
}

void BothKeys(u32 Address){
    int m;

    //checks if any of the letter keys and if the number keys above them are pressed
    for (m = 4; m < 39; m++) {
    if (KeyboadGetKeyIsDown(Address,m)){
    blink43();}
    }
}

/** Main function - we'll never return from here */
void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
    //Initialise the usb
    UsbInitialise();
    while(1){
            //check for USB Change, if you connect or disconnect the keyboard
    UsbCheckForChange();
    if (KeyboardCount() > 0){
        //if there is a keyboard set the address and poll the keys and store the value of how many keys are down
        Address = KeyboardGetAddress(0);
        KeyboardPoll(Address);
        KDs = KeyboardGetKeyDownCount(Address);
        //set the boolean to false
        modDown = false;
        checkMod(Address,KDs);
        checkKeys(Address,KDs);

    if(KeyboardCount() == 0){


		SetGpio(16, 0);

        }

       }
    }
}
