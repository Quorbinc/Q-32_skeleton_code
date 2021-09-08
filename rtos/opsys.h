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
  #define TASK_QUEUE_SIZE   32      //--- UpTo 16 Tasks Max waiting in dispatcher
  #define TIMER_QUEUE_SIZE  8       //--- Number of Pacer Timers available

  //--- Structure has 16 Bytes of Data
  //    1 BIG value = Timestamp
  //    1 union of DFLWB for Task Data
  struct PassData
  {
    u64   uxTimeStamp;                            //--- Time Stamp when Schedueled
    union DFLWB unTaskData;                       //--- DFLWB Data union
  };

  //--- 24 Bytes / Task
  struct Task
  {
    u32     ulTimer;                              //--- Timer delay Value (0000 - 4G milliseconds)
    void   (*ptrTask);                            //--- Address Pointer to Task
    struct PassData stPassData;                   //--- Data to pass to function
  };


  //--- Task and Timer Queue Definitions
  extern    struct  Task  stTaskQueue[TASK_QUEUE_SIZE];
  extern    struct  Task  stTimerQueue[TIMER_QUEUE_SIZE];

  //--- Task Dispatcher Queue (FIFO) pointers & counters
  extern    u16 volatile  uwTaskIptr;
  extern    u16 volatile  uwTaskOptr;
  extern    u16 volatile  uwTaskCntr;

//---------------------------------------------------------------------------------------------
//  Task Definition
//---------------------------------------------------------------------------------------------
//
//  //--- 24 Bytes / Task
//  struct Task
//  {
//    u32     ulTimer;                            //--- Timer delay Value (0000 - 4G milliseconds)
//    void    (*ptrTask);                         //--- Address Pointer to Task
//    struct  PassData stPassData;                //--- Generic stPassData Structure
//      8 Bytes Time Stamp;                       //--- .uxTimeStamp
//      union DFLWB unTaskData;                   //--- Data Union unTaskData
//  };
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
//  structure PassData
//  {
//    u64   uxTimeStamp;                          //--- Time Stamp when Schedueled
//    union DFLWB unTaskData;                     //--- DFLWB Data union
//  }
//
//---------------------------------------------------------------------------------------------

  //--- Function Prototypes for Public Use
  u08   fnScheduleTask (struct Task stInTask);
  void  fnDispatcher (void);
  void  fnPurgeTask (void (*ptrTask));
  void  fnNullTask (struct PassData stPassData);
  struct PassData fnEmptyData (void);

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
