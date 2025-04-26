//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                  RTOS Processing code for Modules using STM32L4XX Proc
//                  -----------------------------------------------------
//
//    This code is for use on the STM32L432 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32FXXX Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//                             Date:        02 June 2022
//
//=============================================================================================

#ifndef COMMONHEADER_H
    #define COMMONHEADER_H

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

    typedef   u08*                        p08;    //--- Pointer to Byte
    typedef   u16*                        p16;    //--- Pointer to Word
    typedef   u32*                        p32;    //--- Pointer to Long
    typedef   void*                       pvo;    //--- Pointer to Void

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

    //--- These defines are for assembler "NOP" series of instructions
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
    #define SET_PRIVLEGED_MODE asm("SVC #0\n\t" ::)

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
    //    ubByte == 8 Bit Unsigned Value                      u08
    //    sbByte == 8 Bit Signed Value                        s08
    //    uwWord == 16 Bit Unsigned Value                     u16
    //    swWord == 16 Bit Signed Value                       s16
    //    ulLong == 32 Bit Unsigned Value                     u32
    //    slLong == 32 Bit Signed Value                       s32
    //    uxBig  == 64 Bit Unsigned Value                     u64
    //    sxBig  == 64 Bit Signed Value                       s64
    //    sfFlt  == Single Precision Floating Point Value     sf
    //    dfFlt  == Double Precision Floating Point Value     df
    //    *ubPtr == Pointer to Byte Values                    *u08
    //    *vPntr == Pointer to VOID Values / Functions        *void
    //------------------------------------------------------------------------------------------

    //--- Word Byte Union
    //--- 16 Bit Multi Number Type unions
    //--- 2 Byte Variable union
    union WB
    {
        u16 uwWord;
        s16 swWord;
        u08 ubByte[2];
        s08 sbByte[2];
    };

    //--- Long Word Byte Pointer Union
    //--- 32 Bit Multi Number Type unions
    //--- 4 Byte Variable union
    union   FLWB                    //--- 4 Bytes of Pass Data
    {
        flt   sfFlt;                  //--- 1 single precision floating point
        u32   ulLong;                 //--- 1 Unsigned Long
        s32   slLong;                 //--- 1 Signed Long
        u16   uwWord[2];              //--- 2 Unsigned Word
        s16   swWord[2];              //--- 2 Signed Word
        u08   ubByte[4];              //--- 4 Unsigned Bytes
        s08   sbByte[4];              //--- 4 Signed Bytes
        u08*  ubPtr[1];               //--- 4 u08 Type Pointer
        void* vPntr;                  //--- 1 Void Type Pointers use " *(type*) definition"
    };

    //--- Double Float Long Word Byte Pointer Union
    //--- 64 Bit Variable union (8 Bytes)
    //--- 8 Byte Variable union
    union DFLWB8                    //--- 8 Bytes Binary / Integer Storage
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
        u08*  ubPtr[2];               //--- 2 u08 Type Pointer
        void* vPntr[2];               //--- Void Type Pointers use " *(type*) definition"
    };

    //--- Double Float Long Word Byte Pointer Union
    //--- 128 Bit Variable union (16 Bytes)
    //--- 16 Byte Variable union
    union DFLWB16                   //--- 16 Bytes Binary / Integer Storage
    {
        dbl   dfFlt[2];               //--- 2 Double Precision Float
        u64   uxBig[2];               //--- 2 Unsigned 64 Bit Integer
        s64   sxBig[2];               //--- 2 Signed 64 Bit Integer
        flt   sfFlt[4];               //--- 4 Single Precision Floats
        u32   ulLong[4];              //--- 4 Unsigned Long
        s32   slLong[4];              //--- 4 Signed Long
        u16   uwWord[8];              //--- 8 Unsigned Words
        s16   swWord[8];              //--- 8 Signed Words
        u08   ubByte[16];             //--- 16 Unsigned Bytes
        s08   sbByte[16];             //--- 16 Signed Bytes
        u08*  ubPtr[4];               //--- 4 u08 Type Pointer
        void* vPntr[4];               //--- Void Type Pointers use " *(type*) definition"
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
        u08*  ubPtr[8];               //--- 8 u08 Type Pointer
        void* vPntr[8];               //--- Void Type Pointers use " *(type*) definition"
    };

    //--- Double Float Long Word Byte Pointer Union
    //--- 64 Byte Variable union
    union DFLWB64                   //--- 64 Bytes Variable
    {
        dbl   dfFlt[8];               //--- 8 Double Precision Float
        u64   uxBig[8];               //--- 8 Unsigned 64 Bit Integer
        s64   sxBig[8];               //--- 8 Signed 64 Bit Integer
        flt   sfFlt[16];              //--- 16 Single Precision Floats
        u32   ulLong[16];             //--- 16 Unsigned Long
        s32   slLong[16];             //--- 16 Signed Long
        u16   uwWord[32];             //--- 32 Unsigned Words
        s16   swWord[32];             //--- 32 Signed Words
        u08   ubByte[64];             //--- 64 Unsigned Bytes
        s08   sbByte[64];             //--- 64 Signed Bytes
        u08*  ubPtr[16];              //--- 16 u08 Type Pointer
        void* vPntr[16];              //--- Void Type Pointers use " *(type*) definition"
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
        u08*  ubPtr[64];              //--- 64 u08 Type Pointer
        void* vPntr[64];              //--- Void Type Pointers use: *(type*) definition"
    };

    //--- Handy Dandy General Definitions
    //--- Good & Bad
    #define   OK        0
    #define   GOOD      0
    #define   NOT_GOOD  !0
    #define   BAD       !0

    //--- High and Low States
    #define   HIGH    1
    #define   LOW     0
    #define   High    1
    #define   Low     0
    #define   HI      1
    #define   LO      0
    #define   Hi      1
    #define   Lo      0

    //--- True and False States
    #define   TRUE    1
    #define   FALSE   0
    #define   True    1
    #define   False   0
    #define   true    1
    #define   false   0

    //--- On and Off States
    #define   ON      1
    #define   OFF     0
    #define   On      1
    #define   Off     0
    #define   on      1
    #define   off     0

    //--- Set and Clear States
    #define   SET     1
    #define   CLR     0
    #define   Set     1
    #define   Clr     0
    #define   set     1
    #define   clr     0

    //--- Yes, No and Maybe States
    #define   YES     1
    #define   NO      0
    #define   MAYBE   -1
    #define   Yes     1
    #define   No      0
    #define   Maybe   -1
    #define   yes     1
    #define   no      0
    #define   maybe   -1

    //--- ZERO definitions
    #define   ZERO    0
    #define   Zero    0
    #define   zero    0


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
