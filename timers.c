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

#include "projectdefs.h"


//-----Timer initializing functions-----//
void fnTim1Init (void)   //---Initializes Timer 1
{
    //--- activate the timer in RCC
    RCC_APB2ENR       |= 0x00000800;
    RCC_APB2SMENR     |= 0x00000800;

    //--- Set all tmer registers to their default values
    TIM1_CR1          = 0x0000;
    TIM1_CR2          = 0x00000000;
    TIM1_SMCR         = 0x00000000;
    TIM1_DIER         = 0x0000;
    TIM1_SR           = 0x00000000;
    TIM1_EGR          = 0x0000;
    TIM1_CCMR1        = 0x00000000;
    TIM1_CCMR2        = 0x00000000;
    TIM1_CCER         = 0x00000000;
    TIM1_CNT          = 0x00000000;
    TIM1_PSC          = 0x0000;
    TIM1_ARR          = 0xFFFF;
    TIM1_RCR          = 0x0000;
    TIM1_CCR1         = 0x0000;
    TIM1_CCR2         = 0x0000;
    TIM1_CCR3         = 0x0000;
    TIM1_CCR4         = 0x0000;
    TIM1_BDTR         = 0x00000000;
    TIM1_DCR          = 0x0000;
    TIM1_DMAR         = 0x00000000;
}

void fnTim2Init (void)   //---Initializes Timer 2
{
    //--- activate the timer in RCC
    RCC_APB1ENR1      |= 0x00000001;
    RCC_APB1SMENR1    |= 0x00000001;

    //--- Set all timer registers to their default values
    TIM2_CR1          = 0x0000;
    TIM2_CR2          = 0x0000;
    TIM2_SMCR         = 0x00000000;
    TIM2_DIER         = 0x00000000;
    TIM2_SR           = 0x0000;
    TIM2_EGR          = 0x0000;
    TIM2_CCMR1        = 0x0000;
    TIM2_CCMR2        = 0x0000;
    TIM2_CCER         = 0x0000;
    TIM2_CNT          = 0x00000000;
    TIM2_PSC          = 0x0000;
    TIM2_ARR          = 0xFFFFFFFF;
    TIM2_CCR1         = 0x00000000;
    TIM2_CCR2         = 0x00000000;
    TIM2_CCR3         = 0x00000000;
    TIM2_CCR4         = 0x00000000;
    TIM2_DCR          = 0x0000;
    TIM2_DMAR         = 0x0000;
}

void fnTim6Init (void)   //---Initializes Timer 6
{
    //--- Activate the timer in RCC
    RCC_APB1ENR1      |= 0x00000010;
    RCC_APB1SMENR1    |= 0x00000010;

    //--- Set all timer registers to their default values
    TIM6_CR1          = 0x0000;
    TIM6_CR2          = 0x0000;
    TIM6_DIER         = 0x0000;
    TIM6_SR           = 0x0000;
    TIM6_EGR          = 0x0000;
    TIM6_CNT          = 0x00000000;
    TIM6_PSC          = 0x0000;
    TIM6_ARR          = 0xFFFF;
}

void fnTim7Init (void)   //---Initializes Timer 7
{
    //--- Activate the timer in RCC
    RCC_APB1ENR1      |= 0x00000020;
    RCC_APB1SMENR1    |= 0x00000020;

    //--- Set all timer registers to their default values
    TIM7_CR1          = 0x0000;
    TIM7_CR2          = 0x0000;
    TIM7_DIER         = 0x0000;
    TIM7_SR           = 0x0000;
    TIM7_EGR          = 0x0000;
    TIM7_CNT          = 0x00000000;
    TIM7_PSC          = 0x0000;
    TIM7_ARR          = 0xFFFF;
}

void fnTim15Init (void)  //---Initializes Timer 15
{
    //--- Activate the timer in RCC
    RCC_APB2ENR       |= 0x00010000;
    RCC_APB2SMENR     |= 0x00010000;

    //--- Set all timer registers to their default values
    TIM15_CR1         = 0x0000;
    TIM15_CR2         = 0x0000;
    TIM15_SMCR        = 0x00000000;
    TIM15_DIER        = 0x0000;
    TIM15_SR          = 0x0000;
    TIM15_EGR         = 0x0000;
    TIM15_CCMR1       = 0x00000000;
    TIM15_CCER        = 0x0000;
    TIM15_CNT         = 0x00000000;
    TIM15_PSC         = 0x0000;
    TIM15_ARR         = 0xFFFF;
    TIM15_RCR         = 0x0000;
    TIM15_CCR1        = 0x0000;
    TIM15_CCR2        = 0x0000;
    TIM15_BDTR        = 0x00000000;
    TIM15_DCR         = 0x0000;
    TIM15_DMAR        = 0x0000;
}

void fnTim16Init (void)  //---Initializes Timer 16
{
    //--- Activate the timer in RCC
    RCC_APB2ENR       |= 0x00020000;
    RCC_APB2SMENR     |= 0x00020000;

    //--- Set all timer registers to their default values
    TIM16_CR1         = 0x0000;
    TIM16_CR2         = 0x0000;
    TIM16_DIER        = 0x0000;
    TIM16_SR          = 0x0000;
    TIM16_EGR         = 0x0000;
    TIM16_CCMR1       = 0x00000000;
    TIM16_CCER        = 0x0000;
    TIM16_CNT         = 0x00000000;
    TIM16_PSC         = 0x0000;
    TIM16_ARR         = 0xFFFF;
    TIM16_RCR         = 0x0000;
    TIM16_CCR1        = 0x0000;
    TIM16_BDTR        = 0x00000000;
    TIM16_DCR         = 0x0000;
    TIM16_DMAR        = 0x0000;
}

//-----generic Timer output-----//
void fnTim1Out(u16 uwChange, u08 ubPin) //--- Output for timer 1
{
    //--- can adjust from 10000 pulses per second to one pulse per 6 seconds.
    switch (ubPin)
    {
        case PA08: //--- TIM1_CH1
            TIM1_CR1 &= 0xFFFE;        //--- disables cen bit
            TIM1_PSC = 7199;           //--- scaled for 10000 counts per second
            TIM1_ARR = uwChange-1;     //--- how many counts until count restarts
            TIM1_CCMR1 |= 0x00000030;  //--- sets OC1M bits to toggle on channel pin
            TIM1_CCER |= 0x00000001;   //--- enables capture compare register for channel 1.
            TIM1_BDTR |= 0x00004000;   //--- Enable MOE bit
            TIM1_CR1 |= 0x0001;        //--- enable CEN bit to start the counter
            break;

        case PA09: //--- TIM1_CH2
            TIM1_CR1 &= 0xFFFE;
            TIM1_PSC = 7199;
            TIM1_ARR = uwChange-1;
            TIM1_CCMR1 |= 0x00003000;  //--- sets OC2M bits to toggle on channel pin
            TIM1_CCER |= 0x00000010;   //--- enables capture compare register for channel 2.
            TIM1_BDTR |= 0x00004000;
            TIM1_CR1 |= 0x0001;
            break;

        case PA10: //--- TIM1_CH3
            TIM1_CR1 &= 0xFFFE;
            TIM1_PSC = 7199;
            TIM1_ARR = uwChange-1;
            TIM1_CCMR2 |= 0x00000030;  //--- sets OC3M bits to toggle on channel pin
            TIM1_CCER |= 0x00000100;   //--- enables capture compare register for channel 3.
            TIM1_BDTR |= 0x00004000;
            TIM1_CR1 |= 0x0001;
            break;

        case PA11: //--- TIM1_CH4
            TIM1_CR1 &= 0xFFFE;
            TIM1_PSC = 7199;
            TIM1_ARR = uwChange-1;
            TIM1_CCMR2 |= 0x00003000;  //--- sets OC4M bits to toggle on channel pin
            TIM1_CCER |= 0x00001000;   //--- enables capture compare register for channel 4.
            TIM1_BDTR |= 0x00004000;
            TIM1_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

void fnTim2Out(u16 uwChange, u08 ubPin) //--- Output for timer 2
{
    //--- can adjust from 10000 pulses per second to one pulse per 5 days.
    switch (ubPin)
    {
        case PA00: //--- TIM2_CH1
            TIM2_CR1 &= 0xFFFE;        //--- disables cen bit
            TIM2_PSC = 7199;           //--- scaled for 10000 counts per second
            TIM2_ARR = uwChange - 1;   //--- how many counts until count restarts
            TIM2_CCMR1 |= 0x00000030;  //--- sets OC1M bits to toggle on channel pin
            TIM2_CCER |= 0x0001;       //--- enables capture compare register for channel 1
            TIM2_CR1 |= 0x0001;        //--- enable CEN bit to start the counter
            break;

        case PA05: //--- TIM2_CH1
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwChange - 1;
            TIM2_CCMR1 |= 0x00000030;  //--- sets OC1M bits to toggle on channel pin
            TIM2_CCER |= 0x0001;       //--- enables capture compare register for channel 1
            TIM2_CR1 |= 0x0001;
            break;

        case PA15: //--- TIM2_CH1
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwChange - 1;
            TIM2_CCMR1 |= 0x00000030;  //--- sets OC1M bits to toggle on channel pin
            TIM2_CCER |= 0x0001;       //--- enables capture compare register for channel 1
            TIM2_CR1 |= 0x0001;
            break;

        case PA01: //--- TIM2_CH2
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwChange - 1;
            TIM2_CCMR1 |= 0x00003000;  //--- sets OC2M bits to toggle on channel pin
            TIM2_CCER |= 0x0010;       //--- enables capture compare register for channel 2
            TIM2_CR1 |= 0x0001;
            break;

        case PB03: //--- TIM2_CH2
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwChange - 1;
            TIM2_CCMR1 |= 0x00003000;  //--- sets OC2M bits to toggle on channel pin
            TIM2_CCER |= 0x0010;       //--- enables capture compare register for channel 2
            TIM2_CR1 |= 0x0001;
            break;

        case PA02: //--- TIM2_CH3
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwChange - 1;
            TIM2_CCMR2 |= 0x00000030;  //--- sets OC3M bits to toggle on channel pin
            TIM2_CCER |= 0x0100;       //--- enables capture compare register for channel 3
            TIM2_CR1 |= 0x0001;
            break;

        case PA03: //--- TIM2_CH4
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwChange - 1;
            TIM2_CCMR2 |= 0x00003000;  //--- sets OC4M bits to toggle on channel pin
            TIM2_CCER |= 0x1000;       //--- enables capture compare register for channel 4
            TIM2_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

void fnTim15Out(u16 uwChange, u08 ubPin) //--- Output for timer 15
{
    switch (ubPin)
    {
        case PA02: //--- TIM15_ CH1
            TIM15_CR1 &= 0xFFFE;       //--- disables cen bit
            TIM15_PSC = 7199;          //--- scaled for 10000 counts per second
            TIM15_ARR = uwChange - 1;  //--- how many counts until count restarts
            TIM15_CCMR1 |= 0x00000030; //--- sets OC1M bits to toggle on channel pin
            TIM15_CCER |= 0x0001;      //--- enables capture compare register for channel 1
            TIM15_BDTR |= 0x00008000;  //--- Enable the MOE bit
            TIM15_CR1 |= 0x0001;       //--- enable CEN bit to start the counter
            break;

        case PA03: //--- TIM15_ CH2
            TIM15_CR1 &= 0xFFFE;
            TIM15_PSC = 7199;
            TIM15_ARR = uwChange - 1;
            TIM15_CCMR1 |= 0x00003000; //--- sets OC2M bits to toggle on channel pin
            TIM15_CCER |= 0x0010;      //--- enables capture compare register for channel 2
            TIM15_BDTR |= 0x00008000;
            TIM15_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

void fnTim16Out(u16 uwChange, u08 ubPin) //--- Output for timer 16
{
    switch (ubPin)
    {
        case PA06: //--- TIM15_ CH1
            TIM16_CR1 &= 0xFFFE;       //--- disables cen bit
            TIM16_PSC = 7199;          //--- scaled for 10000 counts per second
            TIM16_ARR = uwChange - 1;  //--- how many counts until count restarts
            TIM16_CCMR1 |= 0x00000030; //--- sets OC1M bits to toggle on channel pin
            TIM16_CCER |= 0x0001;      //--- enables capture compare register for channel 1
            TIM16_BDTR |= 0x00008000;  //--- Enable the MOE bit
            TIM16_CR1 |= 0x0001;       //--- enable CEN bit to start the counter
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

//-----generic timer input-----//
void fnTim1In(u16 uwPeriod, u08 ubPin) //--- Input for timer 1
{
    switch (ubPin)
    {
        case PA08: //--- TIM1_CH1
            TIM1_CR1 &= 0xFFFE;        //--- disables cen bit
            TIM1_PSC = 7199;           //--- Scale the timer to 10000 counts per second
            TIM1_ARR = uwPeriod - 1;   //--- determine what range in which you want the timer to run
            TIM1_CCMR1 |= 0x00000001;  //--- Set CC1S to 01 to enable input for channel 1
            TIM1_CCER |= 0x00000001;   //--- enable capture compare register on channel 1
            TIM1_CR1 |= 0x0001;        //--- enable CEN bit to start the counter
            break;

        case PA09: //--- TIM1_CH2
            TIM1_CR1 &= 0xFFFE;
            TIM1_PSC = 7199;
            TIM1_ARR = uwPeriod - 1;
            TIM1_CCMR1 |= 0x00000100;  //--- Set CC2S to 01 to enable input for channel 2
            TIM1_CCER |= 0x00000010;   //--- enable capture compare register on channel 2
            TIM1_CR1 |= 0x0001;
            break;

        case PA10: //--- TIM1_CH3
            TIM1_CR1 &= 0xFFFE;
            TIM1_PSC = 7199;
            TIM1_ARR = uwPeriod - 1;
            TIM1_CCMR2 |= 0x00000001;  //--- Set CC3S to 01 to enable input for channel 3
            TIM1_CCER |= 0x00000100;   //--- enable capture compare register on channel 3
            TIM1_CR1 |= 0x0001;
            break;

        case PA11: //--- TIM1_CH4
            TIM1_CR1 &= 0xFFFE;
            TIM1_PSC = 7199;
            TIM1_ARR = uwPeriod - 1;
            TIM1_CCMR2 |= 0x00000100;  //--- Set CC4S to 01 to enable input for channel 4
            TIM1_CCER |= 0x00001000;   //--- enable capture compare register on channel 4
            TIM1_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

void fnTim2In(u16 uwPeriod, u08 ubPin) //--- Input for timer 2
{
    switch (ubPin)
    {
        case PA00: //--- TIM2_CH1
            TIM2_CR1 &= 0xFFFE;        //--- disables cen bit
            TIM2_PSC = 7199;           //--- Scale the timer to 10000 counts per second
            TIM2_ARR = uwPeriod - 1;   //--- determine what range in which you want the timer to run
            TIM2_CCMR1 |= 0x00000001;  //--- Set CC1S to 01 to enable input for channel 1
            TIM2_CCER |= 0x0001;       //--- enable capture compare register on channel 1
            TIM2_CR1 |= 0x0001;        //--- enable CEN bit to start the counter
            break;

        case PA05: //--- TIM2_CH1
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwPeriod - 1;
            TIM2_CCMR1 |= 0x00000001;  //--- Set CC1S to 01 to enable input for channel 1
            TIM2_CCER |= 0x0001;       //--- enable capture compare register on channel 1
            TIM2_CR1 |= 0x0001;
            break;

        case PA15: //--- TIM2_CH1
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwPeriod - 1;
            TIM2_CCMR1 |= 0x00000001;  //--- Set CC1S to 01 to enable input for channel 1
            TIM2_CCER |= 0x0001;       //--- enable capture compare register on channel 1
            TIM2_CR1 |= 0x0001;
            break;

        case PA01: //--- TIM2_CH2
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwPeriod - 1;
            TIM2_CCMR1 |= 0x00000100;  //--- Set CC2S to 01 to enable input for channel 2
            TIM2_CCER |= 0x0010;       //--- enable capture compare register on channel 2
            TIM2_CR1 |= 0x0001;
            break;

        case PB03: //--- TIM2_CH2
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwPeriod - 1;
            TIM2_CCMR1 |= 0x00000100;  //--- Set CC2S to 01 to enable input for channel 2
            TIM2_CCER |= 0x0010;       //--- enable capture compare register on channel 2
            TIM2_CR1 |= 0x0001;
            break;

        case PA02: //--- TIM2_CH3
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwPeriod - 1;
            TIM2_CCMR2 |= 0x00000001;  //--- Set CC3S to 01 to enable input for channel 3
            TIM2_CCER |= 0x0100;       //--- enable capture compare register on channel 3
            TIM2_CR1 |= 0x0001;
            break;

        case PA03: //--- TIM2_CH4
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwPeriod - 1;
            TIM2_CCMR2 |= 0x00000100;  //--- Set CC4S to 01 to enable input for channel 4
            TIM2_CCER |= 0x1000;       //--- enable capture compare register on channel 4
            TIM2_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

void fnTim15In(u16 uwPeriod, u08 ubPin) //--- Input for timer 15
{
    switch (ubPin)
    {
        case PA02: //--- TIM15_ CH1
            TIM15_CR1 &= 0xFFFE;       //--- disables cen bit
            TIM15_PSC = 7199;          //--- Scale the timer to 10000 counts per second
            TIM15_ARR = uwPeriod - 1;  //--- determine what range in which you want the timer to run
            TIM15_CCMR1 |= 0x00000001; //--- Set CC1S to 01 to enable input for channel 1
            TIM15_CCER |= 0x0001;      //--- enable capture compare register on channel 1
            TIM15_CR1 |= 0x0001;       //--- enable CEN bit to start the counter
            break;

        case PA03:
            TIM15_CR1 &= 0xFFFE;
            TIM15_PSC = 7199;
            TIM15_ARR = uwPeriod - 1;
            TIM15_CCMR1 |= 0x00000100; //--- Set CC2S to 01 to enable input for channel 2
            TIM15_CCER |= 0x0010;      //--- enable capture compare register on channel 2
            TIM15_BDTR |= 0x00008000;
            TIM15_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

void fnTim16In(u16 uwPeriod, u08 ubPin) //--- Input for timer 16
{
    switch (ubPin)
    {
        case PA06: //--- TIM15_ CH1
            TIM16_CR1 &= 0xFFFE;       //--- disables cen bit
            TIM16_PSC = 7199;          //--- Scale the timer to 10000 counts per second
            TIM16_ARR = uwPeriod - 1;  //--- determine what range in which you want the timer to run
            TIM16_CCMR1 |= 0x00000001; //--- Set CC1S to 01 to enable input for channel 1
            TIM16_CCER |= 0x0001;      //--- enable capture compare register on channel 1
            TIM16_CR1 |= 0x0001;       //--- enable CEN bit to start the counter
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}


//-----generc PWM output-----//
void fnTim1PWMOut(u16 uwLoad, u08 ubPin) //--- Output for timer 1
{
    //--- can adjust from 10000 pulses per second to one pulse per 6 seconds.
    switch (ubPin)
    {
        case PA08: //--- TIM1_CH1
            TIM1_CR1 &= 0xFFFE;        //--- disables cen bit
            TIM1_ARR = 9999;           //--- how many counts until the counter restarts
            TIM1_CCMR1 |= 0x00000060;  //--- enable PWM mode 1 on the OC1M bits for channel 1
            TIM1_CCER |= 0x00000001;   //--- enable capture compare register on channel 1
            TIM1_BDTR |= 0x00004000;   //--- enable MOE bit
            TIM1_CCR1 = uwLoad;        //--- determine the duty cycle for PWM
            TIM1_CR1 |= 0x0001;        //--- enable CEN bit to start the counter
            break;

        case PA09: //--- TIM1_CH2
            TIM1_CR1 &= 0xFFFE;
            TIM1_ARR = 9999;
            TIM1_CCMR1 |= 0x00006000;  //--- enable PWM mode 1 on the OC1M bits for channel 2
            TIM1_CCER |= 0x00000010;   //--- enable capture compare register on channel 2
            TIM1_BDTR |= 0x00004000;
            TIM1_CCR2 = uwLoad;        //--- determine the duty cycle for PWM
            TIM1_CR1 |= 0x0001;
            break;

        case PA10: //--- TIM1_CH3
            TIM1_CR1 &= 0xFFFE;
            TIM1_ARR = 9999;
            TIM1_CCMR2 |= 0x00000060;  //--- enable PWM mode 1 on the OC1M bits for channel 3
            TIM1_CCER |= 0x00000100;   //--- enable capture compare register on channel 3
            TIM1_BDTR |= 0x00004000;
            TIM1_CCR3 = uwLoad;        //--- determine the duty cycle for PWM
            TIM1_CR1 |= 0x0001;
            break;

        case PA11: //--- TIM1_CH4
            TIM1_CR1 &= 0xFFFE;
            TIM1_ARR = 9999;
            TIM1_CCMR2 |= 0x00006000;  //--- enable PWM mode 1 on the OC1M bits for channel 4
            TIM1_CCER |= 0x00001000;   //--- enable capture compare register on channel 4
            TIM1_BDTR |= 0x00004000;
            TIM1_CCR4 = uwLoad;        //--- determine the duty cycle for PWM
            TIM1_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

void fnTim2PWMOut(u16 uwLoad, u08 ubPin) //--- Output for timer 2
{
    //--- can adjust from 10000 pulses per second to one pulse per 5 days.
    switch (ubPin)
    {
        case PA00: //--- TIM2_CH1
            TIM2_CR1 &= 0xFFFE;        //--- disables cen bit
            TIM2_ARR = 9999;           //--- how many counts until the counter restarts
            TIM2_CCMR1 |= 0x00000060;  //--- enable PWM mode 1 on the OC1M bits for channel 1
            TIM2_CCER |= 0x0001;       //--- enable capture compare register on channel 1
            TIM2_CCR1 = uwLoad;        //--- determine the duty cycle for PWM
            TIM2_CR1 |= 0x0001;        //--- enable CEN bit to start the counter
            break;

        case PA05: //--- TIM2_CH1
            TIM2_CR1 &= 0xFFFE;
            TIM2_ARR = 9999;
            TIM2_CCMR1 |= 0x00000060;  //--- sets OC1M bits to toggle on channel pin
            TIM2_CCER |= 0x0001;       //--- enables capture compare register for channel 1
            TIM2_CCR1 = uwLoad;
            TIM2_CR1 |= 0x0001;
            break;

        case PA15: //--- TIM2_CH1
            TIM2_CR1 &= 0xFFFE;
            TIM2_ARR = 9999;
            TIM2_CCMR1 |= 0x00000060;  //--- sets OC1M bits to toggle on channel pin
            TIM2_CCER |= 0x0001;       //--- enables capture compare register for channel 1
            TIM2_CCR1 = uwLoad;
            TIM2_CR1 |= 0x0001;
            break;

        case PA01: //--- TIM2_CH2
            TIM2_CR1 &= 0xFFFE;
            TIM2_ARR = 9999;
            TIM2_CCMR1 |= 0x00006000;  //--- sets OC2M bits to toggle on channel pin
            TIM2_CCER |= 0x0010;       //--- enables capture compare register for channel 2
            TIM2_CCR2 = uwLoad;
            TIM2_CR1 |= 0x0001;
            break;

        case PB03: //--- TIM2_CH2
            TIM2_CR1 &= 0xFFFE;
            TIM2_ARR = 9999;
            TIM2_CCMR1 |= 0x00006000;  //--- sets OC2M bits to toggle on channel pin
            TIM2_CCER |= 0x0010;       //--- enables capture compare register for channel 2
            TIM2_CCR2 = uwLoad;
            TIM2_CR1 |= 0x0001;
            break;

        case PA02: //--- TIM2_CH3
            TIM2_CR1 &= 0xFFFE;
            TIM2_ARR = 9999;
            TIM2_CCMR2 |= 0x00000060;  //--- sets OC3M bits to toggle on channel pin
            TIM2_CCER |= 0x0100;       //--- enables capture compare register for channel 3
            TIM2_CCR3 = uwLoad;
            TIM2_CR1 |= 0x0001;
            break;

        case PA03: //--- TIM2_CH4
            TIM2_CR1 &= 0xFFFE;
            TIM2_ARR = 9999;
            TIM2_CCMR2 |= 0x00006000;  //--- sets OC4M bits to toggle on channel pin
            TIM2_CCER |= 0x1000;       //--- enables capture compare register for channel 4
            TIM2_CCR4 = uwLoad;
            TIM2_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

void fnTim15PWMOut(u16 uwLoad, u08 ubPin) //--- Output for timer 15
{
    switch (ubPin)
    {
        case PA02: //--- TIM15_ CH1
            TIM15_CR1 &= 0xFFFE;       //--- disables cen bit
            TIM15_ARR = 9999;          //--- how many counts until the counter restarts
            TIM15_CCMR1 |= 0x00000060; //--- enable PWM mode 1 on the OC1M bits for channel 1
            TIM15_CCER |= 0x0001;      //--- enable capture compare register on channel 1
            TIM15_BDTR |= 0x00008000;  //--- Enable the MOE bit
            TIM15_CCR1 = uwLoad;       //--- determine the duty cycle for PWM
            TIM15_CR1 |= 0x0001;       //--- enable CEN bit to start the counter
            break;

        case PA03:
            TIM15_CR1 &= 0xFFFE;
            TIM15_ARR = 9999;
            TIM15_CCMR1 |= 0x00006000; //--- enable PWM mode 1 on the OC1M bits for channel 2
            TIM15_CCER |= 0x0010;      //--- enable capture compare register on channel 2
            TIM15_BDTR |= 0x00008000;
            TIM15_CCR2 = uwLoad;       //--- determine the duty cycle for PWM
            TIM15_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

void fnTim16PWMOut(u16 uwLoad, u08 ubPin) //--- Output for timer 16
{
    switch (ubPin)
    {
        case PA06: //--- TIM15_ CH1
            TIM16_CR1 &= 0xFFFE;       //--- disables cen bit
            TIM16_ARR = 9999;          //--- how many counts until the counter restarts
            TIM16_CCMR1 |= 0x00000060; //--- enable PWM mode 1 on the OC1M bits for channel 1
            TIM16_CCER |= 0x0001;      //--- enable capture compare register on channel 1
            TIM16_BDTR |= 0x00008000;  //--- Enable the MOE bit
            TIM16_CCR1 = uwLoad;       //--- determine the duty cycle for PWM
            TIM16_CR1 |= 0x0001;       //--- enable CEN bit to start the counter
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

//-----generic PWM input-----//
void fnTIM1PWMIn(u16 uwPeriod, u08 ubPin) //--- PWM input for timer 1
{
    switch (ubPin)
    {
        case PA08: //--- TIM1_CH1 is the input while TIM1_CH2 holds the value
            GPIOA_PUPDR = 0x000A0000;
            TIM1_CR1 &= 0xFFFE;        //--- disables cen bit
            TIM1_PSC = 7199;           //--- Scale the timer to 10000 counts per second
            TIM1_ARR = uwPeriod - 1;   //--- how many counts until the counter restarts
            TIM1_CCMR1 |= 0x00000201;  //--- Enables channel 1 and 2 to TI1 input
            TIM1_CCER |= 0x00000031;   //--- Enables channel 1 and 2 and sets CC2P
            TIM1_SMCR |= 0x00000054;   //--- sets SMS to 100 and TS to 101
            TIM1_CR1 |= 0x0001;        //--- enable CEN bit to start the counter
            break;

        case PA09: //--- TIM1_CH2 is the input while TIM1_CH1 holds the value
            GPIOA_PUPDR = 0x000A0000;
            TIM1_CR1 &= 0xFFFE;
            TIM1_PSC = 7199;
            TIM1_ARR = uwPeriod - 1;
            TIM1_CCMR1 |= 0x00000102;  //--- Enables channel 1 and 2 to TI2 input
            TIM1_CCER |= 0x00000013;   //--- Enables channel 1 and 2 and sets CC1P
            TIM1_SMCR |= 0x00000064;
            TIM1_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

void fnTIM2PWMIn(u16 uwPeriod, u08 ubPin) //--- PWM input for timer 2
{
    switch (ubPin)
    {
        case PA00: //--- TIM2_CH1
            GPIOA_PUPDR = 0x8000080A;
            GPIOB_PUPDR = 0x00000080;
            TIM2_CR1 &= 0xFFFE;        //--- disables cen bit
            TIM2_PSC = 7199;           //--- Scale the timer to 10000 counts per second
            TIM2_ARR = uwPeriod - 1;   //--- how many counts until the counter restarts
            TIM2_CCMR1 |= 0x00000201;  //--- Enables channel 1 and 2 to TI1 input
            TIM2_CCER |= 0x00000031;   //--- Enables channel 1 and 2 and sets CC2P
            TIM2_SMCR |= 0x00000054;   //--- sets SMS to 100 and TS to 101
            TIM2_CR1 |= 0x0001;        //--- enable CEN bit to start the counter
            break;

        case PA05: //--- TIM2_CH1
            GPIOA_PUPDR = 0x8000080A;
            GPIOB_PUPDR = 0x00000080;
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwPeriod - 1;
            TIM2_CCMR1 |= 0x00000201;  //--- Enables channel 1 and 2 to TI1 input
            TIM2_CCER |= 0x00000031;   //--- Enables channel 1 and 2 and sets CC2P
            TIM2_SMCR |= 0x00000054;
            TIM2_CR1 |= 0x0001;
            break;

        case PA15: //--- TIM2_CH1
            GPIOA_PUPDR = 0x8000080A;
            GPIOB_PUPDR = 0x00000080;
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwPeriod - 1;
            TIM2_CCMR1 |= 0x00000201;  //--- Enables channel 1 and 2 to TI1 input
            TIM2_CCER |= 0x00000031;   //--- Enables channel 1 and 2 and sets CC2P
            TIM2_SMCR |= 0x00000054;
            TIM2_CR1 |= 0x0001;
            break;

        case PA01: //--- TIM2_CH2
            GPIOA_PUPDR = 0x8000080A;
            GPIOB_PUPDR = 0x00000080;
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwPeriod - 1;
            TIM2_CCMR1 |= 0x00000102;  //--- Enables channel 1 and 2 to TI1 input
            TIM2_CCER |= 0x00000013;   //--- Enables channel 1 and 2 and sets CC1P
            TIM2_SMCR |= 0x00000064;
            TIM2_CR1 |= 0x0001;
            break;

        case PB03: //--- TIM2_CH2
            GPIOA_PUPDR = 0x8000080A;
            GPIOB_PUPDR = 0x00000080;
            TIM2_CR1 &= 0xFFFE;
            TIM2_PSC = 7199;
            TIM2_ARR = uwPeriod - 1;
            TIM2_CCMR1 |= 0x00000102;  //--- Enables channel 1 and 2 to TI1 input
            TIM2_CCER |= 0x00000013;   //--- Enables channel 1 and 2 and sets CC1P
            TIM2_SMCR |= 0x00000064;
            TIM2_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}

void fnTIM15PWMIn(u16 uwPeriod, u08 ubPin) //--- PWM input for timer 15
{
    switch (ubPin)
    {
        case PA02: //--- TIM2_CH1
            GPIOA_PUPDR = 0x000000A0;
            TIM15_CR1 &= 0xFFFE;       //--- disables cen bit
            TIM15_PSC = 7199;          //--- Scale the timer to 10000 counts per second
            TIM15_ARR = uwPeriod - 1;  //--- how many counts until the counter restarts
            TIM15_CCMR1 |= 0x00000201; //--- Enables channel 1 and 2 to TI1 input
            TIM15_CCER |= 0x00000031;  //--- Enables channel 1 and 2 and sets CC2P
            TIM15_SMCR |= 0x00000054;  //--- sets SMS to 100 and TS to 101
            TIM15_CR1 |= 0x0001;       //--- enable CEN bit to start the counter
            break;

        case PA03: //--- TIM2_CH2
            GPIOA_PUPDR = 0x000000A0;
            TIM15_CR1 &= 0xFFFE;
            TIM15_PSC = 7199;
            TIM15_ARR = uwPeriod - 1;
            TIM15_CCMR1 |= 0x00000102; //--- Enables channel 1 and 2 to TI1 input
            TIM15_CCER |= 0x00000013;  //--- Enables channel 1 and 2 and sets CC1P
            TIM15_SMCR |= 0x00000064;
            TIM15_CR1 |= 0x0001;
            break;

        default: //--- This will turn the red LED on continuously to indicate an error.
            PA04_OUT;
            SET_PA04;
    }
}
