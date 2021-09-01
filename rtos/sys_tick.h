//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                        Pacer Interrupt and Pacer Dependant Tasks
//
//                           Written By:  Sancar James Fredsti
//
//===========================================================================================--

#ifndef PACER_H
  #define PACER_H

  //-------------------------------------------------------------------------------------------
  //                     Program Defines and RAM Storage Definitions
  //-------------------------------------------------------------------------------------------

  extern  u32   ulFastTimeCount[4];               //--- Handy Delay
;                                                 //--- General Delay Timer @ 100 uSec
  extern  u64   uxSysTick;                        //--- Master Tick Timer 2^64 100 uSec Ticks

  extern  u16   uwPacerPhase;                     //--- Pacer Phase Counter
  extern  u16   uwPacerTick;                      //--- Pacer Slow Tick Count
  extern  u16   uwLEDcntr;                        //--- LED On Period
  extern  u16   uwLEDtime;                        //--- LED period time

  //--- NOTE: USART Character Time spacing is defined in "uart_com"

  //-------------------------------------------------------------------------------------------
  //                          Function Prototypes & Definitions
  //    This function is called from the systick Hardware Injterrupt
  //-------------------------------------------------------------------------------------------

  void  fnSysTick (void);                         //--- System SysTick IRQ Handler
  u32   fnReadFastCounter(u08 ubCntrNum);
  void  fnClearFastCounter(u08 ubCntrNum);
  void  fnSetFastCounter(u08 ubCntrNum, u32 ulDownCount);
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