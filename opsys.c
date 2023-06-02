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

  #define TESTHELP_FLAG

//---------------------------------------------------------------------------------------------
//  Task Definition
//---------------------------------------------------------------------------------------------
//
//  Task Function Definition:
//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  ALL Tasks MUST use this Function Structure Definition
//  (u16) fnTaskName (union DFLWB unTaskData)
//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//  //--- 16 Bytes / Task
//  struct Task
//  {
//    u16     uwTimer;                            //--- Task Timer delay value (0 - 65KmSec)
//    u16     uwFlags;                            //--- Task Extra Flags Pass Data
//    void    (*ptrTask);                         //--- Address Pointer To Task
//    union DFLWB unTaskData;                     //--- Generic (8 Byte) PassData Union
//  };
//
//  ubFlags     = Generic Status Information for Task Call
//  uwTimer     = Task Execution delay time in mSec (0 = no delay else execution delayed n mSec)
//  *ptrTask    = Memory address of schedueled Task
//  unTaskData  = Task Data Payload as an 8 byte union
//
//  A Task will return a 32 bit code showing the Task Error or Return Condition
//
//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  (u16) fnTaskName (union DFLWB unTaskData)
//  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//  32 Bit Returned Value from Task
//  struct TaskRet
//  {
//    u16 uwErrCode;          //--- Returned Error Code Value.  (0x0000 = No Error)
//    u16 uwRetVal;           //--- Generic
//  }
//
//
//---------------------------------------------------------------------------------------------
//  Task Data Union Definition
//
//  This union definition allows a multitude of different variable types to be passed to a Task
//  all within a single 8 Byte data load.
//---------------------------------------------------------------------------------------------
//
//  union DFLWB                                   //--- 8 Bytes Binary / Integer Storage
//  {
//    dbl   dfFlt;                                //--- 1 Double Precision Float
//    u64   uxLL;                                 //--- 1 Unsigned 64 Bit Long Long Integer
//    s64   sxLL;                                 //--- 1 Signed 64 Bit Long Long Integer
//    flt   sfFlt[2];                             //--- 2 Single Precision Floats
//    u32   ulLong[2];                            //--- 2 Unsigned Long
//    s32   slLong[2];                            //--- 2 Signed Long
//    u16   uwWord[4];                            //--- 4 Unsigned Words
//    s16   swWord[4];                            //--- 4 Signed Words
//    u08   ubByte[8];                            //--- 8 Unsigned Bytes
//    s08   sbByte[8];                            //--- 8 Signed Bytes
//    u08*  ubPtr[2];                             //--- 2 General Purpose Byte Pointers
//    void* vPntr[2];                             //--- 2 Void Type Pointers
//  };
//
//
//---------------------------------------------------------------------------------------------
//
//  Format for schedueling a Task:
//
//  To Schedule a Task the following Code Should be Used
//
//  1.  Create the Task Structure Locally or use the globally defined temporary Task Structure
//      struct Task stNewTask;
//
//  2.  Define the Task Properties
//      stNewTask.ubPriority = Value (0 to 15)        //--- Task Priority
//      stNewTask.ubFlags = Value (0 to 255)          //--- Random Signal Byte to Pass to Task
//      stNewTask.uwTimer = execution delay in mSec   //--- Deley Time
//      stNewTask.ulTime Stamp = System Time Stamp    //--- System Time at Schedueling
//      stNewTask.*ptrTask = Memory Address of Task   //--- Calls this address when Dispatched
//      stNewTask.unTaskData = 8 Bytes of union Data  //--- Data Load to Pass to Task
//
//
//  Schedueler Function Prototype
//  union LWB fnSchedule (struct Task stInTask)



//            TASK_QUEUE_SIZE   32                //--- UpTo 32 Tasks Max waiting in dispatcher
struct  Task  stTaskQueue[TASK_QUEUE_SIZE];

//            TIMER_QUEUE_SIZE  10                //--- UpTo 10 Timers phased 100 uSec apart
struct  Task  stTimerQueue[TIMER_QUEUE_SIZE];

#define EmptyData unEmptyData.uxBig = 0x0000000000000000;

u16 volatile  uwTaskIptr;                         //--- Task Queue In Pointer
u16 volatile  uwTaskOptr;                         //--- Task Queue Out Pointer
u16 volatile  uwTaskCntr;                         //--- Task Queue Task Counter

struct  Task  stWorkTask;                         //--- Generic Global Work Task

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
//      or Defined.
//
//      Errors Generated: 0=No Errors     -1 = No Timers Available    -2 = Task Queue Full
//
//      Error Union Construct = LWB
//      MSB value of Byte[3] = Error Code ( 0 = No Error, Otherwise Error in Schedueling
//---------------------------------------------------------------------------------------------

u32 fnScheduleTask (struct Task stInTask)
{
  u16   uwError = 0;                              //--- Schedule Return Value/Error
  u32   ulC;                                      //--- Generic Counter

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  GID;                                            //--- Kill All Interrutps

  STK_CTRL &= 0x00000005;                         //--- Keep SysTick Enabled - Ignore New Int

  // stInTask.ulTimeStamp = (u32)(uxSysTick & 0xFFFFFFFF);  //--- Get Schedule Time Stamp
  // ubIP = stInTask.ubPriority;                     //--- Grab the Incomming Priority Level

  //--- Test (if Task Timer Set > 0)
  //    If > 0 then schedule this as a Timer Task  with 1mSec Resoultion
  if (stInTask.uwTimer > 0)
  {
    //--- If this is a Timer Task, find the first empty timer location in Timer QUEUE
    for (ulC = 0; ulC < TIMER_QUEUE_SIZE; ulC++)
    {
      if (!(stTimerQueue[ulC].uwTimer))           //--- Test if timer type is requested
      {
        stTimerQueue[ulC] = stInTask;             //--- Save Task to TimerQueue
        uwError = NO_ERROR;                       //--- ErrorCode = success
      }
      else
      {
        uwError = ERR_RTOS_SCHED_NO_TIMER;        //--- Error for no timers available
        fnError (uwError);                        //--- Call the error handler
      }
    }
  }
  else
  {
    //--- Test if Task Queue is full
    if (uwTaskCntr < (TASK_QUEUE_SIZE - 1))       //--- Is there Room in the QUEUE?
    {
      //--- Place Task at current Queue In Pointer
      //--- Extract Task number and data to pass to Task from TaskFifo
      stInTask.uwTimer = 0;                       //--- Zero the timer value for safety
      stTaskQueue[uwTaskIptr] = stInTask;         //--- Save Task to TaskQueue
      uwTaskIptr++;                               //--- Bumb the Input Pointer
      uwTaskIptr %= TASK_QUEUE_SIZE;              //--- Roll it over
      uwTaskCntr++;                               //--- Bump task counter +1
      uwError = NO_ERROR;                         //--- Exit with success
    }
    else   //--- Task Queue is Full Error
    {
      uwError = ERR_RTOS_SCHED_QUEUE_FULL;        //--- Set Error No QUEUE Room
    }
  }

  //--- If Not thru interrupt then enable Interrupts on Exit
  if (!(NVIC_IABR0 || NVIC_IABR1 || NVIC_IABR2))
  {
    GIE;                                          //--- Enable On Exit
  }

  //--- Re Enable SYS_TICK upon exit / Test if SYS_TICK Occured while Schedueling
  if (STK_CTRL & 0x00010000)                      //--- Test if SysTick under flow occured
  {
    fnSysTick_IRQ();                              //--- Execute the SysTick function
                                                  //--- To makeup for the one we skipped
  }

  STK_CTRL |= 0x00000007;                         //--- Re Enable SysTick Interrupt
  return uwError;
}


//---------------------------------------------------------------------------------------------
//                                     Task Dispatcher
//
//  Task Function Definition:
//  fnFunctionName (struct PassData stTaskData)
//
//---------------------------------------------------------------------------------------------

u16   uwLTP;                  //--- FIFO Location of Last Task Executed
u16   uwNTP;                  //--- FIFO Location of Next Available Empty Task in FIFO

void  fnDispatcher (void)
{
  union DFLWB unTaskData;                         //--- Task Pass Data Union
  u16   (*ptrTask)(union DFLWB unTaskData);       //--- Task with data & returns Error Code
                                                  //    Includes Error Code a 1 Word Generic

  u32 ulTaskRet;                                  //--- Task Return Code

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  GID;                                            //--- Kill Interrupts on Entry

  //--- Test if Task waiting in Dispatch FIFO  TaskCounter > 0
  if (uwTaskCntr > 0)
  {
    uwTaskCntr--;                                 //--- Bump counter -1

    //--- Extract Task address and data to pass to Task from TaskFifo
    //    ptrTask = (void (*)(struct PassData))stTaskQueue[uwTaskOptr].ptrTask;

    ptrTask = (void (*)) stTaskQueue[uwTaskOptr].ptrTask;
    unTaskData = stTaskQueue[uwTaskOptr].unTaskData;   //--- Copy Data Structure
    uwTaskOptr++;                                 //--- Bump the Out Pointer
    uwTaskOptr %= TASK_QUEUE_SIZE;                //--- Roll the Out Pointer Over
    uwLTP = uwTaskOptr;                           //--- Save the FIFO Position for Next Task
    GIE;                                          //--- Enable Interrupts On befor call

    //--- Call the TASK and process any error return codes
    ulTaskRet = (u32)(*ptrTask)(unTaskData);      //--- Call Task With Data & Get Return Code

    //--- If return code is != to ZERO then process Task Error Return Code
    if (ulTaskRet)                                //--- If an error return code then process it
    {
      GIE;                                        //--- Enable General Interrupt Flag
      fnError (ulTaskRet);                        //--- Process Error
    }
  }
  else
  {
    GIE;                                          //--- Enable Interrupts & Exit
  }

  //--- Interrupt Catch-Up Pause Period, Helps Synchronize NVIC after Task Call
  nop8;
}


//---------------------------------------------------------------------------------------------
//                            Purge a Task from the Task Dispatcher & Timer Queues
//---------------------------------------------------------------------------------------------
void  fnPurgeTask (void (*ptrTask))
{
  u32   ulTp;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  GID;                                            //--- Kill interrupts whine doing this

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
    if (stTimerQueue[ulTp].uwTimer)               //--- Test if timer active
    {
      if (stTimerQueue[ulTp].ptrTask == ptrTask)
      {
        stTimerQueue[ulTp].uwTimer = 0;
        stTimerQueue[ulTp].ptrTask = (void *)&fnNullTask;
      }
    }
  }

  GIE;
}

//---------------------------------------------------------------------------------------------
//                                  Null or Do Nothing Task
//---------------------------------------------------------------------------------------------
void  fnNullTask (union DFLWB unNothing)
{
  GIE;                                            //--- Enable Interrupts on Exit
}

//---------------------------------------------------------------------------------------------
//    Define an empty Task Data Field
//---------------------------------------------------------------------------------------------

union DFLWB unEmptyData;

//=============================================================================================
//   How the RTOS Functions Work
//=============================================================================================
//
//  The RTOS centers around a Task Queue of executable code sections which are called a "Task"
//
//  This RTOS System is a powerful yet simplified event driven operating system. Operating
//  with very little system resource overhead.  It is composed of 4 main sections.
//
//  (1) The Task Definition:
//      --------------------
//      A Task is defined as a function with a predefined Data Input Construct and a predefined
//      Data Return Construct.
//
//      A Task has definiton is pointer to a function location.  Along with the function upto
//      8 bytes of task data may be passed.  The data may be of any allowable "C" type
//      (Numeric, String, Pointers, Etc.) which allows for flexible data and variable passage. In
//      addition each task contains a TimeStamp within the data field so analysis related to
//      time synchronization can be easily be accomplished.
//
//  (2) The Task Scheduling and Dispatching section:
//      --------------------------------------------
//      This section takes requests for Tasks and places them in either a Task Queue or
//      into a Timer Queue. All Tasks, when schedueled, have a system Time Stamp Value
//      This time stamp allows for timing corrections should the Task require it.
//
//  (3) The Event Driven Interrupts:
//      ----------------------------
//      These interrupts occur after a particular hardware or software event occurs.  The
//      interrupt services the hardware and either takes immediate action or the event is
//      converted to a Task and is schedueled for execution. The Task may be schedueled to
//      execute at a pre determined time delay if required.
//
//  (4) The uninterruptable PACER time and phase interrupt ("SysTick"):
//      ---------------------------------------------------------------
//      This is the "HeartBeat" of the system and is known as "The Pacer" interrupt which
//      occurs at interval of 100 uSec or (10,000 times / second). Items that need to occur
//      at precise intervals are scheduled by the Pacer.  In addition the Pacer handles the
//      transmission of data via USART1 or USART2 and automatically adjusts for different
//      Baud Rates.
//
//  Tasks may be recursive in nature giving them the ability to periodically reschedule
//  themselves with little or no operating system burden.
//
//  The Task Sheduling and Dispatching allowes for fast reaction to events with the ability to
//  process important data and calculations in the background.  An event schedules a Task
//  and passes the data for that Task to a FIFO buffer.  When the current Task finishes its
//  operations it returns to the Dispatcher where the next Task is fetched and executed.
//  For an RTOS system Very little time is spent in an Interrupt service routine. Events
//  typically acquire data from hardware stimulii and schedule a Task for action on the data
//  at the appropriate time thus making sure there are little or no conflicts between hardware
//  interrupts, events and the system thread operation.
//
//  In the RTOS system there exists a set of 10 delayed action timers that allow for execution
//  of functions at an exact time in the future (+/- 1mSec). Each time the Pacer Interrupt
//  is entered the timers are decremented by 1.  When a timer value reaches 0 the corrisponding
//  function is scheduled to be executed. This frees the system from loop polling and pausing
//  delays.
//
//=============================================================================================
//  Time Keeping within the Quorb RTOS:
//=============================================================================================
//
//  The SysTick timer is an exceptionally high priority function that cannot be interrupted
//  or disabled by normal program thread operation.  This is the "Pacer" that controls
//  the timing of the Quorb RTOS.  Each time the Pacer code is executed a 64 bit counter is
//  incremented.  This value allows for high accuracy time value that is accurate to within
//  +/- 100 uSec.  If the Quorb RTOS time keeping functions are enabled then the RTOS can
//  synchronize it self to an external time source for stratum 1 time accuracy to less than
//  1 mSec Time uncertanty. (See the Quorb Time keeping library)
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
