# QMX-32 Capella code reference
In the QMX-32 Skeleton code, we have made a large number of core macros and functions for you to use to easily write your program.  Here, they are laid out for easy reference.  As more code is written for the RTOS more functions and macros will be documented here making this software easier to use over time.

## Pin manipulation
Pins are the first and last interface you have with your chip, and as such are the first and last part you will manipulate.  Fortunately there are easy macros for you to do so.  

### defining pin types
There are four main modes a pin can be in.  They are input, output, analog and alternate.  Setting them is as simple as ```P'PIN'_'MODE';```.  An example for each is below.  
```C
PA10_IN;      //--- Sets pin A10 as an input.
PB05_OUT;     //--- Sets pin B05 as an output.
PA06_ANA;     //--- Sets pin A06 as an analog.  
PB12_ALT;     //--- Sets pin B12 as an alternate.
```

### toggling pins high and low
First things first, your pins need to do something.  While there is a lot they can do, the simplest thing is to set them high (sending out a voltage) or low (not sending out a voltage).  Some examples are below.
```C
SET_PA00;     //--- Sets pin A00 high
CLR_PB11;     //--- Sets pin B11 low.
```

### detecting pin input
If a pin can be an output, it can be an input as well.  You can use the command ```TST_P'PIN'```.  When this command is executed it will hold a value of either 1 or 0 depending on whether the pin is high or low respectively.  You may not want to use this as a standalone command as in the other pin modes.  Instead you want to nest it in an if statement such as in the code snippet below.
```C
if (TST_PB04)     //--- Tests if PB04 is high or low
{
    SET_PA03;     //--- If PB04 is high, PA03 will be set high
}
else
{
    CLR_PA03;     //--- If PB04 is low, PA03 will be set low
}
```

### assigning alternate functions to pins.
Alternate functions are not strongly tied to the pin itself, instead they are tied to other hardware within the chip such as i2c, timers, and uart.  Assigning an alternate function to a pin merely routes the pin to that other piece of hardware.  It is important to keep in mind that not every pin will go to every other piece of hardware in the chip.  For example, functions tied to timer 16 in the QMX-32 are only tied to pins A06, B05 and B06.  Which alternate functions tie to which pins can be determined in the datasheet or reference manual.  To assign an alternate function, define the target pin as an alternate pin and then the command after is ```P'PIN'_AF'NUMBER'```  Some code syntax is laid out below.
```C
PA06_ALT;     //--- Pin A06 is defined as an alternate pin
PA06_AF14;    //--- Alternate function 14 is used which is Channel one of timer 16.
```
