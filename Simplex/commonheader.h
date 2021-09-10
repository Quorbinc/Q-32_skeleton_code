//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                  Base Processing code for Modules using STM32F05X Proc
//                  -----------------------------------------------------
//
//    This code is for use on the STM32F446 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32FXXX Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//
//=============================================================================================

#ifndef COMMONHEADER_H
  #define COMMONHEADER_H

  //------------------------------------------------------------------------------------------
  //  Codeing Definitions and pre naming convention
  //------------------------------------------------------------------------------------------
  //
  //  All Variable Names begin with a 2 or three lower case letter sequence which defines the
  //  variable type.
  //
  //  Unsigned Char                     = ch      chExample
  //  Unsigned Byte and Char Types      = ub      ubExample
  //  Signed Byte and Char Types        = sb      sbExample
  //  Unsigned Integer/Word Types       = uw      uwExample
  //  Signed Integer/Word Types         = sw      swExample
  //  Unsigned Long (32bit) Types       = ul      ulExample
  //  Signed Long (32bit) Types         = sl      slExample
  //  Unsigned Long Long (64bit) Types  = ux      uxExample
  //  Signed Long Long (64bit) Types    = sx      sxExample
  //  Signed Long Long (64bit) Types    = sd      sdExample
  //  Single Precision Float            = sf      sfExample
  //  Double Precision Float            = df      dfExample
  //  Structures                        = st      stExample.uwData
  //  Unions                            = un      unExample.uwData
  //  Functions                         = fn      fnExample ()
  //
  //------------------------------------------------------------------------------------------

  //--- Typedefs for software           Type    PreName Notation
  //--- Function:                               //--- fn

  typedef   unsigned char               u08;    //--- ub
  typedef   unsigned short              u16;    //--- uw
  typedef   unsigned long               u32;    //--- ul
  typedef   unsigned long long          u64;    //--- ux

  typedef   signed char                 s08;    //--- sb
  typedef   signed short                s16;    //--- sw
  typedef   signed long                 s32;    //--- sl
  typedef   signed long long            s64;    //--- sx

  typedef   float                       flt;    //--- sf
  typedef   double                      dbl;    //--- df

  //--- Typedefs for I/O & Volatile Types

  typedef   volatile unsigned char      vu08;
  typedef   volatile unsigned short     vu16;
  typedef   volatile unsigned long      vu32;
  typedef   volatile unsigned long long vu64;

  typedef   volatile signed char        vs08;
  typedef   volatile signed short       vs16;
  typedef   volatile signed long        vs32;
  typedef   volatile signed long long   vs64;

  typedef   volatile float              vsf;
  typedef   volatile double             vdf;


  //--- Max and Min values for integer variable Types
  #define u08_MAX    ((u08)255)
  #define s08_MAX    ((s08)127)
  #define s08_MIN    ((s08)-128)

  #define u16_MAX    ((u16)65535)
  #define s16_MAX    ((s16)32767)
  #define s16_MIN    ((s16)-32768)

  #define u32_MAX    ((u32)4294967295)
  #define s32_MAX    ((s32)2147483647)
  #define s32_MIN    ((s32)-2147483648)

  #define u64_MAX    ((u64)18446744073709551616)
  #define s64_MAX    ((s64)9223372036854775807)
  #define s64_MIN    ((s64)-9223372036854775808)

  #define __ASM       asm                         //--- asm keyword for gcc
  #define __STATIC    static                      //--- inline Static
  #define __INLINE    inline                      //--- inline keyword for gcc
  #define __STATIC_INLINE  static inline

  //--- General Interrupt Enable and Disable
  #define GIE       asm("cpsie   i")              //--- Global Interrupt Enable
  #define GID       asm("cpsid   i")              //--- Global Interrupt Disable

  //--- A series of NOP defines for wasting time
  #define nop       asm ("nop\n\t" ::)

  #define nop2      asm ("nop\n\t" "nop\n\t" ::)

  #define nop4      asm ("nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" ::)

  #define nop8      asm ("nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t"::)

  #define nop12     asm ("nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t"::)

  #define nop16     asm ("nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t"::)

  #define nop24     asm ("nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t"::)

  #define nop32     asm ("nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t"::)

  #define nop48     asm ("nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t"::)

  #define nop100    asm ("nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t" \
                         "nop\n\t" "nop\n\t" "nop\n\t" "nop\n\t"::)

  //--- Software Interrupt Service Call
  #define SVC_CALL  asm ("SVC #0x00\n\t" ::)

  //--- DSB & ISB
  #define __DSB     asm ( "DSB\n\t" ::)

  #define __ISB     asm ( "ISB\n\t" ::)

  //--- Floating Point Hardware Enable
  #define FPU_ENA   asm ( "LDR.W R0, = 0xE000ED88\n\t" \
                          "LDR R1, [R0]\n\t" \
                          "ORR R1, #0x00F00000\n\t" \
                          "STR R1, [R0]\n\t" \
                          "DSB\n\t" \
                          "ISB\n\t" ::)

  //--- These structures & unions are useful for breaking up and assembling different
  //    data types.

  //--- 16 Bit Variable union
  union WB
  {
    u16 uwWord;
    s16 swWord;
    u08 ubByte[2];
    s08 sbByte[2];
  };

  //--- 32 Bit Multi Number Type unions
  union   FLWB          //--- 4 Bytes of Pass Data
  {
    flt   sfFlt;
    u32   ulLong;
    s32   slLong;
    u16   uwWord[2];
    s16   swWord[2];
    u08   ubByte[4];
    s08   sbByte[4];
  };

  //--- Double Float Long Word Byte Union  8 Bytes in length
  //--- 64 Bit Variable integer union
  union DFLWB             //--- 8 Bytes Binary / Integer Storage
  {
    dbl dfFlt;            //--- Double Precision Float
    u64 uxBig;            //--- Unsigned 64 Bit Integer
    s64 sxBig;            //--- Signed 64 Bit Integer
    flt sfFlt[2];         //--- 2 Single Precision Floats
    u32 ulLong[2];        //--- 2 Unsigned Long
    s32 slLong[2];        //--- 2 Signed Long
    u16 uwWord[4];        //--- 4 Unsigned Words
    s16 swWord[4];        //--- 4 Signed Words
    u08 ubByte[8];        //--- 8 Unsigned Bytes
    s08 sbByte[8];        //--- 8 Signed Bytes
  };

  //--- Double Float Long Word Byte Union
  //--- 32 Byte (256 Bit] Variable union
  union DFLWB32           //--- 32 Bytes Variable
  {
    dbl   dfFlt[4];       //--- 4 Double Precision Float            8 Bytes / Value
    u64   uxBig[4];       //--- 4 Unsigned 64 Bit Integer           8 Bytes / Value
    s64   sxBig[4];       //--- 4 Signed 64 Bit Integer             8 Bytes / Value
    flt   sfFlt[8];       //--- 8 Single Precision Floats           4 Bytes / Value
    u32   ulLong[8];      //--- 8 Unsigned Long                     4 Bytes / Value
    s32   slLong[8];      //--- 8 Signed Long                       4 Bytes / Value
    u08*  ubPtr[8];       //--- 8 General Purpose Pointers (byte]   4 Bytes / Value
    u16   uwWord[16];     //--- 16 Unsigned Words                   2 Bytes / Value
    s16   swWord[16];     //--- 16 Signed Words                     2 Bytes / Value
    u08   ubByte[32];     //--- 32 Unsigned Bytes                   1 Bytes / Value
    s08   sbByte[32];     //--- 32 Signed Bytes                     1 Bytes / Value
  };

  //--- Double Float Long Word Byte Union
  //--- 256 Byte Variable union
  union DFLWB256          //--- 256 Bytes Binary / Integer Storage
  {
    dbl dfFlt[32];        //--- Double Precision Float
    u64 uxBig[32];        //--- Unsigned 64 Bit Integer
    s64 sxBig[32];        //--- Signed 64 Bit Integer
    flt sfFlt[64];        //--- 2 Single Precision Floats
    u32 ulLong[64];       //--- 2 Unsigned Long
    s32 slLong[64];       //--- 2 Signed Long
    u16 uwWord[128];      //--- 4 Unsigned Words
    s16 swWord[128];      //--- 4 Signed Words
    u08 ubByte[256];      //--- 8 Unsigned Bytes
    s08 sbByte[256];      //--- 8 Signed Bytes
  };

  //--- 256 Byte, 128 Word, 64 Long, 64 Float
  union BWLRec
  {
    flt   sfFlt[64];
    u32   ulLong[64];
    s32   slLong[64];
    u16   uwWord[128];
    s16   swWord[128];
    u08   ubByte[256];
    s08   sbByte[256];
  };

  //--- Clock Time Structure ---//
  struct TimeDate
  {
    u08   ubYrs;                                  //--- Year 00-99
    u08   ubMth;                                  //--- Month 01-12
    u08   ubDay;                                  //--- Date 01-31
    u08   ubHrs;                                  //--- Hour 00-23
    u08   ubMin;                                  //--- Minute 00-59
    u08   ubSec;                                  //--- Second 00-59
    u16   uwMsec;                                 //--- Milli Seconds
    u32   ulNanoSec;                              //--- Nano Seconds
  };

  //-------------------------------------------------------------------------------------------
  //    Set and or Clear bit ad system address
  //    --------------------------------------
  //    Adds = Memory / I/O System Address
  //    Bit = Bit number (0 - 31)
  //-------------------------------------------------------------------------------------------

  #define SET_BIT(Adds, Bit)  ((Adds) |= (0x00000001 << (Bit)))
  #define CLR_BIT(Adds, Bit)  ((Adds) &= ~(0x00000001 << (Bit)))

  #define SET_BITS(Adds, Bits)  ((Adds) |= (Bits))
  #define CLR_BITS(Adds, Bits)  ((Adds) &= ~(Bits))

  //------------------------------------------------------------------------------------------
  //  Single I/O Port Toggeling
  //------------------------------------------------------------------------------------------

  //--- Long value for Sets or Clears GPIO Bit
  //--- GPIO SET Bits = 0x....SSSS       //--- Use Lower Word of Long for Set
  //--- GPIO CLR Bits = 0xCCCC....       //--- Use Upper Word of Long for Clear

  #define SET_PA00  GPIOA_BSRR = (u32) 0x00000001
  #define CLR_PA00  GPIOA_BSRR = (u32) 0x00010000

  #define SET_PA01  GPIOA_BSRR = (u32) 0x00000002
  #define CLR_PA01  GPIOA_BSRR = (u32) 0x00020000

  #define SET_PA02  GPIOA_BSRR = (u32) 0x00000004
  #define CLR_PA02  GPIOA_BSRR = (u32) 0x00040000

  #define SET_PA03  GPIOA_BSRR = (u32) 0x00000008
  #define CLR_PA03  GPIOA_BSRR = (u32) 0x00080000

  #define SET_PA04  GPIOA_BSRR = (u32) 0x00000010
  #define CLR_PA04  GPIOA_BSRR = (u32) 0x00100000

  #define SET_PA05  GPIOA_BSRR = (u32) 0x00000020
  #define CLR_PA05  GPIOA_BSRR = (u32) 0x00200000

  #define SET_PA06  GPIOA_BSRR = (u32) 0x00000040
  #define CLR_PA06  GPIOA_BSRR = (u32) 0x00400000

  #define SET_PA07  GPIOA_BSRR = (u32) 0x00000080
  #define CLR_PA07  GPIOA_BSRR = (u32) 0x00800000

  #define SET_PA08  GPIOA_BSRR = (u32) 0x00000100
  #define CLR_PA08  GPIOA_BSRR = (u32) 0x01000000

  #define SET_PA09  GPIOA_BSRR = (u32) 0x00000200
  #define CLR_PA09  GPIOA_BSRR = (u32) 0x02000000

  #define SET_PA10  GPIOA_BSRR = (u32) 0x00000400
  #define CLR_PA10  GPIOA_BSRR = (u32) 0x04000000

  #define SET_PA11  GPIOA_BSRR = (u32) 0x00000800
  #define CLR_PA11  GPIOA_BSRR = (u32) 0x08000000

  #define SET_PA12  GPIOA_BSRR = (u32) 0x00001000
  #define CLR_PA12  GPIOA_BSRR = (u32) 0x10000000

  #define SET_PA13  GPIOA_BSRR = (u32) 0x00002000
  #define CLR_PA13  GPIOA_BSRR = (u32) 0x20000000

  #define SET_PA14  GPIOA_BSRR = (u32) 0x00004000
  #define CLR_PA14  GPIOA_BSRR = (u32) 0x40000000

  #define SET_PA15  GPIOA_BSRR = (u32) 0x00008000
  #define CLR_PA15  GPIOA_BSRR = (u32) 0x80000000

  #define SET_PB00  GPIOB_BSRR = (u32) 0x00000001
  #define CLR_PB00  GPIOB_BSRR = (u32) 0x00010000

  #define SET_PB01  GPIOB_BSRR = (u32) 0x00000002
  #define CLR_PB01  GPIOB_BSRR = (u32) 0x00020000

  #define SET_PB02  GPIOB_BSRR = (u32) 0x00000004
  #define CLR_PB02  GPIOB_BSRR = (u32) 0x00040000

  #define SET_PB03  GPIOB_BSRR = (u32) 0x00000008
  #define CLR_PB03  GPIOB_BSRR = (u32) 0x00080000

  #define SET_PB04  GPIOB_BSRR = (u32) 0x00000010
  #define CLR_PB04  GPIOB_BSRR = (u32) 0x00100000

  #define SET_PB05  GPIOB_BSRR = (u32) 0x00000020
  #define CLR_PB05  GPIOB_BSRR = (u32) 0x00200000

  #define SET_PB06  GPIOB_BSRR = (u32) 0x00000040
  #define CLR_PB06  GPIOB_BSRR = (u32) 0x00400000

  #define SET_PB07  GPIOB_BSRR = (u32) 0x00000080
  #define CLR_PB07  GPIOB_BSRR = (u32) 0x00800000

  #define SET_PB08  GPIOB_BSRR = (u32) 0x00000100
  #define CLR_PB08  GPIOB_BSRR = (u32) 0x01000000

  #define SET_PB09  GPIOB_BSRR = (u32) 0x00000200
  #define CLR_PB09  GPIOB_BSRR = (u32) 0x02000000

  #define SET_PB10  GPIOB_BSRR = (u32) 0x00000400
  #define CLR_PB10  GPIOB_BSRR = (u32) 0x04000000

  #define SET_PB11  GPIOB_BSRR = (u32) 0x00000800
  #define CLR_PB11  GPIOB_BSRR = (u32) 0x08000000

  #define SET_PB12  GPIOB_BSRR = (u32) 0x00001000
  #define CLR_PB12  GPIOB_BSRR = (u32) 0x10000000

  #define SET_PB13  GPIOB_BSRR = (u32) 0x00002000
  #define CLR_PB13  GPIOB_BSRR = (u32) 0x20000000

  #define SET_PB14  GPIOB_BSRR = (u32) 0x00004000
  #define CLR_PB14  GPIOB_BSRR = (u32) 0x40000000

  #define SET_PB15  GPIOB_BSRR = (u32) 0x00008000
  #define CLR_PB15  GPIOB_BSRR = (u32) 0x80000000

  #define SET_PC00  GPIOC_BSRR = (u32) 0x00000001
  #define CLR_PC00  GPIOC_BSRR = (u32) 0x00010000

  #define SET_PC01  GPIOC_BSRR = (u32) 0x00000002
  #define CLR_PC01  GPIOC_BSRR = (u32) 0x00020000

  #define SET_PC02  GPIOC_BSRR = (u32) 0x00000004
  #define CLR_PC02  GPIOC_BSRR = (u32) 0x00040000

  #define SET_PC03  GPIOC_BSRR = (u32) 0x00000008
  #define CLR_PC03  GPIOC_BSRR = (u32) 0x00080000

  #define SET_PC04  GPIOC_BSRR = (u32) 0x00000010
  #define CLR_PC04  GPIOC_BSRR = (u32) 0x00100000

  #define SET_PC05  GPIOC_BSRR = (u32) 0x00000020
  #define CLR_PC05  GPIOC_BSRR = (u32) 0x00200000

  #define SET_PC06  GPIOC_BSRR = (u32) 0x00000040
  #define CLR_PC06  GPIOC_BSRR = (u32) 0x00400000

  #define SET_PC07  GPIOC_BSRR = (u32) 0x00000080
  #define CLR_PC07  GPIOC_BSRR = (u32) 0x00800000

  #define SET_PC08  GPIOC_BSRR = (u32) 0x00000100
  #define CLR_PC08  GPIOC_BSRR = (u32) 0x01000000

  #define SET_PC09  GPIOC_BSRR = (u32) 0x00000200
  #define CLR_PC09  GPIOC_BSRR = (u32) 0x02000000

  #define SET_PC10  GPIOC_BSRR = (u32) 0x00000400
  #define CLR_PC10  GPIOC_BSRR = (u32) 0x04000000

  #define SET_PC11  GPIOC_BSRR = (u32) 0x00000800
  #define CLR_PC11  GPIOC_BSRR = (u32) 0x08000000

  #define SET_PC12  GPIOC_BSRR = (u32) 0x00001000
  #define CLR_PC12  GPIOC_BSRR = (u32) 0x10000000

  #define SET_PC13  GPIOC_BSRR = (u32) 0x00002000
  #define CLR_PC13  GPIOC_BSRR = (u32) 0x20000000

  #define SET_PC14  GPIOC_BSRR = (u32) 0x00004000
  #define CLR_PC14  GPIOC_BSRR = (u32) 0x40000000

  #define SET_PC15  GPIOC_BSRR = (u32) 0x00008000
  #define CLR_PC15  GPIOC_BSRR = (u32) 0x80000000

  //-------------------------------------------------------------------------------------------
  //    Input and Test Specific Logical Port Pins
  //-------------------------------------------------------------------------------------------

  #define TST_PA00  (GPIOA_IDR & 0x0001)
  #define TST_PA01  (GPIOA_IDR & 0x0002)
  #define TST_PA02  (GPIOA_IDR & 0x0004)
  #define TST_PA03  (GPIOA_IDR & 0x0008)
  #define TST_PA04  (GPIOA_IDR & 0x0010)
  #define TST_PA05  (GPIOA_IDR & 0x0020)
  #define TST_PA06  (GPIOA_IDR & 0x0040)
  #define TST_PA07  (GPIOA_IDR & 0x0080)
  #define TST_PA08  (GPIOA_IDR & 0x0100)
  #define TST_PA09  (GPIOA_IDR & 0x0200)
  #define TST_PA10  (GPIOA_IDR & 0x0400)
  #define TST_PA11  (GPIOA_IDR & 0x0800)
  #define TST_PA12  (GPIOA_IDR & 0x1000)
  #define TST_PA13  (GPIOA_IDR & 0x2000)
  #define TST_PA14  (GPIOA_IDR & 0x4000)
  #define TST_PA15  (GPIOA_IDR & 0x8000)

  #define TST_PB00  (GPIOB_IDR & 0x0001)
  #define TST_PB01  (GPIOB_IDR & 0x0002)
  #define TST_PB02  (GPIOB_IDR & 0x0004)
  #define TST_PB03  (GPIOB_IDR & 0x0008)
  #define TST_PB04  (GPIOB_IDR & 0x0010)
  #define TST_PB05  (GPIOB_IDR & 0x0020)
  #define TST_PB06  (GPIOB_IDR & 0x0040)
  #define TST_PB07  (GPIOB_IDR & 0x0080)
  #define TST_PB08  (GPIOB_IDR & 0x0100)
  #define TST_PB09  (GPIOB_IDR & 0x0200)
  #define TST_PB10  (GPIOB_IDR & 0x0400)
  #define TST_PB11  (GPIOB_IDR & 0x0800)
  #define TST_PB12  (GPIOB_IDR & 0x1000)
  #define TST_PB13  (GPIOB_IDR & 0x2000)
  #define TST_PB14  (GPIOB_IDR & 0x4000)
  #define TST_PB15  (GPIOB_IDR & 0x8000)

  #define TST_PC00  (GPIOC_IDR & 0x0001)
  #define TST_PC01  (GPIOC_IDR & 0x0002)
  #define TST_PC02  (GPIOC_IDR & 0x0004)
  #define TST_PC03  (GPIOC_IDR & 0x0008)
  #define TST_PC04  (GPIOC_IDR & 0x0010)
  #define TST_PC05  (GPIOC_IDR & 0x0020)
  #define TST_PC06  (GPIOC_IDR & 0x0040)
  #define TST_PC07  (GPIOC_IDR & 0x0080)
  #define TST_PC08  (GPIOC_IDR & 0x0100)
  #define TST_PC09  (GPIOC_IDR & 0x0200)
  #define TST_PC10  (GPIOC_IDR & 0x0400)
  #define TST_PC11  (GPIOC_IDR & 0x0800)
  #define TST_PC12  (GPIOC_IDR & 0x1000)
  #define TST_PC13  (GPIOC_IDR & 0x2000)
  #define TST_PC14  (GPIOC_IDR & 0x4000)
  #define TST_PC15  (GPIOC_IDR & 0x8000)


  //--- Handy Dandy General Definitions
  #define   HIGH    1
  #define   LOW     0

  #define   TRUE    1
  #define   FALSE   0

  #define   True    1
  #define   False   0

  #define   true    1
  #define   false   0

  #define   ON      1
  #define   OFF     0

  #define   SET     1
  #define   CLR     0

  #define   YES     1
  #define   NO      0
  #define   MAYBE   -1

  //  #define   NULL    (0)       //--- Basic Null
  #define   ZERO    0

  //--- Non-printing ASCII codes
  #define   NUL     (0x00)    //--- Null
  #define   SOH     (0x01)    //--- start of heading
  #define   STX     (0x02)    //--- start of text
  #define   ETX     (0x03)    //--- end of text
  #define   EOT     (0x04)    //--- end of transmission
  #define   ENQ     (0x05)    //--- enquiry
  #define   ACK     (0x06)    //--- acknowledge
  #define   BEL     (0x07)    //--- bell
  #define   BS      (0x08)    //--- backspace
  #define   HT      (0x09)    //--- horizontal tab
  #define   LF      (0x0A)    //--- NL linefeed, new line
  #define   VT      (0x0B)    //--- vertical tab
  #define   FF      (0x0C)    //--- NP form feed, new page
  #define   CR      (0x0D)    //--- carriage return
  #define   SO      (0x0E)    //--- shift out
  #define   SI      (0x0F)    //--- shift in
  #define   DLE     (0x10)    //--- datalink escape
  #define   DC1     (0x11)    //--- device control 1
  #define   DC2     (0x12)    //--- device control 2
  #define   DC3     (0x13)    //--- device control 3
  #define   DC4     (0x14)    //--- device control 4
  #define   NAK     (0x15)    //--- negative acknowledge
  #define   SYN     (0x16)    //--- synchronous idle
  #define   ETB     (0x17)    //--- end of transmission block
  #define   CAN     (0x18)    //--- cancel
  #define   EM      (0x19)    //--- end of medium
  #define   SUB     (0x1A)    //--- substitute
  #define   ESC     (0x1B)    //--- escape
  #define   FS      (0x1C)    //--- file separator
  #define   GS      (0x1D)    //--- group separator
  #define   RS      (0x1E)    //--- record separator
  #define   US      (0x1F)    //--- unit separator
  #define   DEL     (0x7F)    //--- delete

  //--- CORTEX MACROS FOR GCC
  void __WFI(void);
  void __WFE(void);
  void __SEV(void);
//  void __ISB(void);
//  void __DSB(void);
  void __DMB(void);
  void __SVC(void);
  u32  __MRS_CONTROL(void);
  void __MSR_CONTROL(u32 Control);
  u32  __MRS_PSP(void);
  void __MSR_PSP(u32 TopOfProcessStack);
  u32  __MRS_MSP(void);
  void __MSR_MSP(u32 TopOfMainStack);
  void __SETPRIMASK(void);
  void __RESETPRIMASK(void);
  void __SETFAULTMASK(void);
  void __RESETFAULTMASK(void);
  void __BASEPRICONFIG(u32 NewPriority);
  u32  __GetBASEPRI(void);
  u16  __REV_HalfWord(u16 Data);
  u32  __REV_Word(u32 Data);
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
