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

//---------------------------------------------------------------------------------------------
//         Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#include "projectdefs.h"

//---------------------------------------------------------------------------------------------
//    Select Pulse Out GPIO Pins
//---------------------------------------------------------------------------------------------

vu32* Cptr;                                       //--- Clock Bit Port Pointer
u32 ulCsetMask;                                   //--- Clock Bit Mask General
u32 ulCclrMask;                                   //--- Clock Bit Mask General

vu32* Dptr;                                       //--- Data Bit Port Pointer
u32 ulDsetMask;                                   //--- Data Bit Mask General
u32 ulDclrMask;                                   //--- Data Bit Mask General

//---------------------------------------------------------------------------------------------
//--- Define the Port and Pin for Clock & Data Value Output
//    Define these before compiling Program.
//    These MACROS are for use with the PORT BSRR Register
//---------------------------------------------------------------------------------------------

#define Cptr  &GPIOA_BSRR                         //--- Define Clock Port Pointer
#define Dptr  &GPIOA_BSRR                         //--- Define Data Port Pointer

#define Dpin  06                                  //--- Define Data Port Bit
#define Cpin  07                                  //--- Define Clock Port Bit

#define SetCpin   *Cptr = ulCsetMask
#define ClrCpin   *Cptr = ulCclrMask
#define SetDpin   *Dptr = ulDsetMask
#define ClrDpin   *Dptr = ulDclrMask

//---  #define SET_BIT(Adds, Bit)  ((u32* Adds) |=  (0x00000001 << (Bit)))
//---  #define CLR_BIT(Adds, Bit)  ((u32* Adds) &= ~(0x00000001 << (Bit+16)))

//---------------------------------------------------------------------------------------------
//  Pulse A Value Out To I/O Pins
//  Pulse Either Byte, Woer, or Long on I/O Pins
//  NOTE: I/O Pins must be sefined prior to calling this function
//
//  Entry:  Value is ALWAYS an unsigned long
//          Type (0)=Nibble) (1)=Byte, (2)=Word, (3)=Long
//---------------------------------------------------------------------------------------------
//
//  Input:  ulVal   =   up to a 32 Bit Value
//          ubLen   =   Number of Bits to Output
//
//  Address Clk = GPIO(A-F)_BSRR
//  ubClkBit = Clock Port Bit (0-15)
//
//  Address Dat = GPIO(A-F)_BSRR
//  ubDatBit = Data Port Bit  (0-15)
//---------------------------------------------------------------------------------------------
void  fnPulseValueOut ( u08 ubType, u32 ulPVO )
{
    switch (ubType)
    {
        //--- Pulse Nibble Out
        case 0:
            fnPulseNibbleOut ((u08) (ulPVO & 0x0000000F));
            break;

        //--- Pulse Byte Out
        case 1:
            fnPulseByteOut ((u08) (ulPVO & 0x000000FF));
            break;

        //--- Pulse Word Out
        case 2:
            fnPulseWordOut ((u16) (ulPVO & 0x0000FFFF));
            break;

        //--- Pulse Long Out
        case 3:
            fnPulseLongOut ((u32) (ulPVO & 0xFFFFFFFF));
            break;

        //--- Selection Error - Just Exit
        default:
            break;
    }

}


//---------------------------------------------------------------------------------------------
//    Set up Pins to use for Pulse Data Outs
//    A pin is defined as a value from 0x00 to 0xFF. The High Nibble is the PORT Value
//    with 0x0# = GPIOA and 0xF# = GPIOO.  The Low Nibble is the Pin Number from 0 to 15
//    with 0x#0 = Pin-00 and 0x#F = Pin-15.
//    Example: PORT "E"  PIN #8 = [ 0x48 ]
//
//    Bits are pulsed out starting with:
//      MSB (Shows on Left Side of pulse train) to
//      LSB (Shows on Right Side of pulse train)
//
//      Bit Layout On Scope Screen
//     MSB                            LSB
//      |                              |
//      ................................
//      33222222222211111111110000000000
//      10987654321098765432109876543210
//---------------------------------------------------------------------------------------------
//--- Output A Pulse Byte
void  fnPulseNibbleOut (u08 ubPulseNibble)
{
    u16 uwA;
    u08 ubB = 0x04;                                 //--- Set Hi Bit Mask

    //--- Define Bit Masks for Set/Clr Pins
    ulCsetMask = (0x00000001 << Cpin);
    ulCclrMask = (0x00000001 << (Cpin + 16));
    ulDsetMask = (0x00000001 << Dpin);
    ulDclrMask = (0x00000001 << (Dpin + 16));

    //--- Clear Clock & Data Pins
    ClrCpin;
    ClrDpin;

    //--- Pulse the Value Out
    for (uwA = 0; uwA < 4; uwA++)
    {
        if (ubPulseNibble & ubB)
        {
            SetDpin;
        }
        else
        {
            ClrDpin;
        }

        nop4;
        SetCpin;                                      //--- Set Clock Hi
        nop4;
        ClrCpin;                                      //--- Set Clock Lo
        nop4;
        ClrDpin;                                      //--- Set Data Lo

        ubB = ubB >> 1;                               //--- Rotate to Next Bit Lower
    }

    //--- Inter Value Time Spacer
    for (uwA = 0; uwA < 12; uwA++)
    {
        nop4;                                          //--- Inter Value Spacer
    }
}

//--- Output A Pulse Byte
void  fnPulseByteOut (u08 ubPulseByte)
{
    u16 uwA;
    u08 ubB = 0x80;                                 //--- Set High Bit Mask

    //--- Define Bit Masks for Set/Clr Pins
    ulCsetMask = (0x00000001 << Cpin);
    ulCclrMask = (0x00000001 << (Cpin + 16));
    ulDsetMask = (0x00000001 << Dpin);
    ulDclrMask = (0x00000001 << (Dpin + 16));

    //--- Clear Clock & Data Pins
    ClrCpin;
    ClrDpin;

    //--- Pulse the Value Out
    for (uwA = 0; uwA < 8; uwA++)
    {
        if (ubPulseByte & ubB)
        {
            SetDpin;
        }
        else
        {
            ClrDpin;
        }

        nop4;
        SetCpin;                                      //--- Set Clock Hi
        nop4;
        ClrCpin;                                      //--- Set Clock Lo
        nop4;
        ClrDpin;                                      //--- Set Data Lo
        ubB = ubB >> 1;                               //--- Rotate to Next Bit Lower
    }

    //--- Inter Value Time Spacer
    for (uwA = 0; uwA < 12; uwA++)
    {
        nop4;                                          //--- Inter Value Spacer
    }
}

//--- Output a 16 Bit Word Value
void  fnPulseWordOut (u16 uwPulseWord)
{
    u16 uwA;
    u16 uwB = 0x8000;                                 //--- Set MSB Bit Mask

    //--- Define Bit Masks for Set/Clr Pins
    ulCsetMask = (0x00000001 << Cpin);
    ulCclrMask = (0x00000001 << (Cpin + 16));
    ulDsetMask = (0x00000001 << Dpin);
    ulDclrMask = (0x00000001 << (Dpin + 16));

    //--- Clear Clock & Data Pins
    ClrCpin;
    ClrDpin;

    //--- Pulse the Value Out
    for (uwA = 0; uwA < 16; uwA++)
    {
        if (uwPulseWord & uwB)
        {
            SetDpin;
        }
        else
        {
            ClrDpin;
        }

        nop4;
        SetCpin;                                      //--- Set Clock Hi
        nop4;
        ClrCpin;                                      //--- Set Clock Hi
        nop4;
        ClrDpin;                                      //--- Set Clock Hi

        uwB = uwB >> 1;                               //--- Rotate to Next Bit Lower
    }

    //--- Inter Value Time Spacer
    for (uwA = 0; uwA < 12; uwA++)
    {
        nop4;                                          //--- Inter Value Spacer
    }
}

//--- Output a 32 Bit Long Value
//    Outputs Data Bits Highest to Lowest order

void  fnPulseLongOut (u32 ulPulseLong)
{
    u16 uwA;
    u32 ulB = 0x80000000;                            //--- Set MSB Bit Mask

    //--- Define Bit Masks for Set/Clr Pins
    ulCsetMask = (0x00000001 << Cpin);
    ulCclrMask = (0x00000001 << (Cpin + 16));
    ulDsetMask = (0x00000001 << Dpin);
    ulDclrMask = (0x00000001 << (Dpin + 16));

    //--- Clear Clock & Data Pins
    ClrCpin;
    ClrDpin;

    //--- Pulse the Value Out
    for (uwA = 0; uwA < 32; uwA++)
    {
        if ((ulPulseLong & ulB) > 0)
        {
            SetDpin;
        }
        else
        {
            ClrDpin;
        }

        nop4;
        SetCpin;                                      //--- Set Clock Hi
        nop4;
        ClrCpin;                                      //--- Set Clock Hi
        nop4;
        ClrDpin;                                      //--- Set Clock Hi

        ulB = ulB >> 1;                               //--- Rotate to Next Bit Lower
    }

    //--- Inter Value Time Spacer
    for (uwA = 0; uwA < 12; uwA++)
    {
        nop4;                                          //--- Inter Value Spacer
    }
}


//---------------------------------------------------------------------------------------------
//    Read a CPU CORE Register and Return to Caller
//
//    Register Number Returns Register as in List
//    -----     NAME
//      00      R0
//      01      R1
//      02      R2
//      03      R3
//      04      R4
//      05      R5
//      06      R6
//      07      R7
//      08      R8
//      09      R9
//      10      R10
//      11      R11
//      12      R12
//      13      R13   SP
//      14      R14   LR
//      15      R15   PC
//      16      PSR
//      17      PRIMASK
//      18      FAULTMASK
//      19      BASEPRI
//      20      CONTROL
//
//---------------------------------------------------------------------------------------------
u32  fnReadCPUregister (u08 ubRegNum)
{
    u32 ulResult;

    switch (ubRegNum)
    {
        //--- Register R0
        case 0:
            __ASM volatile ("MOV R0, R0\n\t" : "=r" (ulResult) );
            break;

        //--- Register R1
        case 1:
            __ASM volatile ("MOV R0, R1\n\t" : "=r" (ulResult) );
            break;

        //--- Register R2
        case 2:
            __ASM volatile ("MOV R0, R2\n\t" : "=r" (ulResult) );
            break;

        //--- Register R3
        case 3:
            __ASM volatile ("MOV R0, R3\n\t" : "=r" (ulResult) );
            break;

        //--- Register R4
        case 4:
            __ASM volatile ("MOV R0, R4\n\t" : "=r" (ulResult) );
            break;

        //--- Register R5
        case 5:
            __ASM volatile ("MOV R0, R5\n\t" : "=r" (ulResult) );
            break;

        //--- Register R6
        case 6:
            __ASM volatile ("MOV R0, R6\n\t" : "=r" (ulResult) );
            break;

        //--- Register R7
        case 7:
            __ASM volatile ("MOV R0, R7\n\t" : "=r" (ulResult) );
            break;

        //--- Register R8
        case 8:
            __ASM volatile ("MOV R0, R8\n\t" : "=r" (ulResult) );
            break;

        //--- Register R9
        case 9:
            __ASM volatile ("MOV R0, R9\n\t" : "=r" (ulResult) );
            break;

        //--- Register R10
        case 10:
            __ASM volatile ("MOV R0, R10\n\t" : "=r" (ulResult) );
            break;

        //--- Register R11
        case 11:
            __ASM volatile ("MOV R0, R11\n\t" : "=r" (ulResult) );
            break;

        //--- Register R12
        case 12:
            __ASM volatile ("MOV R0, R12\n\t" : "=r" (ulResult) );
            break;

        //--- Register R13  STACK POINTER
        case 13:
            __ASM volatile ("MOV R0, SP\n\t" : "=r" (ulResult) );
            break;

        //--- Register R14  LINK REGISTER - RETURN LINK
        case 14:
            __ASM volatile ("MOV R0, LR\n\t" : "=r" (ulResult) );
            break;

        //--- Register R15  PROGRAM COUNTER (PC)
        case 15:
            __ASM volatile ("MOV R0, PC\n\t" : "=r" (ulResult) );
            break;

        //--- Register PSR
        case 16:
            __ASM volatile ("MRS R0, PSR\n\t" : "=r" (ulResult) );
            break;

        //--- Register PRIMASK
        case 17:
            __ASM volatile ("MRS R0, PRIMASK\n\t" : "=r" (ulResult) );
            break;

        //--- Register FAULTMASK
        case 18:
            __ASM volatile ("MRS R0, FAULTMASK\n\t" : "=r" (ulResult) );
            break;

        //--- Register BASEPRI
        case 19:
            __ASM volatile ("MRS R0, BASEPRI\n\t" : "=r" (ulResult) );
            break;

        //--- Register CONTROL
        case 20:
            __ASM volatile ("MRS R0, CONTROL\n\t" : "=r" (ulResult) );
            break;

        default:
            ulResult = 0xFFFFFFFF;
            break;
    }
    return ulResult;
}

//---------------------------------------------------------------------------------------------
//    Output a series of Pulses on Clock Pin
//---------------------------------------------------------------------------------------------
void  fnPulseOut (u08 ubPulseCntr)
{
    //--- Output a short pulse
    if (ubPulseCntr)
    {
        SetCpin;
        nop8;                                         //--- Tiny Delay
        ClrCpin;
        ubPulseCntr--;                                //--- Down Count # of Pulses
        nop12;
    }
}
