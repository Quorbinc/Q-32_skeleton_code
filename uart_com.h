
//=============================================================================================
//                                Fredsti Industries,  Ltd.
//                                -------------------------
//
//                      USART and Communications Including USB C2102
//
//                           Written By:  Sancar James Fredsti
//
//                                Created: 01 August 2007
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
  #define USART1_FLAG
  #define BAUDRATE1             115200U           //--- 115200 Baud
  #define USART1_RX_SIZE        1024              //--- Up to 1024 Characters for RX FIFO
  #define USART1_TX_SIZE        1024              //--- Up to 1024 Characters for TX FIFO
  #define USART1_MAX_TX_IN      1022              //--- Up to 1022 Characters ready to go out

  extern    u08   ubTxt[1024];                    //--- Generic Message Constructor String
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

  extern    u16   uwXmit_1_Count;                 //--- Character Spacing Delay 100uSec
  extern    u16   uwXmit_1_Delay;                 //--- Character Spacing Delay 100uSec

  //--- USART Control Functions
  void  fnInitUSART1 (u32 ulBaud);                //--- Initialize USART1 Communications
  void  fnUSART1_IRQ(void);                       //--- #37 - USART1 General Interrupt
  void  fnUSART1_RxEna (u08 ubOnOff);             //--- Enable / Disable USART
  void  fnXmitSvc_1 (void);                       //--- Send 1 Character OUT via SysTick
  void  fnTxtToFIFO_1 (u08 ubOut[]);              //--- Place String into TX FIFO
  void  fnByteToFIFO_1 (u08 ubByte);              //--- Place 1 Byte into TX FIFO
  void  fnMsgOut_1 (u08 ubOut[]);                 //--- Output Message String
  u16   fnGetNextUSART1 (void);                   //--- Test if a character is Waiting
                                                  //    Returns (0) if Nothing
                                                  //    or (0x80XX) byte is Waiting in RX FIFO

  //-------------------------------------------------------------------------------------------
  //            Function Prototypes
  //-------------------------------------------------------------------------------------------

  #define USART2_FLAG                             //--- USART2 = Message Communications Port
  #define BAUDRATE2            115200U            //--- 115200 Baud
  #define USART2_TX_SIZE       1024               //--- 1024 Bytes
  #define USART2_RX_SIZE       1024               //--- 1024 Bytes
  #define USART2_MAX_TX_IN     1022               //--- Up to 1022 Characters ready to go out

  //--- USART Channel #2 Definitions
  extern    u16   uwUSART2TxCntr;                 //--- Tx Chr Cntr
  extern    u16   uwUSART2TxIptr;                 //--- Tx In Pointer
  extern    u16   uwUSART2TxOptr;                 //--- Tx Out Pointer
  extern    u08   ubUSART2TxFIFO[USART2_TX_SIZE]; //--- Tx Character FIFO

  extern    u16   uwUSART2RxCntr;                 //--- Rx Chr Cntr
  extern    u16   uwUSART2RxIptr;                 //--- Rx In Pointer
  extern    u16   uwUSART2RxOptr;                 //--- Rx Out Pointer
  extern    u08   ubUSART2RxFIFO[USART2_RX_SIZE]; //--- Rx Character FIFO

  extern    u16   uwXmit_2_Count;                 //--- Character Spacing Delay 100uSec
  extern    u16   uwXmit_2_Delay;                 //--- Character Spacing Delay 100uSec

  //--- Service Functions for USART #2
  void  fnInitUSART2 (u32 ulBaud);                //--- Initialize USART2 Communications
  void  fnUSART2_IRQ(void);                       //--- 38 - USART2 General Interrupt
  void  fnUSART2_RxEna (u08 ubOnOff);
  void  fnXmitSvc_2 (void);
  void  fnTxtToFIFO_2 (u08 ubOTxt[]);
  void  fnByteToFIFO_2 (u08 ubChar);
  u16   fnGetNextUSART2 (void);
  void  fnStringOut_2 (u08 ubOut[]);
  void  fnArrayOut_2 (u08 ubOut[], u16 uwArraySize);
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
