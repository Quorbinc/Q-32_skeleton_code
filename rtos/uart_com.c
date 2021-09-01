//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                                   USART Communications
//
//                           Written By:  Sancar James Fredsti
//
//                                Created: 12 August 2021
//
//=============================================================================================

//------  Revision History

//---------------------------------------------------------------------------------------------
//         Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#include "projectdefs.h"

//--- Generic Text and String Allotments
u08   ubTxt[256];                   //--- Generic Message Constructor String
u08   ubStr[256];                   //--- Generic Sub String Constructor

//---------------------------------------------------------------------------------------------
//                         USART Control RAM & ROM definitions
//---------------------------------------------------------------------------------------------
//--- USART Channel #1 Definitions
u16   uwUSART1TxCntr;               //--- Tx Chr Cntr
u16   uwUSART1TxIptr;               //--- Tx In Pointer
u16   uwUSART1TxOptr;               //--- Tx Out Pointer
u08   ubUSART1TxFIFO[USART1_TX_SIZE]; //--- Tx Character FIFO

u16   uwUSART1RxCntr;               //--- Rx Chr Cntr
u16   uwUSART1RxIptr;               //--- Rx In Pointer
u16   uwUSART1RxOptr;               //--- Rx Out Pointer
u08   ubUSART1RxFIFO[USART1_RX_SIZE]; //--- Rx Character FIFO

struct RxMsg_1 stUSART1_Rx_Msg;                   //--- Current Receive Message Buffer
struct RxMsg_1 stUSART1_Msg_FIFO[16];             //--- Received Message FIFO

u16   uwRx1MsgIP;                                 //--- Rx Message In Pointer
u16   uwRx1MsgOP;                                 //--- Rx Message Out Pointer
u16   uwRx1MsgCNT;                                //--- Rx Message Counter Pointer

u08   ubRxState1;                                 //--- Rx State Machine Current State
u08   ubRxLRC1;                                   //--- Current LRC Calculation Value
u16   uwErrCntr1;                                 //--- Number of errors encountered

u16   uwXmit_1_Count;                             //--- Character Spacing Delay 100uSec
u16   uwXmit_1_Delay;                             //--- Character Spacing Delay 100uSec

#define USART1PARITY      1
#define USART1LEN         8
#define USART1BAUD        115200
#define USART1_BRR_VAL    SYSCLK/USART1BAUD

//---------------------------------------------------------------------------------------------
//                    Initialize USART1 for Transmit and receive @ 115200
//---------------------------------------------------------------------------------------------
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

  //--- Modify this depending on USART Set_Up Parameters
  USART1_CR1 = 0x202C;                            //--- N81, Rx Int, Enable

  nop48;                                          //--- Waste a little time

  fnClrIntPend (USART1_IRQn);                     //--- Clear ANY interrupt
  fnEnaInt (USART1_IRQn);                         //--- Enable the interrupt

  //--- Calculate the PACER Ticks required between BYTE Transmissions
  //    10000 / (ulBaud / 10)
  uwXmit_1_Delay = (u16)10000 / (ulBaud / 10);
  uwXmit_1_Count = uwXmit_1_Delay;                //--- Reset the Count

  USART1_DR = ZERO;                               //--- Send a Zero
}

//---------------------------------------------------------------------------------------------
//                     Check for and Return Data for USART Rx FIFO  (Polled Rx)
//---------------------------------------------------------------------------------------------
u16   fnGetNextUSART1 (void)
{
  u16 uwRxData = 0;                               //--- Zero Data on Entry

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

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

//---------------------------------------------------------------------------------------------
//  Function Name  : USART_1 Rx Interrupt Handler
//---------------------------------------------------------------------------------------------
void  fnUSART1_IRQ(void)     // 37 - USART1 General Interrupt              0x000000D4
{
  u08 ubRxData;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  GID;                                            //--- Kill Interrupts
  fnClrIntPend (USART1_IRQn);                     //--- Clear the interrupt

  if (USART1_SR & 0x0008)                         //--- Is overrun error triggered?
  {
    ubRxData = (u08)USART1_DR;                    //--- Read in the data byte from USART
    GIE;                                          //--- Enable Interrupts
    return;                                       //--- Get out of here
  }

  ubRxData = (u08)USART1_DR;                      //--- Read in the data byte from USART

  //--- Copy Rx Data to Rx FIFO
  if (uwUSART1RxCntr < (USART1_RX_SIZE - 2))
  {
    ubUSART1RxFIFO[uwUSART1RxIptr] = ubRxData;
    uwUSART1RxCntr++;                             //--- Bump the RX Counter
    uwUSART1RxIptr++;                             //--- Bump the In Pointer
    uwUSART1RxIptr %= USART1_RX_SIZE;             //--- Roll Over the FIFO
  }

  ubRxData = (u08)USART1_DR;                      //--- Read in the data byte from USART
  GIE;                                            //--- Enable Interrupts before Exit
}

//---------------------------------------------------------------------------------------------
//                       Extract and Transmit 1 Byte from TX FIFO
//                       ----------------------------------------
//                       This function is called from the Pacer
//---------------------------------------------------------------------------------------------
void  fnXmitSvc_1 (void)
{
  GID;                                            //--- Kill All Interrupts

  //--- Service USART #1 Transmit
  if (uwUSART1TxCntr > 0)                         //--- Test if Character Waiting
  {
    USART1_DR = ubUSART1TxFIFO[uwUSART1TxOptr];   //--- Xmit the data
    uwUSART1TxCntr--;                             //--- Bump the Counter -1
    uwUSART1TxOptr++;                             //--- Bump pointer
    uwUSART1TxOptr %= USART1_TX_SIZE;             //--- Rollover mask
  }

  GIE;                                            //--- Restore All Interrupts
}

//---------------------------------------------------------------------------------------------
//                         Send a single character to TX FIFO
//---------------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------------
//                     Transmit a Packet for data to Host
//
//          ubFC = Message Function Code
//          ubSC = Message Sub Command
//          ubDL = Number of Data Unions Transmitted
//          ubData = FBWL Union  (4 Bytes;
//---------------------------------------------------------------------------------------------

void  fnSendPacketToHost (u08 ubFC, u08 ubSC, u08 ubDL, union DFLWB unData[4])
{
  u08 ubMessage[40];
  u08 ubLRC;
  u08 ubWork;
  u08 ubCntr;
  u08 ubDP;
  u08 ubVP;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  for (ubCntr = 0; ubCntr < 40; ubCntr++)
  {
    ubMessage[ubCntr] = 0;
  }

  ubMessage[0] = 0x01;
  ubMessage[1] = 0xE1;
  ubMessage[2] = 0x69;
  ubMessage[3] = 0xA5;
  ubMessage[4] = 0x3C;
  ubLRC = 0x01^0xE1^0x69^0xA5^0x3C;               //--- Calculate Message Header LRC

  //--- Add In Function Code
  ubMessage[5] = ubFC;
  ubLRC ^= ubFC;

  //--- Add In Sub Function Code
  ubMessage[6] = ubSC;
  ubLRC ^= ubSC;

  //--- Get number of Variables Sent (4 bytes Each)
  ubMessage[7] = ubDL;
  ubLRC ^= ubDL;                                  //--- Calculate New LRC
  ubDP = 8;                                       //--- Next Byte in Message starts @ 8
  ubVP = 0;                                       //--- Var Pointer = 0

  //--- Data Blocks are always 8 bytes
  if (ubDL > 0)                                   //--- If Number of FBWL unions is > 0
  {
    for (ubVP = 0; ubVP < ubDL; ubVP++)
    {
      ubWork = unData[ubVP].ubByte[0];
      ubMessage[ubDP] = ubWork;
      ubLRC ^= ubWork;
      ubDP++;

      ubWork = unData[ubVP].ubByte[1];
      ubMessage[ubDP] = ubWork;
      ubLRC ^= ubWork;
      ubDP++;

      ubWork = unData[ubVP].ubByte[2];
      ubMessage[ubDP] = ubWork;
      ubLRC ^= ubWork;
      ubDP++;

      ubWork = unData[ubVP].ubByte[3];
      ubMessage[ubDP] = ubWork;
      ubLRC ^= ubWork;
      ubDP++;

      ubWork = unData[ubVP].ubByte[4];
      ubMessage[ubDP] = ubWork;
      ubLRC ^= ubWork;
      ubDP++;

      ubWork = unData[ubVP].ubByte[5];
      ubMessage[ubDP] = ubWork;
      ubLRC ^= ubWork;
      ubDP++;

      ubWork = unData[ubVP].ubByte[6];
      ubMessage[ubDP] = ubWork;
      ubLRC ^= ubWork;
      ubDP++;

      ubWork = unData[ubVP].ubByte[7];
      ubMessage[ubDP] = ubWork;
      ubLRC ^= ubWork;
      ubDP++;
    }
  }

  //--- Terminate message with LRC and ~LRC
  ubMessage [ubDP] = ubLRC;
  ubDP++;
  ubMessage [ubDP] = ~ubLRC;
  ubDP++;

  //--- Move Message to transmit FIFO
  for (ubWork = (0); ubWork < ubDP; ubWork++)
  {
    fnByteToFIFO_1 (ubMessage[ubWork]);
  }
}


//---------------------------------------------------------------------------------------------
//                         Send END Back to Host
//---------------------------------------------------------------------------------------------
void  fnSendStop (void)
{
  u08 ubLRC = 0;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  fnByteToFIFO_1 (0x01);                          //--- Start of Header
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0xE1);                          //--- Header E1
  ubLRC ^= 0xE1;

  fnByteToFIFO_1 (0x69);                          //--- Header 69
  ubLRC ^= 0x69;

  fnByteToFIFO_1 (0xA5);                          //--- Header A5
  ubLRC ^= 0xA5;

  fnByteToFIFO_1 (0x3C);                          //--- Header 3C
  ubLRC ^= 0x3C;

  fnByteToFIFO_1 (0x01);                          //--- STOP Function Code
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0x00);                          //--- Sub Function Code = 00
  ubLRC ^= 0x00;

  fnByteToFIFO_1 (0x01);                          //--- Data Length = 1
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (ubLRC);                         //--- LRC

  fnByteToFIFO_1 (~ubLRC);                        //--- ~LRC
}

//---------------------------------------------------------------------------------------------
//                         Send Start Button Back to Host
//---------------------------------------------------------------------------------------------
void  fnSendStart (void)
{
  u08 ubLRC = 0;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  fnByteToFIFO_1 (0x01);                          //--- Start of Header
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0xE1);                          //--- Header E1
  ubLRC ^= 0xE1;

  fnByteToFIFO_1 (0x69);                          //--- Header 69
  ubLRC ^= 0x69;

  fnByteToFIFO_1 (0xA5);                          //--- Header A5
  ubLRC ^= 0xA5;

  fnByteToFIFO_1 (0x3C);                          //--- Header 3C
  ubLRC ^= 0x3C;

  fnByteToFIFO_1 (0x02);                          //--- New Start Button Pressed
  ubLRC ^= 0x02;

  fnByteToFIFO_1 (0x00);                          //--- Sub Function Code = 00
  ubLRC ^= 0x00;

  fnByteToFIFO_1 (0x01);                          //--- Data Length = 1
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (ubLRC);                         //--- LRC

  fnByteToFIFO_1 (~ubLRC);                        //--- ~LRC
}

//---------------------------------------------------------------------------------------------
//    Send Program Request To Host  Code = 0xF0
//---------------------------------------------------------------------------------------------
void  fnProgramLoadRequest (void)
{
  u08 ubLRC = 0;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  fnByteToFIFO_1 (0x01);                          //--- Start of Header
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0xE1);                          //--- Header E1
  ubLRC ^= 0xE1;

  fnByteToFIFO_1 (0x69);                          //--- Header 69
  ubLRC ^= 0x69;

  fnByteToFIFO_1 (0xA5);                          //--- Header A5
  ubLRC ^= 0xA5;

  fnByteToFIFO_1 (0x3C);                          //--- Header 3C
  ubLRC ^= 0x3C;

  fnByteToFIFO_1 (0xF0);                          //--- Start Load Request
  ubLRC ^= 0xF0;

  fnByteToFIFO_1 (0x00);                          //--- Sub Function Code = 00
  ubLRC ^= 0x00;

  fnByteToFIFO_1 (0x01);                          //--- Data Length = 1 4 Byte Union
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (ubLRC);                         //--- LRC

  fnByteToFIFO_1 (~ubLRC);                        //--- ~LRC
}

//---------------------------------------------------------------------------------------------
//    Send Next Program Line Request To Host  Code = 0xF1
//---------------------------------------------------------------------------------------------
void fnSendNextLineRequest (void)
{
  u08 ubLRC = 0;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  fnByteToFIFO_1 (0x01);                          //--- Start of Header
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0xE1);                          //--- Header E1
  ubLRC ^= 0xE1;

  fnByteToFIFO_1 (0x69);                          //--- Header 69
  ubLRC ^= 0x69;

  fnByteToFIFO_1 (0xA5);                          //--- Header A5
  ubLRC ^= 0xA5;

  fnByteToFIFO_1 (0x3C);                          //--- Header 3C
  ubLRC ^= 0x3C;

  fnByteToFIFO_1 (0xF1);                          //--- ACK Function Code
  ubLRC ^= 0xFE;

  fnByteToFIFO_1 (0x00);                          //--- Sub Function Code = 00
  ubLRC ^= 0x00;

  fnByteToFIFO_1 (0x01);                          //--- Data Length = 1 4 Byte Union
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (ubLRC);                         //--- LRC

  fnByteToFIFO_1 (~ubLRC);                        //--- ~LRC
}

//---------------------------------------------------------------------------------------------
//                         Send ACK Back to Host
//---------------------------------------------------------------------------------------------
void  fnSendACK (u08 ubRxFC)
{
  u08 ubLRC = 0;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  fnByteToFIFO_1 (0x01);                          //--- Start of Header
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0xE1);                          //--- Header E1
  ubLRC ^= 0xE1;

  fnByteToFIFO_1 (0x69);                          //--- Header 69
  ubLRC ^= 0x69;

  fnByteToFIFO_1 (0xA5);                          //--- Header A5
  ubLRC ^= 0xA5;

  fnByteToFIFO_1 (0x3C);                          //--- Header 3C
  ubLRC ^= 0x3C;

  fnByteToFIFO_1 (0xFE);                          //--- ACK Function Code
  ubLRC ^= 0xFE;

  fnByteToFIFO_1 (0x00);                          //--- Sub Function Code = 00
  ubLRC ^= 0x00;

  fnByteToFIFO_1 (0x01);                          //--- Data Length = 1 4 Byte Union
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (ubRxFC);                        //--- Received function code to ACK
  ubLRC ^= ubRxFC;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (ubLRC);                         //--- LRC

  fnByteToFIFO_1 (~ubLRC);                        //--- ~LRC
}

//---------------------------------------------------------------------------------------------
//                         Send NAK Back to Host
//---------------------------------------------------------------------------------------------
void  fnSendNAK (u08 ubRxFC, u08 ubEC)
{
  u08 ubLRC = 0;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  fnByteToFIFO_1 (0x01);                          //--- Start of Header
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0xE1);                          //--- Header E1
  ubLRC ^= 0xE1;

  fnByteToFIFO_1 (0x69);                          //--- Header 69
  ubLRC ^= 0x69;

  fnByteToFIFO_1 (0xA5);                          //--- Header A5
  ubLRC ^= 0xA5;

  fnByteToFIFO_1 (0x3C);                          //--- Header 3C
  ubLRC ^= 0x3C;

  fnByteToFIFO_1 (0xFF);                          //--- NACK Function Code
  ubLRC ^= 0xFF;

  fnByteToFIFO_1 (0x00);                          //--- Sub Function Code = 00
  ubLRC ^= 0x00;

  fnByteToFIFO_1 (0x01);                          //--- Data Length = 1
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (ubRxFC);                        //--- Received function code to NACK
  ubLRC ^= ubRxFC;

  fnByteToFIFO_1 (ubEC);                          //--- Error Code
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (ubLRC);                         //--- LRC
  fnByteToFIFO_1 (~ubLRC);                        //--- ~LRC Bit Compliment
}

//---------------------------------------------------------------------------------------------
//                         Send ERR Back to Host
//---------------------------------------------------------------------------------------------
void  fnSendERR (u16 uwErrLine, u08 ubRxFC)
{
  u08 ubLRC = 0;
  u08 ubA;
  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  fnByteToFIFO_1 (0x01);                          //--- Start of Header
  ubLRC ^= 0x01;

  fnByteToFIFO_1 (0xE1);                          //--- Header E1
  ubLRC ^= 0xE1;

  fnByteToFIFO_1 (0x69);                          //--- Header 69
  ubLRC ^= 0x69;

  fnByteToFIFO_1 (0xA5);                          //--- Header A5
  ubLRC ^= 0xA5;

  fnByteToFIFO_1 (0x3C);                          //--- Header 3C
  ubLRC ^= 0x69;

  fnByteToFIFO_1 (0xFD);                          //--- Error Function Code
  ubLRC ^= 0xFD;

  fnByteToFIFO_1 (0x00);                          //--- Sub Function Code = 00
  ubLRC ^= 0x00;

  fnByteToFIFO_1 (0x01);                          //--- Data Length = 1 Long
  ubLRC ^= 0x01;

  ubA = uwErrLine & 0xFF;                         //--- Line Number Low
  fnByteToFIFO_1 (ubA);                           //--- Transmitted Error Line #
  ubLRC ^= ubA;

  ubA = (uwErrLine / 16) & 0xFF;                  //--- Line Number High
  fnByteToFIFO_1 (ubA);                           //--- Transmitted Error Line #
  ubLRC ^= ubA;

  fnByteToFIFO_1 (ubRxFC);                        //--- Command Function to Report
  ubLRC ^= ubRxFC;

  fnByteToFIFO_1 (0);                             //--- Null
  ubLRC ^= 0;

  fnByteToFIFO_1 (ubLRC);                         //--- LRC
  fnByteToFIFO_1 (~ubLRC);                        //--- ~LRC
}

//---------------------------------------------------------------------------------------------
//    COM PORT #1 RX StateMachine
//---------------------------------------------------------------------------------------------
//
//--- Minimum COM Data Carrier Definition
//  union DFLWB                     //--- 8 Bytes Binary / Integer Storage
//  {
//    dbl   dfFlt;                  //--- 1 Double Precision Float
//    u64   uxBig;                  //--- 1 Unsigned 64 Bit Integer
//    s64   sxBig;                  //--- 1 Signed 64 Bit Integer
//    flt   sfFlt[2];               //--- 2 Single Precision Floats
//    u32   ulLong[2];              //--- 2 Unsigned Long
//    s32   slLong[2];              //--- 2 Signed Long
//    u16   uwWord[4];              //--- 4 Unsigned Words
//    s16   swWord[4];              //--- 4 Signed Words
//    u08   ubByte[8];              //--- 8 Unsigned Bytes
//    s08   sbByte[8];              //--- 8 Signed Bytes
//    u08*  ubPtr[2];               //--- 2 General Purpose Pointers (byte]
//    void* vPntr[2];               //--- 2 Void Type Pointers
//  };
//
//--- ComData Formatted Communications Message (Sans Headers & LRC)
//  struct  RxMsg_1
//  {
//    u08 ubFC;                                     //--- Function Code
//    u08 ubSubCmd;                                 //--- Sub Command or Axis Value
//    u08 ubDlen;                                   //--- Number of FBWL Unions
//    union DFLWB unComData[4];                     //--- Up to 4 Variable Data unions Available
//                                                  //    Up to 32 Total Bytes of Data
//  };
//
//
//---------------------------------------------------------------------------------------------
//    Definition of Communications Packets structures and Unions
//---------------------------------------------------------------------------------------------
//
//  State Machine States
//  00 = Wait for 01
//  01 = Wait for E1
//  02 = Wait for 69
//  03 = Wait for A5
//  04 = Wait For 3C
//  05 = Get Function Code
//  06 = Get Sub Function Code
//  07 = Get Data Length  If (0) goto State #9  #=Number of DFLWB Unions
//  08 = Receive Data Tail (32 Bytes)
//  09 = Get LRC
//  10 = Get LRC Compliment
//
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//    Process complete message from RX State Machine #1
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//    If USART2 is defined then include this basic Code
//
//    USART-2 is a character basted communications used for DeBug and Messaging Functions
//---------------------------------------------------------------------------------------------

//--- USART Channel #2 Definitions
u16   uwUSART2TxCntr;               //--- Tx Chr Cntr
u16   uwUSART2TxIptr;               //--- Tx In Pointer
u16   uwUSART2TxOptr;               //--- Tx Out Pointer
u08   ubUSART2TxFIFO[USART2_TX_SIZE]; //--- Tx Character FIFO

u16   uwUSART2RxCntr;               //--- Rx Chr Cntr
u16   uwUSART2RxIptr;               //--- Rx In Pointer
u16   uwUSART2RxOptr;               //--- Rx Out Pointer
u08   ubUSART2RxFIFO[USART2_RX_SIZE]; //--- Rx Character FIFO

u16   uwRxState2;                   //--- Rx State Machine Current State
u08   ubRxLRC2;                     //--- Current LRC Calculation Value
u16   uwErrCntr2;                   //--- Number of errors encountered

u16   uwXmit_2_Count;               //--- Character Spacing Delay 100uSec
u16   uwXmit_2_Delay;               //--- Character Spacing Delay 100uSec

//---------------------------------------------------------------------------------------------
//                    Initialize USART2 for Transmit and receive @ 115200
//---------------------------------------------------------------------------------------------
void  fnInitUSART2 (u32 ulBaud)                    //--- Initialize USART1 Communications
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

  USART1_BRR = SYSCLK / ulBaud;                   //--- Set Baud Rate to integer part

  USART2_CR3 = 0x0000;                            //--- All Synchronous Stuff Off
  USART2_CR2 = 0x0000;

  //--- Modify this depending on USART Set_Up Parameters
  USART2_CR1 = 0x202C;                            //--- N81, Rx Int, Enable

  nop12;                                          //--- Waste a little time

  fnClrIntPend (USART2_IRQn);                     //--- Clear ANY interrupt
  fnEnaInt (USART2_IRQn);                         //--- Enable the interrupt

  //--- Calculate the PACER Ticks required between BYTE Transmissions
  //    10000 / (ulBaud / 10)
  uwXmit_2_Delay = (u16)10000 / (ulBaud / 10);
  uwXmit_2_Count = uwXmit_2_Delay;                //--- Reset the Count

  USART1_DR = ZERO;                               //--- Send a Carriage Return to Start
}

//---------------------------------------------------------------------------------------------
//  Function Name  : USART_2 Rx Interrupt Handler
//---------------------------------------------------------------------------------------------
void  fnUSART2_IRQ(void)                        //--- 38 - USART2 General Interrupt
{
  u08 ubRxData;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

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


//---------------------------------------------------------------------------------------------
//                     Check for and Return Data for USART Rx FIFO (Polled USART RX)
//---------------------------------------------------------------------------------------------
u16   fnGetNextUSART2 (void)
{
  u16 uwRxData = 0;                               //--- Zero Data on Entry

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

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

//---------------------------------------------------------------------------------------------
//                       Extract and Transmit 1 Byte from TX FIFO
//                       ----------------------------------------
//                       This function is called once every 100uS
//---------------------------------------------------------------------------------------------
void  fnXmitSvc_2 (void)
{
  GID;                                            //--- Kill All Interrupts
  //--- Service USART #1 Transmit
  if (uwUSART2TxCntr > 0)                         //--- Test if Character Waiting
  {
    USART2_DR = ubUSART2TxFIFO[uwUSART2TxOptr];   //--- Xmit the data
    uwUSART2TxCntr--;                             //--- Bump the Counter -1
    uwUSART2TxOptr++;                             //--- Bump pointer
    uwUSART2TxOptr %= USART2_TX_SIZE;             //--- Rollover at 8192 Characters
  }

  GIE;                                            //--- Restore All Interrupts
}

//---------------------------------------------------------------------------------------------
//                     Send a single Byte or character to TX FIFO
//---------------------------------------------------------------------------------------------
void  fnByteToFIFO_2 (u08 ubChar)
{
  //--- Place Character in FIFO
  if (uwUSART2TxCntr < (USART2_TX_SIZE - 2))
  {
    ubUSART2TxFIFO[uwUSART2TxIptr] = ubChar;      //--- Put Char in FIFO
    uwUSART2TxIptr++;                             //--- Bump pointer
    uwUSART2TxIptr %= USART2_TX_SIZE;             //--- Rollover at 8192 Characters
    uwUSART2TxCntr++;                             //--- Bump the Counter
  };
}

//---------------------------------------------------------------------------------------------
//                     Export String to USART_2 Tx FIFO
//---------------------------------------------------------------------------------------------
void  fnMsgOut_2 (u08 ubOut[])
{
  u16 uwSlen;
  u16 uwPtr;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  uwSlen = strlen (ubOut);

  for (uwPtr = 0; uwPtr < uwSlen; uwPtr++)
  {
    fnByteToFIFO_2 (ubOut[uwPtr]);
  }
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

