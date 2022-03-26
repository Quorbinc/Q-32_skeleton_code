# Quorb Basic RTOS


### QUORB BASIC RTOS DEFINED:
The QUORB BASIC RTOS System is a powerful yet simplified event driven operating system taking up less than 2K of program space. This RTOS opperates with very little system resource overhead.  It is composed of 4 main sections. 
1. Task thread execution all TASKs are a common "C" function with a defined data load. 
2. TASK Scheduling and TASK Dispatching functions which control the placement of TASKs into a Queue and the execution order by the Dispatcher. 
3. SYS_TICK Interrupt which controls timed and repetitive functions it also executes a set of "house keeping" functions. 
4. Event Driven Interrupts.  

These sections make up an efficient task scheduling and dispatching real time operating system. This allows for the fast handling of real time events and processing of data when execution load in the system is less off loading the time of processing system events.


### BASIC RTOS OPERATION:
There are 2 types of TASKS handled within the operating system, these are the "Timed" and "Event Driven" types. During operation, TASKs are "stimulated" by hardware reactions and interrupts. In a background process additional TASKs can be schedueled by an internal accurate time based interrupt. Additionally events can be created during software polled loops or status checking usually encountered in the "main" endless loop. Timed tasks are processed by a background function that runs continuously, this process is referred to as the "SYS_TICK".  This process can only be paused by a direct intervening process that is available for use in special cases.  The SYS_TICK is always running and allows the system to keep perfect time and sequencing of time driven actions.


### TASK DEFINITION:
A TASK is defined as a structure placed into a storage location for execution at another time.  The TASK resides in program memory at a fixed memory location and is a compiled function.  The TASK contains several components that allow the invocation of a code thread.  TASKS are placed into a memory QUEUE by the SCHEDUELER function on the basis of timing.  TASKs are executed when the DISPATCHER takes the TASK structure from the QUEUE and calls it by the execution memory address.  All Tasks have the same defined structure which defines the TASKs execution address, Timing Information and passable data load.  It should be noted that tasks are stored and executed by data value and not by reference.  If the user wishes to pass data to the TASK by reference, then the memory location of the data is passed as a pointer after the data has been placed in a memory buffer.  The executed TASK should return the referenced data to the heap upon exit.


### TASK STRUCTURE DEFINED:
A Task is defined as a function with a predefined Data Input Construct and a predefined Return Construct. Containing the following structures and fields.  A TASK has a fixed length of 16 bytes

```C
//--- 16 Byte Task Definition
struct TASK
{
    u32     ulTimeDelay;          //--- Execution Time Delay if > 0     4 Bytes
                                  //    This allows for a TASK to be executed at
                                  //    specific time or delay.
    u32     *ulTaskAddress;       //--- Pointer to actual Task Address  4 Bytes 32 bit address

    union   TASKDATA TaskData;    //--- 8 Bytes of Passable Data        8 Bytes
}
```

### TASKDATA UNION DEFINED:
TASKDATA is an 8 byte C coded union containing be defined as virtually ANY type of "C" data to be passed.

```
//--- 8 Byte Task Data definition
union TASKDATA
{
    dbl   dfFlt;                                //--- 1 Double Precision Float
    u64   uxLL;                                 //--- 1 Unsigned 64 Bit Long Long Integer
    s64   sxLL;                                 //--- 1 Signed 64 Bit Long Long Integer
    u08*  ubPtr[2];                             //--- 2 General Purpose Byte Pointers
    void* vPntr[2];                             //--- 2 Void Type Pointers
    flt   sfFlt[2];                             //--- 2 Single Precision Floats
    u32   ulLong[2];                            //--- 2 Unsigned Long
    s32   slLong[2];                            //--- 2 Signed Long
    u16   uwWord[4];                            //--- 4 Unsigned Words (16 Bit)
    s16   swWord[4];                            //--- 4 Signed Words (16 Bit)
    u08   ubByte[8];                            //--- 8 Unsigned Bytes
    s08   sbByte[8];                            //--- 8 Signed Bytes
};
```

### TASK SCHEDUELING AND DISPATCHING:
The Task Scheduling and Dispatching allows for fast reaction to events with the ability to process important data and calculations in the background.  An event schedules a Task and passes the data for that Task to a FIFO buffer.  When the current Task finishes its operations it returns to the Dispatcher where the next Task is fetched and executed.  For an RTOS system Very little time is spent in an Interrupt service routine. Events typically acquire data from hardware stimuli and schedule a Task for action on the data at the appropriate time thus making sure there are little or no conflicts between hardware interrupts, events and the system thread operation.


### SCHEDULING TASKS:
A TASK may be scheduled from within any mode of processor operation. Any thread, interrupt, or function operation can schedule a TASK.  All TASKs have the same structure allowing for simple data passing when they are scheduled.  The user creates a TASK structure in memory (either local or global), assigns the values to the TASK structure that are required then calls the SCHEDUELER to place the TASK into the QUEUE buffer at an empty location.  The scheduler then examines the tasks priority level and inserts the task into the QUEUE depending on its priority level.  The SCHEDUELER returns an error code showing the success or scheduling error type.  "0" = success in scheduling and any other numeric value represents the error encountered.


### DISPATCHER OPERATION:
The Dispatcher is called from the "main" tight loop.  During operation the dispatcher Tests to see if there are any tasks waiting for execution.  If there is a TASK waiting in the QUEUE then the DISPATCHER extracts the first available TASK from the QUEUE and
then calls the TASK as a function.  When the TASK finishes execution it will return to the Dispatcher with an error code should the TASK exit with an error.  If there is an error returned from the task then a general purpose error handler is executed to process any ramifications of the error.


### TASK QUEUE INNER WORKINGS:
The TASK Queue is a circular buffer which contains active Tasks placed in a FIFO (First in First ont) buffer.
After a previous TASK has completed the Dispatcher Examines the returned Error Code and processes any returned Errors from the TASK.  If no errors are returned by the TASK the DISPATCHER exits back to the "main loop".  If there are polled or looped actions that the "main" needs to execute then these calls can be to the program.  When the "main loop" returns back to the top of the loop the DISPATCHER is called again.


### SYS_TICK TIMER INTERRUPT:
This is the "HeartBeat" of the system and is a precisley timed interrupt.  This interrupt has a system level priority and cannot be  disabled except during RTOS internal functions.  This interrupt occurs at interval of 100 uSec or (10,000 Times / second). During the SYS_TICK interrupt there are a series of "house keeping" actions.  These are automatically schedueled during this interrupt for execution at a time the RTOS sees fit.  Internal to the SYS_TICK is a 64 bit time keeping register that is bumped +1 every time the SYS_TICK executes, since the SYS_TICK interrupt cannot be totally disabled this register is always accurate to the system clock. The accuracy of the CLOCK typically is +/- 1 PPM.

In the RTOS system there exists a set of 10 delayed action timers that allow for execution of functions at an exact time in the future (+/- 1mSec). Each time the SYS_TICK Interrupt is entered one of 10 possible active timers is decremented by 1.  When a timer value reaches zero (0) the corresponding function is scheduled to be executed. This frees the system from loop polling and pausing delays.  TASKs can be delayed or predicted to 1 mSec accuracy within 4.97 days.


### THE EVENT DRIVEN INTERRUPTS:
These interrupts occur after a particular hardware or software event occurs.  The NVIC interrupt CONTROLLER services the hardware or software associated with the interrupt and either takes immediate action or the event is converted to a TASK and is scheduled for later execution. The Task may be scheduled to execute at a pre determined time delay if required.  Under the RTOS, events generated from hardware or software sources are processed to handle the capture or action on data from or to the system operation.
