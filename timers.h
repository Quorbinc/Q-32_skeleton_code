//=============================================================================================
//                                        Quorb Inc.
//                                       ------------
//
//                            Timer input and oputput routines
//                               --------------------------
//
//       This code is for use on the QUORB QMX Processor Series of Micro Controllers
//
//                             Written By:  Sancar James Fredsti
//
//                                  (C) 2021 Quorb Inc
//=============================================================================================

#ifndef TIMER_H
    #define TIMER_H

    #include "projectdefs.h"

    //-----Timer 1 definitions-----//
    #ifdef TIM1_FLAG
        void fnTim1Init (void);
        void fnTim1Out(u16 uwChange, u08 ubPin);
        void fnTim1In(u16 uwPeriod, u08 ubPin);
        void fnTim1PWMOut(u16 uwLoad, u08 ubPin);
        void fnTIM1PWMIn(u16 uwPeriod, u08 ubPin);
    #endif

    //-----Timer 2 definitions-----//
    #ifdef TIM2_FLAG
        void fnTim2Init (void);
        void fnTim2Out(u16 uwChange, u08 ubPin);
        void fnTim2In(u16 uwPeriod, u08 ubPin);
        void fnTim2PWMOut(u16 uwLoad, u08 ubPin);
        void fnTIM2PWMIn(u16 uwPeriod, u08 ubPin);
    #endif

    //-----Timer 6 definitions-----//
    #ifdef TIM6_FLAG
        void fnTim6Init (void);
    #endif

    //-----Timer 7 definitions-----//
    #ifdef TIM7_FLAG
        void fnTim7Init (void);
    #endif

    //-----Timer 15 definitions-----//
    #ifdef TIM15_FLAG
        void fnTim15Init (void);
        void fnTim15Out(u16 uwChange, u08 ubPin);
        void fnTim15In(u16 uwPeriod, u08 ubPin);
        void fnTim15PWMOut(u16 uwLoad, u08 ubPin);
        void fnTIM15PWMIn(u16 uwPeriod, u08 ubPin);
    #endif

    //-----Timer 16 definitions-----//
    #ifdef TIM16_FLAG
        void fnTim16Init (void);
        void fnTim16Out(u16 uwChange, u08 ubPin);
        void fnTim16In(u16 uwPeriod, u08 ubPin);
        void fnTim16PWMOut(u16 uwLoad, u08 ubPin);
    #endif
#endif
