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
  #define EEPROM_H

  //-------------------------------------------------------------------------------------------
  #define EEPROM_PAGE_SIZE 32               //--- 32 Bytes / EEPROM Page Count in bytes

  //  Uncomment Size of EEPROM Supplied on Board in Bits
  //  -----------------------------------------------------------------------
  //  #define EEPROM_SIZE 1024                    //--- 1K Bits
  //  #define EEPROM_SIZE 2048                    //--- 2K Bits
  //  #define EEPROM_SIZE 4096                    //--- 4K Bits
  //  #define EEPROM_SIZE 8192                    //--- 8K Bits
  //  #define EEPROM_SIZE 16384                   //--- 16K Bits
  //  #define EEPROM_SIZE 32768                   //--- 32K Bits
  //  #define EEPROM_SIZE 65536                   //--- 64K Bits = Default Size = 65536
  //  #define EEPROM_SIZE 131072                  //--- 128K Bits
  //  #define EEPROM_SIZE 262144                  //--- 256K Bits
  //  #define EEPROM_SIZE 524288                  //--- 512K Bits

  //  define EEPROM_Size in bits
  //

  //--- Set number of pages available at each density
  //    UnComment the EEPROM Size

  //--- Depending on EEPROM SIZE 1Kb
  //    #define EEPROM_PAGE_COUNT = 128     //--- Number of Pages in EEPROM for 1Kb

  //--- Depending on EEPROM SIZE 2Kb
  //    #define EEPROM_PAGE_COUNT = 256     //--- Number of Pages in EEPROM for 2Kb

  //--- Depending on EEPROM SIZE 4Kb
  //    #define EEPROM_PAGE_COUNT = 512     //--- Number of Pages in EEPROM for  4Kb

  //--- Depending on EEPROM SIZE 8Kb
  //    #define EEPROM_PAGE_COUNT = 1024    //--- Number of Pages in EEPROM for  8Kb

  //--- Depending on EEPROM SIZE 16Kb
  //    #define EEPROM_PAGE_COUNT = 2048    //--- Number of Pages in EEPROM for 16Kb

  //--- Depending on EEPROM SIZE 32Kb
  //    #define EEPROM_PAGE_COUNT = 4096    //--- Number of Pages in EEPROM for 32Kb

  //--- Depending on EEPROM SIZE 64Kb
  //--- #define EEPROM_PAGE_COUNT = 256           //--- Number of Pages in EEPROM for 64Kb

  //--- Depending on EEPROM SIZE 128Kb
  //    #define EEPROM_PAGE_COUNT = 512     //--- Number of Pages in EEPROM for 128Kb

  //--- Depending on EEPROM SIZE 512Kb
  //    #define EEPROM_PAGE_COUNT = 2048    //--- Number of Pages in EEPROM for 512Kb

  #define EEPROM_BYTE_COUNT EEPROM_SIZE / 8;
  #define EEPROM_PAGE_COUNT 256             //--- Number of Byte  Pages in EEPROM for 64Kb

  #define EEPROM_ADDS 0xA0                  //--- I2C EEPROM ADDRESS Shifted by 1 already

  extern u08   ubEEPROM_Count;

  //--- Read Random Values from EEPROM Default = 32 Bit Read
  u08   fnReadByte (u32 Address);           //--- Read a single random Byte
  u16   fnReadWord (u32 Address);           //--- Read a single random Word
  u32   fnReadLong (u32 Address);           //--- Read a single random Long
  u64   fnReadBig  (u32 Address);           //--- Read a single random Big
  flt   fnReadFloat (u32 Address);          //--- Read a single random Float

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
