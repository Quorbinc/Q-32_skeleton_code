//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                                 USART #2 Communications
//
//                           Written By:  Sancar James Fredsti
//
//                                Created: 28 January 2023
//
//=============================================================================================

//------  Revision History
//        REV 1.0 Release for production
//

#include "projectdefs.h"

//---------------------------------------------------------------------------------------------
//                         USART Control RAM & ROM definitions
//---------------------------------------------------------------------------------------------

#ifdef USART1_USED
  //--- Generic Text and String Allotments
  u08   ubU2Txt[1024];                            //--- Generic Message Constructor String
  u08   ubU2Str[128];                             //--- Generic Sub String Constructor

  //--- USART Channel #2 Definitions
  u16   uwUSART2TxCntr;                           //--- Tx Chr Cntr
  u16   uwUSART2TxIptr;                           //--- Tx In Pointer
  u16   uwUSART2TxOptr;                           //--- Tx Out Pointer
  u08   ubUSART2TxFIFO[USART2_TX_SIZE];           //--- Tx Character FIFO

  u16   uwUSART2RxCntr;                           //--- Rx Chr Cntr
  u16   uwUSART2RxIptr;                           //--- Rx In Pointer
  u16   uwUSART2RxOptr;                           //--- Rx Out Pointer
  u08   ubUSART2RxFIFO[USART2_RX_SIZE];           //--- Rx Character FIFO

  u16   uwRxState2;                               //--- Rx State Machine Current State
  u08   ubRxLRC2;                                 //--- Current LRC Calculation Value
  u16   uwErrCntr2;                               //--- Number of errors encountered

  u16   uwXmit_2_Count;                           //--- Character Spacing Delay 100uSec
  u16   uwXmit_2_Delay;                           //--- Character Spacing Delay 100uSec

  //--- Define USART Set-Up
  #define USART2_PARITY     0                     //--- Typically no Parity
  #define USART2_LEN        8                     //--- Typically 8 Bits Data Len
  #define USART2_BAUD       115200                //--- Typically 115200 Baudrate

  //-------------------------------------------------------------------------------------------
  //                    Initialize USART2 for Transmit and receive @ 115200
  //-------------------------------------------------------------------------------------------
  void  fnInitUSART2 (u32 ulBaud)                   //--- Initialize USART2 Communications
  {
    uwUSART2TxCntr = 0;                             //--- Reset the FIFO's
    uwUSART2TxIptr = 0;
    uwUSART2TxOptr = 0;

    uwUSART2RxCntr = 0;
    uwUSART2RxIptr = 0;
    uwUSART2RxOptr = 0;

    USART2_CR1 = 0x0000;                            //--- Kill the UART
    USART2_CR2 = 0x0000;
    USART2_CR3 = 0x0000;

    fnClrIntPend (USART2_IRQn);                     //--- Clear ANY interrupt

    //--- Calculate Baud Rate
    //    NOTE: BAUD rates lower than 1000 are not possible with this USART
    //    OverSampling by 16 used  Base Clock = System Clock = 72 MHz

    USART2_BRR = SYSCLK / ulBaud;                   //--- Set Baud Rate to integer part

    USART2_CR3 = 0x0000;                            //--- All Synchronous Stuff Off
    USART2_CR2 = 0x0000;

    //--- Modify this depending on USART Set_Up Parameters
    USART2_CR1 = 0x202C;                            //--- N81, Rx Int, Enable

    nop4;                                           //--- Waste a little time

    fnClrIntPend (USART2_IRQn);                     //--- Clear ANY interrupt
    fnEnaInt (USART2_IRQn);                         //--- Enable the interrupt

    //--- Calculate the PACER Ticks required between BYTE Transmissions
    //    10000 / (ulBaud / 10)
    uwXmit_2_Delay = (u16) (SYS_TICK_FREQ / (ulBaud / 10));
    uwXmit_2_Count = uwXmit_2_Delay;                //--- Reset the Count

    USART2_DR = ZERO;                               //--- Send a NULL Character
  }

  //-------------------------------------------------------------------------------------------
  //  Function Name  : USART_2 Rx Interrupt Handler //--- 38 - USART2 General Interrupt
  //-------------------------------------------------------------------------------------------
  void  fnUSART2_IRQ(void)
  {
    u08 ubRxData;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    GID;                                            //--- Kill Interrupts
    fnClrIntPend (USART2_IRQn);                     //--- Clear the interrupt

    if (USART2_SR & 0x0008)                         //--- Is overrun error triggered?
    {
      ubRxData = (u08)USART2_DR;                    //--- Read in the data byte from USART
      GIE;                                          //--- Enable Interrupts
      return;                                       //--- Get out of here
    }

    ubRxData = (u08)USART2_DR;                      //--- Read in the data byte from USART

    //--- Copy Rx Data to Rx FIFO
    if (uwUSART2RxCntr < (USART2_RX_SIZE - 2))
    {
      ubUSART2RxFIFO[uwUSART1RxIptr] = ubRxData;
      uwUSART2RxCntr++;                             //--- Bump the RX Counter
      uwUSART2RxIptr++;                             //--- Bump the In Pointer
      uwUSART2RxIptr %= USART2_RX_SIZE;             //--- Roll Over the FIFO
    }

    ubRxData = (u08)USART2_DR;                      //--- Read in the data byte from USART
    GIE;                                            //--- Enable Interrupts
  }


  //-------------------------------------------------------------------------------------------
  //               Check for and Return Data for USART Rx FIFO (Polled USART RX)
  //-------------------------------------------------------------------------------------------
  u16   fnGetNextUSART2 (void)
  {
    u16 uwRxData = 0;                               //--- Zero Data on Entry

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    GID;                                            //--- Kill Interrupts

    if (uwUSART2RxCntr)                             //--- Get FIFO Counter
    {
      //--- Extract the Data Byte
      uwRxData = (u16) ubUSART2RxFIFO[uwUSART1RxOptr];
      uwRxData |= 0x8000;                           //--- Set the valid data flag in Hi Byte
      uwUSART2RxCntr --;                            //--- Bump the counter
      uwUSART2RxOptr ++;                            //--- Bump the input pointer
      uwUSART2RxOptr %= USART2_RX_SIZE;             //--- Modulo Count Rx FIFO Size
    }
    else
    {
      uwRxData = 0x0000;                            //--- No Data Available
    }

    GIE;
    return uwRxData;                                //--- Return the data
  }

  //-------------------------------------------------------------------------------------------
  //                       Extract and Transmit 1 Byte from TX FIFO
  //                       ----------------------------------------
  //                       This function is called once every 100uS
  //-------------------------------------------------------------------------------------------
  void  fnXmitSvc_2 (void)
  {
    //--- Service USART #1 Transmit
    if (uwUSART2TxCntr > 0)                         //--- Test if Character Waiting
    {
      GID;                                          //--- Kill All Interrupts
      USART2_DR = ubUSART2TxFIFO[uwUSART2TxOptr];   //--- Xmit the data
      uwUSART2TxCntr--;                             //--- Bump the Counter -1
      uwUSART2TxOptr++;                             //--- Bump pointer
      uwUSART2TxOptr %= USART2_TX_SIZE;             //--- Rollover at 8192 Characters
      GIE;                                          //--- Restore All Interrupts
    }
  }

  //-------------------------------------------------------------------------------------------
  //                     Send a single Byte or character to TX FIFO
  //-------------------------------------------------------------------------------------------
  void  fnByteToFIFO_2 (u08 ubChar)
  {
    //--- Place Character in FIFO
    if (uwUSART2TxCntr < (USART2_TX_SIZE - 2))
    {
      GID;                                          //--- Kill All Interrupts
      ubUSART2TxFIFO[uwUSART2TxIptr] = ubChar;      //--- Put Char in FIFO
      uwUSART2TxIptr++;                             //--- Bump pointer
      uwUSART2TxIptr %= USART2_TX_SIZE;             //--- Rollover at 8192 Characters
      uwUSART2TxCntr++;                             //--- Bump the Counter
      GIE;                                          //--- Restore All Interrupts
    };
  }

  //-------------------------------------------------------------------------------------------
  //                     Output ASCII String to USART_2 Tx FIFO
  //-------------------------------------------------------------------------------------------

  void fnStringOut_2 (u08 ubOut[])
  {
    u16 uwSlen;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    uwSlen = strlen (ubOut);                      //--- Obtain Standard String Length
    fnArrayOut_2 (ubOut, uwSlen);                 //--- Output String Type Variable
  }

  //-------------------------------------------------------------------------------------------
  //                     Export an Array of Bytes to USART_2 Tx FIFO
  //-------------------------------------------------------------------------------------------
  void fnArrayOut_2 (u08 ubOut[], u16 uwArraySize)
  {
    u16 uwPtr;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- Kill Interrupts while testing
    GID;

    //--- Test if this message is smaller than remaining FIFO size
    if ((uwUSART2TxCntr + uwArraySize) < (USART2_TX_SIZE - 2))
    {
      for (uwPtr = 0; uwPtr < uwArraySize; uwPtr++)
      {
        fnByteToFIFO_2 (ubOut[uwPtr]);
      }
    }
    else
    {
           //--- To be added by user
    }
  }

// #endif

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
