//=============================================================================================
//                                       Quorb Inc.
//                                -------------------------
//
//                                  QMX-32 Start Up Code
//                                  --------------------
//
//    This code is for use on the STM32F05X Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32     Series Micro Controller Products
//
//                           Written By:  Sancar James Fredsti
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//                      Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#include "projectdefs.h"

//--------------------------------------------------------------------------------------------
//    Project Peripherials List
//--------------------------------------------------------------------------------------------
//
//  This processor uses the internal 16 MHz STM32L oscillator.
//  By default this base software uses the 16 MHz Internal Oscillator and configures the system
//  clock to operate at 80 MHz using the RCC PLL Configuration.
//
//  Peripherial       Configurations
//  --------------------------------
//  Upon System Initialization the following peripherials are enabled and operating as a
//  default system configuration.
//
//--------------------------------------------------------------------------------------------

u08     ubSVCn;                                   //--- Software Interrupt Select Numberin RAM
u32     tmp;                                      //--- Temporary Number
u32     ulT = 0;
u16     uwReturnVal;

extern u32 volatile  ulBusyFlags; //--- Busy flag pulled in from opsys.c

//---------------------------------------------------------------------------------------------
//      This is the Reset Code Entry Point from the RESET Pin
//---------------------------------------------------------------------------------------------
void  fnReset_IRQ (void)                          //--- Reset Handler                0x00000004
{
    u32 *pulSrc;                                    //--- Src & Dst Pointers
    u32 *pulDest;

    //--- Zero fill the bss segment
    //--- This flushes all junk from RAM
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0x00000000;
    }

    //--- Copy the data segment initializers from flash to SRAM
    pulSrc = &_sidata;

    for(pulDest = &_sdata; pulDest < &_edata; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    //--- Set Priviledged Mode to Enable
    SET_PRIVLEGED_MODE;

    //-------------------------------------------------------------------------------------------
    //    Set Access for BDCR Access
    //-------------------------------------------------------------------------------------------
    //--- Configure Flash Memory Operation.  enable the PRFTEN, ICEN, DCEN and Latency (2) bits
    FLASH_ACR = 0x00000704;
    nop4;

    //-------------------------------------------------------------------------------------------
    //    Clear Clocks & RCC Registers
    //-------------------------------------------------------------------------------------------
    //--- No Clock Interrupts for now
    RCC_CIER = 0x00000000;                          //--- No Clock Interrupts Allowed
    RCC_CICR = 0x0000077F;                          //--- Clear Clock Interrupts

    //--- AP & AH Peripherial Resets
    RCC_APB1RSTR1 = 0xFFFFFFFF;                     //--- Reset All Peripherials
    RCC_APB1RSTR1 = 0x00000000;                     //--- Clear All Peripherial Resets

    RCC_APB1RSTR2 = 0xFFFFFFFF;                     //--- Reset All Peripherials
    RCC_APB1RSTR2 = 0x00000000;                     //--- Clear All Peripherial Resets

    RCC_APB2RSTR = 0xFFFFFFFF;                      //--- Reset All Peripherials
    RCC_APB2RSTR = 0x00000000;                      //--- Clear All Peripherial Resets

    RCC_AHB1RSTR = 0xFFFFFFFF;                      //--- Reset All Peripherials
    RCC_AHB1RSTR = 0x00000000;                      //--- Clear All Peripherial Resets

    RCC_AHB2RSTR = 0xFFFFFFFF;                      //--- Reset All Peripherials
    RCC_AHB2RSTR = 0x00000000;                      //--- Clear All Peripherial Resets

    RCC_AHB3RSTR = 0xFFFFFFFF;                      //--- Reset All Peripherials
    RCC_AHB3RSTR = 0x00000000;                      //--- Clear All Peripherial Resets
    nop8;                                           //--- Waste a little time

    //===========================================================================================
    //    The system clock is derived from the MSI clock which is phase locked to the crystal
    //    controlled LSE Clock at 32768 Hz.  To allow for a 48 MHz clock to be generated for
    //    the USB and Random Number Generator the system clock operates at 72 MHz from which
    //    the 48 MHz clock is derived by dividing the system clock by 3 then multiplying by 2.
    //===========================================================================================

    //-------------------------------------------------------------------------------------------
    //    Enable the following APB1 Peripherials To Start With
    //    This peripherial Register is changed later in Boot Process
    //-------------------------------------------------------------------------------------------
    //--- Enable the following APB1 Peripherials.  Enable the PWREN and RTCAPBEN bits.
    RCC_APB1ENR1 = 0x10000400;
    RCC_APB1SMENR1 = 0x10000400;
    nop4;     //--- Waste a little time

    //--- Power Control Register #1.  Enable DBP and VOS (0) bits
    PWR_CR1 |= 0x00000300;
    nop4;     //--- Waste a little time

    //--- This is for setting LSE with Oscillator.  Enable LSEON, LSEBYP, LSEDRV (0 & 1), RTCSEL (0), RTCEN, LSCOEN, and LSCOSEL bits
    RCC_BDCR = 0x0200811D;

    //--- Wait for LSE Clock to settle for up To 100,000 Loops
    ulT = 100000;

    //--- Test if LSE is Ready and running
    while (!(RCC_BDCR & 0x00000002) && (ulT > 0))
    {
        ulT--;                                        //--- Decrement Period Counter
        nop4;
    }

    //--- Notate Success of LSE in SystemFlags
    if (ulT > 0)
    {
        ulSystemFlags |= 0x00000001;                  //--- Success = Hi Bit (0)
    }
    else
    {
        ulSystemFlags &= 0xFFFFFFFE;                  //--- Failure = Lo Bit (0)
    }

    //-------------------------------------------------------------------------------------------
    //    Configure System Clocks
    //-------------------------------------------------------------------------------------------

    //--- Turn on MSI.  Enable MSION, MSIRGSEL, MSIRANGE (1 & 2) bits
    RCC_CR = 0x00000069;

    //--- Wait for MSI Clock to settle
    ulT = 100000;

    while (((RCC_CR & 0x00000002) != 0x00000002) && (ulT > 0))
    {
        ulT--;                                        //--- Decrement Period Counter
        nop12;
    }

    //--- Notate Success of MSI @ 4 MHz at StartUp
    if (ulT > 0)
    {
        ulSystemFlags |= 0x00000002;                  //--- Success = Hi
    }
    else
    {
        ulSystemFlags &= 0xFFFFFFFD;                  //--- Failure = Lo
    }

    //--- Turn on MSI PLL link to LSE.  Enable MSION, MSIPLLEN, MSIRGSEL, and MSIRANGE (1 & 2) bits.
    RCC_CR |= 0x0000006D;
    nop4;

    //--- Wait for MSI Clock PLL to settle
    ulT = 100000;

    while (((RCC_CR & 0x00000002) != 0x00000002) && (ulT > 0))
    {
        ulT--;                                        //--- Decrement Period Counter
        nop12;
    }

    //--- Notate Success of MSI PLL @ 4 MHz at StartUp
    if (ulT > 0)
    {
        ulSystemFlags |= 0x00000004;                  //--- Success = Hi
    }
    else
    {
        ulSystemFlags &= 0xFFFFFFFB;                  //--- Failure = Lo
    }

    //--- Enable Main PLL in RCC_PLLCFGR.  Enable PLLSRC (0), PLLN(3 & 6), PLLREN, and PLLR (0) bits.
    RCC_PLLCFGR = 0x03504801;
    nop48;

    //--- Turn on Main PLL Enable.  Enable MSION, MSIPLLEN, MSIRGSEL, MSIRANGE (1 & 2), and PLLON bits
    RCC_CR |= 0x0100006D;
    nop48;

    //--- Wait for PLL & MSI clocks to show "Ready"
    ulT = 100000;  //    Wait for upto 100K Loops

    while (((RCC_CR & 0x02000002) != 0x02000002) && ulT)
    {
        ulT--;                                        //--- Decrement Period Counter
        nop12;
    }

    //--- Notate Success of Main PLL StartUp
    if (ulT > 0)
    {
        ulSystemFlags |= 0x00000008;                  //--- Success = Hi
    }
    else
    {
        ulSystemFlags &= 0xFFFFFFF7;                  //--- Failure = Lo
    }

    //--- Configure the clock.  Enable SW (0 & 1), MCOSEL (0), and MCPRE (0 & 1) bits.
    RCC_CFGR = 0x31000003;

    //--- Wait for System to show PLL as Sys Clock
    ulT = 1000;  //    Wait for upto 100K Loops

    while (((RCC_CFGR & 0x0000000C) != 0x0000000C) && ulT)
    {
        ulT--;                                        //--- Decrement Period Counter
        nop12;
    }

    //--- Notate Success of PLL StartUp
    if (ulT > 0)
    {
        ulSystemFlags |= 0x00000010;                  //--- Success = Hi
    }
    else
    {
        ulSystemFlags &= 0xFFFFFFEF;                  //--- Failure = Lo
    }

    //--- Independant Clock Config Register.
    //--- Enable USART1SEL (1), USART2SEL (1), USART3SEL (1), USART4SEL (1), LPUART1SEL (1), I2C1SEL (1), I2C2SEL (1), I2C3SEL (1), and ADCSEL (0 & 1) bits.
    RCC_CCIPR = 0x3002A855;

    //-------------------------------------------------------------------------------------------
    //    Enable the following Peripherials Refer to Ref Manual Page
    //-------------------------------------------------------------------------------------------
    //--- Enable the following AHB1 Peripherials.  Enable FLASHEN bit.
    RCC_AHB1ENR   = 0x00000100;
    RCC_AHB1SMENR = 0x00000100;

    //--- Enable the following AHB2 Peripherials.  Enable GPIOA, GPIOB, GPIOC, ADCEN, and RNGEN bits.
    RCC_AHB2ENR   = 0x00042007;
    RCC_AHB2SMENR = 0x00042007;

    //--- Enable the following AHB3 Peripherials.  Register set to all zeros.
    RCC_AHB3ENR   = 0x00000000;
    RCC_AHB3SMENR = 0x00000000;

    //-------------------------------------------------------------------------------------------
    //    Enable the following APB1 Peripherials
    //-------------------------------------------------------------------------------------------
    //--- Enable the following APB1 Peripherials.  Enable WWDGEN, USART2EN, I2C1EN, and LPTIM1EN bits.
    RCC_APB1ENR1   = 0x10220400;
    RCC_APB1SMENR1 = 0x10220400;

    //--- Enable the following APB1 Peripherials.  Register set to all zeros.
    RCC_APB1ENR2   = 0x00000000;
    RCC_APB1SMENR2 = 0x00000000;

    //-------------------------------------------------------------------------------------------
    //    Enable the following APB2 Peripherials
    //-------------------------------------------------------------------------------------------
    //--- Enable the following APB2 Peripherials.  Enable SYSCFGEN bit, Enable USART1, Enable SPI1.
    RCC_APB2ENR   = 0x00005001;
    RCC_APB2SMENR = 0x00005001;

    //--- Wait to settle down
    nop8;

    //--- Initialize NVIC Table of Vectors
    fnInitNVIC();

    //===========================================================================================
    //    Configure GPIO Ports
    //===========================================================================================

    //-------------------------------------------------------------------------------------------
    //      Configure GPIO_A
    //-------------------------------------------------------------------------------------------
    //--- Set All Pins as Output
    #ifndef Debug_Flag
        GPIOA_MODER = 0x55555555;
    #endif

    #ifdef Debug_Flag
        GPIOA_MODER = 0x69555555;     //--- Keeping pins 13 and 14 as alternate function to preserve the debugger.
    #endif

    //--- All Outputs are Push/Pull
    GPIOA_OTYPER = 0x00000000;

    //--- Every One is High Speed
    GPIOA_OSPEEDR = 0xFFFFFFFF;

    //--- Set All As No Pull Up or Down
    GPIOA_PUPDR = 0x00000000;

    //--- Start with all 0's out
    GPIOA_ODR = 0x00000000;

    //--- Nothing to BSRR
    GPIOA_BSRR = 0x00000000;

    //--- All Ports are unlocked
    GPIOA_LCKR = 0x00000000;

    //--- Set AFRL to 0
    GPIOA_AFRL = 0x00000000;

    //--- Set AFRH to 0
    GPIOA_AFRH = 0x00000000;

    //--- Waste a little Time for things to settle down
    nop8;

    //-------------------------------------------------------------------------------------------
    //      Configure GPIO_B
    //-------------------------------------------------------------------------------------------
    //--- Set All Pins as Output
    GPIOB_MODER = 0x55555555;

    //--- All Outputs are Push/Pull
    GPIOB_OTYPER = 0x00000000;

    //--- Every One is High Speed
    GPIOB_OSPEEDR = 0xFFFFFFFF;

    //--- Set All As No Pull Up or Down
    GPIOB_PUPDR = 0x00000000;

    //--- Start with all 0's out
    GPIOB_ODR = 0x00000000;

    //--- Nothing to BSRR
    GPIOB_BSRR = 0x00000000;

    //--- All Ports are unlocked
    GPIOB_LCKR = 0x00000000;

    //--- Set AFRL to 0
    GPIOB_AFRL = 0x00000000;

    //--- Set AFRH to 0
    GPIOB_AFRH = 0x00000000;

    //--- Waste a little Time for things to settle down
    nop8;

    //-------------------------------------------------------------------------------------------
    //      Configure GPIO_C
    //-------------------------------------------------------------------------------------------
    //--- Set All Pins as Output
    GPIOC_MODER = 0x55555555;

    //--- All Outputs are Push/Pull
    GPIOC_OTYPER = 0x00000000;

    //--- Every One is High Speed
    GPIOC_OSPEEDR = 0xFFFFFFFF;

    //--- Set All As No Pull Up or Down
    GPIOC_PUPDR = 0x00000000;

    //--- Start with all 0's out
    GPIOC_ODR = 0x00000000;

    //--- Nothing to BSRR
    GPIOC_BSRR = 0x00000000;

    //--- All Ports are unlocked
    GPIOC_LCKR = 0x00000000;

    //--- Set AFRL to 0
    GPIOC_AFRL = 0x00000000;

    //--- Set AFRH to 0
    GPIOC_AFRH = 0x00000000;

    //--- Waste a little Time for things to settle down
    nop8;

    //--- Always Enable FPU in STM32L432
    SET_PRIVLEGED_MODE;
    FPU_ENA;

    //--- Preset internal reference voltage to 2.500V.  Enable ENVR and VRS bits.
    VREFBUF_CSR = 0x00000005;

    unEmptyData.uxBig[0] = 0;                       //--- Clear Data Union
    unEmptyData.uxBig[1] = 0;                       //--- Clear Data Union

    ulBusyFlags = 0;                                //--- All Task Busy Flags are Off

    //-------------------------------------------------------------------------------------------
    //  Start Up SysTick Timer As Pacer Set for 10 KHz  100uSec base frequency
    //-------------------------------------------------------------------------------------------

    SET_PRIVLEGED_MODE;

    fnInitSysTick ();                               //--- Start Up the SysTick

    //--- If DEFINED then startup UART Communications
    #ifdef USART1_FLAG
        fnInitUSART1 (USART1_BAUD);     //--- Initialize USART1 Communications
    #endif

    #ifdef USART2_FLAG
        fnInitUSART2 (USART2_BAUD);     //--- Initialize USART2 Communications
    #endif



    //-------------------------------------------------------------------------------------------
    //  Add Other Peripherial Initializations Here USART #2 = Debug USART
    //-------------------------------------------------------------------------------------------

    //--- Show that Init Complete
    ulSystemFlags |= 0xC0000000;                    //--- Start-Up Success = Hi

    nop4;                                           //--- A Brief Pause

    GIE;                                            //--- Enable All Other Interrupts

    //--- Schedule First Recursion Task
    stWorkTask.uwTimer = 333;                       //--- Timer Delay = 333
    stWorkTask.ptrTask = &tkRecursion;              //--- Reschedule This Task
    stWorkTask.uwFlags = 0;                         //--- No Flags
    stWorkTask.unTaskData = unEmptyData;            //--- Clear First Try
    uwReturnVal = fnScheduleTask (stWorkTask);

    //--- Call the Main Function after basic boot complete
    main();

    //--- If we return from the MAIN function then something has gone Terribly Wrong!!!!
    GID;                                            //--- Kill All Interrupts
    nop8;                                           //--- Short Pause to let NVIC Catch Up

    SET_PRIVLEGED_MODE;
    SCB_AIRCR = 0x05FA0004;                         //--- Emergency Call RESET
}
