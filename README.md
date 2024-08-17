# Q-32_skeleton_code
This is the skeleton code for Quorb Inc's QMX-32 board.  All you need to do is write your code, compile it, and upload it and then  your board is programmed.

## Getting started
Getting a project running is easy.  
1. Open PROJECT.c.
2. Scroll down to the main function
3. Add your code to the main function. 
4. load it into the QMX-32 and you're off.
```C
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
The above code is a simple blink led function.  It will set PA_14 as an output, turn it on, wait for a half second, turn it off, wait for another half second and repeat the loop.  This looping method is a common way microcontrollers are programmed to operate but we have thrown in a different operating method.

## Using Tasks for real time operations
To use the RTOS nature of our software, we revolve everything we do around tasks, and task dispatching.  Tasks to start with are functions which start with the below format.  These functions get addressed in a task assignment and are then executed by the dispatcher
```C
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
```C
struct Task
{
    u16     uwTimer;            //--- Task Timer delay value (0 - 65535 mSec)
    u16     uwFlags;            //--- Temporary Flags to Pass
    void    (*ptrTask);         //--- Address Pointer of Task
    union DFLWB unTaskData;     //--- Generic unDFLB Data Union
};
```

## Putting it all together
To schedule and use tasks, you can make a program like the program below in project.c and project.h to blink an LED
```C
//-----Some code omitted for clarity-----//

struct Task LEDTask //--- Defines a task to be used.

int main (void)
{
    PA14_OUT;                              //--- Set PA14 as Output
    
    //--- Lines 73 through 77 schedule the blinkLED task to kick the program off
    LEDTask.uwTimer = 333;
    LEDTask.ptrTask = &BlinkLED;
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
void BlinkLED (union DFLWB unTD)
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
    stTask.ptrTask = &BlinkLED;
    stTask.uwFlags = 0;
    stTask.unTaskData = unTD;
    uwReturnVal = fnScheduleTask (stTask);
}
```
Make sure you include the below line in project.h
```C
void BlinkLED (union DFLWB unTD);
```
What the above program will do is enter main and schedule the blinkled function.  The program will then enter the loop in which it will continue to execute the dispatcher.  Once the first scheduled task counts down to zero, it will execute the BlinkLED function which will toggle the pin accordingly and then schedule itself again as a continuous loop blinking the LED in the same manor as the loop method above.

## When where to use tasks
You can use tasks anywhere you decide so long as your program is able to get to a point where it can hit the task schedule.  If you schedule a task within a function that is never called, then the task will never be scheduled, so this allows you a lot of freedom in where you can place tasks.  Like earlier, you can call the task call at the beginning of the main function before the loop is called.  You can use an if statement in the main loop so if a condition is met, such as a button gets pressed, it will then schedule a task.  You can have an interrupt schedule a task, which has an added bonus of getting you in and out of the interrupt faster than if you have the interrupt run through lines upon lines of code.     
