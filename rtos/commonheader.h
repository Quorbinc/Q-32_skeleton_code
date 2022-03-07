//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                  Base Processing code for Modules using STM32L4XX Proc
//                  -----------------------------------------------------
//
//    This code is for use on the STM32L432 Processor Series of Micro Controllers it is
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

  //--- Type Defs for software          Type    PreName Notation
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

  //--- Max and Min values for variable Types
  #define u08_MAX    ((u08)255)
  #define s08_MAX    ((s08)127)
  #define s08_MIN    ((s08)-128)
  #define u16_MAX    ((u16)65535U)
  #define s16_MAX    ((s16)32767)
  #define s16_MIN    ((s16)-32768)
  #define u32_MAX    ((u32)4294967295UL)
  #define s32_MAX    ((s32)2147483647)
  #define s32_MIN    ((s32)-2147483648)

  #define __ASM       asm                         //--- asm keyword for gcc
  #define __INLINE    inline                      //--- inline keyword for gcc
  #define __STATIC_INLINE  static inline

  #define GIE       asm("cpsie   i")              //--- Global Interrupt Enable
  #define GID       asm("cpsid   i")              //--- Global Interrupt Disable

  //--- These defines are for assembler NOP series of instructions
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

  //--- Floating Point Hardware Enable
  #define FPU_ENA   asm ( "LDR.W R0, = 0xE000ED88\n\t" \
                          "LDR R1, [R0]\n\t" \
                          "ORR R1, #0x00F00000\n\t" \
                          "STR R1, [R0]\n\t" \
                          "DSB\n\t" \
                          "ISB\n\t" ::)

  //------------------------------------------------------------------------------------------
  //--- These Names Define Specific Data Types
  //--- For these structures and unions the following type definitions apply:
  //
  //    ubByte == 8 Bit Unsigned Value
  //    sbByte == 8 Bit Signed Value
  //    uwWord == 16 Bit Unsigned Value
  //    swWord == 16 Bit Signed Value
  //    ulLong == 32 Bit Unsigned Value
  //    slLong == 32 Bit Signed Value
  //    uxBig  == 64 Bit Unsigned Value
  //    sxBig  == 64 Bit Signed Value
  //    sfFlt  == Single Precision Floating Point Value
  //    dfFlt  == Double Precision Floating Point Value
  //    *ubPtr == Pointer to Byte Values
  //    *vPntr == Pointer to VOID Values / Functions
  //------------------------------------------------------------------------------------------

  //--- 16 Bit Variable union
  union WB
  {
    u16 uwWord;
    s16 swWord;
    u08 ubByte[2];
    s08 sbByte[2];
  };

  //--- 32 Bit Variable union
  union LWB
  {
    u32   ulLong;                 //--- 1 32 Bit unsigned Long
    s32   slLong;                 //--- 1 32 Bit Signed Long
    u16   uwWord[2];              //--- 2 Unsigned Word
    s16   swWord[2];              //--- 2 Signed Word
    u08   ubByte[4];              //--- 4 Unsigned Bytes
    s08   sbByte[4];              //--- 4 Signed Bytes
  };


  //--- Float Long Word Byte Pointer Union
  //--- 32 Bit Multi Number Type unions
  union   FLWB                    //--- 4 Bytes of Pass Data
  {
    flt   sfFlt;                  //--- 1 single precision floating point
    u32   ulLong;                 //--- 1 Unsigned Long
    s32   slLong;                 //--- 1 Signed Long
    u16   uwWord[2];              //--- 2 Unsigned Word
    s16   swWord[2];              //--- 2 Signed Word
    u08   ubByte[4];              //--- 4 Unsigned Bytes
    s08   sbByte[4];              //--- 4 Signed Bytes
    u08*  ubPtr;                  //--- 1 General Purpose Pointers (byte)
    void* vPntr;                  //--- 1 Void Type Pointers
  };

  //--- Double Float Long Word Byte Pointer Union
  //--- 8 Byte Variable nion
  union DFLWB                     //--- 8 Bytes Binary / Integer Storage
  {
    dbl   dfFlt;                  //--- 1 Double Precision Float
    u64   uxBig;                  //--- 1 Unsigned 64 Bit Integer
    s64   sxBig;                  //--- 1 Signed 64 Bit Integer
    flt   sfFlt[2];               //--- 2 Single Precision Floats
    u32   ulLong[2];              //--- 2 Unsigned Long
    s32   slLong[2];              //--- 2 Signed Long
    u16   uwWord[4];              //--- 4 Unsigned Words
    s16   swWord[4];              //--- 4 Signed Words
    u08   ubByte[8];              //--- 8 Unsigned Bytes
    s08   sbByte[8];              //--- 8 Signed Bytes
    u08*  ubPtr[2];               //--- 2 General Purpose Pointers (byte]
    void* vPtr[2];                //--- 2 Void Type Pointers
  };

  //--- Double Float Long Word Byte Pointer Union
  //--- 32 Byte Variable union
  union DFLWB32                   //--- 32 Bytes Variable
  {
    dbl   dfFlt[4];               //--- 4 Double Precision Float
    u64   uxBig[4];               //--- 4 Unsigned 64 Bit Integer
    s64   sxBig[4];               //--- 4 Signed 64 Bit Integer
    flt   sfFlt[8];               //--- 8 Single Precision Floats
    u32   ulLong[8];              //--- 8 Unsigned Long
    s32   slLong[8];              //--- 8 Signed Long
    u16   uwWord[16];             //--- 16 Unsigned Words
    s16   swWord[16];             //--- 16 Signed Words
    u08   ubByte[32];             //--- 32 Unsigned Bytes
    s08   sbByte[32];             //--- 32 Signed Bytes
    u08*  ubPtr[8];               //--- 8 General Purpose Pointers (byte]
    void* vPntr[8];               //--- 8 Void Type Pointers
  };

  //--- Double Float Long Word Byte Pointer Union
  //--- 256 Byte Variable union
  union DFLWB256                  //--- 256 Byte Variable
  {
    dbl   dfFlt[32];              //--- 32 Double Precision Float
    u64   uxBig[32];              //--- 32 Unsigned 64 Bit Integer
    s64   sxBig[32];              //--- 32 Signed 64 Bit Integer
    flt   sfFlt[64];              //--- 64 Single Precision Floats
    u32   ulLong[64];             //--- 64 Unsigned Long
    s32   slLong[64];             //--- 64 Signed Long
    u16   uwWord[128];            //--- 128 Unsigned Words
    s16   swWord[128];            //--- 128 Signed Words
    u08   ubByte[256];            //--- 256 Unsigned Bytes
    s08   sbByte[256];            //--- 256 Signed Bytes
    u08*  ubPtr[64];              //--- 64 General Purpose Pointers (byte]
    void* vPtr[64];               //--- 64 Void Type Pointers
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


  //--- Pin definition macros

  //--------------------------------------------------------------------------------------
  //   These Macros and and then or a target pin in order
  //   to define the pin as the user desires such as an  
  //   input, output, analog, or alternate function pin. 
  //--------------------------------------------------------------------------------------

  //----------------------------------
  //          GPIOA pin changes       
  //----------------------------------

  //--- Pin 00 settings
  #define PA00_IN  GPIOA_MODER &= 0xFFFFFFFC; GPIOA_MODER |= 0x00000000;
  #define PA00_OUT GPIOA_MODER &= 0xFFFFFFFC; GPIOA_MODER |= 0x00000001;
  #define PA00_ALT GPIOA_MODER &= 0xFFFFFFFC; GPIOA_MODER |= 0x00000002;
  #define PA00_ANA GPIOA_MODER &= 0xFFFFFFFC; GPIOA_MODER |= 0x00000003;

  //--- Pin 01 settings
  #define PA01_IN  GPIOA_MODER &= 0xFFFFFFF3; GPIOA_MODER |= 0x00000000;
  #define PA01_OUT GPIOA_MODER &= 0xFFFFFFF3; GPIOA_MODER |= 0x00000004;
  #define PA01_ALT GPIOA_MODER &= 0xFFFFFFF3; GPIOA_MODER |= 0x00000008;
  #define PA01_ANA GPIOA_MODER &= 0xFFFFFFF3; GPIOA_MODER |= 0x0000000C;

  //--- Pin 02 settings
  #define PA02_IN  GPIOA_MODER &= 0xFFFFFFCF; GPIOA_MODER |= 0x00000000;
  #define PA02_OUT GPIOA_MODER &= 0xFFFFFFCF; GPIOA_MODER |= 0x00000010;
  #define PA02_ALT GPIOA_MODER &= 0xFFFFFFCF; GPIOA_MODER |= 0x00000020;
  #define PA02_ANA GPIOA_MODER &= 0xFFFFFFCF; GPIOA_MODER |= 0x00000030;

  //--- Pin 03 settings
  #define PA03_IN  GPIOA_MODER &= 0xFFFFFF3F; GPIOA_MODER |= 0x00000000;
  #define PA03_OUT GPIOA_MODER &= 0xFFFFFF3F; GPIOA_MODER |= 0x00000040;
  #define PA03_ALT GPIOA_MODER &= 0xFFFFFF3F; GPIOA_MODER |= 0x00000080;
  #define PA03_ANA GPIOA_MODER &= 0xFFFFFF3F; GPIOA_MODER |= 0x000000C0;

  //--- Pin 04 settings
  #define PA04_IN  GPIOA_MODER &= 0xFFFFFCFF; GPIOA_MODER |= 0x00000000;
  #define PA04_OUT GPIOA_MODER &= 0xFFFFFCFF; GPIOA_MODER |= 0x00000100;
  #define PA04_ALT GPIOA_MODER &= 0xFFFFFCFF; GPIOA_MODER |= 0x00000200;
  #define PA04_ANA GPIOA_MODER &= 0xFFFFFCFF; GPIOA_MODER |= 0x00000300;

  //--- Pin 05 settings
  #define PA05_IN  GPIOA_MODER &= 0xFFFFF3FF; GPIOA_MODER |= 0x00000000;
  #define PA05_OUT GPIOA_MODER &= 0xFFFFF3FF; GPIOA_MODER |= 0x00000400;
  #define PA05_ALT GPIOA_MODER &= 0xFFFFF3FF; GPIOA_MODER |= 0x00000800;
  #define PA05_ANA GPIOA_MODER &= 0xFFFFF3FF; GPIOA_MODER |= 0x00000C00;

  //--- Pin 06 settings
  #define PA06_IN  GPIOA_MODER &= 0xFFFFCFFF; GPIOA_MODER |= 0x00000000;
  #define PA06_OUT GPIOA_MODER &= 0xFFFFCFFF; GPIOA_MODER |= 0x00001000;
  #define PA06_ALT GPIOA_MODER &= 0xFFFFCFFF; GPIOA_MODER |= 0x00002000;
  #define PA06_ANA GPIOA_MODER &= 0xFFFFCFFF; GPIOA_MODER |= 0x00003000;

  //--- Pin 07 settings
  #define PA07_IN  GPIOA_MODER &= 0xFFFF3FFF; GPIOA_MODER |= 0x00000000;
  #define PA07_OUT GPIOA_MODER &= 0xFFFF3FFF; GPIOA_MODER |= 0x00004000;
  #define PA07_ALT GPIOA_MODER &= 0xFFFF3FFF; GPIOA_MODER |= 0x00008000;
  #define PA07_ANA GPIOA_MODER &= 0xFFFF3FFF; GPIOA_MODER |= 0x0000C000;

  //--- Pin 08 settings
  #define PA08_IN  GPIOA_MODER &= 0xFFFCFFFF; GPIOA_MODER |= 0x00000000;
  #define PA08_OUT GPIOA_MODER &= 0xFFFCFFFF; GPIOA_MODER |= 0x00010000;
  #define PA08_ALT GPIOA_MODER &= 0xFFFCFFFF; GPIOA_MODER |= 0x00020000;
  #define PA08_ANA GPIOA_MODER &= 0xFFFCFFFF; GPIOA_MODER |= 0x00030000;

  //--- Pin 09 settings
  #define PA09_IN  GPIOA_MODER &= 0xFFF3FFFF; GPIOA_MODER |= 0x00000000;
  #define PA09_OUT GPIOA_MODER &= 0xFFF3FFFF; GPIOA_MODER |= 0x00040000;
  #define PA09_ALT GPIOA_MODER &= 0xFFF3FFFF; GPIOA_MODER |= 0x00080000;
  #define PA09_ANA GPIOA_MODER &= 0xFFF3FFFF; GPIOA_MODER |= 0x000C0000;

  //--- Pin 10 settings
  #define PA10_IN  GPIOA_MODER &= 0xFFCFFFFF; GPIOA_MODER |= 0x00000000;
  #define PA10_OUT GPIOA_MODER &= 0xFFCFFFFF; GPIOA_MODER |= 0x00100000;
  #define PA10_ALT GPIOA_MODER &= 0xFFCFFFFF; GPIOA_MODER |= 0x00200000;
  #define PA10_ANA GPIOA_MODER &= 0xFFCFFFFF; GPIOA_MODER |= 0x00300000;

  //--- Pin 11 settings
  #define PA11_IN  GPIOA_MODER &= 0xFF3FFFFF; GPIOA_MODER |= 0x00000000;
  #define PA11_OUT GPIOA_MODER &= 0xFF3FFFFF; GPIOA_MODER |= 0x00400000;
  #define PA11_ALT GPIOA_MODER &= 0xFF3FFFFF; GPIOA_MODER |= 0x00800000;
  #define PA11_ANA GPIOA_MODER &= 0xFF3FFFFF; GPIOA_MODER |= 0x00C00000;

  //--- Pin 12 settings
  #define PA12_IN  GPIOA_MODER &= 0xFCFFFFFF; GPIOA_MODER |= 0x00000000;
  #define PA12_OUT GPIOA_MODER &= 0xFCFFFFFF; GPIOA_MODER |= 0x01000000;
  #define PA12_ALT GPIOA_MODER &= 0xFCFFFFFF; GPIOA_MODER |= 0x02000000;
  #define PA12_ANA GPIOA_MODER &= 0xFCFFFFFF; GPIOA_MODER |= 0x03000000;

  //--- Pin 13 settings
  #define PA13_IN  GPIOA_MODER &= 0xF3FFFFFF; GPIOA_MODER |= 0x00000000;
  #define PA13_OUT GPIOA_MODER &= 0xF3FFFFFF; GPIOA_MODER |= 0x04000000;
  #define PA13_ALT GPIOA_MODER &= 0xF3FFFFFF; GPIOA_MODER |= 0x08000000;
  #define PA13_ANA GPIOA_MODER &= 0xF3FFFFFF; GPIOA_MODER |= 0x0C000000;

  //--- Pin 14 settings
  #define PA14_IN  GPIOA_MODER &= 0xCFFFFFFF; GPIOA_MODER |= 0x00000000;
  #define PA14_OUT GPIOA_MODER &= 0xCFFFFFFF; GPIOA_MODER |= 0x10000000;
  #define PA14_ALT GPIOA_MODER &= 0xCFFFFFFF; GPIOA_MODER |= 0x20000000;
  #define PA14_ANA GPIOA_MODER &= 0xCFFFFFFF; GPIOA_MODER |= 0x30000000;

  //--- Pin 15 settings
  #define PA15_IN  GPIOA_MODER &= 0x3FFFFFFF; GPIOA_MODER |= 0x00000000;
  #define PA15_OUT GPIOA_MODER &= 0x3FFFFFFF; GPIOA_MODER |= 0x40000000;
  #define PA15_ALT GPIOA_MODER &= 0x3FFFFFFF; GPIOA_MODER |= 0x80000000;
  #define PA15_ANA GPIOA_MODER &= 0x3FFFFFFF; GPIOA_MODER |= 0xC0000000;


  //----------------------------------
  //          GPIOB pin changes       
  //----------------------------------

  //--- Pin 00 settings
  #define PB00_IN  GPIOB_MODER &= 0xFFFFFFFC; GPIOB_MODER |= 0x00000000;
  #define PB00_OUT GPIOB_MODER &= 0xFFFFFFFC; GPIOB_MODER |= 0x00000001;
  #define PB00_ALT GPIOB_MODER &= 0xFFFFFFFC; GPIOB_MODER |= 0x00000002;
  #define PB00_ANA GPIOB_MODER &= 0xFFFFFFFC; GPIOB_MODER |= 0x00000003;

  //--- Pin 01 settings
  #define PB01_IN  GPIOB_MODER &= 0xFFFFFFF3; GPIOB_MODER |= 0x00000000;
  #define PB01_OUT GPIOB_MODER &= 0xFFFFFFF3; GPIOB_MODER |= 0x00000004;
  #define PB01_ALT GPIOB_MODER &= 0xFFFFFFF3; GPIOB_MODER |= 0x00000008;
  #define PB01_ANA GPIOB_MODER &= 0xFFFFFFF3; GPIOB_MODER |= 0x0000000C;

  //--- Pin 02 settings
  #define PB02_IN  GPIOB_MODER &= 0xFFFFFFCF; GPIOB_MODER |= 0x00000000;
  #define PB02_OUT GPIOB_MODER &= 0xFFFFFFCF; GPIOB_MODER |= 0x00000010;
  #define PB02_ALT GPIOB_MODER &= 0xFFFFFFCF; GPIOB_MODER |= 0x00000020;
  #define PB02_ANA GPIOB_MODER &= 0xFFFFFFCF; GPIOB_MODER |= 0x00000030;

  //--- Pin 03 settings
  #define PB03_IN  GPIOB_MODER &= 0xFFFFFF3F; GPIOB_MODER |= 0x00000000;
  #define PB03_OUT GPIOB_MODER &= 0xFFFFFF3F; GPIOB_MODER |= 0x00000040;
  #define PB03_ALT GPIOB_MODER &= 0xFFFFFF3F; GPIOB_MODER |= 0x00000080;
  #define PB03_ANA GPIOB_MODER &= 0xFFFFFF3F; GPIOB_MODER |= 0x000000C0;

  //--- Pin 04 settings
  #define PB04_IN  GPIOB_MODER &= 0xFFFFFCFF; GPIOB_MODER |= 0x00000000;
  #define PB04_OUT GPIOB_MODER &= 0xFFFFFCFF; GPIOB_MODER |= 0x00000100;
  #define PB04_ALT GPIOB_MODER &= 0xFFFFFCFF; GPIOB_MODER |= 0x00000200;
  #define PB04_ANA GPIOB_MODER &= 0xFFFFFCFF; GPIOB_MODER |= 0x00000300;

  //--- Pin 05 settings
  #define PB05_IN  GPIOB_MODER &= 0xFFFFF3FF; GPIOB_MODER |= 0x00000000;
  #define PB05_OUT GPIOB_MODER &= 0xFFFFF3FF; GPIOB_MODER |= 0x00000400;
  #define PB05_ALT GPIOB_MODER &= 0xFFFFF3FF; GPIOB_MODER |= 0x00000800;
  #define PB05_ANA GPIOB_MODER &= 0xFFFFF3FF; GPIOB_MODER |= 0x00000C00;

  //--- Pin 06 settings
  #define PB06_IN  GPIOB_MODER &= 0xFFFFCFFF; GPIOB_MODER |= 0x00000000;
  #define PB06_OUT GPIOB_MODER &= 0xFFFFCFFF; GPIOB_MODER |= 0x00001000;
  #define PB06_ALT GPIOB_MODER &= 0xFFFFCFFF; GPIOB_MODER |= 0x00002000;
  #define PB06_ANA GPIOB_MODER &= 0xFFFFCFFF; GPIOB_MODER |= 0x00003000;

  //--- Pin 07 settings
  #define PB07_IN  GPIOB_MODER &= 0xFFFF3FFF; GPIOB_MODER |= 0x00000000;
  #define PB07_OUT GPIOB_MODER &= 0xFFFF3FFF; GPIOB_MODER |= 0x00004000;
  #define PB07_ALT GPIOB_MODER &= 0xFFFF3FFF; GPIOB_MODER |= 0x00008000;
  #define PB07_ANA GPIOB_MODER &= 0xFFFF3FFF; GPIOB_MODER |= 0x0000C000;

  //--- Pin 08 settings
  #define PB08_IN  GPIOB_MODER &= 0xFFFCFFFF; GPIOB_MODER |= 0x00000000;
  #define PB08_OUT GPIOB_MODER &= 0xFFFCFFFF; GPIOB_MODER |= 0x00010000;
  #define PB08_ALT GPIOB_MODER &= 0xFFFCFFFF; GPIOB_MODER |= 0x00020000;
  #define PB08_ANA GPIOB_MODER &= 0xFFFCFFFF; GPIOB_MODER |= 0x00030000;

  //--- Pin 09 settings
  #define PB09_IN  GPIOB_MODER &= 0xFFF3FFFF; GPIOB_MODER |= 0x00000000;
  #define PB09_OUT GPIOB_MODER &= 0xFFF3FFFF; GPIOB_MODER |= 0x00040000;
  #define PB09_ALT GPIOB_MODER &= 0xFFF3FFFF; GPIOB_MODER |= 0x00080000;
  #define PB09_ANA GPIOB_MODER &= 0xFFF3FFFF; GPIOB_MODER |= 0x000C0000;

  //--- Pin 10 settings
  #define PB10_IN  GPIOB_MODER &= 0xFFCFFFFF; GPIOB_MODER |= 0x00000000;
  #define PB10_OUT GPIOB_MODER &= 0xFFCFFFFF; GPIOB_MODER |= 0x00100000;
  #define PB10_ALT GPIOB_MODER &= 0xFFCFFFFF; GPIOB_MODER |= 0x00200000;
  #define PB10_ANA GPIOB_MODER &= 0xFFCFFFFF; GPIOB_MODER |= 0x00300000;

  //--- Pin 11 settings
  #define PB11_IN  GPIOB_MODER &= 0xFF3FFFFF; GPIOB_MODER |= 0x00000000;
  #define PB11_OUT GPIOB_MODER &= 0xFF3FFFFF; GPIOB_MODER |= 0x00400000;
  #define PB11_ALT GPIOB_MODER &= 0xFF3FFFFF; GPIOB_MODER |= 0x00800000;
  #define PB11_ANA GPIOB_MODER &= 0xFF3FFFFF; GPIOB_MODER |= 0x00C00000;

  //--- Pin 12 settings
  #define PB12_IN  GPIOB_MODER &= 0xFCFFFFFF; GPIOB_MODER |= 0x00000000;
  #define PB12_OUT GPIOB_MODER &= 0xFCFFFFFF; GPIOB_MODER |= 0x01000000;
  #define PB12_ALT GPIOB_MODER &= 0xFCFFFFFF; GPIOB_MODER |= 0x02000000;
  #define PB12_ANA GPIOB_MODER &= 0xFCFFFFFF; GPIOB_MODER |= 0x03000000;

  //--- Pin 13 settings
  #define PB13_IN  GPIOB_MODER &= 0xF3FFFFFF; GPIOB_MODER |= 0x00000000;
  #define PB13_OUT GPIOB_MODER &= 0xF3FFFFFF; GPIOB_MODER |= 0x04000000;
  #define PB13_ALT GPIOB_MODER &= 0xF3FFFFFF; GPIOB_MODER |= 0x08000000;
  #define PB13_ANA GPIOB_MODER &= 0xF3FFFFFF; GPIOB_MODER |= 0x0C000000;

  //--- Pin 14 settings
  #define PB14_IN  GPIOB_MODER &= 0xCFFFFFFF; GPIOB_MODER |= 0x00000000;
  #define PB14_OUT GPIOB_MODER &= 0xCFFFFFFF; GPIOB_MODER |= 0x10000000;
  #define PB14_ALT GPIOB_MODER &= 0xCFFFFFFF; GPIOB_MODER |= 0x20000000;
  #define PB14_ANA GPIOB_MODER &= 0xCFFFFFFF; GPIOB_MODER |= 0x30000000;

  //--- Pin 15 settings
  #define PB15_IN  GPIOB_MODER &= 0x3FFFFFFF; GPIOB_MODER |= 0x00000000;
  #define PB15_OUT GPIOB_MODER &= 0x3FFFFFFF; GPIOB_MODER |= 0x40000000;
  #define PB15_ALT GPIOB_MODER &= 0x3FFFFFFF; GPIOB_MODER |= 0x80000000;
  #define PB15_ANA GPIOB_MODER &= 0x3FFFFFFF; GPIOB_MODER |= 0xC0000000;


  //----------------------------------
  //          GPIOC pin changes       
  //----------------------------------

  //--- Pin 00 settings
  #define PC00_IN  GPIOC_MODER &= 0xFFFFFFFC; GPIOC_MODER |= 0x00000000;
  #define PC00_OUT GPIOC_MODER &= 0xFFFFFFFC; GPIOC_MODER |= 0x00000001;
  #define PC00_ALT GPIOC_MODER &= 0xFFFFFFFC; GPIOC_MODER |= 0x00000002;
  #define PC00_ANA GPIOC_MODER &= 0xFFFFFFFC; GPIOC_MODER |= 0x00000003;

  //--- Pin 01 settings
  #define PC01_IN  GPIOC_MODER &= 0xFFFFFFF3; GPIOC_MODER |= 0x00000000;
  #define PC01_OUT GPIOC_MODER &= 0xFFFFFFF3; GPIOC_MODER |= 0x00000004;
  #define PC01_ALT GPIOC_MODER &= 0xFFFFFFF3; GPIOC_MODER |= 0x00000008;
  #define PC01_ANA GPIOC_MODER &= 0xFFFFFFF3; GPIOC_MODER |= 0x0000000C;

  //--- Pin 02 settings
  #define PC02_IN  GPIOC_MODER &= 0xFFFFFFCF; GPIOC_MODER |= 0x00000000;
  #define PC02_OUT GPIOC_MODER &= 0xFFFFFFCF; GPIOC_MODER |= 0x00000010;
  #define PC02_ALT GPIOC_MODER &= 0xFFFFFFCF; GPIOC_MODER |= 0x00000020;
  #define PC02_ANA GPIOC_MODER &= 0xFFFFFFCF; GPIOC_MODER |= 0x00000030;

  //--- Pin 03 settings
  #define PC03_IN  GPIOC_MODER &= 0xFFFFFF3F; GPIOC_MODER |= 0x00000000;
  #define PC03_OUT GPIOC_MODER &= 0xFFFFFF3F; GPIOC_MODER |= 0x00000040;
  #define PC03_ALT GPIOC_MODER &= 0xFFFFFF3F; GPIOC_MODER |= 0x00000080;
  #define PC03_ANA GPIOC_MODER &= 0xFFFFFF3F; GPIOC_MODER |= 0x000000C0;

  //--- Pin 04 settings
  #define PC04_IN  GPIOC_MODER &= 0xFFFFFCFF; GPIOC_MODER |= 0x00000000;
  #define PC04_OUT GPIOC_MODER &= 0xFFFFFCFF; GPIOC_MODER |= 0x00000100;
  #define PC04_ALT GPIOC_MODER &= 0xFFFFFCFF; GPIOC_MODER |= 0x00000200;
  #define PC04_ANA GPIOC_MODER &= 0xFFFFFCFF; GPIOC_MODER |= 0x00000300;

  //--- Pin 05 settings
  #define PC05_IN  GPIOC_MODER &= 0xFFFFF3FF; GPIOC_MODER |= 0x00000000;
  #define PC05_OUT GPIOC_MODER &= 0xFFFFF3FF; GPIOC_MODER |= 0x00000400;
  #define PC05_ALT GPIOC_MODER &= 0xFFFFF3FF; GPIOC_MODER |= 0x00000800;
  #define PC05_ANA GPIOC_MODER &= 0xFFFFF3FF; GPIOC_MODER |= 0x00000C00;

  //--- Pin 06 settings
  #define PC06_IN  GPIOC_MODER &= 0xFFFFCFFF; GPIOC_MODER |= 0x00000000;
  #define PC06_OUT GPIOC_MODER &= 0xFFFFCFFF; GPIOC_MODER |= 0x00001000;
  #define PC06_ALT GPIOC_MODER &= 0xFFFFCFFF; GPIOC_MODER |= 0x00002000;
  #define PC06_ANA GPIOC_MODER &= 0xFFFFCFFF; GPIOC_MODER |= 0x00003000;

  //--- Pin 07 settings
  #define PC07_IN  GPIOC_MODER &= 0xFFFF3FFF; GPIOC_MODER |= 0x00000000;
  #define PC07_OUT GPIOC_MODER &= 0xFFFF3FFF; GPIOC_MODER |= 0x00004000;
  #define PC07_ALT GPIOC_MODER &= 0xFFFF3FFF; GPIOC_MODER |= 0x00008000;
  #define PC07_ANA GPIOC_MODER &= 0xFFFF3FFF; GPIOC_MODER |= 0x0000C000;

  //--- Pin 08 settings
  #define PC08_IN  GPIOC_MODER &= 0xFFFCFFFF; GPIOC_MODER |= 0x00000000;
  #define PC08_OUT GPIOC_MODER &= 0xFFFCFFFF; GPIOC_MODER |= 0x00010000;
  #define PC08_ALT GPIOC_MODER &= 0xFFFCFFFF; GPIOC_MODER |= 0x00020000;
  #define PC08_ANA GPIOC_MODER &= 0xFFFCFFFF; GPIOC_MODER |= 0x00030000;

  //--- Pin 09 settings
  #define PC09_IN  GPIOC_MODER &= 0xFFF3FFFF; GPIOC_MODER |= 0x00000000;
  #define PC09_OUT GPIOC_MODER &= 0xFFF3FFFF; GPIOC_MODER |= 0x00040000;
  #define PC09_ALT GPIOC_MODER &= 0xFFF3FFFF; GPIOC_MODER |= 0x00080000;
  #define PC09_ANA GPIOC_MODER &= 0xFFF3FFFF; GPIOC_MODER |= 0x000C0000;

  //--- Pin 10 settings
  #define PC10_IN  GPIOC_MODER &= 0xFFCFFFFF; GPIOC_MODER |= 0x00000000;
  #define PC10_OUT GPIOC_MODER &= 0xFFCFFFFF; GPIOC_MODER |= 0x00100000;
  #define PC10_ALT GPIOC_MODER &= 0xFFCFFFFF; GPIOC_MODER |= 0x00200000;
  #define PC10_ANA GPIOC_MODER &= 0xFFCFFFFF; GPIOC_MODER |= 0x00300000;

  //--- Pin 11 settings
  #define PC11_IN  GPIOC_MODER &= 0xFF3FFFFF; GPIOC_MODER |= 0x00000000;
  #define PC11_OUT GPIOC_MODER &= 0xFF3FFFFF; GPIOC_MODER |= 0x00400000;
  #define PC11_ALT GPIOC_MODER &= 0xFF3FFFFF; GPIOC_MODER |= 0x00800000;
  #define PC11_ANA GPIOC_MODER &= 0xFF3FFFFF; GPIOC_MODER |= 0x00C00000;

  //--- Pin 12 settings
  #define PC12_IN  GPIOC_MODER &= 0xFCFFFFFF; GPIOC_MODER |= 0x00000000;
  #define PC12_OUT GPIOC_MODER &= 0xFCFFFFFF; GPIOC_MODER |= 0x01000000;
  #define PC12_ALT GPIOC_MODER &= 0xFCFFFFFF; GPIOC_MODER |= 0x02000000;
  #define PC12_ANA GPIOC_MODER &= 0xFCFFFFFF; GPIOC_MODER |= 0x03000000;

  //--- Pin 13 settings
  #define PC13_IN  GPIOC_MODER &= 0xF3FFFFFF; GPIOC_MODER |= 0x00000000;
  #define PC13_OUT GPIOC_MODER &= 0xF3FFFFFF; GPIOC_MODER |= 0x04000000;
  #define PC13_ALT GPIOC_MODER &= 0xF3FFFFFF; GPIOC_MODER |= 0x08000000;
  #define PC13_ANA GPIOC_MODER &= 0xF3FFFFFF; GPIOC_MODER |= 0x0C000000;

  //--- Pin 14 settings
  #define PC14_IN  GPIOC_MODER &= 0xCFFFFFFF; GPIOC_MODER |= 0x00000000;
  #define PC14_OUT GPIOC_MODER &= 0xCFFFFFFF; GPIOC_MODER |= 0x10000000;
  #define PC14_ALT GPIOC_MODER &= 0xCFFFFFFF; GPIOC_MODER |= 0x20000000;
  #define PC14_ANA GPIOC_MODER &= 0xCFFFFFFF; GPIOC_MODER |= 0x30000000;

  //--- Pin 15 settings
  #define PC15_IN  GPIOC_MODER &= 0x3FFFFFFF; GPIOC_MODER |= 0x00000000;
  #define PC15_OUT GPIOC_MODER &= 0x3FFFFFFF; GPIOC_MODER |= 0x40000000;
  #define PC15_ALT GPIOC_MODER &= 0x3FFFFFFF; GPIOC_MODER |= 0x80000000;
  #define PC15_ANA GPIOC_MODER &= 0x3FFFFFFF; GPIOC_MODER |= 0xC0000000;

  //-----------------------------------
  //     GPIOA alternate functions     
  //-----------------------------------

  //--- PA00 alternate functions
  #define PA00_AF00 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x00000000;
  #define PA00_AF01 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x00000001;
  #define PA00_AF02 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x00000002;
  #define PA00_AF03 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x00000003;
  #define PA00_AF04 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x00000004;
  #define PA00_AF05 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x00000005;
  #define PA00_AF06 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x00000006;
  #define PA00_AF07 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x00000007;
  #define PA00_AF08 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x00000008;
  #define PA00_AF09 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x00000009;
  #define PA00_AF10 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x0000000A;
  #define PA00_AF11 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x0000000B;
  #define PA00_AF12 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x0000000C;
  #define PA00_AF13 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x0000000D;
  #define PA00_AF14 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x0000000E;
  #define PA00_AF15 GPIOA_AFRL &= 0xFFFFFFF0; GPIOA_AFRL |= 0x0000000F;


  //--- PA01 alternate functions
  #define PA01_AF00 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x00000000;
  #define PA01_AF01 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x00000010;
  #define PA01_AF02 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x00000020;
  #define PA01_AF03 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x00000030;
  #define PA01_AF04 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x00000040;
  #define PA01_AF05 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x00000050;
  #define PA01_AF06 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x00000060;
  #define PA01_AF07 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x00000070;
  #define PA01_AF08 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x00000080;
  #define PA01_AF09 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x00000090;
  #define PA01_AF10 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x000000A0;
  #define PA01_AF11 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x000000B0;
  #define PA01_AF12 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x000000C0;
  #define PA01_AF13 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x000000D0;
  #define PA01_AF14 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x000000E0;
  #define PA01_AF15 GPIOA_AFRL &= 0xFFFFFF0F; GPIOA_AFRL |= 0x000000F0;


  //--- PA02 alternate functions
  #define PA02_AF00 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000000;
  #define PA02_AF01 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000100;
  #define PA02_AF02 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000200;
  #define PA02_AF03 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000300;
  #define PA02_AF04 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000400;
  #define PA02_AF05 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000500;
  #define PA02_AF06 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000600;
  #define PA02_AF07 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000700;
  #define PA02_AF08 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000800;
  #define PA02_AF09 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000900;
  #define PA02_AF10 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000A00;
  #define PA02_AF11 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000B00;
  #define PA02_AF12 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000C00;
  #define PA02_AF13 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000D00;
  #define PA02_AF14 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000E00;
  #define PA02_AF15 GPIOA_AFRL &= 0xFFFFF0FF; GPIOA_AFRL |= 0x00000F00;


  //--- PA03 alternate functions
  #define PA03_AF00 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x00000000;
  #define PA03_AF01 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x00001000;
  #define PA03_AF02 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x00002000;
  #define PA03_AF03 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x00003000;
  #define PA03_AF04 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x00004000;
  #define PA03_AF05 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x00005000;
  #define PA03_AF06 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x00006000;
  #define PA03_AF07 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x00007000;
  #define PA03_AF08 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x00008000;
  #define PA03_AF09 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x00009000;
  #define PA03_AF10 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x0000A000;
  #define PA03_AF11 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x0000B000;
  #define PA03_AF12 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x0000C000;
  #define PA03_AF13 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x0000D000;
  #define PA03_AF14 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x0000E000;
  #define PA03_AF15 GPIOA_AFRL &= 0xFFFF0FFF; GPIOA_AFRL |= 0x0000F000;


  //--- PA04 alternate functions
  #define PA04_AF00 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x00000000;
  #define PA04_AF01 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x00010000;
  #define PA04_AF02 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x00020000;
  #define PA04_AF03 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x00030000;
  #define PA04_AF04 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x00040000;
  #define PA04_AF05 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x00050000;
  #define PA04_AF06 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x00060000;
  #define PA04_AF07 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x00070000;
  #define PA04_AF08 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x00080000;
  #define PA04_AF09 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x00090000;
  #define PA04_AF10 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x000A0000;
  #define PA04_AF11 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x000B0000;
  #define PA04_AF12 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x000C0000;
  #define PA04_AF13 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x000D0000;
  #define PA04_AF14 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x000E0000;
  #define PA04_AF15 GPIOA_AFRL &= 0xFFF0FFFF; GPIOA_AFRL |= 0x000F0000;


  //--- PA05 alternate functions
  #define PA05_AF00 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00000000;
  #define PA05_AF01 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00100000;
  #define PA05_AF02 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00200000;
  #define PA05_AF03 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00300000;
  #define PA05_AF04 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00400000;
  #define PA05_AF05 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00500000;
  #define PA05_AF06 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00600000;
  #define PA05_AF07 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00700000;
  #define PA05_AF08 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00800000;
  #define PA05_AF09 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00900000;
  #define PA05_AF10 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00A00000;
  #define PA05_AF11 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00B00000;
  #define PA05_AF12 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00C00000;
  #define PA05_AF13 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00D00000;
  #define PA05_AF14 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00E00000;
  #define PA05_AF15 GPIOA_AFRL &= 0xFF0FFFFF; GPIOA_AFRL |= 0x00F00000;


  //--- PA06 alternate functions
  #define PA06_AF00 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x00000000;
  #define PA06_AF01 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x01000000;
  #define PA06_AF02 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x02000000;
  #define PA06_AF03 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x03000000;
  #define PA06_AF04 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x04000000;
  #define PA06_AF05 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x05000000;
  #define PA06_AF06 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x06000000;
  #define PA06_AF07 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x07000000;
  #define PA06_AF08 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x08000000;
  #define PA06_AF09 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x09000000;
  #define PA06_AF10 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x0A000000;
  #define PA06_AF11 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x0B000000;
  #define PA06_AF12 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x0C000000;
  #define PA06_AF13 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x0D000000;
  #define PA06_AF14 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x0E000000;
  #define PA06_AF15 GPIOA_AFRL &= 0xF0FFFFFF; GPIOA_AFRL |= 0x0F000000;


  //--- PA07 alternate functions
  #define PA07_AF00 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0x00000000;
  #define PA07_AF01 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0x10000000;
  #define PA07_AF02 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0x20000000;
  #define PA07_AF03 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0x30000000;
  #define PA07_AF04 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0x40000000;
  #define PA07_AF05 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0x50000000;
  #define PA07_AF06 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0x60000000;
  #define PA07_AF07 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0x70000000;
  #define PA07_AF08 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0x80000000;
  #define PA07_AF09 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0x90000000;
  #define PA07_AF10 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0xA0000000;
  #define PA07_AF11 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0xB0000000;
  #define PA07_AF12 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0xC0000000;
  #define PA07_AF13 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0xD0000000;
  #define PA07_AF14 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0xE0000000;
  #define PA07_AF15 GPIOA_AFRL &= 0x0FFFFFFF; GPIOA_AFRL |= 0xF0000000;


  //--- PA08 alternate functions
  #define PA08_AF00 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x00000000;
  #define PA08_AF01 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x00000001;
  #define PA08_AF02 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x00000002;
  #define PA08_AF03 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x00000003;
  #define PA08_AF04 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x00000004;
  #define PA08_AF05 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x00000005;
  #define PA08_AF06 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x00000006;
  #define PA08_AF07 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x00000007;
  #define PA08_AF08 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x00000008;
  #define PA08_AF09 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x00000009;
  #define PA08_AF10 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x0000000A;
  #define PA08_AF11 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x0000000B;
  #define PA08_AF12 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x0000000C;
  #define PA08_AF13 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x0000000D;
  #define PA08_AF14 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x0000000E;
  #define PA08_AF15 GPIOA_AFRH &= 0xFFFFFFF0; GPIOA_AFRH |= 0x0000000F;


  //--- PA09 alternate functions
  #define PA09_AF00 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x00000000;
  #define PA09_AF01 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x00000010;
  #define PA09_AF02 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x00000020;
  #define PA09_AF03 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x00000030;
  #define PA09_AF04 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x00000040;
  #define PA09_AF05 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x00000050;
  #define PA09_AF06 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x00000060;
  #define PA09_AF07 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x00000070;
  #define PA09_AF08 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x00000080;
  #define PA09_AF09 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x00000090;
  #define PA09_AF10 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x000000A0;
  #define PA09_AF11 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x000000B0;
  #define PA09_AF12 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x000000C0;
  #define PA09_AF13 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x000000D0;
  #define PA09_AF14 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x000000E0;
  #define PA09_AF15 GPIOA_AFRH &= 0xFFFFFF0F; GPIOA_AFRH |= 0x000000F0;


  //--- PA10 alternate functions
  #define PA10_AF00 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000000;
  #define PA10_AF01 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000100;
  #define PA10_AF02 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000200;
  #define PA10_AF03 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000300;
  #define PA10_AF04 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000400;
  #define PA10_AF05 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000500;
  #define PA10_AF06 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000600;
  #define PA10_AF07 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000700;
  #define PA10_AF08 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000800;
  #define PA10_AF09 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000900;
  #define PA10_AF10 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000A00;
  #define PA10_AF11 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000B00;
  #define PA10_AF12 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000C00;
  #define PA10_AF13 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000D00;
  #define PA10_AF14 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000E00;
  #define PA10_AF15 GPIOA_AFRH &= 0xFFFFF0FF; GPIOA_AFRH |= 0x00000F00;


  //--- PA11 alternate functions
  #define PA11_AF00 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x00000000;
  #define PA11_AF01 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x00001000;
  #define PA11_AF02 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x00002000;
  #define PA11_AF03 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x00003000;
  #define PA11_AF04 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x00004000;
  #define PA11_AF05 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x00005000;
  #define PA11_AF06 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x00006000;
  #define PA11_AF07 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x00007000;
  #define PA11_AF08 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x00008000;
  #define PA11_AF09 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x00009000;
  #define PA11_AF10 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x0000A000;
  #define PA11_AF11 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x0000B000;
  #define PA11_AF12 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x0000C000;
  #define PA11_AF13 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x0000D000;
  #define PA11_AF14 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x0000E000;
  #define PA11_AF15 GPIOA_AFRH &= 0xFFFF0FFF; GPIOA_AFRH |= 0x0000F000;


  //--- PA12 alternate functions
  #define PA12_AF00 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x00000000;
  #define PA12_AF01 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x00010000;
  #define PA12_AF02 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x00020000;
  #define PA12_AF03 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x00030000;
  #define PA12_AF04 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x00040000;
  #define PA12_AF05 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x00050000;
  #define PA12_AF06 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x00060000;
  #define PA12_AF07 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x00070000;
  #define PA12_AF08 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x00080000;
  #define PA12_AF09 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x00090000;
  #define PA12_AF10 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x000A0000;
  #define PA12_AF11 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x000B0000;
  #define PA12_AF12 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x000C0000;
  #define PA12_AF13 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x000D0000;
  #define PA12_AF14 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x000E0000;
  #define PA12_AF15 GPIOA_AFRH &= 0xFFF0FFFF; GPIOA_AFRH |= 0x000F0000;


  //--- PA13 alternate functions
  #define PA13_AF00 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00000000;
  #define PA13_AF01 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00100000;
  #define PA13_AF02 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00200000;
  #define PA13_AF03 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00300000;
  #define PA13_AF04 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00400000;
  #define PA13_AF05 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00500000;
  #define PA13_AF06 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00600000;
  #define PA13_AF07 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00700000;
  #define PA13_AF08 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00800000;
  #define PA13_AF09 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00900000;
  #define PA13_AF10 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00A00000;
  #define PA13_AF11 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00B00000;
  #define PA13_AF12 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00C00000;
  #define PA13_AF13 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00D00000;
  #define PA13_AF14 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00E00000;
  #define PA13_AF15 GPIOA_AFRH &= 0xFF0FFFFF; GPIOA_AFRH |= 0x00F00000;


  //--- PA14 alternate functions
  #define PA14_AF00 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x00000000;
  #define PA14_AF01 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x01000000;
  #define PA14_AF02 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x02000000;
  #define PA14_AF03 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x03000000;
  #define PA14_AF04 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x04000000;
  #define PA14_AF05 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x05000000;
  #define PA14_AF06 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x06000000;
  #define PA14_AF07 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x07000000;
  #define PA14_AF08 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x08000000;
  #define PA14_AF09 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x09000000;
  #define PA14_AF10 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x0A000000;
  #define PA14_AF11 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x0B000000;
  #define PA14_AF12 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x0C000000;
  #define PA14_AF13 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x0D000000;
  #define PA14_AF14 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x0E000000;
  #define PA14_AF15 GPIOA_AFRH &= 0xF0FFFFFF; GPIOA_AFRH |= 0x0F000000;


  //--- PA15 alternate functions
  #define PA15_AF00 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0x00000000;
  #define PA15_AF01 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0x10000000;
  #define PA15_AF02 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0x20000000;
  #define PA15_AF03 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0x30000000;
  #define PA15_AF04 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0x40000000;
  #define PA15_AF05 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0x50000000;
  #define PA15_AF06 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0x60000000;
  #define PA15_AF07 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0x70000000;
  #define PA15_AF08 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0x80000000;
  #define PA15_AF09 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0x90000000;
  #define PA15_AF10 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0xA0000000;
  #define PA15_AF11 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0xB0000000;
  #define PA15_AF12 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0xC0000000;
  #define PA15_AF13 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0xD0000000;
  #define PA15_AF14 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0xE0000000;
  #define PA15_AF15 GPIOA_AFRH &= 0x0FFFFFFF; GPIOA_AFRH |= 0xF0000000;


  //-----------------------------------
  //     GPIOB alternate functions     
  //-----------------------------------

  //--- PB00 alternate functions
  #define PB00_AF00 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x00000000;
  #define PB00_AF01 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x00000001;
  #define PB00_AF02 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x00000002;
  #define PB00_AF03 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x00000003;
  #define PB00_AF04 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x00000004;
  #define PB00_AF05 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x00000005;
  #define PB00_AF06 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x00000006;
  #define PB00_AF07 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x00000007;
  #define PB00_AF08 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x00000008;
  #define PB00_AF09 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x00000009;
  #define PB00_AF10 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x0000000A;
  #define PB00_AF11 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x0000000B;
  #define PB00_AF12 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x0000000C;
  #define PB00_AF13 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x0000000D;
  #define PB00_AF14 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x0000000E;
  #define PB00_AF15 GPIOB_AFRL &= 0xFFFFFFF0; GPIOB_AFRL |= 0x0000000F;


  //--- PB01 alternate functions
  #define PB01_AF00 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x00000000;
  #define PB01_AF01 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x00000010;
  #define PB01_AF02 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x00000020;
  #define PB01_AF03 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x00000030;
  #define PB01_AF04 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x00000040;
  #define PB01_AF05 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x00000050;
  #define PB01_AF06 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x00000060;
  #define PB01_AF07 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x00000070;
  #define PB01_AF08 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x00000080;
  #define PB01_AF09 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x00000090;
  #define PB01_AF10 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x000000A0;
  #define PB01_AF11 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x000000B0;
  #define PB01_AF12 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x000000C0;
  #define PB01_AF13 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x000000D0;
  #define PB01_AF14 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x000000E0;
  #define PB01_AF15 GPIOB_AFRL &= 0xFFFFFF0F; GPIOB_AFRL |= 0x000000F0;


  //--- PB02 alternate functions
  #define PB02_AF00 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000000;
  #define PB02_AF01 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000100;
  #define PB02_AF02 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000200;
  #define PB02_AF03 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000300;
  #define PB02_AF04 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000400;
  #define PB02_AF05 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000500;
  #define PB02_AF06 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000600;
  #define PB02_AF07 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000700;
  #define PB02_AF08 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000800;
  #define PB02_AF09 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000900;
  #define PB02_AF10 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000A00;
  #define PB02_AF11 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000B00;
  #define PB02_AF12 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000C00;
  #define PB02_AF13 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000D00;
  #define PB02_AF14 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000E00;
  #define PB02_AF15 GPIOB_AFRL &= 0xFFFFF0FF; GPIOB_AFRL |= 0x00000F00;


  //--- PB03 alternate functions
  #define PB03_AF00 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x00000000;
  #define PB03_AF01 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x00001000;
  #define PB03_AF02 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x00002000;
  #define PB03_AF03 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x00003000;
  #define PB03_AF04 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x00004000;
  #define PB03_AF05 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x00005000;
  #define PB03_AF06 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x00006000;
  #define PB03_AF07 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x00007000;
  #define PB03_AF08 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x00008000;
  #define PB03_AF09 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x00009000;
  #define PB03_AF10 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x0000A000;
  #define PB03_AF11 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x0000B000;
  #define PB03_AF12 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x0000C000;
  #define PB03_AF13 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x0000D000;
  #define PB03_AF14 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x0000E000;
  #define PB03_AF15 GPIOB_AFRL &= 0xFFFF0FFF; GPIOB_AFRL |= 0x0000F000;


  //--- PB04 alternate functions
  #define PB04_AF00 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x00000000;
  #define PB04_AF01 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x00010000;
  #define PB04_AF02 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x00020000;
  #define PB04_AF03 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x00030000;
  #define PB04_AF04 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x00040000;
  #define PB04_AF05 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x00050000;
  #define PB04_AF06 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x00060000;
  #define PB04_AF07 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x00070000;
  #define PB04_AF08 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x00080000;
  #define PB04_AF09 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x00090000;
  #define PB04_AF10 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x000A0000;
  #define PB04_AF11 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x000B0000;
  #define PB04_AF12 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x000C0000;
  #define PB04_AF13 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x000D0000;
  #define PB04_AF14 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x000E0000;
  #define PB04_AF15 GPIOB_AFRL &= 0xFFF0FFFF; GPIOB_AFRL |= 0x000F0000;


  //--- PB05 alternate functions
  #define PB05_AF00 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00000000;
  #define PB05_AF01 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00100000;
  #define PB05_AF02 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00200000;
  #define PB05_AF03 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00300000;
  #define PB05_AF04 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00400000;
  #define PB05_AF05 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00500000;
  #define PB05_AF06 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00600000;
  #define PB05_AF07 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00700000;
  #define PB05_AF08 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00800000;
  #define PB05_AF09 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00900000;
  #define PB05_AF10 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00A00000;
  #define PB05_AF11 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00B00000;
  #define PB05_AF12 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00C00000;
  #define PB05_AF13 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00D00000;
  #define PB05_AF14 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00E00000;
  #define PB05_AF15 GPIOB_AFRL &= 0xFF0FFFFF; GPIOB_AFRL |= 0x00F00000;


  //--- PB06 alternate functions
  #define PB06_AF00 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x00000000;
  #define PB06_AF01 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x01000000;
  #define PB06_AF02 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x02000000;
  #define PB06_AF03 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x03000000;
  #define PB06_AF04 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x04000000;
  #define PB06_AF05 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x05000000;
  #define PB06_AF06 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x06000000;
  #define PB06_AF07 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x07000000;
  #define PB06_AF08 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x08000000;
  #define PB06_AF09 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x09000000;
  #define PB06_AF10 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x0A000000;
  #define PB06_AF11 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x0B000000;
  #define PB06_AF12 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x0C000000;
  #define PB06_AF13 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x0D000000;
  #define PB06_AF14 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x0E000000;
  #define PB06_AF15 GPIOB_AFRL &= 0xF0FFFFFF; GPIOB_AFRL |= 0x0F000000;


  //--- PB07 alternate functions
  #define PB07_AF00 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0x00000000;
  #define PB07_AF01 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0x10000000;
  #define PB07_AF02 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0x20000000;
  #define PB07_AF03 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0x30000000;
  #define PB07_AF04 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0x40000000;
  #define PB07_AF05 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0x50000000;
  #define PB07_AF06 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0x60000000;
  #define PB07_AF07 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0x70000000;
  #define PB07_AF08 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0x80000000;
  #define PB07_AF09 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0x90000000;
  #define PB07_AF10 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0xA0000000;
  #define PB07_AF11 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0xB0000000;
  #define PB07_AF12 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0xC0000000;
  #define PB07_AF13 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0xD0000000;
  #define PB07_AF14 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0xE0000000;
  #define PB07_AF15 GPIOB_AFRL &= 0x0FFFFFFF; GPIOB_AFRL |= 0xF0000000;


  //--- PB08 alternate functions
  #define PB08_AF00 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x00000000;
  #define PB08_AF01 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x00000001;
  #define PB08_AF02 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x00000002;
  #define PB08_AF03 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x00000003;
  #define PB08_AF04 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x00000004;
  #define PB08_AF05 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x00000005;
  #define PB08_AF06 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x00000006;
  #define PB08_AF07 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x00000007;
  #define PB08_AF08 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x00000008;
  #define PB08_AF09 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x00000009;
  #define PB08_AF10 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x0000000A;
  #define PB08_AF11 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x0000000B;
  #define PB08_AF12 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x0000000C;
  #define PB08_AF13 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x0000000D;
  #define PB08_AF14 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x0000000E;
  #define PB08_AF15 GPIOB_AFRH &= 0xFFFFFFF0; GPIOB_AFRH |= 0x0000000F;


  //--- PB09 alternate functions
  #define PB09_AF00 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x00000000;
  #define PB09_AF01 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x00000010;
  #define PB09_AF02 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x00000020;
  #define PB09_AF03 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x00000030;
  #define PB09_AF04 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x00000040;
  #define PB09_AF05 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x00000050;
  #define PB09_AF06 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x00000060;
  #define PB09_AF07 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x00000070;
  #define PB09_AF08 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x00000080;
  #define PB09_AF09 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x00000090;
  #define PB09_AF10 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x000000A0;
  #define PB09_AF11 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x000000B0;
  #define PB09_AF12 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x000000C0;
  #define PB09_AF13 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x000000D0;
  #define PB09_AF14 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x000000E0;
  #define PB09_AF15 GPIOB_AFRH &= 0xFFFFFF0F; GPIOB_AFRH |= 0x000000F0;


  //--- PB10 alternate functions
  #define PB10_AF00 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000000;
  #define PB10_AF01 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000100;
  #define PB10_AF02 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000200;
  #define PB10_AF03 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000300;
  #define PB10_AF04 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000400;
  #define PB10_AF05 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000500;
  #define PB10_AF06 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000600;
  #define PB10_AF07 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000700;
  #define PB10_AF08 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000800;
  #define PB10_AF09 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000900;
  #define PB10_AF10 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000A00;
  #define PB10_AF11 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000B00;
  #define PB10_AF12 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000C00;
  #define PB10_AF13 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000D00;
  #define PB10_AF14 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000E00;
  #define PB10_AF15 GPIOB_AFRH &= 0xFFFFF0FF; GPIOB_AFRH |= 0x00000F00;


  //--- PB11 alternate functions
  #define PB11_AF00 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x00000000;
  #define PB11_AF01 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x00001000;
  #define PB11_AF02 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x00002000;
  #define PB11_AF03 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x00003000;
  #define PB11_AF04 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x00004000;
  #define PB11_AF05 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x00005000;
  #define PB11_AF06 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x00006000;
  #define PB11_AF07 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x00007000;
  #define PB11_AF08 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x00008000;
  #define PB11_AF09 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x00009000;
  #define PB11_AF10 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x0000A000;
  #define PB11_AF11 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x0000B000;
  #define PB11_AF12 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x0000C000;
  #define PB11_AF13 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x0000D000;
  #define PB11_AF14 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x0000E000;
  #define PB11_AF15 GPIOB_AFRH &= 0xFFFF0FFF; GPIOB_AFRH |= 0x0000F000;


  //--- PB12 alternate functions
  #define PB12_AF00 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x00000000;
  #define PB12_AF01 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x00010000;
  #define PB12_AF02 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x00020000;
  #define PB12_AF03 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x00030000;
  #define PB12_AF04 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x00040000;
  #define PB12_AF05 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x00050000;
  #define PB12_AF06 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x00060000;
  #define PB12_AF07 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x00070000;
  #define PB12_AF08 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x00080000;
  #define PB12_AF09 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x00090000;
  #define PB12_AF10 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x000A0000;
  #define PB12_AF11 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x000B0000;
  #define PB12_AF12 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x000C0000;
  #define PB12_AF13 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x000D0000;
  #define PB12_AF14 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x000E0000;
  #define PB12_AF15 GPIOB_AFRH &= 0xFFF0FFFF; GPIOB_AFRH |= 0x000F0000;


  //--- PB13 alternate functions
  #define PB13_AF00 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00000000;
  #define PB13_AF01 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00100000;
  #define PB13_AF02 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00200000;
  #define PB13_AF03 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00300000;
  #define PB13_AF04 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00400000;
  #define PB13_AF05 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00500000;
  #define PB13_AF06 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00600000;
  #define PB13_AF07 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00700000;
  #define PB13_AF08 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00800000;
  #define PB13_AF09 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00900000;
  #define PB13_AF10 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00A00000;
  #define PB13_AF11 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00B00000;
  #define PB13_AF12 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00C00000;
  #define PB13_AF13 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00D00000;
  #define PB13_AF14 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00E00000;
  #define PB13_AF15 GPIOB_AFRH &= 0xFF0FFFFF; GPIOB_AFRH |= 0x00F00000;


  //--- PB14 alternate functions
  #define PB14_AF00 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x00000000;
  #define PB14_AF01 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x01000000;
  #define PB14_AF02 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x02000000;
  #define PB14_AF03 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x03000000;
  #define PB14_AF04 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x04000000;
  #define PB14_AF05 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x05000000;
  #define PB14_AF06 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x06000000;
  #define PB14_AF07 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x07000000;
  #define PB14_AF08 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x08000000;
  #define PB14_AF09 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x09000000;
  #define PB14_AF10 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x0A000000;
  #define PB14_AF11 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x0B000000;
  #define PB14_AF12 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x0C000000;
  #define PB14_AF13 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x0D000000;
  #define PB14_AF14 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x0E000000;
  #define PB14_AF15 GPIOB_AFRH &= 0xF0FFFFFF; GPIOB_AFRH |= 0x0F000000;


  //--- PB15 alternate functions
  #define PB15_AF00 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0x00000000;
  #define PB15_AF01 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0x10000000;
  #define PB15_AF02 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0x20000000;
  #define PB15_AF03 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0x30000000;
  #define PB15_AF04 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0x40000000;
  #define PB15_AF05 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0x50000000;
  #define PB15_AF06 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0x60000000;
  #define PB15_AF07 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0x70000000;
  #define PB15_AF08 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0x80000000;
  #define PB15_AF09 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0x90000000;
  #define PB15_AF10 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0xA0000000;
  #define PB15_AF11 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0xB0000000;
  #define PB15_AF12 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0xC0000000;
  #define PB15_AF13 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0xD0000000;
  #define PB15_AF14 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0xE0000000;
  #define PB15_AF15 GPIOB_AFRH &= 0x0FFFFFFF; GPIOB_AFRH |= 0xF0000000;


  //-----------------------------------
  //     GPIOC alternate functions     
  //-----------------------------------

  //--- PC00 alternate functions
  #define PC00_AF00 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x00000000;
  #define PC00_AF01 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x00000001;
  #define PC00_AF02 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x00000002;
  #define PC00_AF03 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x00000003;
  #define PC00_AF04 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x00000004;
  #define PC00_AF05 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x00000005;
  #define PC00_AF06 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x00000006;
  #define PC00_AF07 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x00000007;
  #define PC00_AF08 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x00000008;
  #define PC00_AF09 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x00000009;
  #define PC00_AF10 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x0000000A;
  #define PC00_AF11 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x0000000B;
  #define PC00_AF12 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x0000000C;
  #define PC00_AF13 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x0000000D;
  #define PC00_AF14 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x0000000E;
  #define PC00_AF15 GPIOC_AFRL &= 0xFFFFFFF0; GPIOC_AFRL |= 0x0000000F;


  //--- PC01 alternate functions
  #define PC01_AF00 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x00000000;
  #define PC01_AF01 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x00000010;
  #define PC01_AF02 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x00000020;
  #define PC01_AF03 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x00000030;
  #define PC01_AF04 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x00000040;
  #define PC01_AF05 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x00000050;
  #define PC01_AF06 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x00000060;
  #define PC01_AF07 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x00000070;
  #define PC01_AF08 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x00000080;
  #define PC01_AF09 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x00000090;
  #define PC01_AF10 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x000000A0;
  #define PC01_AF11 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x000000B0;
  #define PC01_AF12 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x000000C0;
  #define PC01_AF13 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x000000D0;
  #define PC01_AF14 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x000000E0;
  #define PC01_AF15 GPIOC_AFRL &= 0xFFFFFF0F; GPIOC_AFRL |= 0x000000F0;


  //--- PC02 alternate functions
  #define PC02_AF00 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000000;
  #define PC02_AF01 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000100;
  #define PC02_AF02 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000200;
  #define PC02_AF03 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000300;
  #define PC02_AF04 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000400;
  #define PC02_AF05 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000500;
  #define PC02_AF06 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000600;
  #define PC02_AF07 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000700;
  #define PC02_AF08 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000800;
  #define PC02_AF09 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000900;
  #define PC02_AF10 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000A00;
  #define PC02_AF11 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000B00;
  #define PC02_AF12 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000C00;
  #define PC02_AF13 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000D00;
  #define PC02_AF14 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000E00;
  #define PC02_AF15 GPIOC_AFRL &= 0xFFFFF0FF; GPIOC_AFRL |= 0x00000F00;


  //--- PC03 alternate functions
  #define PC03_AF00 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x00000000;
  #define PC03_AF01 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x00001000;
  #define PC03_AF02 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x00002000;
  #define PC03_AF03 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x00003000;
  #define PC03_AF04 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x00004000;
  #define PC03_AF05 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x00005000;
  #define PC03_AF06 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x00006000;
  #define PC03_AF07 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x00007000;
  #define PC03_AF08 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x00008000;
  #define PC03_AF09 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x00009000;
  #define PC03_AF10 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x0000A000;
  #define PC03_AF11 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x0000B000;
  #define PC03_AF12 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x0000C000;
  #define PC03_AF13 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x0000D000;
  #define PC03_AF14 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x0000E000;
  #define PC03_AF15 GPIOC_AFRL &= 0xFFFF0FFF; GPIOC_AFRL |= 0x0000F000;


  //--- PC04 alternate functions
  #define PC04_AF00 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x00000000;
  #define PC04_AF01 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x00010000;
  #define PC04_AF02 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x00020000;
  #define PC04_AF03 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x00030000;
  #define PC04_AF04 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x00040000;
  #define PC04_AF05 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x00050000;
  #define PC04_AF06 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x00060000;
  #define PC04_AF07 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x00070000;
  #define PC04_AF08 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x00080000;
  #define PC04_AF09 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x00090000;
  #define PC04_AF10 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x000A0000;
  #define PC04_AF11 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x000B0000;
  #define PC04_AF12 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x000C0000;
  #define PC04_AF13 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x000D0000;
  #define PC04_AF14 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x000E0000;
  #define PC04_AF15 GPIOC_AFRL &= 0xFFF0FFFF; GPIOC_AFRL |= 0x000F0000;


  //--- PC05 alternate functions
  #define PC05_AF00 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00000000;
  #define PC05_AF01 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00100000;
  #define PC05_AF02 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00200000;
  #define PC05_AF03 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00300000;
  #define PC05_AF04 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00400000;
  #define PC05_AF05 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00500000;
  #define PC05_AF06 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00600000;
  #define PC05_AF07 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00700000;
  #define PC05_AF08 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00800000;
  #define PC05_AF09 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00900000;
  #define PC05_AF10 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00A00000;
  #define PC05_AF11 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00B00000;
  #define PC05_AF12 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00C00000;
  #define PC05_AF13 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00D00000;
  #define PC05_AF14 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00E00000;
  #define PC05_AF15 GPIOC_AFRL &= 0xFF0FFFFF; GPIOC_AFRL |= 0x00F00000;


  //--- PC06 alternate functions
  #define PC06_AF00 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x00000000;
  #define PC06_AF01 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x01000000;
  #define PC06_AF02 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x02000000;
  #define PC06_AF03 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x03000000;
  #define PC06_AF04 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x04000000;
  #define PC06_AF05 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x05000000;
  #define PC06_AF06 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x06000000;
  #define PC06_AF07 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x07000000;
  #define PC06_AF08 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x08000000;
  #define PC06_AF09 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x09000000;
  #define PC06_AF10 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x0A000000;
  #define PC06_AF11 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x0B000000;
  #define PC06_AF12 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x0C000000;
  #define PC06_AF13 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x0D000000;
  #define PC06_AF14 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x0E000000;
  #define PC06_AF15 GPIOC_AFRL &= 0xF0FFFFFF; GPIOC_AFRL |= 0x0F000000;


  //--- PC07 alternate functions
  #define PC07_AF00 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0x00000000;
  #define PC07_AF01 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0x10000000;
  #define PC07_AF02 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0x20000000;
  #define PC07_AF03 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0x30000000;
  #define PC07_AF04 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0x40000000;
  #define PC07_AF05 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0x50000000;
  #define PC07_AF06 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0x60000000;
  #define PC07_AF07 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0x70000000;
  #define PC07_AF08 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0x80000000;
  #define PC07_AF09 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0x90000000;
  #define PC07_AF10 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0xA0000000;
  #define PC07_AF11 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0xB0000000;
  #define PC07_AF12 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0xC0000000;
  #define PC07_AF13 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0xD0000000;
  #define PC07_AF14 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0xE0000000;
  #define PC07_AF15 GPIOC_AFRL &= 0x0FFFFFFF; GPIOC_AFRL |= 0xF0000000;


  //--- PC08 alternate functions
  #define PC08_AF00 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x00000000;
  #define PC08_AF01 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x00000001;
  #define PC08_AF02 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x00000002;
  #define PC08_AF03 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x00000003;
  #define PC08_AF04 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x00000004;
  #define PC08_AF05 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x00000005;
  #define PC08_AF06 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x00000006;
  #define PC08_AF07 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x00000007;
  #define PC08_AF08 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x00000008;
  #define PC08_AF09 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x00000009;
  #define PC08_AF10 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x0000000A;
  #define PC08_AF11 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x0000000B;
  #define PC08_AF12 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x0000000C;
  #define PC08_AF13 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x0000000D;
  #define PC08_AF14 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x0000000E;
  #define PC08_AF15 GPIOC_AFRH &= 0xFFFFFFF0; GPIOC_AFRH |= 0x0000000F;


  //--- PC09 alternate functions
  #define PC09_AF00 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x00000000;
  #define PC09_AF01 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x00000010;
  #define PC09_AF02 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x00000020;
  #define PC09_AF03 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x00000030;
  #define PC09_AF04 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x00000040;
  #define PC09_AF05 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x00000050;
  #define PC09_AF06 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x00000060;
  #define PC09_AF07 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x00000070;
  #define PC09_AF08 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x00000080;
  #define PC09_AF09 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x00000090;
  #define PC09_AF10 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x000000A0;
  #define PC09_AF11 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x000000B0;
  #define PC09_AF12 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x000000C0;
  #define PC09_AF13 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x000000D0;
  #define PC09_AF14 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x000000E0;
  #define PC09_AF15 GPIOC_AFRH &= 0xFFFFFF0F; GPIOC_AFRH |= 0x000000F0;


  //--- PC10 alternate functions
  #define PC10_AF00 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000000;
  #define PC10_AF01 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000100;
  #define PC10_AF02 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000200;
  #define PC10_AF03 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000300;
  #define PC10_AF04 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000400;
  #define PC10_AF05 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000500;
  #define PC10_AF06 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000600;
  #define PC10_AF07 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000700;
  #define PC10_AF08 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000800;
  #define PC10_AF09 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000900;
  #define PC10_AF10 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000A00;
  #define PC10_AF11 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000B00;
  #define PC10_AF12 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000C00;
  #define PC10_AF13 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000D00;
  #define PC10_AF14 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000E00;
  #define PC10_AF15 GPIOC_AFRH &= 0xFFFFF0FF; GPIOC_AFRH |= 0x00000F00;


  //--- PC11 alternate functions
  #define PC11_AF00 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x00000000;
  #define PC11_AF01 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x00001000;
  #define PC11_AF02 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x00002000;
  #define PC11_AF03 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x00003000;
  #define PC11_AF04 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x00004000;
  #define PC11_AF05 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x00005000;
  #define PC11_AF06 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x00006000;
  #define PC11_AF07 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x00007000;
  #define PC11_AF08 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x00008000;
  #define PC11_AF09 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x00009000;
  #define PC11_AF10 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x0000A000;
  #define PC11_AF11 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x0000B000;
  #define PC11_AF12 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x0000C000;
  #define PC11_AF13 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x0000D000;
  #define PC11_AF14 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x0000E000;
  #define PC11_AF15 GPIOC_AFRH &= 0xFFFF0FFF; GPIOC_AFRH |= 0x0000F000;


  //--- PC12 alternate functions
  #define PC12_AF00 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x00000000;
  #define PC12_AF01 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x00010000;
  #define PC12_AF02 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x00020000;
  #define PC12_AF03 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x00030000;
  #define PC12_AF04 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x00040000;
  #define PC12_AF05 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x00050000;
  #define PC12_AF06 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x00060000;
  #define PC12_AF07 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x00070000;
  #define PC12_AF08 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x00080000;
  #define PC12_AF09 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x00090000;
  #define PC12_AF10 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x000A0000;
  #define PC12_AF11 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x000B0000;
  #define PC12_AF12 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x000C0000;
  #define PC12_AF13 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x000D0000;
  #define PC12_AF14 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x000E0000;
  #define PC12_AF15 GPIOC_AFRH &= 0xFFF0FFFF; GPIOC_AFRH |= 0x000F0000;


  //--- PC13 alternate functions
  #define PC13_AF00 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00000000;
  #define PC13_AF01 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00100000;
  #define PC13_AF02 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00200000;
  #define PC13_AF03 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00300000;
  #define PC13_AF04 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00400000;
  #define PC13_AF05 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00500000;
  #define PC13_AF06 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00600000;
  #define PC13_AF07 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00700000;
  #define PC13_AF08 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00800000;
  #define PC13_AF09 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00900000;
  #define PC13_AF10 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00A00000;
  #define PC13_AF11 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00B00000;
  #define PC13_AF12 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00C00000;
  #define PC13_AF13 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00D00000;
  #define PC13_AF14 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00E00000;
  #define PC13_AF15 GPIOC_AFRH &= 0xFF0FFFFF; GPIOC_AFRH |= 0x00F00000;


  //--- PC14 alternate functions
  #define PC14_AF00 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x00000000;
  #define PC14_AF01 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x01000000;
  #define PC14_AF02 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x02000000;
  #define PC14_AF03 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x03000000;
  #define PC14_AF04 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x04000000;
  #define PC14_AF05 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x05000000;
  #define PC14_AF06 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x06000000;
  #define PC14_AF07 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x07000000;
  #define PC14_AF08 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x08000000;
  #define PC14_AF09 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x09000000;
  #define PC14_AF10 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x0A000000;
  #define PC14_AF11 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x0B000000;
  #define PC14_AF12 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x0C000000;
  #define PC14_AF13 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x0D000000;
  #define PC14_AF14 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x0E000000;
  #define PC14_AF15 GPIOC_AFRH &= 0xF0FFFFFF; GPIOC_AFRH |= 0x0F000000;


  //--- PC15 alternate functions
  #define PC15_AF00 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0x00000000;
  #define PC15_AF01 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0x10000000;
  #define PC15_AF02 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0x20000000;
  #define PC15_AF03 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0x30000000;
  #define PC15_AF04 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0x40000000;
  #define PC15_AF05 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0x50000000;
  #define PC15_AF06 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0x60000000;
  #define PC15_AF07 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0x70000000;
  #define PC15_AF08 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0x80000000;
  #define PC15_AF09 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0x90000000;
  #define PC15_AF10 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0xA0000000;
  #define PC15_AF11 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0xB0000000;
  #define PC15_AF12 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0xC0000000;
  #define PC15_AF13 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0xD0000000;
  #define PC15_AF14 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0xE0000000;
  #define PC15_AF15 GPIOC_AFRH &= 0x0FFFFFFF; GPIOC_AFRH |= 0xF0000000;



  //------------------------------------------------------------------------------------------
  //  Single I/O Port Bit Toggeling
  //------------------------------------------------------------------------------------------
  #define SET_BIT(Adds, Bit)  ((Adds) |=  (0x00000001 << (Bit)))
  #define CLR_BIT(Adds, Bit)  ((Adds) &= ~(0x00000001 << (Bit)))

  #define SET_BITS(Adds, Bits)  ((Adds) |=  (Bits))
  #define CLR_BITS(Adds, Bits)  ((Adds) &= ~(Bits))

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
  //    Input and Test Specific Logical Port Pins Definitions
  //-------------------------------------------------------------------------------------------

  //-------------------------------------------------------------------------------------------
  //  These macros are used to detect if a pin is high or low
  //  for being set as an input or for self testing.
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
  //    Defined by ST Microelectronics
  void __WFI(void);
  void __WFE(void);
  void __SEV(void);
  void __ISB(void);
  void __DSB(void);
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
