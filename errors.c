//========================================================1====================================
//                                        Quorb Inc.
//                                       ------------
//
//                                Error Handeling Routines
//                               --------------------------
//
//       This code is for use on the QUORB QMX Processor Series of Micro Controllers
//
//                             Written By:  Sancar James Fredsti
//
//                                  (C) 2021 Quorb Inc
//=============================================================================================

#include "projectdefs.h"

//--- Error Queue (FIFO) pointers & counters
u16 volatile  uwErrIptr;                          //--- Error Queue In Pointer
u16 volatile  uwErrOptr;                          //--- Error Queue Out Pointer
u16 volatile  uwErrCntr;                          //--- Error Queue Counter

struct ErrorS ErrFIFO [32];

//--- Error Quantity Counters
u16 uwCore_Errs;                                  //--- CorTex Errors
u16 uwSCB_Errs;                                   //--- System Control Block Errors
u16 uwSysTick_Errs;                               //--- SysTick Errors
u16 uwMemory_Errs;                                //--- Memory Errors
u16 uwFPU_Errs;                                   //--- FPU Errors
u16 uwMath_Usage_Errs;                            //--- Math Usage Errors
u16 uwMath_Hardware_Errs;                         //--- Math Hardware Errors
u16 uwRTOS_Errs;                                  //--- RTOS Error
u16 uwSched_Errs;                                 //--- Scheduling Errors
u16 uwNoTimer_Errs;                               //--- No Timers Available
u16 uwQueueFull_Errs;                             //--- Task Queue Full Errors
u16 uwDisp_Errs;                                  //--- Dispatching Errors
u16 uwMath_Errs;                                  //--- Number of Math Errors
u16 uwCom_Errs;                                   //--- Number of Communications Errors
u16 uwUSART1_Errs;                                //--- Number of USART-1 Errors
u16 uwUSART2_Errs;                                //--- Number of USART-2 Errors
u16 uwUnkn_Errs;                                  //--- Number of USB Com Errors
u16 uwUSB_Errs;

//--- Generic Error Processing Error
void  fnError (u16 uwErrCode)
{
    //--- Exit if No Error
    if (!uwErrCode) return;

    //--- Process Error depending on TYPE Code
    switch (uwErrCode & 0xF000)
    {
        //--- Nothing Error Type
        case 0x0000:
            break;

        //--- CORTEX Core Error
        case 0x1000:
            uwCore_Errs++;                             //--- Bump Error Type Counter
            break;

        //--- System Control Block Error
        case 0x2000:
            break;

        //--- Memory Protection Error
        case 0x3000:
            break;

        //--- FPU Error
        case 0x4000:
            break;

        //--- STACK Over/Under Flow
        case 0x5000:
            break;

        //--- Math HW (+-*\)
        case 0x6000:
            break;

        //--- Math Library Error
        case 0x7000:
            break;

        //--- Peripherial HW Error
        case 0x8000:
            break;

        //--- User SW Error
        case 0x9000:
            break;

        //--- NMI Fault
        case 0xA000:
            break;

        //--- SysTick Error
        case 0xB000:
            break;

        //--- Hard Fault Error
        case 0xC000:
            break;

        //--- USB Defined Error
        case 0xD000:
            break;

        //--- Undefined
        case 0xE000:
            break;

        //--- RTOS Error
        case 0xF000:
            if (uwRTOS_Errs < 0xFFFE)
            uwRTOS_Errs++;                                //--- Bump the Error Type Counter

        //--- Switch on RTOS Error Type
        switch (uwErrCode & 0x0FFF)
        {
            //--- Unknown
            case 0x0000:
                break;

            //--- Scheduling Queue Full
            case 0x0001:
                break;

            //--- Scheduling No Timers Available
            case 0x0002:
                break;

            //--- Scheduling Address Bad
            case 0x0003:
                break;

            //--- Scheduling Error Generic
            case 0x0004:
                break;

            //--- Dispatch Error Address Bad
            case 0x0005:
                break;

            //--- Dispatch Error
            case 0x0006:
                break;

            //---
            case 0x0007:
                break;

            //---
            case 0x0008:
                break;

            //---
            case 0x0009:
                break;

            //---
            case 0x000A:
                break;

            //---
            case 0x000B:
                break;

            //---
            case 0x000C:
                break;

            //---
            case 0x000D:
                break;

            //---
            case 0x000E:
                break;

            //---
            case 0x000F:
                break;
        }
        break;

        //--- Default Unknown Error
        default:
            uwUnkn_Errs++;
            return;
    }
}
