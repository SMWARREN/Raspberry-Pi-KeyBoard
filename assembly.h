/******************************************************************************
*	assembly.h
*	 by Alex Chadwick
*
*	assembly.h A header file defining the sybols from the assembly code to
*	be called from either C or C++.
******************************************************************************/

#ifndef _ASSEMBLY_H_
#define _ASSEMBLY_H_

#ifdef __cplusplus
/*	extern "C" is required in C++ to indicate these functions are not subject
	to name mangling. It is not legal in C hence the ifdef __cplusplus. */
extern "C" {
#endif

void* GetGpioAddress();
void SetGpioFunction(unsigned int gpioRegister, unsigned int function);
void SetGpio(unsigned int gpioRegister, unsigned int value);
void* GetSystemTimerBase();
unsigned long long GetTimeStamp();
void Wait(unsigned int delayInMicroSeconds);

#ifdef __cplusplus
}
#endif

#endif
