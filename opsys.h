//=============================================================================================
//                                Fredsti Industries,  Ltd.
//                                -------------------------
//
//                         Real Time Operating System Core Header
//                         --------------------------------------
//
//                           Written By:  Sancar James Fredsti
//
//                                Created: 01 August 2007
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//                       Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#ifndef OPSYS_H
    #define OPSYS_H
    #define TASK_QUEUE_SIZE   32                    //--- UpTo 32 Tasks Max waiting in dispatcher
    #define TIMER_QUEUE_SIZE  10                    //--- Number of Pacer Timers available

    #define ERR_RTOS_SCHED_QUEUE_FULL   0xF001      //--- No Queue Slots Available
    #define ERR_RTOS_SCHED_NO_TIMER     0xF002      //--- No Timers Available

    //--- 24 Bytes / Task
    struct Task
    {
        u16     uwTimer;                              //--- Task Timer delay value (0 - 65KmSec)
        u16     uwFlags;                              //--- Task Extra Flags Pass Data
        void    (*ptrTask);                           //--- Address Pointer of Task
        union DFLWB16 unTaskData;                     //--- Generic (16 Byte) PassData Union
    };

    //--- Structure Returned by ALL Tasks
    struct TaskRet
    {
        u16 uwErrCode;          //--- Returned Error Code Value.  (0x0000 = No Error)
        u16 uwRetVal;           //--- Generic Return Value
    };

    //--- Global Work Task Definition
    extern    struct  Task  stWorkTask;

    //--- Task and Timer Queue Definitions
    extern    struct  Task  stTaskQueue[TASK_QUEUE_SIZE];
    extern    struct  Task  stTimerQueue[TIMER_QUEUE_SIZE];

    //--- Task Dispatcher Queue (FIFO) pointers & counters
    extern    u16 volatile  uwTaskIptr;
    extern    u16 volatile  uwTaskOptr;
    extern    u16 volatile  uwTaskCntr;

    //--- Define Empty Data Union.
    extern    union DFLWB16 unEmptyData;

    //--- Function Prototypes for Public Use
    u32   fnScheduleTask (struct Task stInTask);
    void  fnDispatcher (void);
    void  fnPurgeTask (void (*ptrTask));
    void  fnNullTask (union DFLWB16 unTaskData);
#endif
