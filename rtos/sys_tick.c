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

u64   uxTick = 0;                               //--- Master Tick Timer 2^64 100uSec Counts
u16   uwPacerTick = 0;                          //--- Pacer Tick Short Time Keeping
u16   uwPacerPhase = 0;                         //--- Pacer Phase (10 phases)
u16   uwLEDcntr = 0;                            //--- Pacer LED Fade In/Out Counter
u16   uwLEDtime = 0;
u16   uwFastDelay;                              //--- Handy Delay Timer

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
void fnPacer (void)
{
  struct  Task  stWork;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //--- Set Test Pulse Hi   OUTPUT PA15
  //    Comment this out if PA15 used for something else
  #ifdef PacerTest
    SET_PA15;                                   //--- Pacer Test Pulse Lo
  #endif
  uxTick++;                                         //--- Advance Gross 64 Bit Timer 1 tick

  //--- Increments of 100uSec Delay                 //--- Externally readable Downcount Delay
  if(uwFastDelay) uwFastDelay--;

  //===========================================================================================
  //    Phased Pacer Tasks 10 Phased Tasks Total Ctcle time = 1.000 mSec
  //===========================================================================================

  //--- Depending on Pacer Phase Determine Action
  switch (uwPacerPhase % 10)
  {
    case 0x00:                                    //--- At this point update modulo phases
      uwPacerTick++;                              //--- Bump 1ms Pacer Tick
      uwPacerTick %= 60000;                       //--- 60,000 Pacer Ticks = 1 Minuite

      //--- If Test Routines are Active then output pulses
        fnPulseOut ();
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timer (0)  at Pacer Phase-1
    //-----------------------------------------------------------------------------------------
    case 0x01:
      if (stTimers[0].ulTimer)                    //--- If timer Active then decrement
      {
        stTimers[0].ulTimer--;                    //--- Decrement timer & test for 0
        if (!stTimers[0].ulTimer)                 //--- Did we get to (0000)?
        {
          stWork.ptrTask = stTimers[0].ptrTask;
          stWork.unTaskData = stTimers[0].unTaskData;
          fnScheduleTask (stWork);
        }
      }
      break;
    //-----------------------------------------------------------------------------------------
    //--- Process Timer (1)  at Pacer Phase-2
    //-----------------------------------------------------------------------------------------
    case 0x02:
      if (stTimers[1].ulTimer)                    //--- If timer Active then decrement
      {
        stTimers[1].ulTimer--;                    //--- Decrement timer & test for 0
        if (!stTimers[1].ulTimer)                 //--- Did we get to (0000)?
        {
          stWork.ptrTask = stTimers[1].ptrTask;
          stWork.unTaskData = stTimers[1].unTaskData;
          fnScheduleTask (stWork);
        }
      }
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timer (2)  at Pacer Phase-3
    //-----------------------------------------------------------------------------------------
    case 0x03:
      if (stTimers[2].ulTimer)                    //--- If timer Active then decrement
      {
        stTimers[2].ulTimer--;                    //--- Decrement timer & test for 0
        if (!stTimers[2].ulTimer)                 //--- Did we get to (0000)?
        {
          stWork.ptrTask = stTimers[2].ptrTask;
          stWork.unTaskData = stTimers[2].unTaskData;
          fnScheduleTask (stWork);
        }
      }
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process Timer (3)  at Pacer Phase-4
    //-----------------------------------------------------------------------------------------
    case 0x04:
      if (stTimers[3].ulTimer)                        //--- If timer Active then decrement
      {
        stTimers[3].ulTimer--;                        //--- Decrement timer & test for 0
        if (!stTimers[3].ulTimer)                     //--- Did we get to (0000)?
        {
          stWork.ptrTask = stTimers[3].ptrTask;
          stWork.unTaskData = stTimers[3].unTaskData;
          fnScheduleTask (stWork);
        }
      }
      break;

    //-----------------------------------------------------------------------------------------
    //--- Process PACER LED Visual Bright and Dim & Update Motion
    //-----------------------------------------------------------------------------------------
    case 0x05:
      //--- Every 25 mSec change LED PWM
      if (!(uwPacerTick % 25))
      {
        if (ulSystemFlags & 0x80000000)           //--- Test Brightening / Dimming
        {
          uwLEDcntr--;
          uwLEDtime = uwLEDcntr;
          if (uwLEDcntr < 2)
          {
            ulSystemFlags &= 0x7FFFFFFF;          //--- Clear Brightening Flag LED dims
          }
        }
        else
        {
          uwLEDcntr++;
          uwLEDtime = uwLEDcntr;
          if (uwLEDcntr > 24)
          {
            ulSystemFlags |= 0x80000000;          //--- Set Brightening Flag LED brightens
          }
        }
      }

      //--- Turn LED On/Off variable time amounts
      if (uwLEDtime)
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
      else
      {
        SET_PC15;                                //--- Turn LED Off!
      }
      break;

    //-----------------------------------------------------------------------------------------
    //    Process PACER Phase 6 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x06:
      break;

    //-----------------------------------------------------------------------------------------
    //    Process PACER Phase 7 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x07:
      break;

    //-----------------------------------------------------------------------------------------
    //    Process PACER Phase 8 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x08:
      break;

    //-----------------------------------------------------------------------------------------
    //    Process PACER Phase 9 Time Slot
    //-----------------------------------------------------------------------------------------
    case 0x09:
      break;

    //--- Error in state machine
    default:
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

  if (uwXmit_1_Count)                         //--- Is Xmit Timer Active?
  {
    uwXmit_1_Count--;                         //--- Yes so decrement Counter
    if (!uwXmit_1_Count)                      //--- Did we reach TX period time?
    {
      uwXmit_1_Count = uwXmit_1_Delay;        //--- Refresh the Period Count
      fnXmitSvc_1 ();                         //--- Call the Xmit Service Routine
    }
  }

  if (uwXmit_2_Count)                         //--- Is Xmit Timer Active?
  {
    uwXmit_2_Count--;                         //--- Yes so decrement Counter
    if (!uwXmit_2_Count)                      //--- Did we reach TX period time?
    {
      uwXmit_2_Count = uwXmit_2_Delay;        //--- Refresh the Period Count
      fnXmitSvc_2 ();                         //--- Call the Xmit Service Routine
    }
  }

  //--- Set Test Pulse Lo   OUTPUT PA15
  //    Comment this out if PA15 used for something else
  #ifdef PULSES
    fnPulseOut();
  #endif
  #ifdef PacerTest
    CLR_PA15;                                   //--- Pacer Test Pulse Lo
  #endif
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
