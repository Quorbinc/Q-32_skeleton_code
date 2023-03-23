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

    //-----Timer initializing functions-----//
    void fnTim1Init (void);
    void fnTim2Init (void);
    void fnTim6Init (void);
    void fnTim7Init (void);
    void fnTim15Init (void);
    void fnTim16Init (void);

    //-----Generic timer output-----//
    void fnTim1Out(u16 uwChange, u08 ubPin);
    void fnTim2Out(u16 uwChange, u08 ubPin);
    void fnTim15Out(u16 uwChange, u08 ubPin);
    void fnTim16Out(u16 uwChange, u08 ubPin);

    //-----generic timer input-----//
    void fnTim1In(u16 uwPeriod, u08 ubPin);
    void fnTim2In(u16 uwPeriod, u08 ubPin);
    void fnTim15In(u16 uwPeriod, u08 ubPin);
    void fnTim16In(u16 uwPeriod, u08 ubPin);

    //-----generc PWM output-----//
    void fnTim1PWMOut(u16 uwLoad, u08 ubPin);
    void fnTim2PWMOut(u16 uwLoad, u08 ubPin);
    void fnTim15PWMOut(u16 uwLoad, u08 ubPin);
    void fnTim16PWMOut(u16 uwLoad, u08 ubPin);

    //-----generic PWM input-----//
    void fnTIM1PWMIn(u16 uwPeriod, u08 ubPin);
    void fnTIM2PWMIn(u16 uwPeriod, u08 ubPin);
    void fnTIM15PWMIn(u16 uwPeriod, u08 ubPin);
#endif
