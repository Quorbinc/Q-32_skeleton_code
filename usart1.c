//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                                 USART #1 Communications
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
  u08   ubU1Txt[1024];                            //--- Generic Message Constructor String
  u08   ubU1Str[128];                             //--- Sub Constructor String

  //--- USART Channel #1 Definitions
  u16   uwUSART1TxCntr;                           //--- Tx Chr Cntr
  u16   uwUSART1TxIptr;                           //--- Tx In Pointer
  u16   uwUSART1TxOptr;                           //--- Tx Out Pointer
  u08   ubUSART1TxFIFO[USART1_TX_SIZE];           //--- Tx Character FIFO

  u16   uwUSART1RxCntr;                           //--- Rx Chr Cntr
  u16   uwUSART1RxIptr;                           //--- Rx In Pointer
  u16   uwUSART1RxOptr;                           //--- Rx Out Pointer
  u08   ubUSART1RxFIFO[USART1_RX_SIZE];           //--- Rx Character FIFO

  u16   uwXmit_1_Count;                           //--- Character Spacing Delay 100uSec
  u16   uwXmit_1_Delay;                           //--- Character Spacing Delay 100uSec

  //--- Define USART Set-Up
  #define USART1_PARITY     0                     //--- No Parity
  #define USART1_LEN        8                     //--- 8 Bits Data Length
  #define USART1_BAUD       115200                //--- Typically 115200 Baudrate

  //-------------------------------------------------------------------------------------------
  //               Initialize USART1 for Transmit and receive @ UP TO 115200
  //-------------------------------------------------------------------------------------------
  void  fnInitUSART1 (u32 ulBaud)                 //--- Initialize USART1 Communications
  {
    // u32 ulWork = 0;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- Define and initialize the FIFO control registers
    uwUSART1TxCntr = 0;                           //--- Reset the FIFO's
    uwUSART1TxIptr = 0;
    uwUSART1TxOptr = 0;

    uwUSART1RxCntr = 0;
    uwUSART1RxIptr = 0;
    uwUSART1RxOptr = 0;

    //--- Set Up GPIO for PA09=TX PA10=RX
    RCC_AHB2ENR |= 0x00000007;                    //--- Enable GPIO A, B, C Clocks
    nop4;

    //--- Set the UART Main Clock to SYSCLK
    RCC_CCIPR &= 0xFFFFFFFC;                      //--- Clear Old Config for bits 0,1
    nop4;
    RCC_CCIPR |= 0x00000001;                      //--- Set New Config = SYSCLK Bit 0=1 1=0

    RCC_APB2ENR |= 0x00004000;                    //--- Enable USART1 Clock
    nop4;

    //---
    GPIOA_MODER &= 0xFFC3FFFF;                    //--- Enable Alternate Functiom Bits PA09 & PA10
    GPIOA_MODER |= 0x00E70000;

    GPIOA_OTYPER &= 0x0000F6FF;                   //--- PA09 & PA10 = PA09 & PA10 OTYPE = Push Pull

    GPIOA_OSPEEDR |= 0x003C0000;                  //--- Outputs PA09 & PA11 = High Speed

    GPIOA_PUPDR |= 0x00140000;                    //--- PA09 & PA10 = Active Pullup

    GPIOA_ODR &= 0x0000F9FF;                      //--- Clear PA09 & PA10 Output Bits

    GPIOA_AFRL &= 0xFFFFFFFF;                     //--- AFRL Not Changed for GPIOA

    GPIOA_AFRH &= 0xFFFFF00F;
    GPIOA_AFRH |= 0x00000770;                     //--- Set PA09 & PA10 to AF#7 For UART1 I/O

    //--- Initialize the Uart Hardware
    //--- First Initialize the UART Peripherial Clock
    USART1_CR1 = 0x0000;                          //--- N81, Rx Int, Disabled
    USART1_CR2 = 0x0000;
    USART1_CR3 = 0x0000;

    USART1_ICR = 0x00121B5F;                      //--- Clear All Interrupt Flags

    //--- Calculate Baud Rate
    //    NOTE: BAUD rates lower than 1000 are not possible with this USART
    //    OverSampling by 16 used  Base Clock = System Clock = 72 MHz
    USART1_BRR = SYSCLK / ulBaud;                 //--- Set Baud Rate to integer part

    //--- Modify this depending on USART Set_Up Parameters See Reference Manual under USARTS
    USART1_CR1 = 0x002C;                          //--- N81, Rx Int, Disabled
    nop4;                                         //--- Waste a little time
    USART1_CR1 = 0x002D;                          //--- N81, Rx Int, Enable

    nop4;                                         //--- Waste a little time

    fnClrIntPend (USART1_IRQn);                   //--- Clear ANY Pending Interrupt
    fnEnaInt (USART1_IRQn);                       //--- Enable the interrupt

    //--- Calculate the PACER Ticks required between BYTE Transmissions
    //    (SysTickFreq / (ulBaud / 10)) + 1
    uwXmit_1_Delay = (u16) ((SYS_TICK_FREQ / (ulBaud / 10)) + 1);
    uwXmit_1_Count = uwXmit_1_Delay;              //--- Reset the Count

    USART1_TDR = ZERO;                            //--- Send a Zero / null
  }

  //-------------------------------------------------------------------------------------------
  //  Function Name  : USART_1 Rx Interrupt Handler
  //
  //  After initialization, any data sent to USART1 is captured and stored in a FIFO buffer
  //  The FIFO Pointers, Counters and Status flags are automatically handled by the Interrupt
  //-------------------------------------------------------------------------------------------
  void  fnUSART1_IRQ(void)     // 37 - USART1 General Interrupt              0x000000D4
  {
    u08 ubRxData;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    GID;                                          //--- Kill Interrupts
    fnClrIntPend (USART1_IRQn);                   //--- Clear the interrupt in NVIC

    ubRxData = (u08)USART1_RDR;                   //--- Read in the data byte from USART
                                                  //--- to clear the RXNE Bit
    //--- Copy Rx Data to Rx FIFO
    if (uwUSART1RxCntr < (USART1_RX_SIZE - 1))    //--- Test if there is room in the RX FIFO
    {
      ubUSART1RxFIFO[uwUSART1RxIptr] = ubRxData;  //--- Copy Data to FIFO
      uwUSART1RxCntr++;                           //--- Bump the RX Counter
      uwUSART1RxIptr++;                           //--- Bump the In Pointer
      uwUSART1RxIptr %= USART1_RX_SIZE;           //--- Roll Over the FIFO
    }

    USART1_ICR = 0x00121B5F;                      //--- Clear All Interrupt Flags for UART
    GIE;                                          //--- Enable Interrupts before Exit
  }

  //-------------------------------------------------------------------------------------------
  //                       Extract and Transmit 1 Byte from TX FIFO
  //                       ----------------------------------------
  //                        This function is called from the Pacer
  //-------------------------------------------------------------------------------------------
  void  fnXmitSvc_1 (void)
  {
    GID;                                            //--- Kill All Interrupts

    //--- Service USART #1 Transmit
    if (uwUSART1TxCntr > 0)                         //--- Test if Character Waiting
    {
      USART1_TDR = ubUSART1TxFIFO[uwUSART1TxOptr];  //--- Xmit the data
      uwUSART1TxCntr--;                             //--- Bump the Counter -1
      uwUSART1TxOptr++;                             //--- Bump pointer
      uwUSART1TxOptr %= USART1_TX_SIZE;             //--- Rollover mask
    }

    GIE;                                            //--- Restore All Interrupts
  }

  //-------------------------------------------------------------------------------------------
  //                         Send a single Byte of data to TX FIFO
  //-------------------------------------------------------------------------------------------
  u08 fnByteToFIFO_1 (u08 ubByte)
  {
    u08 ubFlag;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    GID;                                          //--- Kill All Interrupts
    //--- Place Character in FIFO
    if (uwUSART1TxCntr < (USART1_TX_SIZE - 2))
    {
      ubUSART1TxFIFO[uwUSART1TxIptr] = ubByte;    //--- Put Byte into FIFO
      uwUSART1TxIptr++;                           //--- Bump pointer
      uwUSART1TxIptr %= USART1_TX_SIZE;           //--- Rollover mask
      uwUSART1TxCntr++;                           //--- Bump the Counter
      ubFlag = 0;                                 //--- Success
    }
    else
    {
      ubFlag = 0xFF;                              //--- Error Flag
    }

    GIE;                                          //--- Restore All Interrupts
    return ubFlag;
  }

  //-------------------------------------------------------------------------------------------
  //                                 Send a String to TX FIFO
  //-------------------------------------------------------------------------------------------
  u08 fnTxtToFIFO_1 (u08 ubOut[])                 //--- Place String into TX FIFO
  {
    u16 uwLen = 0;
    u16 uwCntr = 0;
    u08 ubFlag = 0;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    uwLen = (u16) strlen (ubOut);                 //--- Obtain Message Length
    for (uwCntr = 0; uwCntr < uwLen; uwCntr++)
    {
      ubFlag = fnByteToFIFO_1 ((u08) ubOut[uwCntr]); //--- Send Character to TX FIFO
      if (ubFlag != 0) break;                     //--- If Tx Error then Blow Out Of This
    }

    return ubFlag;
  }


  //-------------------------------------------------------------------------------------------
  //                 Check for and Return Data for USART Rx FIFO  (Polled Rx)
  //    This function checks for a current RX Character or Characters in the USART RX FIFO
  //    If a character or Byte is available from the USART then the return integer contains
  //    the character ( data ) in the low Lo Byte  and the High Byte contains a non zero value
  //-------------------------------------------------------------------------------------------
  u16   fnGetNextUSART1 (void)
  {
    u16 uwRxData = 0;                               //--- Zero Data on Entry

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    GID;                                            //--- Kill Interrupts

    if (uwUSART1RxCntr)                             //--- Get FIFO Counter
    {
      //--- Extract the Data Byte
      uwRxData = (u16) ubUSART1RxFIFO[uwUSART1RxOptr];
      uwRxData |= 0x8000;                           //--- Set the valid data flag
      uwUSART1RxCntr --;                            //--- Bump the counter
      uwUSART1RxOptr ++;                            //--- Bump the input pointer
      uwUSART1RxOptr %= USART1_RX_SIZE;             //--- Modulo Count Rx FIFO Size
    }
    else
    {
      uwRxData = 0x0000;                            //--- No Data Available
    }

    GIE;
    return uwRxData;                                //--- Return the data
  }

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
