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

#include "projectdefs.h"                        //--- Master Project Definition File
#define TickRate 10000                          //--- Systick Count Rate in Ticks / Sec

//=============================================================================================
//                     Pacer Interrupt Portion of Operating System
//=============================================================================================

u64   uxSysTick = 0;                            //--- Master Tick Timer 2^64 100uSec Counts
u16   uwPacerTick = 0;                          //--- Pacer Tick Short Time Keeping
u16   uwPacerPhase = 0;                         //--- Pacer Phase (10 phases)
u16   uwLEDcntr = 20;                           //--- Pacer LED Fade In/Out Counter
u16   uwLEDtime = 0;

//--- Tx FIFO Check Delays
u16   uwTxDelay_1;
u16   uwTxDelay_2;

u32   ulFastTimeCount[4];                       //--- 4 Handy Down Counters

//--- For Testing Output a Hi on PA15 for the duration of the PACER Function

//---------------------------------------------------------------------------------------------
//    Initialize Systick Timer
//    ulPeriod = Tick Period in nSec Required
//    NOTE: STM32L4XX Processor Does Not Support AHB/8 Mode STK_CTRL Clock Source Bit
//          MUST Be Set to 1  (Bit #2 - 0x00000004)
//---------------------------------------------------------------------------------------------

void  fnInitSysTick (void)
{
  INIT_SYSTICK;


//  u32 ulCount = (SYSCLK / TickRate) - 1;        //--- Calculate SysTick Clock Down Count 7199

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

//  STK_CTRL = 0x00000004;                        //--- Zero Control Register Enable Clock Source
//  STK_LOAD = ulCount;                           //--- Set the SysTick Load Value
//  STK_VAL = ulCount - 1;                        //--- Preset Initial DownCount
//  STK_CTRL = 0x00000007;                        //--- Enable SysTick, Interrupt Use SysClock
}

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

//void fnSysTick (void)
void fnSysTick_IRQ(void)                        //--- IRQ_- 1
{
  u16 uwErrCode = 0;
  //    Task Structure if Necessary for Project Programmer
  //--- struct Task stTickTask;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //--- Set Test Pulse Hi   OUTPUT PB03
//  SET_PB03;                                     //--- Pacer Test Pulse Hi

  uxSysTick++;                                    //--- Advance the gross 64 bit Timer

  //--- Increments of 100uSec Delay               //--- Externally readable Downcount Delays
  if(ulFastTimeCount[0]) ulFastTimeCount[0]--;
  if(ulFastTimeCount[1]) ulFastTimeCount[1]--;
  if(ulFastTimeCount[2]) ulFastTimeCount[2]--;
  if(ulFastTimeCount[3]) ulFastTimeCount[3]--;

  //--- Bump Tx Delay Timers if Active
  if (uwTxDelay_1) uwTxDelay_1--;
  if (uwTxDelay_2) uwTxDelay_2--;

  //===========================================================================================
  //    Phased Pacer Tasks 10 Phased Tasks Total Ctcle time = 1.000 mSec
  //===========================================================================================

  //--- Depending on Pacer Phase Determine Action
  switch (uwPacerPhase)
  {
    //-----------------------------------------------------------------------------------------
    //--- Process Timer (0)  at Pacer Phase-0
    //-----------------------------------------------------------------------------------------
    case 0x00:                                    //--- At this point update modulo phases
      //--- Test if The Timer at Location [0] == Active Timer
      if (stTimerQueue[0].uwTimer != 0)
      {
        //--- Decrement Timer
        stTimerQueue[0].uwTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTimerQueue[0].uwTimer)
        {
          uwErrCode = fnScheduleTask (stTimerQueue[0]);
          //--- If Schedule Error the process error
          if (uwErrCode) fnError (uwErrCode);
        }
      }

      //--- Add additional actions to be performed during Phase_0 Here
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timer (1)  at Pacer Phase-1
    //-----------------------------------------------------------------------------------------
    case 0x01:
      //--- Test if The Timer at Location [1] == Active Timer
      if (stTimerQueue[1].uwTimer != 0)
      {
        //--- Decrement Timer
        stTimerQueue[1].uwTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTimerQueue[1].uwTimer)
        {
          uwErrCode = fnScheduleTask (stTimerQueue[1]);
          //--- If Schedule Error the process error
          if (uwErrCode) fnError (uwErrCode);
        }
      }

      //--- Add additional actions to be performed during Phase_1 Here
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timer (2)  at Pacer Phase-2
    //-----------------------------------------------------------------------------------------
    case 0x02:
      //--- Test if The Timer at Location [2] == Active Timer
      if (stTimerQueue[2].uwTimer != 0)
      {
        //--- Decrement Timer
        stTimerQueue[2].uwTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTimerQueue[2].uwTimer)
        {
          uwErrCode = fnScheduleTask (stTimerQueue[2]);
          //--- If Schedule Error the process error
          if (uwErrCode) fnError (uwErrCode);
        }
      }

      //--- Add additional actions to be performed during Phase_2 Here
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timer (3)  at Pacer Phase-3
    //-----------------------------------------------------------------------------------------
    case 0x03:
      //--- Test if The Timer at Location [3] == Active Timer
      if (stTimerQueue[3].uwTimer != 0)
      {
        //--- Decrement Timer
        stTimerQueue[3].uwTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTimerQueue[3].uwTimer)
        {
          uwErrCode = fnScheduleTask (stTimerQueue[3]);
          //--- If Schedule Error the process error
          if (uwErrCode) fnError (uwErrCode);
        }
      }

      //--- Add additional actions to be performed during Phase_3 Here
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timer (4)  at Pacer Phase-4
    //-----------------------------------------------------------------------------------------
    case 0x04:
      //--- Test if The Timer at Location [4] == Active Timer
      if (stTimerQueue[4].uwTimer != 0)
      {
        //--- Decrement Timer
        stTimerQueue[4].uwTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTimerQueue[4].uwTimer)
        {
          uwErrCode = fnScheduleTask (stTimerQueue[4]);
          //--- If Schedule Error the process error
          if (uwErrCode) fnError (uwErrCode);
        }
      }

      //--- Add additional actions to be performed during Phase_4 Here
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timers (5) + PACER LED Visual Bright and Dim & Update Motion
    //-----------------------------------------------------------------------------------------
    case 0x05:
      //--- Test if The Timer at Location [5] == Active Timer
      if (stTimerQueue[5].uwTimer != 0)
      {
        //--- Decrement Timer
        stTimerQueue[5].uwTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTimerQueue[5].uwTimer)
        {
          uwErrCode = fnScheduleTask (stTimerQueue[5]);
          //--- If Schedule Error the process error
          if (uwErrCode) fnError (uwErrCode);
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
          if (uwLEDcntr > 49)
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

      //--- Add additional actions to be performed during Phase_5 Here
      break;

    //-----------------------------------------------------------------------------------------
    //    Process Timer (6) + PACER Phase 6 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x06:
      //--- Test if The Timer at Location [6] == Active Timer
      if (stTimerQueue[6].uwTimer != 0)
      {
        //--- Decrement Timer
        stTimerQueue[6].uwTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTimerQueue[6].uwTimer)
        {
          uwErrCode = fnScheduleTask (stTimerQueue[6]);
          //--- If Schedule Error the process error
          if (uwErrCode) fnError (uwErrCode);
        }
      }

      //--- Add additional actions to be performed during Phase_6 Here
      break;

    //-----------------------------------------------------------------------------------------
    //    Process Timers (7) + PACER Phase 7 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x07:
      //--- Test if The Timer at Location [7] == Active Timer
      if (stTimerQueue[7].uwTimer != 0)
      {
        //--- Decrement Timer
        stTimerQueue[7].uwTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTimerQueue[7].uwTimer)
        {
          uwErrCode = fnScheduleTask (stTimerQueue[7]);
          //--- If Schedule Error the process error
          if (uwErrCode) fnError (uwErrCode);
        }
      }

      //--- Add additional actions to be performed during Phase_7 Here
      break;

    //-----------------------------------------------------------------------------------------
    //    Process Timers (8) + PACER Phase 8 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x08:
      //--- Test if The Timer at Location [8] == Active Timer
      if (stTimerQueue[8].uwTimer != 0)
      {
        //--- Decrement Timer
        stTimerQueue[8].uwTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTimerQueue[8].uwTimer)
        {
          uwErrCode = fnScheduleTask (stTimerQueue[8]);
          //--- If Schedule Error the process error
          if (uwErrCode) fnError (uwErrCode);
        }
      }

      //--- Add additional actions to be performed during Phase_8 Here
      break;

    //-----------------------------------------------------------------------------------------
    //    Process Timers (9) + PACER Phase 9 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x09:
      //--- Test if The Timer at Location [9] == Active Timer
      if (stTimerQueue[9].uwTimer != 0)
      {
        //--- Decrement Timer
        stTimerQueue[9].uwTimer--;

        //--- If Timer now == 0 then treat it as a regular task by changing Task Flags
        if (!stTimerQueue[9].uwTimer)
        {
          uwErrCode = fnScheduleTask (stTimerQueue[9]);
          //--- If Schedule Error the process error
          if (uwErrCode) fnError (uwErrCode);
        }
      }

      //--- Bump the Pacer Tick
      uwPacerTick++;                              //--- Bump 1ms Pacer Tick
      uwPacerTick %= 60000;                       //--- 60,000 Pacer Ticks = 1 Minuite

      //--- Add additional actions to be performed during Phase_9 Here
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

  #ifdef USART1_FLAG

    if (uwXmit_1_Count)                             //--- Is Xmit Timer Active?
    {
      uwXmit_1_Count--;                             //--- Yes so decrement Counter
      if (!uwXmit_1_Count)                          //--- Did we reach TX period time?
      {
        uwXmit_1_Count = XMIT_1_DELAY;              //--- Refresh the Period Count
        fnXmitSvc_1 ();                             //--- Call the Xmit Service Routine
      }
    }
  #endif

  #ifdef USART2_FLAG
    if (uwXmit_2_Count)                             //--- Is Xmit Timer Active?
    {
      uwXmit_2_Count--;                             //--- Yes so decrement Counter
      if (!uwXmit_2_Count)                          //--- Did we reach TX period time?
      {
        uwXmit_2_Count = XMIT_2_DELAY;              //--- Refresh the Period Count
        fnXmitSvc_2 ();                             //--- Call the Xmit Service Routine
      }
    }
  #endif

  //--- Set Test Pulse Lo   OUTPUT PA03
//  CLR_PB03;                                    //--- Pacer Test Pulse Lo
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

//--- Set a fast timer down count
void fnSetFastCounter(u08 ubCntrNum, u32 ulDownCount)
{
  ulFastTimeCount[ubCntrNum] = ulDownCount;
}

//#############################################################################################
//      General Section Headers
//#############################################################################################

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
