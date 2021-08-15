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

  //  #define OS_TYPE 1                               //--- Quorb RTOS is in effect
  #define OS_TYPE 0                               //--- Polled Loop OPSYS is in effect

  //--- Define Software Version
  #define MAJOR_VER   0                           //--- 0 = Pre Release
  #define MINOR_VER   1                           //--- 1 = First Release
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
  #define AHBCLK    SYSCLK
  #define PCLK1     SYSCLK
  #define PCLK2     SYSCLK

  //--- Define Memory Sizes
  #define RAM_SIZE    65536                       //--- 64K of RAM
  #define FLASH_SIZE  262144                      //--- 256K of Flash Memory
  #define I2C_EEPROM  8192                        //--- 8192 Bytes of EEPROM 64K Bits
  #define STACK_SIZE  4096                        //--- Stack Size = 4K   By Default

  //--- Numeric Port Number Values
  #define PA00  0
  #define PA01  1
  #define PA02  2
  #define PA03  3
  #define PA04  4
  #define PA05  5
  #define PA06  6
  #define PA07  7
  #define PA08  8
  #define PA09  9                                 //--- Also Used as USART0 TXD
  #define PA10  10                                //--- Also Used as USART0 RXD
  #define PA11  11                                //--- Also Used as USB DM
  #define PA12  12                                //--- Also Used as USB DP
  #define PA13  13
  #define PA14  14
  #define PA15  15

  #define PB00  16
  #define PB01  17
  #define PB02  18                                //--- Unassigned in 432 Devices
  #define PB03  19
  #define PB04  20
  #define PB05  21
  #define PB06  22                                //--- Also Used as I2C Data
  #define PB07  23                                //--- Also Used as I2C Clock

  #define PC14  24                                //--- LSE Clock Input
  #define PC15  25                                //--- Used to Drive Pacer LED

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

  //--- Include the common definitions used by QUORB Inc.
  #include  "commonheader.h"
  #include  "STM32L432_Map.h"                     //--- Processor Address and Definition MAP
  #include  "STM32L432_BitDefs.h"                 //--- Processor Peripherial Definitions
  #include  "UserCode.h"                          //--- Main Program
  #include  "startup.h"                           //--- Initialization Functions & Routines
  #include  "genrtn.h"
  #include  "interrupts.h"                        //--- Interrupt Definitions
#endif
