Sean Warren

12/3/2014

======================================
# Query the keyboard
1. if a letter or one of the symbols from the number row over the letters is pressed: blink the ok LED 4 times rapidly (4 'dots' to use the tutorial's terminology)
2. if one of the 8 special keys are pressed, blink the ok LED 3 times slowly (3 dashes)
3. if both of the above are pressed, blink 4 dots followed by 3 dashes
4. if any other key is pressed, blink dash-dot-dash-dot-dash-dot.


======================================

To build my project I used this Build Command

-----------------------------------------------------------------------------

> @ECHO ON

> arm-none-eabi-gcc -O0 -mfpu=vfp -mfloat-abi=soft -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g -Wl,-T,rpi.x -I./csud-master/include -o kernel-009.elf gpio.s systemTimer.s armc-009.c armc-009-cstartup.c armc-009-start.S armc-009-cstubs.c -L. -lcsud arm-none-eabi-objcopy kernel-009.elf -O binary kernel.img pause

------------------------------------------------------------------------------
https://github.com/BrianSidebotham/arm-tutorial-rpi

> This repository contains the code for the Raspberry-Pi bare-metal programming in C series. The home of the tutorial and all of the articles relating to the code is at http://www.valvers.com/embedded-linux/raspberry-pi

> You can build on linux, windows, or MAC - all you need is the arm-none-eabi toolchain.

> For all platforms, you can get the required toolchain used in this tutorial from the https://launchpad.net/gcc-arm-embedded project - I recommend getting the 4.7 toolchain because I've had problems with the 4.9 toolchain.

In my project, I used the arm009 files to base my main structure off. If you build my project with the build command you will get warnings that pertain to the output saying the output uses 2-byte wchar_t yet the output is to use 4-byte wchar_t; use of wchar_t values across objects may fail. But the program still accomplishes all of the goals of the project. I also included some assembler files to make proccesing the lights faster because I wanted to learn how to use the assembler commands with C. I Implemented these two function in my program.


```C++
/* NEW
* SetGpio sets the GPIO pin addressed by register r0 high if r1 != 0 and low
* otherwise. 
* C++ Signature: void SetGpio(u32 gpioRegister, u32 value)
*/

/*
* Wait waits at least a specified number of microseconds before returning.
* The duration to wait is given in r0.
* C++ Signature: void Wait(u32 delayInMicroSeconds)
*/

```

