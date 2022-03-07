//===========================================================================================//
//                                       Quorb Inc.                                          //
//                                -------------------------                                  //
//                                                                                           //
//                                  QMX-32 Start Up Code                                     //
//                                  --------------------                                     //
//                                                                                           //
//    This code is for use on the STM32F05X Processor Series of Micro Controllers it is      //
//    It is not fully compatible with other STM32     Series Micro Controller Products       //
//                                                                                           //
//                           Written By:  Sancar James Fredsti                               //
//                                                                                           //
//===========================================================================================//

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
u32     ulSystemFlags = 0;

//---------------------------------------------------------------------------------------------
//      This is the Reset Code Entry Point from the RESET Pin
//---------------------------------------------------------------------------------------------
void  fnReset_IRQ (void)                          //--- Reset Handler                0x00000004
{
  u32 *pulSrc;                                    //--- Src & Dst Pointers
  u32 *pulDest;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  //--- Zero fill the bss segment
  //    This flushes all junk from RAM
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
  ubSVCn = 0x05;                                  //--- Set the SVC Number
  SVC_CALL;                                       //--- Call Software Service Interrupt

  //-------------------------------------------------------------------------------------------
  //    Set Access for BDCR Access
  //-------------------------------------------------------------------------------------------
  //--- Configure Flash Memory Operation
  //      GPIO AFRH
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //---   .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0111 0000 0100
  //    FLASH = 4 Wait States
  //    Instruction Cache Enabled
  //    Prefetch Enabled
  //    4 Wait States for Flash to run @ 72Mhz Clock
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

  nop4;                                          //--- Waste a little time

  //-------------------------------------------------------------------------------------------
  //    Enable the following APB1 Peripherials To Start With
  //    This peripherial Register is changed later in Boot Process
  //-------------------------------------------------------------------------------------------
  //--- Enable the following APB1 Peripherials
  //--- RCC Peripherial Clock 1
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  // USED ...w .... .... .... .... .w.. .... ....
  // VAL  0001 0000 0000 0000 0000 0100 0000 0000
  //
  //      Name             Bit#  On/Off
  //      -------------    ----   ---
  //      RTCAPB            10    Hi              //--- Enable RTC Clock
  //      PWREN             28    Hi              //--- Enable Access to Power Registers
  //      All Others              Lo
  //
  RCC_APB1ENR1 = 0x10000400;
  RCC_APB1SMENR1 = 0x10000400;

  nop4;                                          //--- Waste a little time
  //--- Power Control Register #1
  //    SET VOS to range 1 & DBP to RTC Access OK
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  // USED .... .... .... .... .w.. .www .... .www
  // VAL  0000 0000 0000 0000 0000 0011 0000 0000
  //
  //      Name             Bit#  On/Off
  //      -------------    ----   ---
  //      LPMS-0            00    Lo
  //      LPMS-1            01    Lo
  //      LPMS-0            02    Lo
  //      DBP Access        08    Hi
  //      VOS-0             09    Hi
  //      VOS-1             10    Lo
  //      LPR               14    Lo
  //      All Others              Lo
  //
  PWR_CR1 |= 0x00000300;                            //--- Enable BDCR Write

  nop4;

  //--- This is for setting LSE with Oscillator
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  // USED .... ..ww .... ...w w... ..ww wrww wrww
  // S/C  0000 0010 0000 0000 1000 0001 0001 1101
  //
  //      Name             Bit#  On/Off
  //      -------------    ----   ---
  //      LSE ON            00    Hi
  //      LSE Bypass Ena    02    Hi
  //      Low Drive 0       03    Hi
  //      Low Drive 1       04    Lo
  //      LSE_CSS Enable    05    Lo
  //      LSE Clock PropEna 07    Lo  Reverse Logic = Enabled
  //      RTC Select 0      08    Hi  = LSE Clock
  //      RTC Select 1      09    Lo  = LSE Clock
  //      RTC_Enabled       15    Hi  = Enabled
  //      LSCO = Disabled   24    Lo
  //      LSCO = LSE        25    Hi
  RCC_BDCR = 0x0200811D;                          //--- Turn Off LSE Output

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

  //--- Turn on MSI
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  // USED .... rwrw .... wwrw .... wrww wwww wwrw
  // VAL  0000 0000 0000 0000 0000 0000 0110 1001
  //
  //--- Turn on MSI PLL link to LSE
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  // USED .... rwrw .... wwrw .... wrww wwww wwrw
  // S/C  0000 0000 0000 0000 0000 0000 0110 1101
  //
  //    Name             Bit#       On/Off
  //    -------------    ----        ---
  //    MSI_ON           0          On
  //    MSI_PLL Enable   2          Off
  //    MSI RANGE        3          On  MSI by RCC_CR
  //    MSI Range        4,5,6,7    LHHL MSI FREQ = 4 MHz
  //    HSI Osc.         8          Off
  //    HSI KERON        9          Off
  //    HSI ASFS         11         Off
  //    HSE_ON           16         Off
  //    HSE_BYP          18         Off
  //    CSS_ON           19         Off
  //    Main System      24         Off
  //    PLLSAI1_ON       26         Off
  RCC_CR = 0x00000069;

  //--- Wait for MSI Clock to settle
  ulT = 100000;

  while (((RCC_CR & 0x00000002) != 0x00000002) && (ulT > 0))
  {
    ulT--;                                        //--- Decrement Period Counter
    nop4;
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

  //--- Turn on MSI PLL link to LSE
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  // USED .... rwrw .... wwrw .... wrww wwww wwrw
  // S/C  0000 0000 0000 0000 0000 0000 0110 1101
  //
  //    Name             Bit#       On/Off
  //    -------------    ----        ---
  //    MSI_ON           0          On
  //    MSI_PLL Enable   2          On
  //    MSI RANGE        3          On  MSI by RCC_CR
  //    MSI Range        4,5,6,7    LHHL MSI FREQ = 4 MHz
  //    HSI Osc.         8          Off
  //    HSI KERON        9          Off
  //    HSI ASFS         11         Off
  //    HSE_ON           16         Off
  //    HSE_BYP          18         Off
  //    CSS_ON           19         Off
  //    Main System      24         Off
  //    PLLSAI1_ON       26         Off

  RCC_CR |= 0x0000006D;
  nop4;

  //--- Wait for MSI Clock PLL to settle
  ulT = 100000;

  while (((RCC_CR & 0x00000002) != 0x00000002) && (ulT > 0))
  {
    ulT--;                                        //--- Decrement Period Counter
    nop4;
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

  //--- Enable Main PLL in RCC_PLLCFGR
  //--- RCC_PLLCFGR
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //---   .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0001 0001
  //
  //--- Set SYSCLK source & Configure System PLL
  //
  //    MSI_VALUE = 4000000                           3322 2222 2222 1111 1111 1100 0000 0000
  //                                                  1098 7654 3210 9876 5432 1098 7654 3210
  //                                                     0    3    5    0    4    8    0    1
  //                                                  0000 0011 0101 0000 0100 1000 0000 0001
  //    PLL Source = MSI (4 MHz)                      .... .... .... .... .... .... .... ..01
  //    PLLM = 0  /1 = ( 4 MHz )                      .... .... .... .... .... .... 0000 00
  //    PLLN = 72  (288 MHz) (4 * 72 = 288) 0x48      .... .... .... .... 0100 1000
  //    PLLP = Disabled                               .... .... .... 0000
  //    PLLQ = /6 = (288 / 6) = 48 MHz + Ena          .... .... 0101
  //    PLLR = /4   (288 / 4) = 72 MHz + Enable       .... 0011
  //    PLLP = OFF                                    0000
  //
  //    PLLVCO INPUT = ((4000000 / 1) * 72) = 288 MHz
  //    PLLCLK = VCO / 4 = 72 MHz
  RCC_PLLCFGR = 0x03504801;
  nop4;

  //--- Turn on Main PLL Enable
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //---   .... .... .... .... .... .... .... ....
  //      0000 0001 0000 0000 0000 0000 0110 1101
  //
  //    Name             Bit#       On/Off
  //    -------------    ----        ---
  //    MSI_ON           0          On
  //    MSI_PLL Enable   2          Off
  //    MSI RANGE        3          On  MSI by RCC_CR
  //    MSI Range        4,5,6,7    LHHL MSI FREQ = 4 MHz
  //    HSI Osc.         8          Off
  //    HSI KERON        9          Off
  //    HSI ASFS         11         Off
  //    HSE_ON           16         Off
  //    HSE_BYP          18         Off
  //    CSS_ON           19         Off
  //    Main System      24         Off
  //    PLLSAI1_ON       26         Off
  RCC_CR |= 0x0100006D;
  nop4;

  //--- Wait for PLL & MSI clocks to show "Ready"
  ulT = 100000;  //    Wait for upto 100K Loops

  while (((RCC_CR & 0x02000002) != 0x02000002) && ulT)
  {
    ulT--;                                        //--- Decrement Period Counter
    nop4;
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

  //--- RCC_CSR is Preset to 0x0C000600
  //    This Sets the MSI Clock to 4.00 MHz upon reset
  //--- RCC_CSR
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      1100 0000 0000 0000 0000 0110 0000 0000
  //
  //    RCC_CSR = 0x0C000600;

  //------ Normal RCC_CFGR Configuration-----------------
  //--- RCC Configuration Register
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0011
  //      FLASH MEMORY ON
  //      System Clock = PLL (72 MHz)
  //      AHB Prescale = /1
  //      APB1 Prescale = /1
  //      APB2 Prescale = /1
  //      Wake Up = MSI
  //      No MCO Output on PA08
  //  RCC_CFGR = 0x01000003;

  //------ Test Usage Only ------------------------------
  //      MCO on Pin PA08 = Sysclk / 8
  //      .... .... .... .... .... .... .... ....
  //      0011 0001 0000 0000 0000 0000 0000 0011
  //-----------------------------------------------------

  //------ Test RCC_CFGR --------------------------------
  //      System Clock Selected as MCO Output = 72 mhZ
  //      MCO / 1  = 72 MHz = PA08
  //      .... .... .... .... .... .... .... ....
  //      0000 0001 0000 0000 0000 0000 0000 0011
  //-----------------------------------------------------
  //      FLASH MEMORY ON
  //      System Clock = PLL (72 MHz)
  //      AHB Prescale = /1
  //      APB1 Prescale = /1
  //      APB2 Prescale = /1
  //      Wake Up = MSI
  //      SysClock / 8 Output on PA08
  RCC_CFGR = 0x31000003;

  //--- Wait for System to show PLL as Sys Clock
  ulT = 100000;  //    Wait for upto 100K Loops

  while (((RCC_CFGR & 0x0000000C) != 0x0000000C) && ulT)
  {
    ulT--;                                        //--- Decrement Period Counter
    nop4;
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

  //--- Independant Clock Config Register
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  //
  RCC_CCIPR = 0x00000000;

  //-------------------------------------------------------------------------------------------
  //    Enable the following Peripherials Refer to Ref Manual Page
  //-------------------------------------------------------------------------------------------
  //--- Enable the following AHB1 Peripherials
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... ...w ...w ...w .... ..ww
  //      0000 0000 0000 0000 0000 0001 0000 0000
  //      Name             Bit#  On/Off
  //      -------------    ----   ---
  //      DMA 1             0     Off
  //      DMA 2             1     Off
  //      Flash Memory      8     On
  //      CRC Generator Off 12    Off
  //      Touch Sensor Off  16    Off
  RCC_AHB1ENR = 0x00000100;
  RCC_AHB1SMENR = 0x00000100;

  //--- Enable the following AHB2 Peripherials
  //--- RCC Configuration Register
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .w.w ..w. ...w ...w wwww
  //      0000 0000 0000 0101 0000 0000 0000 0111
  //      Name             Bit#  On/Off
  //      -------------    ----   ---
  //      GPIO A Port       0     On
  //      GPIO B Port       1     On
  //      GPIO C Port       2     On
  //      GPIO D Port Off   3     Off
  //      GPIO E Port Off   4     Off
  //      GPIO H Port Off   7     Off
  //      ADC Enable        13    Off
  //      AESEN Encoder     16    Off
  //      Random Number     18    Off
  RCC_AHB2ENR = 0x00000007;
  RCC_AHB2SMENR = 0x00000007;

  //--- Enable the following AHB3 Peripherials
  //--- RCC Configuration Register
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... ...| .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  //      QPSI Off
  RCC_AHB3ENR = 0x00000000;
  RCC_AHB3SMENR = 0x00000000;

  //-------------------------------------------------------------------------------------------
  //    Enable the following APB1 Peripherials
  //-------------------------------------------------------------------------------------------
  //--- Enable the following APB1 Peripherials
  //--- RCC Peripherial Clock 1
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  // USED wwww .www www. www. ww.. .www ..ww ..ww
  // S/C  0001 0000 0010 0000 0000 1000 0000 0000
  //      Name             Bit#  On/Off
  //      -------------    ----   ---
  //      Timer 2           00    Off
  //      Timer 3           01    Off
  //      Timer 6           04    Off
  //      Timer 7           05    Off
  //      LCD               09    Off
  //      RTCAPB            10    Off
  //      WWDG              11    Off
  //      SPI2              14    Off
  //      SPI3              15    Off
  //      UART 2            17    Off
  //      UART 3            18    Off
  //      UART 4            19    Off
  //      I2C1              21    Off
  //      I2C2              22    Off
  //      I2C3              23    Off
  //      CRS               24    Off
  //      CAN 1             25    Off
  //      USB FS            26    Off
  //      PWREN             28    On
  //      DAC 1             29    Off
  //      OPAMP             30    Off
  //      LPTIM 1           31    Off
  //
  RCC_APB1ENR1 = 0x10000000;
  RCC_APB1SMENR1 = 0x10000000;

  //--- Enable the following APB1 Peripherials
  //--- RCC Peripherial Clock 1
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... ..|. ._||
  //      0000 0000 0000 0000 0000 0000 0000 0000
  //
  //  LPUART 1 Ena      Off
  //  I2C4 Ena          Off
  //  LPUART 1 Ena      Off
  //  LPUART 1 Ena      Off
  RCC_APB1ENR2 = 0x00000000;
  RCC_APB1SMENR2 = 0x00000000;

  //-------------------------------------------------------------------------------------------
  //    Enable the following APB2 Peripherials
  //-------------------------------------------------------------------------------------------
  //--- Enable the following APB2 Peripherials
  //--- RCC Peripherial Clock 2 Enable
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ...|
  //      0000 0000 0000 0000 0000 0000 0000 0001
  //
  //
  RCC_APB2ENR = 0x00000001;
  RCC_APB2SMENR = 0x00000001;

  //--- Wait to settle down
  nop4;

  //===========================================================================================
  //    Configure GPIO Ports
  //===========================================================================================

  //-------------------------------------------------------------------------------------------
  //      Configure GPIO_A
  //-------------------------------------------------------------------------------------------
  //      GPIO MODE
  //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
  //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
  //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
  //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      00 00.00 00.00 00.00 00.01 01.01 01.01 01.01 01
  //      OT OT OT OT OT OT OT OT OT OT OT OT OT OT OT OT
  // GPIOA_MODER = 0x55555555;                       //--- Pin PA08 = Regular I/O

  //----- Test Configuration ------------
  GPIOA_MODER = 0x55555555;                   //--- Set PA08 = I/O Type A08 = MOC Out
  //-------------------------------------

  //      GPIO OTYPE
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOA_OTYPER = 0x00000000;                      //--- All Outputs are Push/Pull

  //      GPIO OSPEED
  //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
  //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
  //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
  //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11
  //      FS FS FS FS FS FS FS FS FS FS FS FS FS FS FS FS
  GPIOA_OSPEEDR = 0xFFFFFFFF;                     //--- Every One is High Speed

  //      GPIO INPUT PUPD RESISTORS
  //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
  //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
  //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
  //      .. ..|.. ..|.. ..|.. ..|.. ..|.. ..|.. ..|.. ..
  //      00 00 00 00 00 00 00 01 00 00 00 00 00 00 00 00
  //      NP NP NP NP NP NP NP NP NP NP NP NP NP NP NP NP
  GPIOA_PUPDR = 0x00000000;                       //--- Set No Port A Pins as PU

  //      GPIO ODR
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOA_ODR = 0x00000000;                         //--- Start with all 0's out

  //      GPIOBSRR
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOA_BSRR = 0x00000000;                        //--- Nothing to BSRR

  //      GPIO LCKR
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOA_LCKR = 0x00000000;                        //--- All Ports are unlocked

  //      GPIO AFRL
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOA_AFRL = 0x00000000;                        //--- Set AFRL to 0

  //      GPIO AFRH
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOA_AFRH = 0x00000000;                        //--- Set AFRH to 0


  //-------------------------------------------------------------------------------------------
  //      Configure GPIO_B
  //-------------------------------------------------------------------------------------------
  //      GPIO MODE
  //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
  //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
  //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
  //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      00 00 00 00 00 00 00 00 01 01 01 01 01 01 01 01
  //      IN IN.IN IN.IN IN.IN IN.OT OT.OT OT.OT OT.OT OT
  GPIOB_MODER = 0x55555555;

  //      GPIO OTYPE
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOB_OTYPER = 0x00000000;

  //      GPIO OSPEED
  //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
  //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
  //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
  //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11
  //      FS FS FS FS FS FS FS FS FS FS FS FS FS FS FS FS
  GPIOB_OSPEEDR = 0xFFFFFFFF;

  //      GPIO INPUT PUPD RESISTORS
  //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
  //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
  //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
  //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  GPIOB_PUPDR = 0x00000000;

  //      GPIO ODR
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOB_ODR = 0x00000000;

  //      GPIOBSRR
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOB_BSRR = 0x00000000;

  //      GPIO LCKR
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOB_LCKR = 0x00000000;

  //      GPIO AFRL
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0100 0100 0000 0000 0000 0000 0000 0000
  GPIOB_AFRL = 0x00000000;

  //      GPIO AFRH
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOB_AFRH = 0x00000000;

  //--- Waste a little Time for things to settle down
  nop4;

  //-------------------------------------------------------------------------------------------
  //      Configure GPIO_C
  //-------------------------------------------------------------------------------------------
  //      GPIO MODE
  //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
  //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
  //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
  //      .w .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  //      OT IN.IN IN.IN IN.IN IN.IN IN.IN IN.IN IN.IN IN
  GPIOC_MODER = 0x55555555;

  //      GPIO OTYPE
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOC_OTYPER = 0x00000000;

  //      GPIO OSPEED
  //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
  //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
  //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
  //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11
  //      FS FS FS FS FS FS FS FS FS FS FS FS FS FS FS FS
  GPIOC_OSPEEDR = 0xFFFFFFFF;

  //      GPIO INPUT PUPD RESISTORS
  //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
  //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
  //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
  //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  GPIOC_PUPDR = 0x00000000;

  //      GPIO ODR
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOC_ODR = 0x00000000;

  //      GPIOBSRR
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOC_BSRR = 0x00000000;

  //      GPIO LCKR
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOC_LCKR = 0x00000000;

  //      GPIO AFRL
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0100 0100 0000 0000 0000 0000 0000 0000
  GPIOC_AFRL = 0x00000000;

  //      GPIO AFRH
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0000
  GPIOC_AFRH = 0x00000000;

  //--- Waste a little Time for things to settle down
  nop4;

  //--- Set Priviledged Mode to Enable
  ubSVCn = 0x05;                                  //--- Set the SVC Number
  SVC_CALL;                                       //--- Call Software Service Interrupt

  //--- Enable FPU
  FPU_ENA;

  //--- Preset internal reference voltage to 2.5V
  //      VREFBUF
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0000 0000 0000 0000 0000 0000 0000 0101
  VREFBUF_CSR = 0x00000005;                       //--- VREF = 2.500V Internal Ref

  //  VREFBUF_CSR = 0x00000001;                     //--- VREF = 2.048V Internal Ref
  //  VREFBUF_CSR = 0x00000000;                     //--- VREF = External Reference

  //--- Start Up SysTick Timer As Pacer Set for 10 KHz
  STK_LOAD = 899;                                 //--- 100 uSec Period (900 - 1)
  STK_VAL = 899;                                  //--- Set STK_VAL to Max Value

  //--- Use the AHB/8 Clock Source
  //--- Enable the Tick Interrupt
  //--- Enable the SysTick Counter
  STK_CTRL = 0x00000003;                          //--- Set Up Systick

  NVIC_SetPriority(-1, 1);

  STK_CTRL = 0x00000003;                          //--- Enable Systick

  //--- Show that Init Complete
  ulSystemFlags |= 0x40000000;                    //--- Hi = Reset Complete

  nop4;

  //--- Call the Main Function after basic boot complete
  main();
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
