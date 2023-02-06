//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                       I2C EEPROM Interface Functions Processing Code
//                       ----------------------------------------------
//
//         This code is for use on the QMX_32 (STM32L432) Series of Micro Controllers
//
//                             Written By:  Sancar James Fredsti
//                                   (C) 2022 QUORB Inc.
//=============================================================================================

#ifndef EEPROM_H
  #define EEPROM_H                                //--- Enable EEPROM Driver

  //-------------------------------------------------------------------------------------------
  #define EEPROM_PAGE_SIZE 32               //--- 32 Bytes / EEPROM Page Count in bytes
    #ifndef I2C1_H  #define I2C1_H          //--- EEPROM MUST USE I2C1 Driver

  //--- Set number of pages available at each density
  //    UnComment the EEPROM Size in bits

  //--- EEPROM SIZE   1 Kbit
``//``` #define EEPROM_BYTES        128
  //    #define EEPROM_PAGES          4     //--- Number of Pages in EEPROM for 1Kb

  //--- EEPROM SIZE   2 Kbit
``//``` #define EEPROM_BYTES        256
  //    #define EEPROM_PAGES          8     //--- Number of Pages in EEPROM for 1Kb

  //--- EEPROM SIZE   4 Kbit
``//``` #define EEPROM_BYTES        512
  //    #define EEPROM_PAGES         16     //--- Number of Pages in EEPROM for 1Kb

  //--- EEPROM SIZE   8 Kbit
``//``` #define EEPROM_BYTES       1024
  //    #define EEPROM_PAGES         32     //--- Number of Pages in EEPROM for 1Kb

  //--- EEPROM SIZE   16 Kbit
``//``` #define EEPROM_BYTES       2048
  //    #define EEPROM_PAGES         64     //--- Number of Pages in EEPROM for 1Kb

  //--- EEPROM SIZE   32K bit
``//``` #define EEPROM_BYTES       4096
  //    #define EEPROM_PAGES        128     //--- Number of Pages in EEPROM for 1Kb

  //--- EEPROM SIZE   64K bit
``//``` #define EEPROM_BYTES       8192
  //    #define EEPROM_PAGES        256     //--- Number of Pages in EEPROM for 1Kb

  //--- EEPROM SIZE   128K bit
``//``` #define EEPROM_BYTES      16384
  //    #define EEPROM_PAGES        512     //--- Number of Pages in EEPROM for 1Kb

  //--- EEPROM SIZE   256K bit
``//``` #define EEPROM_BYTES      32768
  //    #define EEPROM_PAGES       1024     //--- Number of Pages in EEPROM for 1Kb

  //--- EEPROM SIZE   512K it
``//``` #define EEPROM_BYTES      65536
  //    #define EEPROM_PAGES       2048     //--- Number of Pages in EEPROM for 1Kb

  //--- EEPROM SIZE   1M bit
``//``` #define EEPROM_BYTES     131072
  //    #define EEPROM_PAGES       4096     //--- Number of Pages in EEPROM for 1Kb

  #define EEPROM_PAGES            EEPROM_BYTES / 32   //--- 32 bYTES / pAGE
  #define EEPROM_ADDS 0xA0                  //--- I2C EEPROM ADDRESS Shifted by 1 already
                                            //    This Address is the actual ADDRESS Value

  struct EEPROM_Adds
  {
    u32 ulByteAddr;
    u16 uwPageNum;
    u16 uwBufferOffset;
  };



  //-------------------------------------------------------------------------------------------
  //    All EEPROM transactions are performed on a "32 Byte Page Basis
  //-------------------------------------------------------------------------------------------

  //--- Calculate Page Address from Byte Address
  u16   fnCalcPageAdds (u32 ulByteAdds);

  //--- Read Random Values from EEPROM Default = 32 Bit Read
  u08   fnReadByte (u32 Address);           //--- Read a single random Byte
  u16   fnReadWord (u32 Address);           //--- Read a single random Word
  u32   fnReadLong (u32 Address);           //--- Read a single random Long
  u64   fnReadBig  (u32 Address);           //--- Read a single random Big
  flt   fnReadFloat (u32 Address);          //--- Read a single random Float
  u08   fnReadEEPROMpage (u32 ulPage);


  u08   fnWriteByte   (u32 Address, u08 ubByte);
  u08   fnWriteWord   (u32 Address, u16 uwWord);
  u08   fnWriteLong   (u32 Address, u32 ulLong);
  u08   fnWriteFloat  (u32 Address, flt sfFloat);
  u08   fnWriteBytePage   (u32 Address, u08 ubByte[32]);

  u08   fnEEPROM_Wait (void);

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
