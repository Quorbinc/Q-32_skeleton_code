//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                        Real Time Operating System Core Programs
//                  -----------------------------------------------------
//
//    This code is for use on the STM32L432 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32     Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//         Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#include "projectdefs.h"

//---------------------------------------------------------------------------------------------
//  Task Definition
//---------------------------------------------------------------------------------------------
//
//  //--- 24 Bytes / Task
//  struct Task
//  {
//    u32     ulTimer;                            //--- Timer delay Value (0000 - 4G milliseconds)
//    void    (*ptrTask);                         //--- Address Pointer of Task
//    struct  PassData stPassData;                //--- Generic stPassData Structure
//      8 Bytes Time Stamp;                       //--- .uxTimeStamp
//      union DFLWB                               //--- Data Union unTaskData
//  };
//
//
//  Task Function Definition:
//  fnFunctionName (struct PassData stTaskData)
//
//
//  structure PassData
//  {
//    u64   uxTimeStamp;                          //--- Time Stamp when Schedueled
//    union DFLWB stTaskData;                     //--- DFLWB Data union
//  }
//
//---------------------------------------------------------------------------------------------
//  Task Data Union Definition
//---------------------------------------------------------------------------------------------
//
//  union DFLWB                                   //--- 8 Bytes Binary / Integer Storage
//  {
//    dbl   dfFlt;                                //--- 1 Double Precision Float
//    u64   uxBig;                                //--- 1 Unsigned 64 Bit Integer
//    s64   sxBig;                                //--- 1 Signed 64 Bit Integer
//    flt   sfFlt[2];                             //--- 2 Single Precision Floats
//    u32   ulLong[2];                            //--- 2 Unsigned Long
//    s32   slLong[2];                            //--- 2 Signed Long
//    u16   uwWord[4];                            //--- 4 Unsigned Words
//    s16   swWord[4];                            //--- 4 Signed Words
//    u08   ubByte[8];                            //--- 8 Unsigned Bytes
//    s08   sbByte[8];                            //--- 8 Signed Bytes
//    u08*  ubPtr[2];                             //--- 2 General Purpose Pointers [byte]
//    void* vPntr[2];                             //--- 2 Void Type Pointers
//  };
//
//
//---------------------------------------------------------------------------------------------

//            TASK_QUEUE_SIZE   32                //--- UpTo 32 Tasks Max waiting in dispatcher
struct  Task  stTaskQueue[TASK_QUEUE_SIZE];
//            TIMER_QUEUE_SIZE  8                 //--- UpTo 8 Timers
struct  Task  stTimerQueue[TIMER_QUEUE_SIZE];

u16 volatile  uwTaskIptr;                         //--- Task Queue In Pointer
u16 volatile  uwTaskOptr;                         //--- Task Queue Out Pointer
u16 volatile  uwTaskCntr;                         //--- Task Queue Task Counter


//---------------------------------------------------------------------------------------------
//
//                 Real Time Operating System Task Schedueling Function
//                 ----------------------------------------------------
//
//      General Interrupts are disabled upon entry
//      If entry was through an interrupt then interrupts remain disabled else the General
//      Interrupt flag is re-enabled
//
//      Note: There is no default condition for a Task.  Make sure all fields are set
//      or Defined
//---------------------------------------------------------------------------------------------

u08 fnScheduleTask (struct Task stInTask)
{
  u08   ubFlag;
  u32   ulA;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  GID;                                            //--- Kill All Interrutps

  //--- Test (if Task Timer Set > 0), if so then schedule as a timer each value = 1 mSec
  if (stInTask.ulTimer != 0)
  {
    //--- This is a Timer Find First Empty Timer in Timer QUEUE
    for (ulA = 0; ulA < TIMER_QUEUE_SIZE; ulA++)
    {
      if (!(stTimerQueue[ulA].ulTimer))           //--- Test if timer is available
      {
        GID;
        stInTask.stPassData.uxTimeStamp = uxSysTick;  //--- Set Time Stamp when schedueled
        stTimerQueue[ulA] = stInTask;             //--- Save Task to TimerQueue
        ubFlag = 0;                               //--- Exit with success
      }
    }

    if (ulA >= TIMER_QUEUE_SIZE) ubFlag = -1;     //--- Error No Timers Available
  }
  else
  {
    //--- This is a regular Task not a Timer Task
    if (uwTaskCntr < (TASK_QUEUE_SIZE - 1))       //--- Is there Room in the QUEUE?
    {
      //--- Extract Task number and data to pass to Task from TaskFifo
      stInTask.stPassData.uxTimeStamp = uxSysTick;  //--- Set Time Stamp when sschedueled
      stInTask.ulTimer = 0;                       //--- Zero the timer value
      stTaskQueue[uwTaskIptr] = stInTask;         //--- Save Task to TaskQueue
      uwTaskIptr++;                               //--- Bumb the Input Pointer
      uwTaskIptr %= TASK_QUEUE_SIZE;              //--- Roll it over
      uwTaskCntr++;                               //--- Bump task counter +1
      ubFlag = 0;                                 //--- No Errors
    }
    else
    {
      ubFlag = -2;                                //--- Set Error No QUEUE Room
    }
  }

  //--- If Not thru interrupt then enable Interrupts on Exit
  if (!(NVIC_IABR0 || NVIC_IABR1 || NVIC_IABR2))
  {
    GIE;                                          //--- Enable On Exit
  }
  return ubFlag;
}


//---------------------------------------------------------------------------------------------
//                                     Task Dispatcher
//
//  Task Function Definition:
//  fnFunctionName (struct PassData stTaskData)
//
//---------------------------------------------------------------------------------------------
void  fnDispatcher (void)
{
  struct PassData stPassData;
  void  (*ptrTask)(struct PassData stPassData);

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  GID;                                            //--- Kill Interrupts on Entry

  #ifdef TESTHELP_FLAG
    SET_PA10;                                     //--- Dispatcher Test Pulse Hi
  #endif

  //--- Test if Task waiting in Dispatch FIFO  TaskCounter > 0
  if (uwTaskCntr > 0)
  {
    uwTaskCntr--;                                 //--- Bump counter -1

    //--- Extract Task address and data to pass to Task from TaskFifo
//    ptrTask = (void (*)(struct PassData))stTaskQueue[uwTaskOptr].ptrTask;
    ptrTask = (void (*)) stTaskQueue[uwTaskOptr].ptrTask;
    stPassData = stTaskQueue[uwTaskOptr].stPassData;   //--- Copy Data Structure
    uwTaskOptr++;                                 //--- Bump the Out Pointer
    uwTaskOptr %= TASK_QUEUE_SIZE;                //--- Roll the Out Pointer Over

    GIE;                                          //--- Enable Interrupts On Exit
    nop4;                                         //--- Wait for pending Interrupt
    (*ptrTask)(stPassData);                       //--- Call Task Function With Data
  }
  else
  {
    GIE;                                          //--- Enable Interrupts & Exit
  }

  //--- Interrupt Catch-Up Pause Period
  nop8;

  #ifdef TESTHELP_FLAG
    CLR_PA10;                                     //--- Dispatcher Test Pulse Lo
  #endif
}

//---------------------------------------------------------------------------------------------
//                            Purge a Task from the Task Dispatcher
//---------------------------------------------------------------------------------------------

void  fnPurgeTask (void (*ptrTask))
{
  u32   ulTp;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  GID;

  //--- Purge task from task dispatcher

  if (uwTaskCntr)
  {
    for (ulTp = 0; ulTp < TASK_QUEUE_SIZE; ulTp++)
    {
      if (stTaskQueue [ulTp].ptrTask == ptrTask)
      {
        stTaskQueue[ulTp].ptrTask = (void *)&fnNullTask;
      }
    }
  }

  //--- Test if any timers active for the task

  for (ulTp = 0; ulTp < TIMER_QUEUE_SIZE; ulTp++)
  {
    if (stTimerQueue[ulTp].ulTimer)                   //--- Test if timer active
    {
      if (stTimerQueue[ulTp].ptrTask == ptrTask)
      {
        stTimerQueue[ulTp].ulTimer = 0;
        stTimerQueue[ulTp].ptrTask = (void *)&fnNullTask;
      }
    }
  }

  GIE;
}

//---------------------------------------------------------------------------------------------
//                                  Null or Do Nothing Tasks
//---------------------------------------------------------------------------------------------

void  fnNullTask (struct PassData stPassData)
{
  GIE;                                            //--- Enable Interrupts
}

//---------------------------------------------------------------------------------------------
//    Reurn an empty Task Data Field
//---------------------------------------------------------------------------------------------

struct PassData fnEmptyData (void)
{
  struct PassData stEmptyData;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //--- Zero Task Data Structure
  stEmptyData.uxTimeStamp = (u64) 0;              //--- Return Empty Time Stamp
  stEmptyData.unTaskData.uxBig = (u64) 0;         //--- Return Empty Data Fields

  return stEmptyData;
}



//=============================================================================================
//   How the RTOS Functions Work
//=============================================================================================
//
//  This RTOS System is a powerful yet simplified Event Driven Operating System that operates
//  with very little system resource overhead.  It is composed of 3 main sections.
//
//  (1) The Task Scheduling and Dispatching section.
//      --------------------------------------------
//      This section takes requests for Tasks and places them in either a Task Queue or
//      into a Timer Queue. All Tasks, when schedueled, have a system Time Stamp Value
//      This time stamp allows for timing corrections should the Task require it.
//
//  (2) The Event Driven Interrupts
//      ---------------------------
//      These interrupts occur after a particular hardware or software event occurs.  The
//      interrupt services the hardware and either takes immediate action or the event is
//      converted to a Task and is schedueled for execution. The Task may be schedueled to
//      execute at a pre determined time delay if required.
//
//  (3) The uninterruptable PACER time and phase interrupt.
//      ---------------------------------------------------
//      This is the "HeartBeat" of the system and is known as "The Pacer" interrupt which
//      occurs at interval of 100 uSec or (10,000 times / second). Items that need to reoccur
//      at precise intervals are scheduled by the Pacer.  In addition the Pacer handles the
//      transmission of data via USART1 or USART2 and automatically adjusts for different
//      Baud Rates.
//
//  The Task Sheduling and Dispatching allowes for fast reaction to events with the ability to
//  process important data and calculations in the background.  An Event schedules a Task
//  and passes the data for that Task to a FIFO buffer.  When the current Task finishes its
//  operations it returns to the Dispatcher where the next Task is executed.
//  Very little time is spent in the Interrupt service routine. The Scheduling and Dispatching
//  process, thus making sure there are little or no conflicts between Interrupts and Events.
//
//  In the RTOS system there exists a set of 8 delayed action timers that allow for execution
//  of functions at an exact time in the future.  Each time the Pacer Interrupt is entered the
//  timers are decremented by 1.  When a timer reaches 0 the corrisponding function is
//  scheduled then executed. This prevents the OS from having to sit in a loop just testing
//  if it is time to do something.  The granularity of the Timers is 1 mSec.
//
//  A Task is defined as a pointer to a function location.  Along with the Task Address upto
//  8 bytes of task data may be passed.  The data may be of any allowable "C" type
//  (Numeric, String, Pointers, Etc.) which allows for flexible data and variable passage. In
//  addition each task contains a TimeStamp within the data field so analysis related to
//  time synchronization can be easily be accomplished.
//
//  Tasks may be recursive in nature giving them the ability to periodically reschedule
//  themselves with little or no operating system burden load.
//
//=============================================================================================

//=============================================================================================
//     Standardized comment blocks
//=============================================================================================

//|....|....|....*....|....|....*....|....|....^....|....|....*....|....|....*....|....|....|..

//=============================================================================================
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //-------------------------------------------------------------------------------------------
  //
  //-------------------------------------------------------------------------------------------

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //-----------------------------------------------------------------------------------------
    //
    //-----------------------------------------------------------------------------------------

      //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

      //---------------------------------------------------------------------------------------
      //
      //---------------------------------------------------------------------------------------

        //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
