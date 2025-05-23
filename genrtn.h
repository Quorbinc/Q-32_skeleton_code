//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                            General Functions Processing Code
//                  -----------------------------------------------------
//
//    This code is for use on the STM32F446 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32FXXX Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//
//=============================================================================================

//-------------------------------------------------------------------------------------------//
//         Program Defines and RAM Storage Definitions                                       //
//-------------------------------------------------------------------------------------------//

#ifndef GENRTN_H
    #define GENRTN_H

    //--- Data Pulse Output Function

    //--- String Manipulation Functions
    void  fnZeroString (u08 ubString[], u16 uwLen);
    u32   fnMergString (u08 ubDst[], u08 ubSrc[], u16 uwPos, u16 uwLen);
    void  fnGrabArrayBytes (u08 ubDstArray[], u08 ubSrcArray[], u16 uwPtr, u16 uwCount);
    s16   fnFindSinS (u08 ubFind[], u08 ubSrc[]);
    u32   fnRTRIM (u08  ubSrc[]);
    u32   fnLTRIM (u08  ubSrc[]);
    void  fnFtoA(flt sfIn, u08 sOut[]);

    //--- Data Extraction Functions
    void  fnTickDelay (u32 ulDelay);
    u08   fnLoByte  (u16 uwWord);
    u08   fnHiByte  (u16 uwWord);
    u16   fnBytesToWord (u08 ubLoByte, u08 ubHiByte);
    u08   fnBCD2Bin (u08 ubBCD);
    u08   fnBin2BCD (u08 ubBin);
    void  fnByte2Hex (u08 ubByte, u08 ubOut[]);
    void  fnWord2Hex (u16 uwWord, u08 ubOut[]);
    void  fnLong2Hex (u32 ulLong, u08 ubOut[]);
    void  fnBig2Hex (u64 uxBig, u08 ubOut[]);
    u08   fnByte2Chr (u08 ubByte);
    void  fnStrCpy (u08 ubDst[], u08 ubSrc[]);
    u16   fnStrLen (u08 ubSrc[]);
    s64   fnCINTF (flt sfFloat);
    s64   fnCINTD (dbl dblFloat);
    u08   fnLc2Uc (u08  ubChar);
    u08   fnUc2Lc (u08  ubChar);

    //--- Generic Function for STM32
    caddr_t _sbrk ( int increment );

#endif
