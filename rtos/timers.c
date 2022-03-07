//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                         Base Code For STM32F446 Timer Functions
//                  -----------------------------------------------------
//
//    This code is for use on the STM32L432 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32     Series Micro Controller Products
//
//                             Written By:  Ethan James Fredsti
//
//=============================================================================================
#include "projectdefs.h"

void fnTimTwoInit(void)
{
    //---activates timer 2 in RCC if it isn't already.
    RCC_APB1ENR1 |= 0x00000001;
    RCC_APB1SMENR1 |= 0x00000001;

    //---sets all registers to their reset state.
    TIM2_CR1     =   0x0000;
    TIM2_CR2     =   0x0000;
    TIM2_PSC     =   0x0000;
    TIM2_ARR     =   0x0000;
    TIM2_CNT     =   0x00000000;
    TIM2_CR2     =   0x0000;
    TIM2_SMCR    =   0x0000;
    TIM2_DIER    =   0x0000;
    TIM2_SR      =   0x0000;
    TIM2_EGR     =   0x0000;
    TIM2_CCMR1   =   0x00000000;
    TIM2_CCMR2   =   0x00000000;
    TIM2_CCER    =   0x0000;
    TIM2_CCR1    =   0x0000;
    TIM2_CCR2    =   0x0000;
    TIM2_CCR3    =   0x0000;
    TIM2_CCR4    =   0x0000;
    TIM2_DCR     =   0x0000;
    TIM2_DMAR    =   0x0000;
}

//---A simple function that initializes timer 1
void fnTimOneInit(void)
{
    //---activates timer 1 if it is not already.
    RCC_APB2ENR |= 0x00000800;
    RCC_APB2SMENR |= 0x00000800;

    //---sets all registers to their reset state.
    TIM1_CR1     =   0x0000;
    TIM1_CR2     =   0x00000000;
    TIM1_SMCR    =   0x00000000;
    TIM1_DIER    =   0x0000;
    TIM1_SR      =   0x00000000;
    TIM1_EGR     =   0x0000;
    TIM1_CCMR1   =   0x00000000;
    TIM1_CCMR2   =   0x00000000;
    TIM1_CCER    =   0x00000000;
    TIM1_CNT     =   0x00000000;
    TIM1_PSC     =   0x0000;
    TIM1_ARR     =   0x0000;
    TIM1_RCR     =   0x0000;
    TIM1_CCR1    =   0x0000;
    TIM1_CCR2    =   0x0000;
    TIM1_CCR3    =   0x0000;
    TIM1_CCR4    =   0x0000;
    TIM1_BDTR    =   0x00000000;
    TIM1_DCR     =   0x0000;
    TIM1_DMAR    =   0x00000000;
}

//---A simple function that initializes timer 16
void fnTimSixteenInit(void)
{
    //---activates timer 16 if it is not already
    RCC_APB2ENR |= 0x00020000;
    RCC_APB2SMENR |= 0x00020000;

    //---sets all registers to their reset state.
    TIM16_CR1     =   0x0000;
    TIM16_CR2     =   0x0000;
    TIM16_PSC     =   0x0000;
    TIM16_ARR     =   0x0000;
    TIM16_CNT     =   0x0000;
    TIM16_RCR     =   0x0000;
    TIM16_DIER    =   0x0000;
    TIM16_SR      =   0x0000;
    TIM16_EGR     =   0x0000;
    TIM16_CCMR1   =   0x00000000;
    TIM16_CCER    =   0x0000;
    TIM16_CCR1    =   0x0000;
    TIM16_BDTR    =   0x00000000;
    TIM16_DCR     =   0x0000;
    TIM16_DMAR    =   0x0000;
}

//---A simple function that initializes timer 6
void fnTimSixInit(void)
{
    //---Activate timer 6 in the RCC
    RCC_APB1ENR1 |= 0x00000010;
    RCC_APB1SMENR1 |= 0x00000010;
  
    //---set all the registers to reset state
    TIM6_CR1 = 0x0008;
    TIM6_CR2 = 0x0000;
    TIM6_DIER = 0x0000;
    TIM6_SR = 0x0000;
    TIM6_EGR = 0x0000;
    TIM6_CNT = 0x00000000;
    TIM6_PSC = 0x0000;
    TIM6_ARR = 0x00000000;
}

//---An easy to set and use delay function in units of 1/10000th of a second
void fnSimpleDelay(u16 ticker)
{
    fnTimSixInit(); 
    TIM6_CR1 |= 0x0008; //---Activates the One Pulse Mode bit in the control register
    TIM6_PSC = 7199; //---Adjusts the counter speed to 10000 pulses per second
    TIM6_ARR = ticker; //---Load the Auto reload register
    TIM6_CR1 |= 0x0001; //---start the counter
    
    /*
    loop until the counter counts up to the ARR(ticker) and an update event occurs and
    deactivates the timer setting TIM6_CR1 to 0x0008.
    */
    while(TIM6_CR1 != 0x0008)
    {
        nop2; //---waste a small amount of time
    }
}

//=============================================================================================
//     Standardized comment blocks
//=============================================================================================

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

