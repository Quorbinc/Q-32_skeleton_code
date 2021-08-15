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
//
//  struct Task
//  {
//    void    (*ptrTask);                         //--- Pointer to Task
//    union  DFLWB unTaskData;                     //--- Generic Data Union
//  };
//
//  //--- 64 Bit Variable integer union
//  union DFLWB             //--- 8 Bytes Binary / Integer Storage
//  {
//    dbl   dfFlt;          //--- Double Precision Float
//    u64   uxBig;          //--- Unsigned 64 Bit Integer
//    s64   sxBig;          //--- Signed 64 Bit Integer
//    flt   sfFlt[2];       //--- 2 Single Precision Floats
//    u08*  ubPtr[2];       //--- 2 General Purpose Pointers (byte]   4 Bytes / Value
//    void* vPntr[2];       //--- 2 Void Type Pointers
//    u32   ulLong[2];      //--- 2 Unsigned Long
//    s32   slLong[2];      //--- 2 Signed Long
//    u16   uwWord[4];      //--- 4 Unsigned Words
//    s16   swWord[4];      //--- 4 Signed Words
//    u08   ubByte[8];      //--- 8 Unsigned Bytes
//    s08   sbByte[8];      //--- 8 Signed Bytes
//  };
//
//---------------------------------------------------------------------------------------------

struct  Task  stTaskFifo[TASK_FIFO_SIZE];
struct  Timer stTimers[NUMBER_OF_TIMERS];

u16 volatile  uwTaskIptr;                         //--- Task FIFO In Pointer
u16 volatile  uwTaskOptr;                         //--- Task FIFO Out Pointer
u16 volatile  uwTaskCntr;                         //--- Task FIFO Task Counter

//---------------------------------------------------------------------------------------------
//
//                 Real Time Operating System Task Schedueling Function
//                 ----------------------------------------------------
//
//      General Interrupts are disabled upon entry
//      If entry was through an interrupt then interrupts remain disabled else the General
//      Interrupt flag is re-enabled
//---------------------------------------------------------------------------------------------

u16 fnScheduleTask (struct Task stInTask)
{
  u16   uwFlag = TRUE;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  GID;                                            //--- Kill All Interrutps
  if (uwTaskCntr < (TASK_FIFO_SIZE-1))
  {
    //--- Extract Task Address and data to pass to Task from TaskFifo
    stTaskFifo[uwTaskIptr] = stInTask;
    uwTaskIptr++;                                 //--- Bumb the Input Pointer
    uwTaskIptr %= TASK_FIFO_SIZE;                 //--- Roll it over
    uwTaskCntr++;                                 //--- Bump task counter +1
    uwFlag = TRUE;
  }
  else
  {
    uwFlag = FALSE;
  }

  //--- If Not thru interrupt then enable Interrupts on Exit
  if (!(NVIC_IABR0 || NVIC_IABR1 || NVIC_IABR2))
  {
    GIE;                                          //--- Enable On Exit
  }
  return uwFlag;
}

//---------------------------------------------------------------------------------------------
//                                     Task Dispatcher
//---------------------------------------------------------------------------------------------

void  fnDispatchCall (void)
{
  union DFLWB unTaskData;
  void  (*ptrTask) (union DFLWB unTaskData);
  u16   uwRxData;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  GID;                                            //--- Kill Interrupts on Entry

  //--- Test if Task waiting in Dispatch FIFO
  if (uwTaskCntr > 0)
  {
    uwTaskCntr--;                                 //--- Bump counter -1

    //--- Extract Task address and data to pass to Task from TaskFifo
    ptrTask = (void (*)(union DFLWB))stTaskFifo[uwTaskOptr].ptrTask;
    unTaskData = stTaskFifo[uwTaskOptr].unTaskData;
    uwTaskOptr++;                                 //--- Bump the Out Pointer
    uwTaskOptr %= TASK_FIFO_SIZE;                 //--- Roll the Out Pointer Over

    GIE;                                          //--- Enable Interrupts On Exit
    (*ptrTask)(unTaskData);                       //--- Call Task Function With Data

  }
  else
  {
    GIE;                                          //--- Enable Interrupts & Exit
  }

  //--- Interrupt Catch-Up Pause Period
  nop12;
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
    for (ulTp = 0; ulTp < TASK_FIFO_SIZE; ulTp++)
    {
      if (stTaskFifo [ulTp].ptrTask == ptrTask)
      {
        stTaskFifo[ulTp].ptrTask = (void *)&fnNullTask;
      }
    }
  }

  //--- Test if any timers active for the task
  for (ulTp = 0; ulTp < NUMBER_OF_TIMERS; ulTp++)
  {
    if (stTimers[ulTp].ulTimer)                   //--- Test if timer active
    {
      if (stTimers [ulTp].ptrTask == ptrTask)
      {
        stTimers[ulTp].ulTimer = 0;
        stTimers[ulTp].ptrTask = (void *)&fnNullTask;
      }
    }
  }

  GIE;
}


//---------------------------------------------------------------------------------------------
//                                  Null or Do Nothing Tasks
//---------------------------------------------------------------------------------------------

//--- Tasks have variables

void  fnNullTask (union DFLWB unData)
{

}


//---------------------------------------------------------------------------------------------
//                               Set a Timer for Future Execution
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//  struct  Timer
//---------------------------------------------------------------------------------------------

u16 fnScheduleTimer (struct Timer stInTimer)
{
  u32   ulA;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  GID;

  for (ulA = 0; ulA < NUMBER_OF_TIMERS; ulA++)
  {
    if (!(stTimers[ulA].ulTimer))                 //--- Test if timer is available
    {
      GID;
      stTimers[ulA].ulTimer = stInTimer.ulTimer;
      stTimers[ulA].ptrTask = stInTimer.ptrTask;
      stTimers[ulA].unTaskData = stInTimer.unTaskData;
      GIE;
      return TRUE;                                //--- Exit Timer Loop
    }
  }

  GIE;
  return FALSE;
}


//=============================================================================================
//   How the RTOS Functions Work
//=============================================================================================
//
//  This RTOS System is a simplified Event Driven Operating System.  It is composed of 2 main
//  functions (1) The Task Scheduling and Dispatching section and (2) The Event Driven Inter
//  rupt structure.  One of these Events is the "Pacer" interrupt which occurs at intervals
//  of 100 uSec (10,000 times / second). Items that reoccur at precise intervals are scheduled
//  by the Pacer or the Pacer Interrupt directly stimulates the actions to occur.  It is not
//  advised to execute long functions within the Pacer Interrupt.
//
//  The Task Sheduling and Dispatching allowes for fast reaction to events with the ability to
//  process important data and calculations to occur in the background.  An Event schedules the
//  Task and passes the data to a FIFO buffer.  When the current Task finishes its operations
//  it returns to the Dispatcher where the next Task is executed.  Very little time is spent
//  in the Interrupt, Scheduling and Dispatching process, thus making sure there are little or
//  no conflicts between Interrupts and Events.
//
//  In the RTOS system there exists a set of delayed action timers that allow for execution
//  of functions at an exact time in the future.  Each time the Pacer Interrupt is entered the
//  timers are decremented by 1.  When a timer reaches 0 the corrisponding function is
//  scheduled then executed. This prevents the OS from having to sit in a loop just testing
//  if it is time to do something.
//
//  A Task is defined as a pointer to a function.  Along with the Task Address upto 8 bytes of
//  task data may be passed.  The data may be of any type (Numeric, String, Pointers, Etc.)
//  which allows for flexible data and variable passage.
//
//  There are 4 Delayed Task Timers which allow a task to be executed after a defined delay
//  The task can be delayed in 100 uSec increments.  After a time out the task is scheduled
//  for execution.  Latency depends on its position in the Task FIFO.
//
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
