//============================================================================================
//                                        QUORB Inc.                                                 //
//                                -------------------------
//
//                                     C Start Up Code
//                                     ---------------
//
//                           Written By:  Sancar James Fredsti
//
//============================================================================================

#ifndef  STARTUP_H
  #define   STARTUP_H

  // start address for the initialization values of the .data section.defined in linker script
  extern unsigned long _etext;

  // start of internal data
  extern unsigned long _sidata;

  // start address for the .data section. defined in linker script
  extern unsigned long _sdata;

  // end address for the .data section. defined in linker script
  extern unsigned long _edata;

  // start address for the .bss section. defined in linker script
  extern unsigned long _sbss;

  // end address for the .bss section. defined in linker script
  extern unsigned long _ebss;

  // init value for the stack pointer. defined in linker script
  // init value for the stack pointer. defined in linker script
  extern void _estack (void);

  //------------------------------------------------------------------------------------------
  //  GPIO Pin Alternate Function Definitions
  //------------------------------------------------------------------------------------------
  //
  //--- Alternate function AF0 to AF7
  //--- AF#     AF0       AF1       AF2       AF3       AF4       AF5       AF6       AF7
  //    Pin
  //--- PA0     -         TIM2_CH1  -         -         -         -         -         UART2_CTS
  //--- PA1     -         TIM2_CH2  -         -         I2C1_SMBA SPI1_SCK  -         UART2_RTS
  //--- PA2     -         TIM2_CH3  -         -         -         -         -         UART2_TX
  //--- PA3     -         TIM2_CH4  -         -         -         -         -         UART2_RX
  //--- PA4     -         -         -         -         -         SPI1_NSS  SPI3_NSS  UART2_CK
  //--- PA5     -         TIM2_CH1  TIM2_ETR  -         -         SPI1_SCK  -         -
  //--- PA6     -         TIM1_BKIN -         -         -         SPI1_MISO COMP1_OUT UART3_CTS
  //--- PA7     -         TIM1_CH1N -         -         I2C3_SCL  SPI1_MOSI -         -
  //--- PA8     MCO       TIM1_CH1  -         -         -         -         -         UART1_CK
  //--- PA9     -         TIM1_CH2  -         -         I2C1_SCL  -         -         UART1_TX
  //--- PA10    -         TIM1_CH3  -         -         I2C1_SDA  -         -         UART1_RX
  //--- PA11    -         TIM1_CH4  TIM1_BKIN2-         -         SPI1_MISO COMP1_OUT UART1_CTS
  //--- PA12    -         TIM1_ETR  -         -         -         SPI1_MOSI -         UART1_RTS
  //--- PA13  JTMS-SWDIO  IR_OUT    -         -         -         -         -         -
  //--- PA14  JTCK-SWCLK  LPTIM1_O  -         -         I2C1_SMBA -         -         -
  //--- PA15  JTDI        TIM2_CH1  TIM2_ETR  USART2_RX -         SPI1_NSS  SPI3_NSS  UART3_RTS
  //
  //--- PB0     -         TIM1_CH2N -         -         -         SPI1_NSS  -         UART3_CK
  //--- PB1     -         TIM1_CH3N -         -         -         -         -         UART3_RTS
  //---
  //--- PB3 JTDOTRACESWO  TIM2_CH2  -         -         -         SPI1_SCK  SPI3_SCK  UART1_RTS
  //--- PB4   NJTRST      -         -         -         I2C3_SDA  SPI1_MISO SPI3_MISO UART1_CTS
  //--- PB5     -         LPTIM1_IN1 -        -         I2C1_SMBA SPI1_MOSI SPI3_MOSI UART1_CK
  //--- PB6     -         LPTIM1_ETR -        -         I2C1_SCL  -         -         UART1_TX
  //--- PB7     -         LPTIM1_IN2 -        -         I2C1_SDA  -         -         UART1_RX
  //
  //--- PC14    -         -         -         -         -         -         -         -
  //--- PC15    -         -         -         -         -         -         -         -
  //--- PH3     -         -         -         -         -         -         -         -




  //--- Alternate function AF8 to AF15(1)
  //--- AF#   AF8         AF9       AF10      AF11      AF12      AF13      AF14      AF15
  //--- PA0     -         -         -         -         COMP1_OUT SAI1_ECLK TIM2_ETR  EVENTOUT
  //--- PA1     -         -         -         -         -         -         TIM15_C1N EVENTOUT
  //--- PA2   LPUART1_TX  -         QSPI_BK1  -         COMP2_OUT     -     TIM15_CH1 EVENTOUT
  //--- PA3   LPUART1_RX  -         QSPI_CLK  -         -         SAI1MCLK  TIM15_CH2 EVENTOUT
  //--- PA4     -         -         -         -         -         SAI1_FS_B LTIM2_OUT EVENTOUT
  //--- PA5     -         -         -         -         -         -         LTIM2_ETR EVENTOUT
  //--- PA6   LPUART1_CTS -         QSPI_IO3  -         TIM1_BKIN -         TIM16_CH1 EVENTOUT
  //--- PA7     -         -         QSPI_IO2  -         COMP2_OUT -         -         EVENTOUT
  //--- PA8     -         -         -         -         SWPMI1_IO SAI1_SCKA LTIM2_OUT EVENTOUT
  //--- PA9     -         -         -         -         -         SAI1_FS_A TIM15BKIN EVENTOUT
  //--- PA10    -         -         USBCRSSNC -         -         SAI1_SD_A -         EVENTOUT
  //--- PA11    -         CAN1_RX   USB_DM    -         TIM1_BKC1 -         -         EVENTOUT
  //--- PA12    -         CAN1_TX   USB_DP    -         -         -         -         EVENTOUT
  //--- PA13    -         -         USB_NOE   -         SWPMI1TX  SAI1_SD_B -         EVENTOUT
  //--- PA14    -         -         -         -         SWPMI1RX  SAI1_FS_B -         EVENTOUT
  //--- PA15    -         TSCG3_IO1 -         -         SWPMI1SUS -         -         EVENTOUT
  //
  //--- PB0     -         -         QSPIBK1IO1-         COMP1_OUT SAI1_ECLK -         EVENTOUT
  //--- PB1     LUART1RTS -         QSPIBK1IO0-         -         -         LTIM2_IN1 EVENTOUT
  //---
  //--- PB3     -         -         -         -         -         SAI1_SCKB -         EVENTOUT
  //--- PB4     -         TSC_G2IO1 -         -         -         SAI1_MCKB -         EVENTOUT
  //--- PB5     -         TSC_G2IO2 -         -         -         SAI1_SDB  -         EVENTOUT
  //--- PB6     -         TSC_G2IO3 -         -         -         SAI1_FSB  -         EVENTOUT
  //--- PB7     -         TSC_G2IO4 -         -         -         -         -         EVENTOUT
  //
  //--- PC14    -         -         -         -         -         -         -         EVENTOUT
  //--- PC15    -         -         -         -         -         -         -         EVENTOUT
  //--- PH3     -         -         -         -         -         -         -         EVENTOUT

  //------------------------------------------------------------------------------------------
  //  Port Definition Function
  //------------------------------------------------------------------------------------------
  //
  //  All Unused / Not Configured Ports are assigned as FAST digital outputs.  This will
  //  protect ports and allow for debugging flags.
  //
  //        Port A Definition and Functions
  //        -------------------------------
  // Bit     Function Name               Description
  // ----   ---------------------------  ----------------------------------------
  // PA00    GPIO_00
  // PA01    GPIO_01
  // PA02    GPIO_02
  // PA03    GPIO_03
  // PA04    GPIO_04
  // PA05    GPIO_05
  // PA06    GPIO_06
  // PA07    GPIO_07
  // PA08    GPIO_08
  // PA09    GPIO_09
  // PA10    GPIO_10
  // PA11    GPIO_11
  // PA12    GPIO_12
  // PA13    GPIO_13
  // PA14    GPIO_14
  // PA15    GPIO_15
  //
  //        Port B Definition and Functions
  //        -------------------------------
  // PB00    GPIO_16
  // PB01    GPIO_17
  // PB02    UNUSED                      UNASSIGNED/UNUSED
  // PB03    GPIO_19
  // PB04    GPIO_20
  // PB05    GPIO_21
  // PB06    GPIO_22
  // PB07    GPIO_23
  //
  //  GPIOB_CRL = 0x33330000
  //  GPIOB_CRH = 0x34333330
  //
  //------------------------------------------------------------------------------------------

  //------------------------------------------------------------------------------------------
  //                         I/O Port Definition and Assignments
  //------------------------------------------------------------------------------------------
  //
  //  Hi  Nibble  Bits  7,6,5,4 = AF#
  //  Lo  Nibble  Bits  3,2,1,0 = Port Pin Function
  //                    0 0 0 0 = Generic Input
  //                    0 0 0 1 = Generic Output
  //                    0 0 1 0 = Alternate Function
  //                    0 0 1 1 = Analog I/O
  //


  //-------------------------------------------------------------------------------------------
  //--- Define System Clock Values Here
  //-------------------------------------------------------------------------------------------
  //    See Project Defs
  //
  //  System Normally operates from HSI16 Clock
  //  #define sfCPU_FREQ = (flt)72000000.0           /1
  //  #define sfAHB_CLK =  (flt)72000000.0           /1
  //  #define sfAHB_TCLK = (flt)72000000.0           /1
  //
  //  #define sfAPB1_CLK = (flt)72000000.0           /1
  //  #define sfAPB2_CLK = (flt)72000000.0           /1
  //
  //  #define SYSCLK    72000000UL                   //--- System Clock 72.0000MHz
  //  #define PCLK1     SYSCLK                       //--- PCLK1 = 72.0000 MHz
  //  #define PCLK2     SYSCLK                       //--- PCLK2 = 72.0000 MHz
  //

  extern  u08     ubSVCn;
  extern  u32     ulT;
  extern  u32     tmp;                               //--- Temporary Number
  extern  u32     ulSystemFlags;                     //--- System Status Flags (User Defined)

  //--- Function Prototypes
  void  fnReset_IRQ(void);

#endif
