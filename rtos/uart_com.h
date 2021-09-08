
//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                        Real Time Operating System Core Programs
//                  -----------------------------------------------------
//
//    This code is for use on the STM32L432 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32     Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//
//=============================================================================================


//---------------------------------------------------------------------------------------------
//                        Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#ifndef USART_H
  #define USART_H

  //-------------------------------------------------------------------------------------------
  //                        USART Peripheral Driver Definitions
  //-------------------------------------------------------------------------------------------
  #define USART_1                                 //--- USART1 = Debug & Monitor Port
  #define BAUDRATE1             115200U           //--- 115200 Baud
  #define USART1_RX_SIZE        1024              //--- Up to 1024 Characters for RX FIFO
  #define USART1_TX_SIZE        1024              //--- Up to 1024 Characters for TX FIFO
  #define USART1_MAX_TX_IN      1022              //--- Up to 1022 Characters ready to go out

  //--- ComData Formatted Communications Message (Sans Headers & LRC)
  struct  RxMsg_1
  {
    u08 ubFC;                                     //--- Function Code
    u08 ubSC;                                     //--- Sub Command or Axis Value
    u08 ubDlen;                                   //--- Number of FLWB Unions  (0 - 8)
    union DFLWB unComData[4];                     //--- Up To 4 unions Available 64 Bits each
  };

  extern    u08   ubTxt[256];                     //--- Generic Message Constructor String
  extern    u08   ubStr[128];                     //--- Sub Constructor String

  //-------------------------------------------------------------------------------------------
  //                         USART Control RAM & ROM definitions
  //-------------------------------------------------------------------------------------------

  //--- USART Channel #1 Definitions
  extern    u16   uwUSART1TxCntr;                 //--- Tx Chr Cntr
  extern    u16   uwUSART1TxIptr;                 //--- Tx In Pointer
  extern    u16   uwUSART1TxOptr;                 //--- Tx Out Pointer
  extern    u08   ubUSART1TxFIFO[USART1_TX_SIZE]; //--- Tx Data FIFO

  extern    u16   uwUSART1RxCntr;                 //--- Rx Chr Cntr
  extern    u16   uwUSART1RxIptr;                 //--- Rx In Pointer
  extern    u16   uwUSART1RxOptr;                 //--- Rx Out Pointer
  extern    u08   ubUSART1RxFIFO[USART1_RX_SIZE]; //--- Rx Data FIFO

  extern    struct RxMsg_1 stUSART1_Rx_Msg;       //--- Current Receive Message Buffer
  extern    struct RxMsg_1 stUSART1_Msg_FIFO[16]; //--- Received Message FIFO

  extern    u16   uwRx1MsgIP;                     //--- Rx Message In Pointer
  extern    u16   uwRx1MsgOP;                     //--- Rx Message Out Pointer
  extern    u16   uwRx1MsgCNT;                    //--- Rx Message Counter Pointer

  extern    u08   ubRxState1;                     //--- Rx State Machine Current State
  extern    u08   ubRxLRC1;                       //--- Current LRC Calculation Value
  extern    u16   uwErrCntr1;                     //--- Number of errors encountered

  extern    u16   uwXmit_1_Count;                 //--- Character Spacing Delay 100uSec
  extern    u16   uwXmit_1_Delay;                 //--- Character Spacing Delay 100uSec

  extern    u16 uwInByteCntr1;
  extern    u16 uwInBytePntr1;

  void  fnSendPacketToHost (u08 ubFC, u08 ubSC, u08 ubDL, union DFLWB unData[4]);
  void  fnRxStateMachine_1 (u08 ubRxD);

  void  fnSendStart (void);
  void  fnSendStop (void);

  void  fnSendEND (void);
  void  fnSendACK (u08 ubFC);
  void  fnSendNAK (u08 ubFC, u08 ubEC);
  void  fnSendERR (u16 uwErrLine, u08 ubFC);
  void  fnProgramLoadRequest (void);
  void  fnSendNextLineRequest (void);

  //--- USART Control Functions
  void  fnInitUSART1 (u32 ulBaud);                //--- Initialize USART1 Communications
  void  fnUSART1_IRQ(void);                       //--- 37 - USART1 General Interrupt
  void  fnUSART1_RxEna (u08 ubOnOff);
  void  fnXmitSvc_1 (void);
  void  fnTxtToFIFO_1 (u08 ubOTxt[]);
  void  fnByteToFIFO_1 (u08 ubByte);
  u16   fnGetNextUSART1 (void);                   //--- Test if a character is Waiting

  //--- Post Processing of UART1 Received Message
  void  fnProcMessage_1 (union DFLWB unData);

  //-------------------------------------------------------------------------------------------
  //            Function Prototypes
  //-------------------------------------------------------------------------------------------

  #define USART_2                                 //--- USART2 = Message Communications Port
  #define BAUDRATE2            115200U            //--- 115200 Baud
  #define USART2_TX_SIZE       0x1000             //--- 4096 Bytes
  #define USART2_RX_SIZE       0x1000             //--- 4096 Bytes
  #define USART2_MAX_TX_IN     4091               //--- Up to 4091 Characters ready to go out

  //--- USART Channel #2 Definitions
  extern    u16   uwUSART2TxCntr;                 //--- Tx Chr Cntr
  extern    u16   uwUSART2TxIptr;                 //--- Tx In Pointer
  extern    u16   uwUSART2TxOptr;                 //--- Tx Out Pointer
  extern    u08   ubUSART2TxFIFO[USART2_TX_SIZE]; //--- Tx Character FIFO

  extern    u16   uwUSART2RxCntr;                 //--- Rx Chr Cntr
  extern    u16   uwUSART2RxIptr;                 //--- Rx In Pointer
  extern    u16   uwUSART2RxOptr;                 //--- Rx Out Pointer
  extern    u08   ubUSART2RxFIFO[USART2_RX_SIZE]; //--- Rx Character FIFO

  extern    u16   uwRxState2;                     //--- Rx State Machine Current State
  extern    u08   ubRxLRC2;                       //--- Current LRC Calculation Value
  extern    u16   uwErrCntr2;                     //--- Number of errors encountered

  extern    u16   uwXmit_2_Count;                 //--- Character Spacing Delay 100uSec
  extern    u16   uwXmit_2_Delay;                 //--- Character Spacing Delay 100uSec

  //--- Service Functions for USART #2
  void  fnInitUSART2Comm (void);
  void  fnInitUSART2 (u32 ulBaud);                //--- Initialize USART2 Communications
  void  fnUSART2_IRQ(void);                       //--- 38 - USART2 General Interrupt
  void  fnUSART2_RxEna (u08 ubOnOff);
  void  fnXmitSvc_2 (void);
  void  fnTxtToFIFO_2 (u08 ubOTxt[]);
  void  fnByteToFIFO_2 (u08 ubChar);
  u16   fnGetNextUSART2 (void);
  void  fnMsgOut_2 (u08 ubOut[]);

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
