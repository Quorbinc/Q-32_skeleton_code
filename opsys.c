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

struct  Task  stTaskQueue[TASK_QUEUE_SIZE];  //--- UpTo 32 Tasks Max waiting in dispatcher.  TASK_QUEUE_SIZE = 32

struct  Task  stTimerQueue[TIMER_QUEUE_SIZE];  //--- UpTo 10 Timers phased 100 uSec apart.  TIMER_QUEUE_SIZE = 10

#define EmptyData unEmptyData.uxBig = 0x0000000000000000;

u16 volatile  uwTaskIptr;                         //--- Task Queue In Pointer
u16 volatile  uwTaskOptr;                         //--- Task Queue Out Pointer
u16 volatile  uwTaskCntr;                         //--- Task Queue Task Counter

u32 volatile  ulBusyFlags;                        //--- Generic Peripherial Busy Flags

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

    //--- If Schedule Not thru interrupt then enable Interrupts on Exit
    if (!(NVIC_IABR0 || NVIC_IABR1 || NVIC_IABR2))
    {
        GIE;                                          //--- Enable On Exit
    }

    //--- Re Enable SYS_TICK upon exit / Test if SYS_TICK Occured while Schedueling
    if (STK_CTRL & 0x00010000)                      //--- Test if SysTick under flow occured
    {
        fnSysTick_IRQ();                              //--- Execute the SysTick function.  To makeup for the one we skipped
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
    union DFLWB16 unTaskData;                       //--- Task Pass Data Union
    u16   (*ptrTask)(union DFLWB16 unTaskData);     //--- Task with data & returns Error Code Includes Error Code a 1 Word Generic

    u32 ulTaskRet;                                  //--- Task Return Code

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
//                  Purge a Task from the Task Dispatcher & Timer Queues
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
void  fnNullTask (union DFLWB16 unNothing)
{
    GIE;                                            //--- Enable Interrupts on Exit
}

//---------------------------------------------------------------------------------------------
//    Define an empty Task Data Field
//---------------------------------------------------------------------------------------------

union DFLWB16 unEmptyData;
