//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                            Functions used for software debugging
//                  -----------------------------------------------------
//
//    This code is for use on the STM32L432 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32FXXX Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//         Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#include "projectdefs.h"

//---------------------------------------------------------------------------------------------
//    Select Pulse Out GPIO Pins
//---------------------------------------------------------------------------------------------

vu32* Cptr;                                       //--- Clock Bit Pointer
u32 ulCsetMask;                                   //--- Clock Bit Mask General
u32 ulCclrMask;                                   //--- Clock Bit Mask General

vu32* Dptr;                                       //--- Data Bit Pointer
u32 ulDsetMask;                                   //--- Data Bit Mask General
u32 ulDclrMask;                                   //--- Data Bit Mask General

u08 ubSpoFlag = 0;                                //--- Flag that Pulse Bit Ports are Set
u08 ubPulseCntr;                                  //--- Number of Sequential Pulses to output

//--- Set up Pins to use for Pulse Data Outs
void  fnDefinePortPins (u08 ubClkPin, u08 ubDataPin)
{
  ubSpoFlag = 0xFF;

  //--- Define the Clock GPIO Port Address
  switch (ubClkPin & 0xF0)
  {
    case 0x00:
      Cptr = &GPIOA_BSRR;
      break;

    case 0x10:
      Cptr = &GPIOB_BSRR;
      break;

    case 0x20:
      Cptr = &GPIOC_BSRR;
      break;

    case 0x30:
      Cptr = &GPIOD_BSRR;
      break;

    case 0x40:
      Cptr = &GPIOE_BSRR;
      break;

    case 0x50:
      Cptr = &GPIOF_BSRR;
      break;

    case 0x60:
      Cptr = &GPIOG_BSRR;
      break;

    case 0x70:
      Cptr = &GPIOH_BSRR;
      break;

    case 0x80:
      Cptr = &GPIOI_BSRR;
      break;

    case 0x90:
      Cptr = &GPIOJ_BSRR;
      break;

    case 0xA0:
      Cptr = &GPIOK_BSRR;
      break;

    default:
      break;
  }

  //--- Define the Port Pin for Clock Out
  ulCsetMask = (0x00000001 << (ubClkPin & 0x0F));
  ulCclrMask = ~(0x00000001 << ((ubClkPin & 0x0F) + 16));

  //--- Define the Clock GPIO Port Address
  switch (ubDataPin & 0xF0)
  {
    case 0x00:
      Dptr = &GPIOA_BSRR;
      break;

    case 0x10:
      Dptr = &GPIOB_BSRR;
      break;

    case 0x20:
      Dptr = &GPIOC_BSRR;
      break;

    case 0x30:
      Dptr = &GPIOD_BSRR;
      break;

    case 0x40:
      Dptr = &GPIOE_BSRR;
      break;

    case 0x50:
      Dptr = &GPIOF_BSRR;
      break;

    case 0x60:
      Dptr = &GPIOG_BSRR;
      break;

    case 0x70:
      Dptr = &GPIOH_BSRR;
      break;

    case 0x80:
      Dptr = &GPIOI_BSRR;
      break;

    case 0x90:
      Dptr = &GPIOJ_BSRR;
      break;

    case 0xA0:
      Dptr = &GPIOK_BSRR;
      break;

    default:
      break;
  }

  //--- Define the Port Pin for Data Out
  ulDsetMask = (0x00000001 << (ubDataPin & 0x0F));
  ulDclrMask = ~(0x00000001 << ((ubDataPin & 0x0F) + 16));
}

//--- Functions to Set and Clear Pulse Out Pins
void  fnSetCpin (void)
{
  *Cptr |= ulCsetMask;
}

void  fnClrCpin (void)
{
  *Cptr &= ulCclrMask;
}

void  fnSetDpin (void)
{
  *Dptr |= ulDsetMask;
}

void  fnClrDpin (void)
{
  *Dptr &= ulDclrMask;
}

//--- Output A Pulse Byte
void  fnPulseByteOut (u08 ubPulseByte)
{
  u16 uwA;
  u08 ubB = 0x80;                                 //--- Set High Bit Mask

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  if (!ubSpoFlag) return;                         //--- If Pins NOT Defined Just Exit

  //--- Clear Data Pin
  fnClrDpin ();

  //--- Clear Clock Pin
  fnClrCpin ();

  for (uwA = 0; uwA < 8; uwA++)
  {
    if (ubPulseByte & ubB)
    {
      fnSetDpin ();
    }
    else
    {
      fnClrDpin ();
    }

    nop4;

    fnSetCpin ();                                 //--- Set Clock Hi

    nop4;

    fnClrCpin ();                                 //--- Set Clock Hi

    nop4;

    fnClrDpin ();                                 //--- Set Clock Hi

    ubB = ubB >> 1;                               //--- Rotate to Next Bit
  }

  nop24;
}

//--- Output a 16 Bit Word Value
void  fnPulseWordOut (u16 uwPulseWord)
{
  u16 uwA;
  u16 uwB = 0x8000;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  if (!ubSpoFlag) return;                         //--- If Pins NOT Defined Just Exit

  //--- Clear Data Pin
  fnClrDpin ();

  //--- Clear Clock Pin
  fnClrCpin ();


  for (uwA = 0; uwA < 16; uwA++)
  {
    if (uwPulseWord & uwB)
    {
      fnSetDpin ();
    }
    else
    {
      fnClrDpin ();
    }

    nop4;

    fnSetCpin ();                                 //--- Set Clock Hi

    nop4;

    fnClrCpin ();                                 //--- Set Clock Hi

    nop4;

    fnClrDpin ();                                 //--- Set Clock Hi

    uwB = uwB >> 1;                               //--- Rotate to Next Bit
  }

  nop24;
}

//--- Output a 32 Bit Long Value
void  fnPulseLongOut (u32 ulPulseLong)
{
  u16 uwA;
  u32 ulB = 0x80000000;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  if (!ubSpoFlag) return;                         //--- If Pins NOT Defined Just Exit

  //--- Clear Data Pin
  fnClrDpin ();

  //--- Clear Clock Pin
  fnClrCpin ();


  for (uwA = 0; uwA < 32; uwA++)
  {
    if (ulPulseLong & ulB)
    {
      fnSetDpin ();
    }
    else
    {
      fnClrDpin ();
    }

    nop4;

    fnSetCpin ();                                 //--- Set Clock Hi

    nop4;

    fnClrCpin ();                                 //--- Set Clock Hi

    nop4;

    fnClrDpin ();                                 //--- Set Clock Hi

    ulB = ulB >> 1;                               //--- Rotate to Next Bit
  }

  nop24;
}

//---------------------------------------------------------------------------------------------
//    Output a series of Pulses on Clock Pin
//---------------------------------------------------------------------------------------------
void  fnPulseOut (void)
{
  //--- Output a short pulse
  if (ubPulseCntr)
  {
    fnSetDpin ();
    nop8;                                    //--- Tiny Delay
    fnClrDpin ();
    ubPulseCntr--;                            //--- Down Count # of Pulses
    nop12;
  }
}

