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
    #define EEPROM_ADDS 0xA0                  //--- I2C EEPROM ADDRESS Shifted by 1 already

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

    //--- Assign a global EEPROM 32 Byte Memory UNION for 1 PAGE of EEPROM
    extern  union DFLWB32 unEEPROMpage;


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
    u08     fnInitI2C1_Master_Port (void);
    void    fnI2C1_Master_Ops (u08 ubSpeed);

    //--- I2C1 Event and Error Functions
    //  void    fnI2C1_EV_IRQ(void);            // 31 - I2C1 Event                        0x000000BC
    //  void    fnI2C1_ER_IRQ(void);            // 32 - I2C1 Error                        0x000000C0

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
