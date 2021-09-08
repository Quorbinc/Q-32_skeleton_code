//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//                                 SYSTEM SYS_TICK Routine
//                                 PACER  Interrupt Driver
//
//                           Written By:  Sancar James Fredsti
//
//                                Created: 16 Dec 2019
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//       Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#include "projectdefs.h"

//=============================================================================================
//                     Pacer Interrupt Portion of Operating System
//=============================================================================================

u64   uxSysTick = 0;                            //--- Master Tick Timer 2^64 100uSec Counts
u16   uwPacerTick = 0;                          //--- Pacer Tick Short Time Keeping
u16   uwPacerPhase = 0;                         //--- Pacer Phase (10 phases)
u16   uwLEDcntr = 20;                           //--- Pacer LED Fade In/Out Counter
u16   uwLEDtime = 0;

u32   ulFastTimeCount[4];                       //--- Handy Down Counters

//--- For Testing Output a Hi on PA15 for the duration of the PACER Function
#define PacerTest                               //--- Allow Pacer Flag on PA15

//---------------------------------------------------------------------------------------------
//                   Pacer Interrupt Service Call By SYS_TICK_IRQ
//                   --------------------------------------------
//
//  Pacer interrupt occurs once every 100uS (10000 times / Second)  The tasks are divided
//  into 10 groups that occur once every millisecond.
//
//  Note: Pacer Routine Transmits 1 Character from TX Fifos at a Calculated Rate determined
//        By the BAUD rate of the USART
//
//---------------------------------------------------------------------------------------------
void fnSysTick (void)
{
  u08 ubFlag = 0;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //--- Set Test Pulse Hi   OUTPUT PA15
  //    Comment this out if PA15 used for something else
  #ifdef PacerTest
    SET_PA15;                                     //--- Pacer Test Pulse Lo
  #endif

  uxSysTick++;                                    //--- Advance Gross 64 Bit Timer

  //--- Increments of 100uSec Delay               //--- Externally readable Downcount Delays
  if(ulFastTimeCount[0]) ulFastTimeCount[0]--;
  if(ulFastTimeCount[1]) ulFastTimeCount[1]--;
  if(ulFastTimeCount[2]) ulFastTimeCount[2]--;
  if(ulFastTimeCount[3]) ulFastTimeCount[3]--;

  //===========================================================================================
  //    Phased Pacer Tasks 10 Phased Tasks Total Ctcle time = 1.000 mSec
  //===========================================================================================

  //--- Depending on Pacer Phase Determine Action
  switch (uwPacerPhase)
  {
    //-----------------------------------------------------------------------------------------
    //--- Process Timer (0 & 1)  at Pacer Phase-0
    //-----------------------------------------------------------------------------------------
    case 0x00:                                    //--- At this point update modulo phases
      //--- Test if The Timer at Location [0] == Active Timer
      if (stTimerQueue[0].ulTimer > 0)
      {
        //--- Decrement Timer
        stTimerQueue[0].ulTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTaskQueue[0].ulTimer)
        {
          ubFlag = fnScheduleTask (stTimerQueue[0]);
        }
      }

  //--- If test then show where Phase (0) is
  #ifdef PacerTest
      SET_PA00;
      nop8;
      CLR_PA00;
  #endif
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timer (2 & 3)  at Pacer Phase-1
    //-----------------------------------------------------------------------------------------
    case 0x01:
      //--- Test if The Timer at Location [1] == Active Timer
      if (stTimerQueue[1].ulTimer > 0)
      {
        //--- Decrement Timer
        stTimerQueue[1].ulTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTaskQueue[1].ulTimer)
        {
          ubFlag = fnScheduleTask (stTimerQueue[1]);
        }
      }
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timer (4 - 5)  at Pacer Phase-2
    //-----------------------------------------------------------------------------------------
    case 0x02:
      //--- Test if The Timer at Location [2] == Active Timer
      if (stTimerQueue[2].ulTimer > 0)
      {
        //--- Decrement Timer
        stTimerQueue[2].ulTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTaskQueue[2].ulTimer)
        {
          ubFlag = fnScheduleTask (stTimerQueue[2]);
        }
      }
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timer (6 - 7)  at Pacer Phase-3
    //-----------------------------------------------------------------------------------------
    case 0x03:
      //--- Test if The Timer at Location [3] == Active Timer
      if (stTimerQueue[3].ulTimer > 0)
      {
        //--- Decrement Timer
        stTimerQueue[3].ulTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTaskQueue[3].ulTimer)
        {
          ubFlag = fnScheduleTask (stTimerQueue[3]);
        }
      }
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timer (8 - 9)  at Pacer Phase-4
    //-----------------------------------------------------------------------------------------
    case 0x04:
      //--- Test if The Timer at Location [4] == Active Timer
      if (stTimerQueue[4].ulTimer > 0)
      {
        //--- Decrement Timer
        stTimerQueue[4].ulTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTaskQueue[4].ulTimer)
        {
          ubFlag = fnScheduleTask (stTimerQueue[4]);
        }
      }
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timers (10 & 11) + PACER LED Visual Bright and Dim & Update Motion
    //-----------------------------------------------------------------------------------------
    case 0x05:
      //--- Test if The Timer at Location [5] == Active Timer
      if (stTimerQueue[5].ulTimer > 0)
      {
        //--- Decrement Timer
        stTimerQueue[5].ulTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTaskQueue[5].ulTimer)
        {
          ubFlag = fnScheduleTask (stTimerQueue[5]);
        }
      }

      //---------------------------------------------------------------------------------------
      //    Every 25 mSec change LED PWM on the 17 mSec Count
      //---------------------------------------------------------------------------------------
      if ((uwPacerTick % 25) == 17)
      {
        if (ulSystemFlags & 0x80000000)           //--- Test Brightening / Dimming
        {
          uwLEDcntr--;                            //--- Decrement Counter
          if (uwLEDcntr < 2)
          {
            ulSystemFlags &= 0x7FFFFFFF;          //--- Clear Brightening Flag LED dims
          }
        }
        else
        {
          uwLEDcntr++;                            //--- Increment Counter
          if (uwLEDcntr > 24)
          {
            ulSystemFlags |= 0x80000000;          //--- Set Brightening Flag LED brightens
          }
        }

        uwLEDtime = uwLEDcntr;                    //--- Sets the amount of time LED is On/Off
      }

      //--- Turn LED On/Off variable time amounts
      if (uwLEDtime)                              //--- If Timer Active
      {
        uwLEDtime--;                              //--- Decrement LED On Timer

        //--- If Timer = 0 then turn LED Off (Set Hi)
        if (!uwLEDtime)
        {
          SET_PC15;                               //--- Turn LED Off!
        }
        else
        {
          CLR_PC15;                               //--- Turn LED On!
        }
      }
      break;

    //-----------------------------------------------------------------------------------------
    //    Process Timers (12 & 13) + PACER Phase 6 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x06:
      //--- Test if The Timer at Location [6] == Active Timer
      if (stTimerQueue[6].ulTimer > 0)
      {
        //--- Decrement Timer
        stTimerQueue[6].ulTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTaskQueue[6].ulTimer)
        {
          ubFlag = fnScheduleTask (stTimerQueue[6]);
        }
      }
      break;

    //-----------------------------------------------------------------------------------------
    //    Process Timers (14 & 15) + PACER Phase 7 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x07:
      //--- Test if The Timer at Location [7] == Active Timer
      if (stTimerQueue[7].ulTimer > 0)
      {
        //--- Decrement Timer
        stTimerQueue[7].ulTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTaskQueue[7].ulTimer)
        {
          ubFlag = fnScheduleTask (stTimerQueue[7]);
        }
      }
      break;

    //-----------------------------------------------------------------------------------------
    //    Process PACER Phase 8 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x08:
      nop8;            //--- Time Waster
      break;

    //-----------------------------------------------------------------------------------------
    //    Process PACER Phase 9 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x09:
      //--- Bump the Pacer Tick
      uwPacerTick++;                              //--- Bump 1ms Pacer Tick
      uwPacerTick %= 60000;                       //--- 60,000 Pacer Ticks = 1 Minuite
      break;

    //-----------------------------------------------------------------------------------------
    //    If you get here something is wrong
    //-----------------------------------------------------------------------------------------
    default:
      ulSystemFlags |= 0x10000000;                //--- Set the Systick Error Flag
      uwPacerPhase = 0;
      break;
  }

  //--- These Items are executed once every PACER / SysTick Pass
  //--- Bump and Modulo the Phase Counter
  uwPacerPhase++;
  uwPacerPhase %= 10;

  //--- If Xmit Service Timer Active then Bump & Test
  //    This Delay takes care of sending next Byte to UARTS at proper times
  //    Depending on the BaudRate for the UART Port
  //    This TX method can transmit at any BAUD rate up to 115200


  if (uwXmit_1_Count)                             //--- Is Xmit Timer Active?
  {
    uwXmit_1_Count--;                             //--- Yes so decrement Counter
    if (!uwXmit_1_Count)                          //--- Did we reach TX period time?
    {
      uwXmit_1_Count = uwXmit_1_Delay;            //--- Refresh the Period Count
      fnXmitSvc_1 ();                             //--- Call the Xmit Service Routine
    }
  }

  if (uwXmit_2_Count)                             //--- Is Xmit Timer Active?
  {
    uwXmit_2_Count--;                             //--- Yes so decrement Counter
    if (!uwXmit_2_Count)                          //--- Did we reach TX period time?
    {
      uwXmit_2_Count = uwXmit_2_Delay;            //--- Refresh the Period Count
      fnXmitSvc_2 ();                             //--- Call the Xmit Service Routine
    }
  }

  //--- Set Test Pulse Lo   OUTPUT PA15
  //    Comment this out if PA15 used for something else
  #ifdef PacerTest
    CLR_PA15;                                   //--- Pacer Test Pulse Lo
  #endif
}

//---------------------------------------------------------------------------------------------
//    Fast Timer Down Count Functions
//---------------------------------------------------------------------------------------------

//--- Read a fast timer down count
u32  fnReadFastCounter(u08 ubCntrNum)
{
  return ulFastTimeCount[ubCntrNum];
}

//--- Clear a fast timer down count
void fnClearFastCounter(u08 ubCntrNum)
{
  ulFastTimeCount[ubCntrNum] = 0;
}

//--- Setr a fast timer down count
void fnSetFastCounter(u08 ubCntrNum, u32 ulDownCount)
{
  ulFastTimeCount[ubCntrNum] = ulDownCount;
}

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
