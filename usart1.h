
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

#ifndef USART1_H
  #define USART1_H

  //-------------------------------------------------------------------------------------------
  //                        USART Peripheral Driver Definitions
  //-------------------------------------------------------------------------------------------
  #define USART1_RX_SIZE        1024              //--- Up to 1024 Characters for RX FIFO
  #define USART1_TX_SIZE        256               //--- Up to 1024 Characters for TX FIFO
  #define USART1_MAX_TX_IN      254               //--- Up to 1022 Characters ready to go out

  extern    u08   ubU1Txt[1024];                  //--- Generic Message Constructor String
  extern    u08   ubU1Str[128];                   //--- Sub Constructor String

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
  void  fnXmitSvc_1 (void);                       //--- Send 1 Character OUT via SysTick
  u08   fnByteToFIFO_1 (u08 ubByte);              //--- Place 1 Byte into TX FIFO
  u08   fnTxtToFIFO_1 (u08 ubOut[]);              //--- Place String into TX FIFO
  u16   fnGetNextUSART1 (void);                   //--- Test if a character is Waiting
                                                  //    Returns (0) if Nothing
                                                  //    or (0x80XX) byte is Waiting in RX FIFO

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
