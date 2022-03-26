# Quorb Inc. Simplex

## Overview
Simplex is our most redimentry system for embedded programming.  The main intent behind simplex is to just initialize the chip and get it to the main loop, making simplex perfect for simple tasks, education, or testing.

## The files

### Makefile
The makefile outputs the target.hex file as well as the target.elf file for debugging.  as well as other target files which can add additional debugging options.  If you write any additional .c files, make sure you list it in the source section of the makefile or else they will not be compiled.

### STM32L432_BitDefs.h
STM32L432_BitDefs.h is provided by ST and appilies human readable names to all of the individual bits for all of the registers in the chip for easy editing.  

### STM32L432_Map.h
STM32L432_Map.h is also provided by ST.  It lays out the addresses for all of the registers which are used in the chip.  The memory addresses can be used in conjunction with STM32L432_BitDefs.h in order to manipulate the registers within the chip.  Alternatively, all of the register addresses correspond to a thirty-two bit number, so all of the bits can be manipulated by assigning a number to that address.  
```c
//--- example of turning on and off the CEN bit in TIM2 using a bit definition
TIM2_CR1 |= TIM_CR1_CEN; //--- turn on the CEN bit
TIM2_CR1 &= ~(TIM_CR1_CEN); //--- turn off the CEN bit

//--- example of turning on and off the CEN bit in TIM2 using a number
TIM2_CR1 |= 0x00000001; //--- turn on the CEN bit
TIM2_CR1 &= 0xFFFFFFFE; //--- turn off the CEN bit
```

### commonheader.h
Contains common constants and macros which are used across all files such as macros to set GPIO pin modes, turning pins on and off and defining alternate functions.  Constants such as PI are defined as well.

### genrtn.c and .h
Short for general routines.  These files contain useful functions which can be used across all files for troubleshooting or common use that is not limited to any one type of project..

### interrupts.c and .h
These files contain the layout for all of the interrupts that can be thrown in the chip as well as contains empty functions for all of the interrupts.  The instructions for each interrupt are simply filled inbetween the curley brackets.  It is advised that if you are not using an interrupt to just leave the function empty and to keep the function for each interrupt as short as possible.  Function definitions can be cut from the interrupt file and pasted elsewhere for easy reading and troubleshooting.

### projectcode.c .h and .ld
Projectcode.c is where you will put your code in the main loop.  projectcode.h is where you will place any prototypes for any functions you define on your own.  Projectcode.ld is the linkerscript for the chip.

### projectdefs.h
Projectdefs.h is where all of your headerfiles come together.  Every header file has its include statement in this file so all that is required in any additional files you write is include projectdefs.h.

### strtup.c and .h
Startup.c and startup.h are exactly what they sound like.  These programs run the reset interrupt function to initialize the chip and bring all the registers to a starting phase.

### timers.c and .h
Timers.c and timers.h as their name suggests, deal with timer peripherals.  These have functions to initialize any timers you may use as well as use the timers as you need such as delays, timer input and output, and PWM.
