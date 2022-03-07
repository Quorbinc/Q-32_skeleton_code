//=============================================================================================
//                                        QUORB Inc.
//                                -------------------------
//
//                                Project Define Header File
//                               ----------------------------
//
//                           Written By:  Sancar James Fredsti
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//       The Processor uses the following peripherial devices located on the STM32L432
//
//  1.  GPIOA
//  2.  GPIOB
//  3.  SysTick
//  4.  USART1 @ 115200 Baud
//
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//        Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#ifndef PROJECTDEFS_H
  #define PROJECTDEFS_H

  //--- Define processor used
  #define PROCESSOR STM32L432KC                   //--- For this project use the STM32L432

  //--- Define Features Used in this Processor
  #define __CM4_REV                 0x0001U       //--- Core revision r0p1
  #define __MPU_PRESENT             1U            //--- STM32L4XX provides an MPU
  #define __NVIC_PRIO_BITS          4U            //--- STM32L4XX uses 4 Bits for the Priority
  #define __Vendor_SysTickConfig    1U            //--- Set to 1 if different SysTick Config
  #define __FPU_PRESENT             1U            //--- FPU present
  #define __FPU_USED                1U            //--- FPU Used

  //--- Useful Constants for angular computations
  #define sfPI          (flt)3.14159265359        //--- Single Precision PI
  #define sf2PI         (flt) (sfPI * (flt)2.0)   //--- Single Precision 2PI
  #define sfR2A         (flt) 57.295779513        //--- Multiply Radians to Get Angle
  #define sfA2R         (flt) 0.01745329252       //--- Multiply Angle to Get Radians

  //--- Define Operating System Type as either RealTime or User Loop
  //
  //--- This Clock Configuration provides a stable 72 MHz System Clock
  //    A Stable 48 MHz USB and Random Number Clock
  //    A stable 32768 RTC Clock
  //    A PLL Locked Main clock to the RTC Base Clock

  #define OS_TYPE 1                               //--- Quorb RTOS is in effect
  //  #define OS_TYPE 0                               //--- Polled Loop OPSYS is in effect

  //--- Define Software Version
  #define MAJOR_VER   1                           //--- 1 = First Release
  #define MINOR_VER   0                           //--- 0 = First Release

  #define SW_VER   (MAJOR_VER * 16) + MINOR_VER

  //--- Define Timing parameters
  #define SystemCoreClock ((u32) 72000000)
  #define RTC_FREQ        ((u32) 32768)
  #define LSE_FREQ        ((u32) 32768)
  #define MSI_FREQ        ((u32) 16000000)
  #define SYS_FREQ        ((u32) 72000000)
  #define AHB_FREQ        ((u32) 72000000)
  #define APB1_FREQ       ((u32) 72000000)
  #define APB2_FREQ       ((u32) 72000000)

  //--- SYSCLK = (XTALOSC * 3)
  #define SYSCLK    ((u32) 72000000)              //--- System Clock 72.0000MHz
  #define sfSYSCLK  ((flt) 72000000)
  #define AHBCLK    SYSCLK
  #define PCLK1     SYSCLK
  #define PCLK2     SYSCLK

  //--- Define Memory Sizes
  #define RAM_SIZE    65536                       //--- 64K of RAM
  #define FLASH_SIZE  262144                      //--- 256K of Flash Memory
  #define EEPROM_SIZE 8192                        //--- 8192 Bytes of EEPROM 64K Bits
  #define STACK_SIZE  4096                        //--- Stack Size = 4K   By Default

  //--- Enable these flags for the peripherial drivers that are USED in your program
  #define TESTHELP_FLAG                           //--- Test Functions enabled
  //  #define ADC_FLAG                                //--- Uses High Speed ADC
  //  #define DAC1_FLAG                               //--- Uses DAC-1
  //  #define DAC2_FLAG                               //--- Uses DAC-2
  //  #define USART1_FLAG                             //--- This program uses UARTS
  //  #define USART2_FLAG                             //--- This program uses UARTS
  //  #define USART3_FLAG                             //--- This program uses UARTS
  //  #define I2C1_FLAG                               //--- Uses I2C1
  //  #define I2C2_FLAG                               //--- Uses I2C2
  //  #define SPI1_FLAG                               //--- Uses SPI-1 Interface
  //  #define SPI2_FLAG                               //--- Uses SPI-2 Interface
  //  #define QSPI_FLAG                               //--- Uses QSPI Interface
  //  #define USB_FLAG                                //--- Uses USB Full Speed
  //  #define RTC_FLAG                                //--- Uses Real Time Clock
  //  #define RNG_FLAG                                //--- Uses Random Number Generator
  //  #define IWDG_FLAG                               //--- Uses Independant Watch Dog
  //  #define IRTIM_FLAG                              //--- Uses IRTIM InfaRed Interface
  //  #define RTC_FLAG                                //--- Uses Real Time Clock
  //  #define WWTG_FLAG                               //--- Uses Windowed WatchDog
  //  #define TAMP_FLAG                               //--- Uses Tamper Detection
  //  #define SWPMI_FLAG                              //--- Uses Serial Wire Interface
  //  #define CAN_FLAG                                //--- Uses CAN 2.0 Interface
  //  #define SAI_FLAG                                //--- Uses SAI Interface
  //  #define DMA_FLAG                                //--- Uses DMA Interface
  //  #define CRC_FLAG                                //--- Uses CRC Generator
  //  #define PGA_FLAG                                //--- Uses Programable OpAmp
  //  #define COMP1_FLAG                              //--- Uses Comparator #1
  //  #define COMP2_FLAG                              //--- Uses Comparator #2
  //  #define TIM1_FLAG                               //--- Uses Timer-1
  //  #define TIM2_FLAG                               //--- Uses Timer-2
  //  #define TIM3_FLAG                               //--- Uses Timer-3
  //  #define TIM6_FLAG                               //--- Uses Timer-6
  //  #define TIM7_FLAG                               //--- Uses Timer-7
  //  #define TIM15_FLAG                              //--- Uses Timer-15
  //  #define TIM16_FLAG                              //--- Uses Timer-16
  //  #define LPTIM1_FLAG                             //--- Uses LPtimer1
  //  #define LPTIM2_FLAG                             //--- Uses LPtimer2

  //-------------------------------------------------------------------------------------------
  //    Header files for libraries and program sections
  //    NOTE: The original header files have been modified to correct for errors in type
  //          casting and restricted access
  //-------------------------------------------------------------------------------------------

  #include  <reent.h>
  #include  <errno.h>
  #include  <sys/stat.h>
  #include  <sys/types.h>
  #include  <stdio.h>                             //--- Include STDIO
  #include  <string.h>                            //--- Include String Linrary
  #include  <stddef.h>                            //--- Include Standard Definitions
  #include  <stdlib.h>                            //--- Include Standard Linrary Finctions
  #include  <math.h>                              //--- Include Math Library Int & Float
  #include  <stdint.h>                            //--- Include standard types

  #include  "commonheader.h"                      //--- System Common Header
  #include  "STM32L432_Map.h"                     //--- Processor Address and Definition MAP
  #include  "STM32L432_BitDefs.h"                 //--- Processor Peripherial Definitions
  #include  "opsys.h"                             //--- OpSys Core MUST BE INCLUDED
  #include  "sys_tick.h"                          //--- System Tick Interrupt MUST BE INCLUDED
  #include  "main.h"                              //--- Main Program
  #include  "startup.h"                           //--- Initialization Functions & Routines
  #include  "genrtn.h"                            //--- Useful functions
  #include  "interrupts.h"                        //--- Interrupt Definitions & Functions
  #include  "timers.h"

  //--- Include the common definitions used by QUORB
  #ifdef TESTHELP_FLAG
    #include  "test_help.h"
  #endif

  #ifdef USART_FLAG
    #include  "uart_com.h"                        //--- USART Code
  #endif

  #ifdef I2C1_FLAG
    #include  "i2c.h"                             //--- I2C Code
  #endif

  #ifdef SPI_FLAG
    #include  "spi.h"                             //--- SPI Code
  #endif

  #ifdef TIM1_FLAG
    #include  "timers.h"                          //--- TIMER-1 Code
  #endif
#endif

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
