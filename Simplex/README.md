# Quorb Inc. Simplex

## Overview

## The files

### Makefile
The makefile outputs the target .hex file as well as the target.elf file for debugging.  as well as other target files which can additional debugging options.  If you write any additional .c files, make sure you list it in the source section of the makefile.

### STM32L432_BitDefs.h
Defines the bits for all of the registers in the chip for easy editing.

### STM32L432_Map.h
Lays out the addresses for all of the registers in the chip.

### commonheader.h
Contains common constants and macros which are used across all files such as macros to set GPIO pin modes, turning pins on and off and defining alternate functions.  Constants such as PI are defined as well.

### genrtn.c and .h
Short for general routines.  These files contain useful functions which can be used across all files.

### interrupts.c and .h
These files contain the layout for all of the interrupts that can be thrown in the chip as well as contains empty functions for all of the interrupts.  The instructions for each interrupt are simply filled inbetween the curley brackets.  It is advised that if you are not using an interrupt to just leave the function empty and to keep the function for each interrupt as short as possible.  Function definitions can be cut from the interrupt file and pasted elsewhere for easy reading and troubleshooting.

### projectcode.c .h and .ld
Projectcode.c is where you will put your code in the main loop.  projectcode.h is where you will place any prototypes for any functions you define on your own.  Projectcode.ld is the linkerscript for the chip.

### projectdefs.h
Projectdefs.h is where all of your headerfiles come together.  Every header file has its include statement in this file so all that is required in any additional files you write is include projectdefs.h.

### strtup.c and .h

### timers.c and .h
