//===========================================================================================//
//                                Fredsti Industries,  Ltd.                                  //
//                                -------------------------                                  //
//                                                                                           //
//                         Real Time Operating System Core Header                            //
//                         --------------------------------------                            //
//                                                                                           //
//                           Written By:  Sancar James Fredsti                               //
//                                                                                           //
//                                Created: 01 August 2007                                    //
//                                                                                           //
//===========================================================================================//

//------------------------------------------------------------------------------------------//
//                       Program Defines and RAM Storage Definitions                        //
//------------------------------------------------------------------------------------------//

#ifndef OPSYS_H
  #define OPSYS_H
  #define TASK_FIFO_SIZE   64                     //--- 64 Tasks Max waiting in dispatcher
  #define NUMBER_OF_TIMERS  4                     //--- Number of Pacer Timers

  //--- Task Dispatcher Data Structure ---//
  //
  //  structure
  //  {
  //    Address of Task Function
  //
  //    union   DFLWB          //--- 16 Bytes of Storage
  //    {
  //        u32   ulLong;
  //        flt   sfFloat;
  //        u16   uwWord[2];
  //        u08   ubByte[4];
  //    };
  //  }

  //--- 46 Bytes / Task
  struct Task
  {
    u08     ubPriority;                           //--- Task Priority
    u08     ubFlags;                              //--- Any Passable Flags
    u32     ulTimer;                              //--- Timer delay Value (0000 - 4G milliseconds)
    u64     uxTimeStamp;                          //--- Time Stamp when Scheduled
    void    (*ptrTask);                           //--- Address Pointer to Task
    union   DFLWB unTaskData;                     //--- Generic Data Union DFLWB32 8 Byte
  };

  //--- 24 Bytes / Timer Task
  struct Timer
  {
    u32     ulTimer;
    void    (*ptrTask);                           //--- Pointer to Task
    union   DFLWB unTaskData;                     //--- Generic Data Union
  };

  //--- RAM Definitions

  extern    struct  Task  stTaskFifo[TASK_FIFO_SIZE];
  extern    struct  Timer stTimers[NUMBER_OF_TIMERS];

  extern    u16 volatile  uwTaskIptr;
  extern    u16 volatile  uwTaskOptr;
  extern    u16 volatile  uwTaskCntr;

  //--- Function Prototypes for Public Use
  u16   fnScheduleTask (struct Task stInTask);
  void  fnDispatchCall (void);
  u16   fnScheduleTimer (struct Timer stInTimer);

  void  fnPurgeTask (void (*ptrTask));
  void  fnNullTask (union DFLWB unData);
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
