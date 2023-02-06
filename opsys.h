//=============================================================================================
//                                Fredsti Industries,  Ltd.
//                                -------------------------
//
//                         Real Time Operating System Core Header
//                         --------------------------------------
//
//                           Written By:  Sancar James Fredsti
//                                                                                           //
//                                Created: 01 August 2007                                    //
//                                                                                           //
//===========================================================================================//

//---------------------------------------------------------------------------------------------
//                       Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#ifndef OPSYS_H
  #define OPSYS_H
  #define TASK_QUEUE_SIZE   16                    //--- UpTo 16 Tasks Max waiting in dispatcher
  #define TIMER_QUEUE_SIZE  10                    //--- Number of Pacer Timers available

  #define ERR_RTOS_SCHED_QUEUE_FULL   0xF001      //--- No Queue Slots Available
  #define ERR_RTOS_SCHED_NO_TIMER     0xF002      //--- No Timers Available

  //--- Structure has 8 Bytes of Data
  //    1 u32 length Timestamp
  //    1 union of 20 Byte DFLWB for Task Data
//  union DFLWB unPassData;                        //--- DFLWB Data union 8 Bytes

  //--- 16 Bytes / Task
  struct Task
  {
    u16     uwTimer;                            //--- Task Timer delay value (0 - 65KmSec)
    u16     uwFlags;                            //--- Task Extra Flags Pass Data
    void    (*ptrTask);                         //--- Address Pointer of Task
    union DFLWB unTaskData;                     //--- Generic (8 Byte) PassData Union
  };

  //--- Structure for Task Return
  struct TaskRet
  {
    u16         uwErrorCode;                    //--- Called Task Return Error Code
    union LWB   unRetValue;                     //--- Generic LWB union return values
  };

  //--- Work Task Definition
  extern    struct  Task  stWorkTask;

  //--- Task and Timer Queue Definitions
  extern    struct  Task  stTaskQueue[TASK_QUEUE_SIZE];
  extern    struct  Task  stTimerQueue[TIMER_QUEUE_SIZE];

  //--- Task Dispatcher Queue (FIFO) pointers & counters
  extern    u16 volatile  uwTaskIptr;
  extern    u16 volatile  uwTaskOptr;
  extern    u16 volatile  uwTaskCntr;

  //--- Define Empty Data Union.
  extern    union DFLWB unEmptyData;

  //-------------------------------------------------------------------------------------------
  //  Task Definition
  //-------------------------------------------------------------------------------------------
  //
  //  //--- 16 Bytes / Task
  //  struct Task
  //  {
  //    u16     uwTimer;                            //--- Task Timer delay value (0 - 4G mSec)
  //    u16     uwFlags;                            //--- Temporary Flags to Pass
  //    void    (*ptrTask);                         //--- Address Pointer of Task
  //    union DFLWB unTaskData;                     //--- Generic unDFLB Data Union
  //  };
  //
  //  Task Function Definition:
  //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //  ALL Tasks MUST use this Function Definition
  //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //
  //  (u08) ubRetCode tkTaskName (union DFLWB unTaskData)
  //
  //-------------------------------------------------------------------------------------------
  //  Task Data Union Definition
  //-------------------------------------------------------------------------------------------
  //
  //  union DFLWB                                   //--- 8 Bytes Binary / Integer Storage
  //  {
  //    dbl   dfFlt;                                //--- 1 Double Precision Float
  //    u64   uxLL;                                 //--- 1 Unsigned 64 Bit Long Long Integer
  //    s64   sxLL;                                 //--- 1 Signed 64 Bit Long Long Integer
  //    u08*  ubPtr[2];                             //--- 2 General Purpose Byte Pointers
  //    void* vPntr[2];                             //--- 2 Void Type Pointers
  //    flt   sfFlt[2];                             //--- 2 Single Precision Floats
  //    u32   ulLong[2];                            //--- 2 Unsigned Long
  //    s32   slLong[2];                            //--- 2 Signed Long
  //    u16   uwWord[4];                            //--- 4 Unsigned Words (16 Bit)
  //    s16   swWord[4];                            //--- 4 Signed Words (16 Bit)
  //    u08   ubByte[8];                            //--- 8 Unsigned Bytes
  //    s08   sbByte[8];                            //--- 8 Signed Bytes
  //  };
  //
  //
  //-------------------------------------------------------------------------------------------

  //--- Function used to schedule a new Task
  u16   fnScheduleTask (struct Task stInTask);

  //--- Function to fetch the next available Task from the Task Queue
  void  fnDispatcher (void);

  //--- Function to Purge a Task waiting in the Queue
  void  fnPurgeTask (void (*ptrTask));

  //--- Do Nothing Task
  void  tkNullTask (union DFLWB unTaskData);

#endif

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
