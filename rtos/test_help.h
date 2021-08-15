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

  extern  u08 ubSpoFlag;

  extern  u08 ubPulseCntr;                        //--- Number of Sequential Pulses to output

  //--- Set and Clear Generic Port Pin
  void  fnDefinePortPins (u08 ubCpin, u08 ubDpin);

  void  fnSetCpin (void);
  void  fnClrCpin (void);

  void  fnSetDpin (void);
  void  fnClrDpin (void);

  //--- Function Prototypes
  void  fnPulseByteOut (u08 ubPulseByte);
  void  fnPulseWordOut (u16 uwPulseWord);
  void  fnPulseLongOut (u32 ulPulseLong);

  void  fnPulseOut (void);

#endif
