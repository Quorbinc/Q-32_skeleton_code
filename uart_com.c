//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                                   USART Communications
//   Typically USART1 is used for External Device Communications.  USART2 is used for debugging
//
//                           Written By:  Sancar James Fredsti
//
//                                Created: 12 August 2021
//
//=============================================================================================

//------  Revision History
//        REV 1.0 Release for production 01 February 2022
//

//---------------------------------------------------------------------------------------------
//        Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#include "projectdefs.h"

//--- Generic Text and String Allotments
u08   ubTxt[1024];                                //--- Generic Message Constructor String
u08   ubStr[128];                                 //--- Generic Sub String Constructor

//---------------------------------------------------------------------------------------------
//                         USART Control RAM & ROM definitions
//---------------------------------------------------------------------------------------------

#ifdef USART1_FLAG
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

  #define USART1_RX_SIZE        1024              //--- Up to 1024 Characters for RX FIFO
  #define USART1_TX_SIZE        1024              //--- Up to 1024 Characters for TX FIFO
  #define USART1_MAX_TX_IN      1022              //--- Up to 1022 Characters ready to go out

  //--- Define USART Set-Up
  #define USART1_PARITY         0                 //--- Typically no Parity
  #define USART1_LEN            8                 //--- Typically 8 Bits Data Len
  #define USART1_BAUD           115200            //--- Typically 115200 Baudrate

  //--- Systick XMIT Delay
  #define XMIT_1_DELAY (u16)(SYS_TICK_FREQ / (USART1_BAUD / 10)) + 1;

  //-------------------------------------------------------------------------------------------
  //               Initialize USART1 for Transmit and receive @ UP TO 115200
  //-------------------------------------------------------------------------------------------
  void  fnInitUSART1 (u32 ulBaud)                   //--- Initialize USART1 Communications
  {
    uwUSART1TxCntr = 0;                             //--- Reset the FIFO's
    uwUSART1TxIptr = 0;
    uwUSART1TxOptr = 0;

    uwUSART1RxCntr = 0;
    uwUSART1RxIptr = 0;
    uwUSART1RxOptr = 0;

    USART1_CR1 = 0x0000;                            //--- Kill the UART
    USART1_CR2 = 0x0000;
    USART1_CR3 = 0x0000;

    fnClrIntPend (USART1_IRQn);                     //--- Clear ANY interrupt

    //--- Calculate Baud Rate
    //    NOTE: BAUD rates lower than 1000 are not possible with this USART
    //    OverSampling by 16 used  Base Clock = System Clock = 72 MHz
    USART1_BRR = SYSCLK / ulBaud;                   //--- Set Baud Rate to integer part
    USART1_CR3 = 0x0000;                            //--- All Synchronous Stuff Off
    USART1_CR2 = 0x0000;

    //--- Modify this depending on USART Set_Up Parameters See Reference Manual under USARTS
    USART1_CR1 = 0x202C;                            //--- N81, Rx Int, Enable

    nop48;                                          //--- Waste a little time

    fnClrIntPend (USART1_IRQn);                     //--- Clear ANY Pending Interrupt
    fnEnaInt (USART1_IRQn);                         //--- Enable the interrupt

    //--- Calculate the PACER Ticks required between BYTE Transmissions
    //    (SysTickFreq / (ulBaud / 10)) + 1

    uwXmit_1_Count = uwXmit_1_Delay;                //--- Reset the Count

    USART1_TDR = ZERO;                              //--- Send a Zero to init the TX
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

    GID;                                            //--- Kill Interrupts
    fnClrIntPend (USART1_IRQn);                     //--- Clear the interrupt

    if (USART1_SR & 0x0008)                         //--- Is overrun error triggered?
    {
      ubRxData = (u08)USART1_RDR;                   //--- Read & Dump the data byte from USART
      GIE;                                          //--- Enable Interrupts
      return;                                       //--- Get out of here
    }

    ubRxData = (u08)USART1_RDR;                     //--- Read in the data byte from USART

    //--- Copy Rx Data to Rx FIFO
    if (uwUSART1RxCntr < (USART1_RX_SIZE - 2))      //--- Test if there is room in the RX FIFO
    {
      ubUSART1RxFIFO[uwUSART1RxIptr] = ubRxData;
      uwUSART1RxCntr++;                             //--- Bump the RX Counter
      uwUSART1RxIptr++;                             //--- Bump the In Pointer
      uwUSART1RxIptr %= USART1_RX_SIZE;             //--- Roll Over the FIFO
    }

    ubRxData = (u08)USART1_RDR;                     //--- Read in the data byte from USART
    GIE;                                            //--- Enable Interrupts before Exit
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
  //                         Send a single character to TX FIFO
  //-------------------------------------------------------------------------------------------
  void  fnByteToFIFO_1 (u08 ubByte)
  {
    GID;                                            //--- Kill All Interrupts
    //--- Place Character in FIFO
    if (uwUSART1TxCntr < (USART1_TX_SIZE - 2))
    {
      ubUSART1TxFIFO[uwUSART1TxIptr] = ubByte;      //--- Put Byte into FIFO
      uwUSART1TxIptr++;                             //--- Bump pointer
      uwUSART1TxIptr %= USART1_TX_SIZE;             //--- Rollover mask
      uwUSART1TxCntr++;                             //--- Bump the Counter
    };

    GIE;                                            //--- Restore All Interrupts
  }

  //-------------------------------------------------------------------------------------------
  //                     Output ASCII String to USART_2 Tx FIFO
  //
  //    Returns (0) on success and -1 on failure
  //-------------------------------------------------------------------------------------------

  u16 fnStringOut_1 (u08 ubOut[])
  {
    u16 uwSlen;
    u16 uwPtr;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- Get String Length
    uwSlen = strlen (ubOut);                      //--- Obtain Standard String Length

    //--- Is therre room in Tx FIFO?
    if (uwSlen > ((USART1_TX_SIZE -2) - uwUSART1TxCntr)) return -1;

    for (uwPtr = 0; uwPtr < uwSlen; uwPtr++)
    {
      fnByteToFIFO_1 (ubOut[uwPtr]);
    }

    return 0;
  }

#endif

//---------------------------------------------------------------------------------------------
//    If USART2 is defined then include this basic Code
//
//    USART-2 is a character based communications used for DeBug and Messaging Functions
//---------------------------------------------------------------------------------------------

#ifdef USART2_FLAG
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

  #define USART2_RX_SIZE        1024              //--- Up to 1024 Characters for RX FIFO
  #define USART2_TX_SIZE        1024              //--- Up to 1024 Characters for TX FIFO
  #define USART2_MAX_TX_IN      1022              //--- Up to 1022 Characters ready to go out

  //--- Define USART Set-Up
  #define USART2_PARITY         0                 //--- Typically no Parity
  #define USART2_LEN            8                 //--- Typically 8 Bits Data Len
  #define USART2_BAUD           115200            //--- Typically 115200 Baudrate

  //--- Systick XMIT Delay
  #define XMIT_2_DELAY (u16)(SYS_TICK_FREQ / (USART2_BAUD / 10)) + 1;

  //-------------------------------------------------------------------------------------------
  //                    Initialize USART2 for Transmit and receive @ 115200
  //-------------------------------------------------------------------------------------------
  u16  fnInitUSART2 (u32 ulBaud)                   //--- Initialize USART2 Communications
  {
    USART2_CR1 = 0x0000;                           //--- Kill the UART
    USART2_CR2 = 0x0000;
    USART2_CR3 = 0x0000;

    uwUSART2TxCntr = 0;                             //--- Reset the FIFO's
    uwUSART2TxIptr = 0;
    uwUSART2TxOptr = 0;

    uwUSART2RxCntr = 0;
    uwUSART2RxIptr = 0;
    uwUSART2RxOptr = 0;

    fnClrIntPend (USART2_IRQn);                     //--- Clear ANY UART2 interrupts pending

    //--- Set Up Port I/O Pins A2 & A3 for USART-2 Tx&Rx
    //-----------------------------------------------------------------------------------------
    //      Configure GPIO_A
    //-----------------------------------------------------------------------------------------
    //      GPIO MODE  00=Input  01=Output  10=AltFun  11=Analog
    //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
    //      .. .. .. .. .. .. .. .. .. .. .. .. AF AF .. ..
    //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
    //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
    //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
    //      01 01.01 01.01 01.01 10.01 01.01 01.10 10.01 01
    //      OT OT OT OT OT OT OT OT OT OT OT OT OT OT OT OT
    //-----------------------------------------------------------------------------------------

    //----- Bits 2&3 = Alternate Function
    //      Change to USART-2 application
    GPIOA_MODER &= 0xFFFFFF0F;                      //--- Clr Port Pins (2,3)
    GPIOA_MODER |= 0x000000A0;                      //--- Set Port Pins (2,3) for AF

    //      GPIO AFRL
    //      3322 2222 2222 1111 1111 1100 0000 0000
    //      1098 7654 3210 9876 5432 1098 7654 3210
    //      .... .... .... .... .... .... .... ....
    //      0000 0000 0000 0000 0111 0111 0000 0000
    GPIOA_AFRL &= 0xFFFF00FF;                        //--- Clr AFRL for PA02 & PA03
    GPIOA_AFRL |= 0x00007700;                        //--- Set AFRL to USART-2 AFL = 7

    //      GPIO AFRH Un Touched
    //      3322 2222 2222 1111 1111 1100 0000 0000
    //      1098 7654 3210 9876 5432 1098 7654 3210
    //      .... .... .... .... .... .... .... ....
    //      0000 0000 0000 0000 0000 0000 0000 0000
    // GPIOA_AFRH &= 0x00000000;                        //--- Set AFRH to 0
    // GPIOA_AFRH |= 0x00000000;                        //--- Set AFRH to 0

    //      GPIO INPUT PUPD RESISTORS
    //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
    //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
    //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
    //      .. ..|.. ..|.. ..|.. ..|.. ..|.. ..|.. ..|.. ..
    //      00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    //      NP NP NP NP NP NP NP NP NP NP NP NP PU PU NP NP
    GPIOA_PUPDR &= 0xFFFFFF0F;                       //--- Clr PA02 & PA03 Pull U/D
    GPIOA_PUPDR |= 0x00000050;                       //--- Set PA02 & PA03 for Pull Up Default

    //--- Calculate Baud Rate
    //    NOTE: BAUD rates lower than 1000 are not possible with this USART
    //    OverSampling by 16 used  Base Clock = System Clock = 72 MHz
    //    Formula = SysClk (72000000) / Baud (115200)
    USART2_BRR = SYSCLK / ulBaud;                   //--- Set Baud Rate to integer part

    //--- Calculate the PACER Ticks required between BYTE Transmissions
    //    (10000 / (ulBaud / 10)) + 1
    uwXmit_2_Count = XMIT_2_DELAY;                  //--- Reset the Count

    USART2_CR3 = 0x0000;                            //--- All Synchronous Stuff Off
    USART2_CR2 = 0x0000;

    //--- Modify this depending on USART Set_Up Parameters
    USART2_CR1 = 0x000D;                            //--- N81, Rx Int = 1 Tx Int = 0

    nop4;                                           //--- Waste a little time

    fnSetIntPriority (USART2_IRQn, 0x07);           //--- Set Priority in NVIC = 0x07
    fnClrIntPend (USART2_IRQn);                     //--- Clear ANY interrupts pending
    fnEnaInt (USART2_IRQn);                         //--- Enable the interrupt

    USART2_TDR = ZERO;                              //--- Send a NULL Character
    return 0;                                       //--- Return Success
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

    if (USART2_ISR & 0x0008)                        //--- Is overrun error triggered?
    {
      ubRxData = (u08)USART2_RDR;                   //--- Read & Dump the data byte from USART
      GIE;                                          //--- Enable Interrupts
      return;                                       //--- Get out of here
    }

    ubRxData = (u08)USART2_RDR;                      //--- Read in the data byte from USART

    //--- Copy Rx Data to Rx FIFO
    if (uwUSART2RxCntr < (USART2_RX_SIZE - 2))
    {
      ubUSART2RxFIFO[uwUSART2RxIptr] = ubRxData;
      uwUSART2RxCntr++;                             //--- Bump the RX Counter
      uwUSART2RxIptr++;                             //--- Bump the In Pointer
      uwUSART2RxIptr %= USART2_RX_SIZE;             //--- Roll Over the FIFO
    }

    ubRxData = (u08)USART2_RDR;                     //--- Read in the data byte from USART
    GIE;                                            //--- Enable Interrupts
  }

  //-------------------------------------------------------------------------------------------
  //               Check for and Return Data for USART Rx FIFO (Polled USART RX)
  //  This function checks for any data in the Rx FIFO.  If TRUE then it returns a word
  //  value with the Hi Byte set to 0x80 and the Lo Byte set to the Data (00-FF)
  //-------------------------------------------------------------------------------------------
  u16   fnGetNextUSART2 (void)
  {
    u16 uwRxData = 0;                               //--- Zero Data on Entry

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    GID;                                            //--- Kill Interrupts

    if (uwUSART2RxCntr)                             //--- Get FIFO Counter
    {
      //--- Extract the Data Byte
      uwRxData = (u16) ubUSART2RxFIFO[uwUSART2RxOptr];
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
      USART2_TDR = ubUSART2TxFIFO[uwUSART2TxOptr];  //--- Xmit the data
      uwUSART2TxCntr--;                             //--- Bump the Counter -1
      uwUSART2TxOptr++;                             //--- Bump pointer
      uwUSART2TxOptr %= USART2_TX_SIZE;             //--- Rollover at 8192 Characters
      GIE;                                          //--- Restore All Interrupts
    }
  }

  //-------------------------------------------------------------------------------------------
  //                     Send a Single Byte or Character to TX FIFO
  //-------------------------------------------------------------------------------------------
  void  fnByteToFIFO_2 (u08 ubChar)
  {
    //--- Place Character in FIFO
    if (uwUSART2TxCntr < (USART2_TX_SIZE - 2))      //--- Is There Room in FIFO?
    {
      GID;                                          //--- Kill All Interrupts
      ubUSART2TxFIFO[uwUSART2TxIptr] = ubChar;      //--- Put Char in FIFO
      uwUSART2TxIptr++;                             //--- Bump pointer
      uwUSART2TxIptr %= USART2_TX_SIZE;             //--- Rollover at 1K Characters
      uwUSART2TxCntr++;                             //--- Bump the Counter
      GIE;                                          //--- Restore All Interrupts
    };
  }

  //-------------------------------------------------------------------------------------------
  //                     Output ASCII String to USART_2 Tx FIFO
  //
  //    Returns (0) on success and -1 on failure
  //-------------------------------------------------------------------------------------------

  u16 fnStringOut_2 (u08 ubOut[])
  {
    u16 uwSlen;
    u16 uwPtr;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- Get String Length
    uwSlen = strlen (ubOut);                      //--- Obtain Standard String Length

    //--- Is therre room in Tx FIFO?
    if (uwSlen > ((USART2_TX_SIZE -2) - uwUSART2TxCntr)) return -1;

    for (uwPtr = 0; uwPtr < uwSlen; uwPtr++)
    {
      fnByteToFIFO_2 (ubOut[uwPtr]);
    }

    return 0;
  }

  //-------------------------------------------------------------------------------------------
  //                     Export an Array of Bytes to USART_2 Tx FIFO
  //-------------------------------------------------------------------------------------------
  u16 fnArrayOut_2 (u08 ubOut[], u16 uwArraySize)
  {
    u16 uwPtr;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //--- Test if this message is smaller than remaining FIFO size
    if ((uwUSART2TxCntr + uwArraySize) < (USART2_TX_SIZE - 2))
    {
      for (uwPtr = 0; uwPtr < uwArraySize; uwPtr++)
      {
        fnByteToFIFO_2 (ubOut[uwPtr]);
      }

      return (0);             //--- Success
    }
    else
    {
      return (-1);             //--- Failure
    }
  }

#endif                                //--- USART #2 defined

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
