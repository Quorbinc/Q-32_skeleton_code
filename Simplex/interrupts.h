//===========================================================================================//
//                                Fredsti Industries,  Ltd.                                  //
//                                -------------------------                                  //
//                                                                                           //
//                               Interrupt Service  Routines                                 //
//                               ---------------------------                                 //
//                                                                                           //
//                           Written By:  Sancar James Fredsti                               //
//                                                                                           //
//===========================================================================================//


#ifndef INTERRUPTS_H
  #define INTERRUPTS_H

  //-------------------------------------------------------------------------------------------
  //    Interrupt Definition Numeric Table
  //-------------------------------------------------------------------------------------------

  //--- STM32L432 Nested Interrupt Controller Interrupt number defines
  #define Reset_IRQn                 -15  //--- 1 Cortex-M4 Reset Interrupt
  #define NMI_IRQn                   -14  //--- 2 Cortex-M4 Non Maskable Interrupt
  #define HardFault_IRQn             -13  //--- 3 Cortex-M4 Hard Fault Interrupt
  #define MemoryManagement_IRQn      -12  //--- 4 Cortex-M4 Memory Management Interrupt
  #define BusFault_IRQn              -11  //--- 5 Cortex-M4 Bus Fault Interrupt
  #define Illegalt_IRQn              -10  //--- 6 Cortex-M4 Usage Fault Interrupt

  #define uuIRQm9_IRQn               -9
  #define uuIRQm8_IRQn               -8
  #define uuIRQm7_IRQn               -7
  #define uuIRQm6_IRQn               -6
  #define SVCall_IRQn_IRQn           -5   //--- 11 Cortex-M4 SV Call Interrupt
  #define Debug_IRQn                 -4   //--- 12 Cortex-M4 Debug Monitor Interrupt
  #define PendSV_IRQn                -2   //--- 14 Cortex-M4 Pend SV Interrupt
  #define SysTick_IRQn               -1   //--- 15 Cortex-M4 System Tick Interrupt

  //--- Peripherial Function Interrupts
  #define WWDG_IRQn                  0    //--- Window WatchDog Interrupt
  #define PVD_PVM_IRQn               1    //--- PVD/PVM3/PVM4 through EXTI Line detection Interrupts
  #define TAMP_STAMP_IRQn            2    //--- Tamper and TimeStamp interrupts through the EXTI line
  #define RTC_WKUP_IRQn              3    //--- RTC Wakeup interrupt through the EXTI line
  #define FLASH_IRQn                 4    //--- FLASH global Interrupt
  #define RCC_IRQn                   5    //--- RCC global Interrupt
  #define EXTI_0_IRQn                6    //--- EXTI Line0 Interrupt
  #define EXTI_1_IRQn                7    //--- EXTI Line1 Interrupt
  #define EXTI_2_IRQn                8    //--- EXTI Line2 Interrupt
  #define EXTI_3_IRQn                9    //--- EXTI Line3 Interrupt

  #define EXTI_4_IRQn                10   //--- EXTI Line4 Interrupt
  #define DMA1_Channel1_IRQn         11   //--- DMA1 Channel 1 global Interrupt
  #define DMA1_Channel2_IRQn         12   //--- DMA1 Channel 2 global Interrupt
  #define DMA1_Channel3_IRQn         13   //--- DMA1 Channel 3 global Interrupt
  #define DMA1_Channel4_IRQn         14   //--- DMA1 Channel 4 global Interrupt
  #define DMA1_Channel5_IRQn         15   //--- DMA1 Channel 5 global Interrupt
  #define DMA1_Channel6_IRQn         16   //--- DMA1 Channel 6 global Interrupt
  #define DMA1_Channel7_IRQn         17   //--- DMA1 Channel 7 global Interrupt
  #define ADC1_IRQn                  18   //--- ADC1 global Interrupt
  #define CAN1_TX_IRQn               19   //--- CAN1 TX Interrupt

  #define CAN1_RX0_IRQn              20   //--- CAN1 RX0 Interrupt
  #define CAN1_RX1_IRQn              21   //--- CAN1 RX1 Interrupt
  #define CAN1_SCE_IRQn              22   //--- CAN1 SCE Interrupt
  #define EXTI_9_5_IRQn              23   //--- External Line[9:5] Interrupts
  #define TIM1_BRK_TIM15_IRQn        24   //--- TIM1 Break interrupt and TIM15 global interrupt
  #define TIM1_UP_TIM16_IRQn         25   //--- TIM1 Update Interrupt and TIM16 global interrupt
  #define TIM1_TRG_COM_IRQn          26   //--- TIM1 Trigger and Commutation Interrupt
  #define TIM1_CC_IRQn               27   //--- TIM1 Capture Compare Interrupt
  #define TIM2_IRQn                  28   //--- TIM2 global Interrupt
  #define uuIRQi29_IRQn              29

  #define uuIRQi30_IRQn              30
  #define I2C1_EV_IRQn               31   //--- I2C1 Event Interrupt
  #define I2C1_ER_IRQn               32   //--- I2C1 Error Interrupt
  #define I2C2_EV_IRQn               33   //--- I2C2 Event Interrupt
  #define I2C2_ER_IRQn               34   //--- I2C2 Error Interrupt
  #define SPI1_IRQn                  35   //--- SPI1 global Interrupt
  #define SPI2_IRQn                  36   //--- SPI2 global Interrupt
  #define USART1_IRQn                37   //--- USART1 global Interrupt
  #define USART2_IRQn                38   //--- USART2 global Interrupt
  #define USART3_IRQn                39   //--- USART3 global Interrupt

  #define EXTI_15_10_IRQn            40   //--- External Line[15:10] Interrupts
  #define RTC_ALARM_IRQn             41   //--- RTC Alarm (A and B) through EXTI Line Interrupt
  #define uuIRQi42_IRQn              42
  #define uuIRQi43_IRQn              43
  #define uuIRQi44_IRQn              44
  #define uuIRQi45_IRQn              45
  #define uuIRQi46_IRQn              46
  #define uuIRQi47_IRQn              47
  #define uuIRQi48_IRQn              48
  #define SDMMC1_IRQn                49   //--- SDMMC1 global Interrupt

  #define uuIRQi50_IRQn              50
  #define SPI3_IRQn                  51   //--- SPI3 global Interrupt
  #define uuIRQi52_IRQn              52
  #define uuIRQi53_IRQn              53
  #define TIM6_DAC_IRQn              54   //--- TIM6 global and DAC1&2 underrun error  interrupts
  #define TIM7_IRQn                  55   //--- TIM7 global interrupt
  #define DMA2_Channel1_IRQn         56   //--- DMA2 Channel 1 global Interrupt
  #define DMA2_Channel2_IRQn         57   //--- DMA2 Channel 2 global Interrupt
  #define DMA2_Channel3_IRQn         58   //--- DMA2 Channel 3 global Interrupt
  #define DMA2_Channel4_IRQn         59   //--- DMA2 Channel 4 global Interrupt

  #define DMA2_Channel5_IRQn         60   //--- DMA2 Channel 5 global Interrupt
  #define uuIRQi61_IRQn              61
  #define uuIRQi62_IRQn              62
  #define uuIRQi63_IRQn              63
  #define COMP_IRQn                  64   //--- COMP1 and COMP2 Interrupts
  #define LPTIM1_IRQn                65   //--- LP TIM1 interrupt
  #define LPTIM2_IRQn                66   //--- LP TIM2 interrupt
  #define USB_IRQn                   67   //--- USB event Interrupt
  #define DMA2_Channel6_IRQn         68   //--- DMA2 Channel 6 global interrupt
  #define DMA2_Channel7_IRQn         69   //--- DMA2 Channel 7 global interrupt

  #define LPUART1_IRQn               70   //--- LP UART1 interrupt
  #define QUADSPI_IRQn               71   //--- Quad SPI global interrupt
  #define I2C3_EV_IRQn               72   //--- I2C3 event interrupt
  #define I2C3_ER_IRQn               73   //--- I2C3 error interrupt
  #define SAI1_IRQn                  74   //--- Serial Audio Interface 1 global interrupt
  #define uuIRQi75_IRQn              75
  #define SWPMI1_IRQn                76   //--- Serial Wire Interface 1 global interrupt
  #define TSC_IRQn                   77   //--- Touch Sense Controller global interrupt
  #define uuIRQi78_IRQn              78
  #define uuIRQi79_IRQn              79

  #define RNG_IRQn                   80   //--- RNG global interrupt
  #define FPU_IRQn                   81   //--- FPU global interrupt
  #define CRS_IRQn                   82   //--- CRS global interrupt

  //-------------------------------------------------------------------------------------------
  //    Interrupt Service Table and Stack
  //-------------------------------------------------------------------------------------------
  // init value for the stack pointer. defined in linker script
  extern u08 const ubNVICtable [100];

  //-------------------------------------------------------------------------------------------
  //    Interrupt Service Function Prototypes
  //-------------------------------------------------------------------------------------------
  void  fnNull_IRQ(void);            // -15   Null_ IRQReset IRQ                   0x00000004
  void  fnNMI_IRQ(void);             // -14   NMI IRQ                              0x00000008
  void  fnHardFault_IRQ(void);       // -13   Hard Fault IRQ                       0x0000000C
  void  fnMemManage_IRQ(void);       // -12   Memory Management Fault              0x00000010
  void  fnBusFault_IRQ(void);        // -11   Bus Fault                            0x00000014
  void  fnIllegal_IRQ(void);         // -10   Bad Instruction                      0x00000018

  //-   void  fnNull_IRQ(void);            // - 9   Blank                                0x0000001C
  //-   void  fnNull_IRQ(void);            // - 8   Blank                                0x00000020
  //-   void  fnNull_IRQ(void);            // - 7   Blank                                0x00000024
  //-   void  fnNull_IRQ(void);            // - 6   Blank                                0x00000028

  void  fnSVC_IRQ(void);             // - 5   SVCall IRQ                           0x0000002C
  void  fnDebug_IRQ(void);           // - 4   Debug IRQ                            0x00000030
  //-   void  fnNull_IRQ(void);            // - 3   Blank                                0x00000034
  void  fnPendSVC_IRQ(void);         // - 2   PendSV IRQ                           0x00000038
  void  fnSysTick_IRQ(void);         // - 1   SysTick IRQ Non Maskable Tick        0x0000003C

  //--- Peripherial Interrupts
  void  fnWWDG_IRQ(void);            // 00 - Window Watchdog                       0x00000040
  void  fnPVD_IRQ(void);             // 01 - PVD through EXTI Line detect          0x00000044
  void  fnRTC_IRQ(void);             // 02 - RTC Time Stamp                        0x00000048
  void  fnRTC_WKUP_IRQ(void);        // 03 - RTC Wake Up                           0x0000004C
  void  fnFLASH_IRQ(void);           // 04 - Flash                                 0x00000050

  void  fnRCC_IRQ(void);             // 05 - RCC                                   0x00000050
  void  fnEXTI_0_IRQ(void);          // 06 - EXTI Line 0                           0x00000054
  void  fnEXTI_1_IRQ(void);          // 07 - EXTI Line 1                           0x00000058
  void  fnEXTI_2_IRQ(void);          // 08 - EXTI Line 2                           0x0000005C
  void  fnEXTI_3_IRQ(void);          // 09 - EXTI Line 3                           0x00000060
  void  fnEXTI_4_IRQ(void);          // 10 - EXTI Line 4                           0x00000068

  void  fnDMA_11_IRQ(void);          // 11 - DMA1 Channel 1                        0x0000006C
  void  fnDMA_12_IRQ(void);          // 12 - DMA1 Channel 2                        0x00000070
  void  fnDMA_13_IRQ(void);          // 13 - DMA1 Channel 3                        0x00000074
  void  fnDMA_14_IRQ(void);          // 14 - DMA1 Channel 4                        0x00000078
  void  fnDMA_15_IRQ(void);          // 15 - DMA1 Channel 5                        0x0000007C
  void  fnDMA_16_IRQ(void);          // 16 - DMA1 Channel 6                        0x00000080
  void  fnDMA_17_IRQ(void);          // 17 - DMA1 Channel 7                        0x00000084

  void  fnADC_IRQ(void);             // 18 - ADC1 & ADC2                           0x00000088

  void  fnCAN1_TX_IRQ(void);         // 19 - CAN1 TX                               0x0000008C
  void  fnCAN1_RX0_IRQ(void);        // 20 - CAN1 RX0                              0x00000090
  void  fnCAN1_RX1_IRQ(void);        // 21 - CAN1 RX1                              0x00000094
  void  fnCAN1_SCE_IRQ(void);        // 22 - CAN1 SCE                              0x00000098

  void  fnEXTI_5_9_IRQ(void);        // 23 - EXTI Line 5_9                         0x0000009C

  void  fnTIM1_BK_TIM15_IRQ(void);   // 24 - TIM1 Break                            0x000000A0
  void  fnTIM1_UP_TIM16_IRQ(void);   // 25 - TIM1 Update                           0x000000A4
  void  fnTIM1_TRG_COM_IRQ(void);    // 26 - TIM1 Trigger                          0x000000A8
  void  fnTIM1_CC_IRQ(void);         // 27 - TIM1 Capture Compare                  0x000000AC

  void  fnTIM2_IRQ(void);            // 28 - TIM2 Global                           0x000000B0
  void  fnTIM3_IRQ(void);            // 29 - TIM3 Global                           0x000000B4
  void  fnTIM4_IRQ(void);            // 30 - TIM4 Global                           0x000000B8

  void  fnI2C1_EV_IRQ(void);         // 31 - I2C1 Event                            0x000000BC
  void  fnI2C1_ER_IRQ(void);         // 32 - I2C1 Error                            0x000000C0
  void  fnI2C2_EV_IRQ(void);         // 33 - I2C2 Event                            0x000000C4
  void  fnI2C2_ER_IRQ(void);         // 34 - I2C2 Error                            0x000000C8

  void  fnSPI1_IRQ(void);            // 35 - SPI1 General Interrupt                0x000000CC
  void  fnSPI2_IRQ(void);            // 36 - SPI2 General Interrupt                0x000000D0

  void  fnUSART1_IRQ(void);          // 37 - USART1 General Interrupt              0x000000D4
  void  fnUSART2_IRQ(void);          // 38 - USART2 General Interrupt              0x000000D8
  void  fnUSART3_IRQ(void);          // 39 - USART3 General Interrupt              0x000000DC

  void  fnEXTI_10_15_IRQ(void);      // 40 - EXTI Lines 10-15                      0x000000E0
  void  fnRTC_ALARM_IRQ(void);       // 41 - RTC Alarm+                            0x000000E4

  //-   void  fnNull_IRQ(void);            // 42 - Blank                                 0x000000E8
  //-   void  fnNull_IRQ(void);            // 43 - Blank                                 0x000000EC
  //-   void  fnNull_IRQ(void);            // 44 - Blank                                 0x000000F0
  //-   void  fnNull_IRQ(void);            // 45 - Blank                                 0x000000F4
  //-   void  fnNull_IRQ(void);            // 46 - Blank                                 0x000000F8
  //-   void  fnNull_IRQ(void);            // 47 - Blank                                 0x000000FC
  //-   void  fnNull_IRQ(void);            // 48 - Blank                                 0x00000100

  void  fnSDMMC1_IRQ(void);          // 49 - SDMMC1 IRQ                            0x00000104

  //-   void  fnNull_IRQ(void);            // 50 - Blank                                 0x00000108

  void  fnSPI3_IRQ(void);            // 51 - SPI3 General Interrupt                0x0000010C
  void  fnUSART4_IRQ(void);          // 52 - USART4 General Interrupt              0x00000110

  //-   void  fnNull_IRQ(void);            // 53 - Blank                                 0x00000114

  void  fnTIM6_IRQ(void);            // 54 - TIM6 Global DAC Under                 0x00000118
  void  fnTIM7_IRQ(void);            // 55 - TIM7 Global                           0x0000011C

  void  fnDMA_21_IRQ(void);          // 56 - DMA1 Channel 0                        0x00000120
  void  fnDMA_22_IRQ(void);          // 57 - DMA1 Channel 1                        0x00000124
  void  fnDMA_23_IRQ(void);          // 58 - DMA1 Channel 2                        0x00000128
  void  fnDMA_24_IRQ(void);          // 59 - DMA1 Channel 3                        0x0000012C
  void  fnDMA_25_IRQ(void);          // 60 - DMA1 Channel 4                        0x00000130

  //-   void  fnNull_IRQ(void);            // 61 - Blank                                 0x00000134
  //-   void  fnNull_IRQ(void);            // 62 - Blank                                 0x00000138
  //-   void  fnNull_IRQ(void);            // 63 - Blank                                 0x0000013C

  void  fnCOMP_IRQ(void);            // 64 - Analog Compare                        0x00000140
  void  fnLPTIM1_IRQ(void);          // 65 - CAN1 RX1                              0x00000144
  void  fnLPTIM2_IRQ(void);          // 66 - CAN1 SCE                              0x00000148

  void  fnUSB_FS_IRQ(void);          // 67 - Full Speed USB OTG                    0x0000014C

  void  fnDMA_26_IRQ(void);          // 68 - DMA2 Channel 6                        0x00000150
  void  fnDMA_27_IRQ(void);          // 69 - DMA1 Channel 7                        0x00000154
  void  fnLPUART1_IRQ(void);         // 70 - Low Power UART 1                      0x00000158
  void  fnQUADSPI_IRQ(void);         // 71 - QUAD SPI                              0x0000015C
  void  fnI2C3_EV_IRQ(void);         // 72 - I2C3 Event                            0x00000160
  void  fnI2C3_ER_IRQ(void);         // 73 - I2C3 Error                            0x00000164
  void  fnSAI_IRQ(void);             // 74 - SAI IRQ                               0x00000168
  //-   void  fnNull_IRQ(void);            // 75 - Blank                                 0x0000016C
  void  fnSWPMI1_IRQ(void);          // 76 - USB OTG HS Wakeup through             0x00000170
  void  fnTSC_IRQ(void);             // 77 - USB OTG HS                            0x00000174

  //-   void  fnNull_IRQ(void);            // 78 - Blank                                 0x00000178
  //-   void  fnNull_IRQ(void);            // 79 - Blank                                 0x0000017C

  void  fnRNG_IRQ(void);             // 80 - DCMI                                  0x00000180
  void  fnFPU_IRQ(void);             // 81 - Floating Point Interrupt              0x00000184
  void  fnCRS_IRQ(void);             // 82 - CRS Interrupt                         0x00000188

  //-  void  fnI2C4_EV_IRQ(void);         // 83 - I2C4 Event                            0x0000018C
  //-  void  fnI2C4_ER_IRQ(void);         // 84 - I2C4 Error                            0x00000190

  //- void  fnNull_IRQ(void);            // 85 - Blank                                 0x00000194
  //- void  fnNull_IRQ(void);            // 86 - Blank                                 0x00000198
  //- void  fnNull_IRQ(void);            // 87 - Blank                                 0x0000019C
  //- void  fnNull_IRQ(void);            // 88 - Blank                                 0x000001A0
  //- void  fnNull_IRQ(void);            // 89 - Blank                                 0x000001A4
  //- void  fnNull_IRQ(void);            // 90 - Blank                                 0x000001A8
  //- void  fnNull_IRQ(void);            // 91 - Blank                                 0x000001AC

  //-------------------------------------------------------------------------------------------
  //    Initialize NVIC Priority and Interrupt Table
  //-------------------------------------------------------------------------------------------
  void fnInitNVIC (void);

  void  fnEnaInt (u16 uwIntNum);
  void  fnDisInt (u16 uwIntNum);
  void  fnSetInt (u16 uwIntNum);
  void  fnClrInt (u16 uwIntNum);
  void  fnSetIntPriority (u16 uwIntNum, u08 ubPri);
  void  fnSetIntPend (u16 uwIntNum);
  void  fnClrIntPend (u16 uwIntNum);


  //  Enable External Interrupt
  //  The function enables a device-specific interrupt in the NVIC interrupt controller.
  //  \param [in]      IRQn  External interrupt number. Value cannot be negative.
  //
  __STATIC_INLINE void NVIC_EnableIRQ(u32 IRQn)
  {
    NVIC->ISER[(((u32)IRQn) >> 5UL)] = (u32)(1UL << (((u32)IRQn) & 0x1FUL));
  }


  //  Disable External Interrupt
  //  The function disables a device-specific interrupt in the NVIC interrupt controller.
  //  \param [in]      IRQn  External interrupt number. Value cannot be negative.
  //
  __STATIC_INLINE void NVIC_DisableIRQ(u32 IRQn)
  {
    NVIC->ICER[(((u32)IRQn) >> 5UL)] = (u32)(1UL << (((u32)IRQn) & 0x1FUL));
  }

  //  Get Pending Interrupt
  //  The function reads the pending register in the NVIC and returns the pending bit
  //  for the specified interrupt.
  //  \param [in]      IRQn  Interrupt number.
  //
  //  \return             0  Interrupt status is not pending.
  //  \return             1  Interrupt status is pending.
  //
  __STATIC_INLINE u32 NVIC_GetPendingIRQ(u32 IRQn)
  {
    return((u32)(((NVIC->ISPR[(((u32)IRQn) >> 5UL)] & (1UL << (((u32)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }

  //  Set Pending Interrupt
  //  The function sets the pending bit of an external interrupt.
  //  \param [in]      IRQn  Interrupt number. Value cannot be negative.
  //
  __STATIC_INLINE void NVIC_SetPendingIRQ(u32 IRQn)
  {
    NVIC->ISPR[(((u32)IRQn) >> 5UL)] = (u32)(1UL << (((u32)IRQn) & 0x1FUL));
  }

  //  Clear Pending Interrupt
  //  The function clears the pending bit of an external interrupt.
  //  \param [in]      IRQn  External interrupt number. Value cannot be negative.
  //
  __STATIC_INLINE void NVIC_ClearPendingIRQ(u32 IRQn)
  {
    NVIC->ICPR[(((u32)IRQn) >> 5UL)] = (u32)(1UL << (((u32)IRQn) & 0x1FUL));
  }

  //  Get Active Interrupt
  //  The function reads the active register in NVIC and returns the active bit.
  //  \param [in]      IRQn  Interrupt number.
  //
  //  \return             0  Interrupt status is not active.
  //  \return             1  Interrupt status is active.
  //
  __STATIC_INLINE u32 NVIC_GetActive(u32 IRQn)
  {
    return((u32)(((NVIC->IABR[(((u32)IRQn) >> 5UL)] & (1UL << (((u32)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }

  //  Set Interrupt Priority
  //  The function sets the priority of an interrupt.
  //  \note The priority cannot be set for every core interrupt.
  //  \param [in]      IRQn  Interrupt number.
  //  \param [in]  priority  Priority to set. in range of 0 to 0x0F
  //
  __STATIC_INLINE void NVIC_SetPriority(u32 IRQn, u32 priority)
  {
    NVIC->IP[((u32)IRQn)] = (u08)((priority << (8 - __NVIC_PRIO_BITS)) & (u32)0xFFUL);
  }

  //  Get Interrupt Priority
  //  The function reads the priority of an interrupt. The interrupt
  //  number can be positive to specify an external (device specific)
  //  interrupt, or negative to specify an internal (core) interrupt.
  //  \param [in]   IRQn  Interrupt number.
  //  \return             Interrupt Priority. Value is aligned automatically to the implemented
  //
  __STATIC_INLINE u32 NVIC_GetPriority(u32 IRQn)
  {
    return(((u32)NVIC->IP[((u32)IRQn)] >> (8 - __NVIC_PRIO_BITS)));
  }

  //-------------------------------------------------------------------------------------------
  //                           NVIC Interrupt Definition table
  //-------------------------------------------------------------------------------------------
  extern const u08 ubInterruptConfigs[100];

#endif

