//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                          I2C Interface Functions Processing Code
//                  -----------------------------------------------------
//
//    This code is for use on the STM32F446 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32FXXX Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//
//=============================================================================================

//------------------------------------------------------------------------------------------//
//                       Program Defines and RAM Storage Definitions                        //
//------------------------------------------------------------------------------------------//

//--- Master Mode Set-Up

#ifndef I2C_M_DVR_H
  #define I2C_M_DVR_H

  //--- Start and Stop Command Bits
  #define I2C1_START  I2C1_CR2 |= 0x00002000    //--- Set Start Condition
  #define I2C1_STOP   I2C1_CR2 |= 0x00004000    //--- Set Stop Condition

  #define I2C1_CLR_COUNT  I2C1_CR2 &= 0xFF0000FFF
  #define I2C1_SET_COUNT

  //--- Defined in "commonheader.h"
  //    Defines Data Union of 32 Bytes
  //
  //    union DFLWB32                     //--- 32 Byte Variable
  //    {
  //      dbl   dfFlt[4];                 //--- 4 Double Precision Float
  //      u64   uxBig[4];                 //--- 4 Unsigned 64 Bit Integer
  //      s64   sxBig[4];                 //--- 4 Signed 64 Bit Integer
  //      flt   sfFlt[8];                 //--- 8 Single Precision Floats
  //      u32   ulLong[8];                //--- 8 Unsigned Long
  //      s32   slLong[8];                //--- 8 Signed Long
  //      u16   uwWord[16];               //--- 16 Unsigned Words
  //      s16   swWord[16];               //--- 16 Signed Words
  //      u08   ubByte[32];               //--- 32 Unsigned Bytes
  //      s08   sbByte[32];               //--- 32 Signed Bytes
  //      u08*  ubPtr[8];                 //--- 8 Byte Type General Purpose Pointers
  //      void* vPntr[8];                 //--- 8 Void Type Pointers
  //    };

  //--- Assign a global EEPROM 32 Byte Memory UNION
  extern  union DFLWB32 unEEPROMdata;


  //--- EEprom Write Test Pattern
  extern  const u08 ubTestBlock[32];      // = { 0xA5, 0x5A, 0x3C, 0xC3,
                                          //     0xE1, 0x1E, 0x96, 0x69,
                                          //     0x80, 0x01, 0x40, 0x02,
                                          //     0x20, 0x04, 0x10, 0x08,
                                          //     0xBB, 0x44, 0xDD, 0x22,
                                          //     0x77, 0x88, 0x99, 0x66,
                                          //     0x78, 0x87, 0x11, 0x00,
                                          //     0x55, 0xAA, 0x18, 0x81 };

  //--- Functions for processing Flash memory commands and transfers
  u08     fnInitI2C1_Master (u08 ubSpeed);        //--- Initialize I2C1

  //--- I2C1 Event and Error Functions
  void    fnI2C1_EV_IRQ(void);            // 31 - I2C1 Event                        0x000000BC
  void    fnI2C1_ER_IRQ(void);            // 32 - I2C1 Error                        0x000000C0

  //--- Read a 32 Byte Page
  union   DFLWB32 fnI2C_M_PageRead (u16 uwPageNum);

  //--- Read a random 8 Bit Byte
  u08     fnI2C_M_RandomRead (u16 uwM_ADDS, u16 uwLen);

  //--- Write a 32 Byte Page
  u08     fnI2C_M_PageWrite (u16 uwPageNum, union DFLWB32 unPageData);

  //--- Write a Random Byte
  u08     fnI2C_M_RandomByteWrite (u16 uwM_ADDS, u08 ubData);

  //--- Execute a STOP Condition
  u08     fnDoStop(void);

  //--- Wait for EEPROM Write to finish
  u08     fnWaitOnEEPROMwrite(void);

  //--- EEPROM Test Debug Only
  void    fnEEPROMtest (union DFLWB unTaskData);

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
