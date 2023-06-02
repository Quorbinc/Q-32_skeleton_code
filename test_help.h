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

#ifndef TESTHELP_H
  #define TESTHELP_H

  extern  vu32* Cptr;                             //--- Clock Bit Pointer
  extern  u32 ulCsetMask;                         //--- Clock Bit Mask General
  extern  u32 ulCclrMask;                         //--- Clock Bit Mask General

  extern  vu32* Dptr;                             //--- Data Bit Pointer
  extern  u32 ulDsetMask;                         //--- Data Bit Mask General
  extern  u32 ulDclrMask;                         //--- Data Bit Mask General

  //--- Function Prototypes
  void  fnPulseValueOut ( u08 ubType, u32 ulPVO );
  void  fnPulseNibbleOut (u08 ubPulseNibble);
  void  fnPulseByteOut (u08 ubPulseByte);
  void  fnPulseWordOut (u16 uwPulseWord);
  void  fnPulseLongOut (u32 ulPulseLong);

  u32   fnReadCPUregister (u08 ubRegNum);          //--- Return a CPU Register Value.
  void  fnPulseOut (u08 ubPulseCntr);              //--- Output UpTo 255 Pulses

#endif
