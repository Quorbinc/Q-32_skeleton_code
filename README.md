# Q-32_skeleton_code
This is the skeleton code for Quorb Inc's QMX-32 board.  All you need to do is write your code, compile it, and upload the .hex file into your board is programmed.

## Getting started
Getting a project running is easy.  
1. Open PROJECT.c.
2. Scroll down to the main function
3. Add your code to main similar to below. 
4. load it into the QMX-32 and you're off.

```
//--- some code omitted for clarity
int main (void)
{
  PA14_OUT;
  while (1)
  {
    SET_PA14;
    fnTickDelay(5000);
    CLR_PA14;
    fnTickDelay(5000);
  }
}
```
The above code will set PA_14 as an output, turn it on, wait for a half second, turn it off, wait for another half second and repeat the loop.  This looping method is a common way microcontrollers are programmed to operate but we have thrown in a different operating method.

## Using Tasks for real time operations
To use the RTOS nature of our software, we revolve everything we do around tasks, and task dispatching.  Tasks to start with are functions which start with the below format.  These functions get addressed in a task assignment and are then executed by the dispatcher

```
//--- General format
output_value name_of_function (union DFLWB name_of_task_data)
{
  //--- code 
}

//--- Examples 
void BlinkLED (union DFLWB taskdata)
{
  //--- Your code goes here
}

u16 temperature_measurement (union DFLWB temperaturedata)
{
  //--- Your code goes here
}

```

How do you get your defined tasks assigned you ask?  Simple,  You fill out a task struct.  You can have one you work with for everything as many as you need.  Defining a task is as simple as ```struct  Task  nameOfTask``` and then you fill oin the data for the task to get assigned.  A task is laid out below.

```
struct Task
{
  u16     uwTimer;            //--- Task Timer delay value (0 - 65535 mSec)
  u16     uwFlags;            //--- Temporary Flags to Pass
  void    (*ptrTask);         //--- Address Pointer of Task
  union DFLWB unTaskData;     //--- Generic unDFLB Data Union
};
```
To put it all together you can make a program like this in project.c

```
//-----Some code omitted for clarity-----//

struct Task LEDTask //--- Defines a task to be used.

int main (void)
{
    PA14_OUT;                              //--- Set PA14 as Output
    
    LEDTask.uwTimer = 333;
    LEDTask.ptrTask = &tkBlinkLED;
    LEDTask.uwFlags = 0;
    LEDTask.unTaskData = unEmptyData;      //--- Empty Data to Start
    uwReturnVal = fnScheduleTask(LEDTask);

  //--- Main Infinite Loop entry point calls Dispatcher and any polled actions
  
  while (1)
  {
    fnDispatcher();
  }
}

//-----Function for a a task to blink the LED-----//
void tkBlinkLED (union DFLWB unTD)
{
  struct  Task stTask;                              //--- Task Model for Scheduling Tasks

  if (TST_PA14)     //--- Test to see if the pin is high
  {
      CLR_PA14;     //--- Turn the pin off
  }
  else
  {
      SET_PA14;     //--- Turn the pin on
  }

  //--- This task will reschedule itself 2 times / Second
  stTask.uwTimer = 500;                             
  stTask.ptrTask = &tkBlinkLED;
  stTask.uwFlags = 0;
  stTask.unTaskData = unTD;
  uwReturnVal = fnScheduleTask (stTask);
}
```
Make sure you include the below line in project.h
```
void tkBlinkLED (union DFLWB unTD);
```
What the above program will do is enter main and schedule the blinkled function
