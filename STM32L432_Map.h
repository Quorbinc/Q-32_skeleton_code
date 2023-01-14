//=============================================================================================
//                                         QUORB INC.
//                                STM32L432 PROCESSOR DEFINES
//
//  (C) 2021 QUORB INC.
//  (C) 2021 STMicroelectronics.
//=============================================================================================

//--- If not previously defined then define MAP Header
#ifndef STM32L432MAP_H
  #define STM32L432MAP_H

  //-------------------------------------------------------------------------------------------
  //      System Core Address Block Definitions
  //-------------------------------------------------------------------------------------------
  #define ITM_BASE            (0xE0000000UL)                    //--- ITM Base Address
  #define DWT_BASE            (0xE0001000UL)                    //--- DWT Base Address
  #define SCB_BASE            (0xE000ED00UL)                    //--- System Control Block Base Address
  #define CoreDebug_BASE      (0xE000EDF0UL)                    //--- Core Debug Base Address

  #define SCS_BASE            (0xE000E000UL)                    //--- System Control Space Base Address
//  #define SYSTICK_BASE        *(vu32*)(0xE000E010UL)            //--- SysTick Base Address
  #define NVIC_BASE           (0xE000E100UL)                    //--- NVIC Base Address
  #define SCS_ACTLR           *(vu32*)(SCS_BASE + 0x0008U)      //--- Aux Control

//  #if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)
//    #define MPU_BASE          (SCS_BASE +  0x0D90UL)            //--- Memory Protection Unit
//    #define MPU               ((MPU_Type *) MPU_BASE)           //--- Memory Protection Unit
//  #endif

  #define TPI_BASE          (0xE0040000UL)                //--- TPI Base Address
  #define FPU_BASE          (SCS_BASE +  0x0F30UL)        //--- Floating Point Unit
  #define FPU               ((FPU_Type *) FPU_BASE)       //--- Floating Point Unit
  #define FPU_FPCCR         *(vu32*)(FPU_BASE + 0x0004U)  //--- FPU Control
  #define FPU_FPCAR         *(vu32*)(FPU_BASE + 0x0008U)  //--- FPU Contex
  #define FPU_FPDSCR        *(vu32*)(FPU_BASE + 0x000CU)  //--- FPU Status Control

  //-------------------------------------------------------------------------------------------
  //      System Control Block Registers
  //-------------------------------------------------------------------------------------------
  #define SCB_CPUID         *(vu32*)(SCB_BASE + 0x0000U)  //--- CPUID Base
  #define SCB_ICSR          *(vu32*)(SCB_BASE + 0x0004U)  //--- Interrupt Control State
  #define SCB_VTOR          *(vu32*)(SCB_BASE + 0x0008U)  //--- Vector Table Offset
  #define SCB_AIRCR         *(vu32*)(SCB_BASE + 0x000CU)  //--- Application Interrupt Reset
  #define SCB_SCR           *(vu32*)(SCB_BASE + 0x0010U)  //--- System Control Register
  #define SCB_CCR           *(vu32*)(SCB_BASE + 0x0014U)  //--- Configuration Control Register
  #define SCB_SHPR1         *(vu32*)(SCB_BASE + 0x0018U)  //--- System Handler Priority (4,5,6)
  #define SCB_SHPR2         *(vu32*)(SCB_BASE + 0x001CU)  //--- System Handler Priority (11)
  #define SCB_SHPR3         *(vu32*)(SCB_BASE + 0x0020U)  //--- System Handler Priority (14,15)
  #define SCB_SHCSR         *(vu32*)(SCB_BASE + 0x0024U)  //--- System Handler Control
  #define SCB_CFSR          *(vu32*)(SCB_BASE + 0x0028U)  //--- Configurable Fault Status
  #define SCB_MMSR          *(vu32*)(SCB_BASE + 0x0028U)  //--- HardFault Status
  #define SCB_BFSR          *(vu32*)(SCB_BASE + 0x0029U)  //--- BusFault Address
  #define SCB_UFSR          *(vu32*)(SCB_BASE + 0x002AU)  //--- Debug Fault
  #define SCB_HFSR          *(vu32*)(SCB_BASE + 0x002CU)  //--- Auxiliary Fault Status
  #define SCB_MMAR          *(vu32*)(SCB_BASE + 0x0034U)  //--- MemManage Fault Address
  #define SCB_BFAR          *(vu32*)(SCB_BASE + 0x0038U)  //--- MemManage Fault Address
  #define SCB_AFAR          *(vu32*)(SCB_BASE + 0x003CU)  //--- MemManage Fault Address
  #define SCB_CPACR         *(vu32*)(SCB_BASE + 0x0088U)  //--- Coprocessor Access Control

  //-------------------------------------------------------------------------------------------
  //      NVIC Register Definitions
  //-------------------------------------------------------------------------------------------

  typedef struct
  {
    vu32 ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
          u32 RESERVED0[24U];
    vu32 ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
          u32 RSERVED1[24U];
    vu32 ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
          u32 RESERVED2[24U];
    vu32 ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
          u32 RESERVED3[24U];
    vu32 IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
          u32 RESERVED4[56U];
    vu08 IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
          u32 RESERVED5[644U];
    vu32  STIR;                  /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
  } NVIC_Type;


  #define NVIC                  ((NVIC_Type*) NVIC_BASE)        //--- NVIC configuration struct
  #define NVIC_STIR             (NVIC_BASE + 0x0E00U)

  #define NVIC_ISER             (NVIC_BASE + 0x0000U)
  #define NVIC_ISER0            *(vu32*)(NVIC_BASE + 0x0000U)   //--- NVIC Set Enable (000-031)
  #define NVIC_ISER1            *(vu32*)(NVIC_BASE + 0x0004U)   //--- NVIC Set Enable (032-063)
  #define NVIC_ISER2            *(vu32*)(NVIC_BASE + 0x0008U)   //--- NVIC Set Enable (064-095)
  #define NVIC_ISER3            *(vu32*)(NVIC_BASE + 0x000CU)   //--- NVIC Set Enable (096-127)
  #define NVIC_ISER4            *(vu32*)(NVIC_BASE + 0x0010U)   //--- NVIC Set Enable (128-159)
  #define NVIC_ISER5            *(vu32*)(NVIC_BASE + 0x0014U)   //--- NVIC Set Enable (160-191)
  #define NVIC_ISER6            *(vu32*)(NVIC_BASE + 0x0018U)   //--- NVIC Set Enable (192-223)
  #define NVIC_ISER7            *(vu32*)(NVIC_BASE + 0x001CU)   //--- NVIC Set Enable (224-255)

  #define NVIC_ICER             (NVIC_BASE + 0x0080U)
  #define NVIC_ICER0            *(vu32*)(NVIC_BASE + 0x0080U)   //--- NVIC Clr Enable (000-031)
  #define NVIC_ICER1            *(vu32*)(NVIC_BASE + 0x0084U)   //--- NVIC Clr Enable (032-063)
  #define NVIC_ICER2            *(vu32*)(NVIC_BASE + 0x0088U)   //--- NVIC Clr Enable (064-095)
  #define NVIC_ICER3            *(vu32*)(NVIC_BASE + 0x008CU)   //--- NVIC Clr Enable (096-127)
  #define NVIC_ICER4            *(vu32*)(NVIC_BASE + 0x0090U)   //--- NVIC Clr Enable (128-159)
  #define NVIC_ICER5            *(vu32*)(NVIC_BASE + 0x0094U)   //--- NVIC Clr Enable (160-191)
  #define NVIC_ICER6            *(vu32*)(NVIC_BASE + 0x0098U)   //--- NVIC Clr Enable (192-223)
  #define NVIC_ICER7            *(vu32*)(NVIC_BASE + 0x009CU)   //--- NVIC Clr Enable (224-255)

  #define NVIC_ISPR             (NVIC_BASE + 0x0100U)
  #define NVIC_ISPR0            *(vu32*)(NVIC_BASE + 0x0100U)   //--- NVIC Set Pending (000-031)
  #define NVIC_ISPR1            *(vu32*)(NVIC_BASE + 0x0104U)   //--- NVIC Set Pending (032-063)
  #define NVIC_ISPR2            *(vu32*)(NVIC_BASE + 0x0108U)   //--- NVIC Set Pending (064-095)
  #define NVIC_ISPR3            *(vu32*)(NVIC_BASE + 0x010CU)   //--- NVIC Set Pending (096-127)
  #define NVIC_ISPR4            *(vu32*)(NVIC_BASE + 0x0110U)   //--- NVIC Set Pending (128-159)
  #define NVIC_ISPR5            *(vu32*)(NVIC_BASE + 0x0114U)   //--- NVIC Set Pending (160-191)
  #define NVIC_ISPR6            *(vu32*)(NVIC_BASE + 0x0118U)   //--- NVIC Set Pending (192-223)
  #define NVIC_ISPR7            *(vu32*)(NVIC_BASE + 0x011CU)   //--- NVIC Set Pending (224-255)

  #define NVIC_ICPR             (NVIC_BASE + 0x0080U)   //--- NVIC Clr Pending (000-031)
  #define NVIC_ICPR0            *(vu32*)(NVIC_BASE + 0x0180U)   //--- NVIC Clr Pending (000-031)
  #define NVIC_ICPR1            *(vu32*)(NVIC_BASE + 0x0184U)   //--- NVIC Clr Pending (032-063)
  #define NVIC_ICPR2            *(vu32*)(NVIC_BASE + 0x0188U)   //--- NVIC Clr Pending (064-095)
  #define NVIC_ICPR3            *(vu32*)(NVIC_BASE + 0x018CU)   //--- NVIC Clr Pending (096-127)
  #define NVIC_ICPR4            *(vu32*)(NVIC_BASE + 0x0190U)   //--- NVIC Clr Pending (128-159)
  #define NVIC_ICPR5            *(vu32*)(NVIC_BASE + 0x0194U)   //--- NVIC Clr Pending (160-191)
  #define NVIC_ICPR6            *(vu32*)(NVIC_BASE + 0x0198U)   //--- NVIC Clr Pending (192-223)
  #define NVIC_ICPR7            *(vu32*)(NVIC_BASE + 0x019CU)   //--- NVIC Clr Pending (224-255)

  #define NVIC_IABR0            *(vu32*)(NVIC_BASE + 0x0200U)   //--- NVIC Act | Pend (000-031)
  #define NVIC_IABR1            *(vu32*)(NVIC_BASE + 0x0204U)   //--- NVIC Act | Pend (032-063)
  #define NVIC_IABR2            *(vu32*)(NVIC_BASE + 0x0208U)   //--- NVIC Act | Pend (064-095)
  #define NVIC_IABR3            *(vu32*)(NVIC_BASE + 0x020CU)   //--- NVIC Act | Pend (096-127)
  #define NVIC_IABR4            *(vu32*)(NVIC_BASE + 0x0210U)   //--- NVIC Act | Pend (128-159)
  #define NVIC_IABR5            *(vu32*)(NVIC_BASE + 0x0214U)   //--- NVIC Act | Pend (160-191)
  #define NVIC_IABR6            *(vu32*)(NVIC_BASE + 0x0218U)   //--- NVIC Act | Pend (192-223)
  #define NVIC_IABR7            *(vu32*)(NVIC_BASE + 0x021CU)   //--- NVIC Act | Pend (224-255)

  //--- NVIC Priority Registers 32 Bit Spacing
  #define NVIC_IPRI_BASE        *(vu08*)(NVIC_BASE + 0x00000300)
  #define NVIC_IPRI             *(vu32*)(NVIC_BASE + 0x00000300)

  #define NVIC_PR00_03          *(vu32*)(NVIC_IPRI + 0x0000U)
  #define NVIC_PR04_07          *(vu32*)(NVIC_IPRI + 0x0004U)
  #define NVIC_PR08_11          *(vu32*)(NVIC_IPRI + 0x0008U)
  #define NVIC_PR12_15          *(vu32*)(NVIC_IPRI + 0x000CU)
  #define NVIC_PR16_19          *(vu32*)(NVIC_IPRI + 0x0010U)
  #define NVIC_PR20_23          *(vu32*)(NVIC_IPRI + 0x0014U)
  #define NVIC_PR24_27          *(vu32*)(NVIC_IPRI + 0x0018U)
  #define NVIC_PR28_31          *(vu32*)(NVIC_IPRI + 0x001CU)
  #define NVIC_PR32_35          *(vu32*)(NVIC_IPRI + 0x0020U)
  #define NVIC_PR36_39          *(vu32*)(NVIC_IPRI + 0x0024U)

  #define NVIC_PR40_43          *(vu32*)(NVIC_IPRI + 0x0028U)
  #define NVIC_PR44_47          *(vu32*)(NVIC_IPRI + 0x002CU)
  #define NVIC_PR48_51          *(vu32*)(NVIC_IPRI + 0x0030U)
  #define NVIC_PR52_55          *(vu32*)(NVIC_IPRI + 0x0034U)
  #define NVIC_PR56_59          *(vu32*)(NVIC_IPRI + 0x0038U)
  #define NVIC_PR60_63          *(vu32*)(NVIC_IPRI + 0x003CU)
  #define NVIC_PR64_67          *(vu32*)(NVIC_IPRI + 0x0040U)
  #define NVIC_PR68_71          *(vu32*)(NVIC_IPRI + 0x0044U)
  #define NVIC_PR72_75          *(vu32*)(NVIC_IPRI + 0x0048U)
  #define NVIC_PR76_79          *(vu32*)(NVIC_IPRI + 0x004CU)

  #define NVIC_PR80_83          *(vu32*)(NVIC_IPRI + 0x0050U)
  #define NVIC_PR84_87          *(vu32*)(NVIC_IPRI + 0x0054U)
  #define NVIC_PR88_91          *(vu32*)(NVIC_IPRI + 0x0058U)
  #define NVIC_PR92_95          *(vu32*)(NVIC_IPRI + 0x005CU)
  #define NVIC_PR96_99          *(vu32*)(NVIC_IPRI + 0x0060U)

  //--- NVIC Priority Registers Byte Spacing
  #define NVIC_IPRI_BYTES       *(vu08*)(NVIC_BASE + 0x00000300)

  #define NVIC_IPR00            *(vu08*)(NVIC_IPRI_BYTES + 0x0000U)
  #define NVIC_IPR01            *(vu08*)(NVIC_IPRI_BYTES + 0x0001U)
  #define NVIC_IPR02            *(vu08*)(NVIC_IPRI_BYTES + 0x0002U)
  #define NVIC_IPR03            *(vu08*)(NVIC_IPRI_BYTES + 0x0003U)
  #define NVIC_IPR04            *(vu08*)(NVIC_IPRI_BYTES + 0x0004U)
  #define NVIC_IPR05            *(vu08*)(NVIC_IPRI_BYTES + 0x0005U)
  #define NVIC_IPR06            *(vu08*)(NVIC_IPRI_BYTES + 0x0006U)
  #define NVIC_IPR07            *(vu08*)(NVIC_IPRI_BYTES + 0x0007U)
  #define NVIC_IPR08            *(vu08*)(NVIC_IPRI_BYTES + 0x0008U)
  #define NVIC_IPR09            *(vu08*)(NVIC_IPRI_BYTES + 0x0009U)

  #define NVIC_IPR10            *(vu08*)(NVIC_IPRI_BYTES + 0x000AU)
  #define NVIC_IPR11            *(vu08*)(NVIC_IPRI_BYTES + 0x000BU)
  #define NVIC_IPR12            *(vu08*)(NVIC_IPRI_BYTES + 0x000CU)
  #define NVIC_IPR13            *(vu08*)(NVIC_IPRI_BYTES + 0x000DU)
  #define NVIC_IPR14            *(vu08*)(NVIC_IPRI_BYTES + 0x000EU)
  #define NVIC_IPR15            *(vu08*)(NVIC_IPRI_BYTES + 0x000FU)
  #define NVIC_IPR16            *(vu08*)(NVIC_IPRI_BYTES + 0x0010U)
  #define NVIC_IPR17            *(vu08*)(NVIC_IPRI_BYTES + 0x0011U)
  #define NVIC_IPR18            *(vu08*)(NVIC_IPRI_BYTES + 0x0012U)
  #define NVIC_IPR19            *(vu08*)(NVIC_IPRI_BYTES + 0x0013U)

  #define NVIC_IPR20            *(vu08*)(NVIC_IPRI_BYTES + 0x0014U)
  #define NVIC_IPR21            *(vu08*)(NVIC_IPRI_BYTES + 0x0015U)
  #define NVIC_IPR22            *(vu08*)(NVIC_IPRI_BYTES + 0x0016U)
  #define NVIC_IPR23            *(vu08*)(NVIC_IPRI_BYTES + 0x0017U)
  #define NVIC_IPR24            *(vu08*)(NVIC_IPRI_BYTES + 0x0018U)
  #define NVIC_IPR25            *(vu08*)(NVIC_IPRI_BYTES + 0x0019U)
  #define NVIC_IPR26            *(vu08*)(NVIC_IPRI_BYTES + 0x001AU)
  #define NVIC_IPR27            *(vu08*)(NVIC_IPRI_BYTES + 0x001BU)
  #define NVIC_IPR28            *(vu08*)(NVIC_IPRI_BYTES + 0x001CU)
  #define NVIC_IPR29            *(vu08*)(NVIC_IPRI_BYTES + 0x001DU)

  #define NVIC_IPR30            *(vu08*)(NVIC_IPRI_BYTES + 0x001EU)
  #define NVIC_IPR31            *(vu08*)(NVIC_IPRI_BYTES + 0x001FU)
  #define NVIC_IPR32            *(vu08*)(NVIC_IPRI_BYTES + 0x0020U)
  #define NVIC_IPR33            *(vu08*)(NVIC_IPRI_BYTES + 0x0021U)
  #define NVIC_IPR34            *(vu08*)(NVIC_IPRI_BYTES + 0x0022U)
  #define NVIC_IPR35            *(vu08*)(NVIC_IPRI_BYTES + 0x0023U)
  #define NVIC_IPR36            *(vu08*)(NVIC_IPRI_BYTES + 0x0024U)
  #define NVIC_IPR37            *(vu08*)(NVIC_IPRI_BYTES + 0x0025U)
  #define NVIC_IPR38            *(vu08*)(NVIC_IPRI_BYTES + 0x0026U)
  #define NVIC_IPR39            *(vu08*)(NVIC_IPRI_BYTES + 0x0027U)

  #define NVIC_IPR40            *(vu08*)(NVIC_IPRI_BYTES + 0x0028U)
  #define NVIC_IPR41            *(vu08*)(NVIC_IPRI_BYTES + 0x0029U)
  #define NVIC_IPR42            *(vu08*)(NVIC_IPRI_BYTES + 0x002AU)
  #define NVIC_IPR43            *(vu08*)(NVIC_IPRI_BYTES + 0x002BU)
  #define NVIC_IPR44            *(vu08*)(NVIC_IPRI_BYTES + 0x002CU)
  #define NVIC_IPR45            *(vu08*)(NVIC_IPRI_BYTES + 0x002DU)
  #define NVIC_IPR46            *(vu08*)(NVIC_IPRI_BYTES + 0x002EU)
  #define NVIC_IPR47            *(vu08*)(NVIC_IPRI_BYTES + 0x002FU)
  #define NVIC_IPR48            *(vu08*)(NVIC_IPRI_BYTES + 0x0030U)
  #define NVIC_IPR49            *(vu08*)(NVIC_IPRI_BYTES + 0x0031U)

  #define NVIC_IPR50            *(vu08*)(NVIC_IPRI_BYTES + 0x0032U)
  #define NVIC_IPR51            *(vu08*)(NVIC_IPRI_BYTES + 0x0033U)
  #define NVIC_IPR52            *(vu08*)(NVIC_IPRI_BYTES + 0x0034U)
  #define NVIC_IPR53            *(vu08*)(NVIC_IPRI_BYTES + 0x0035U)
  #define NVIC_IPR54            *(vu08*)(NVIC_IPRI_BYTES + 0x0036U)
  #define NVIC_IPR55            *(vu08*)(NVIC_IPRI_BYTES + 0x0037U)
  #define NVIC_IPR56            *(vu08*)(NVIC_IPRI_BYTES + 0x0038U)
  #define NVIC_IPR57            *(vu08*)(NVIC_IPRI_BYTES + 0x0039U)
  #define NVIC_IPR58            *(vu08*)(NVIC_IPRI_BYTES + 0x003AU)
  #define NVIC_IPR59            *(vu08*)(NVIC_IPRI_BYTES + 0x003BU)

  #define NVIC_IPR60            *(vu08*)(NVIC_IPRI_BYTES + 0x003CU)
  #define NVIC_IPR61            *(vu08*)(NVIC_IPRI_BYTES + 0x003DU)
  #define NVIC_IPR62            *(vu08*)(NVIC_IPRI_BYTES + 0x003EU)
  #define NVIC_IPR63            *(vu08*)(NVIC_IPRI_BYTES + 0x003FU)
  #define NVIC_IPR64            *(vu08*)(NVIC_IPRI_BYTES + 0x0040U)
  #define NVIC_IPR65            *(vu08*)(NVIC_IPRI_BYTES + 0x0041U)
  #define NVIC_IPR66            *(vu08*)(NVIC_IPRI_BYTES + 0x0042U)
  #define NVIC_IPR67            *(vu08*)(NVIC_IPRI_BYTES + 0x0043U)
  #define NVIC_IPR68            *(vu08*)(NVIC_IPRI_BYTES + 0x0044U)
  #define NVIC_IPR69            *(vu08*)(NVIC_IPRI_BYTES + 0x0045U)

  #define NVIC_IPR70            *(vu08*)(NVIC_IPRI_BYTES + 0x0046U)
  #define NVIC_IPR71            *(vu08*)(NVIC_IPRI_BYTES + 0x0047U)
  #define NVIC_IPR72            *(vu08*)(NVIC_IPRI_BYTES + 0x0048U)
  #define NVIC_IPR73            *(vu08*)(NVIC_IPRI_BYTES + 0x0049U)
  #define NVIC_IPR74            *(vu08*)(NVIC_IPRI_BYTES + 0x004AU)
  #define NVIC_IPR75            *(vu08*)(NVIC_IPRI_BYTES + 0x004BU)
  #define NVIC_IPR76            *(vu08*)(NVIC_IPRI_BYTES + 0x004CU)
  #define NVIC_IPR77            *(vu08*)(NVIC_IPRI_BYTES + 0x004DU)
  #define NVIC_IPR78            *(vu08*)(NVIC_IPRI_BYTES + 0x004EU)
  #define NVIC_IPR79            *(vu08*)(NVIC_IPRI_BYTES + 0x004FU)

  #define NVIC_IPR80            *(vu08*)(NVIC_IPRI_BYTES + 0x0050U)
  #define NVIC_IPR81            *(vu08*)(NVIC_IPRI_BYTES + 0x0051U)
  #define NVIC_IPR82            *(vu08*)(NVIC_IPRI_BYTES + 0x0052U)
  #define NVIC_IPR83            *(vu08*)(NVIC_IPRI_BYTES + 0x0053U)
  #define NVIC_IPR84            *(vu08*)(NVIC_IPRI_BYTES + 0x0054U)
  #define NVIC_IPR85            *(vu08*)(NVIC_IPRI_BYTES + 0x0055U)
  #define NVIC_IPR86            *(vu08*)(NVIC_IPRI_BYTES + 0x0056U)
  #define NVIC_IPR87            *(vu08*)(NVIC_IPRI_BYTES + 0x0057U)
  #define NVIC_IPR88            *(vu08*)(NVIC_IPRI_BYTES + 0x0058U)
  #define NVIC_IPR89            *(vu08*)(NVIC_IPRI_BYTES + 0x0059U)

  #define NVIC_IPR90            *(vu08*)(NVIC_IPRI_BYTES + 0x005AU)
  #define NVIC_IPR91            *(vu08*)(NVIC_IPRI_BYTES + 0x005BU)
  #define NVIC_IPR92            *(vu08*)(NVIC_IPRI_BYTES + 0x005CU)
  #define NVIC_IPR93            *(vu08*)(NVIC_IPRI_BYTES + 0x005DU)
  #define NVIC_IPR94            *(vu08*)(NVIC_IPRI_BYTES + 0x005EU)
  #define NVIC_IPR95            *(vu08*)(NVIC_IPRI_BYTES + 0x005FU)
  #define NVIC_IPR96            *(vu08*)(NVIC_IPRI_BYTES + 0x0060U)
  #define NVIC_IPR97            *(vu08*)(NVIC_IPRI_BYTES + 0x0061U)
  #define NVIC_IPR98            *(vu08*)(NVIC_IPRI_BYTES + 0x0062U)
  #define NVIC_IPR99            *(vu08*)(NVIC_IPRI_BYTES + 0x0063U)

  //-------------------------------------------------------------------------------------------
  //  Peripherial Base Address Definitions
  //-------------------------------------------------------------------------------------------
  #define FLASH_BASE            (0x08000000UL) //--- FLASH(up to 256 KB) base address
  #define SRAM1_BASE            (0x20000000UL) //--- SRAM1(up to 48 KB) base address
  #define SRAM2_BASE            (0x10000000UL) //--- SRAM2(16 KB) base address
  #define PERIPH_BASE           (0x40000000UL) //--- Peripheral base address
  #define QSPI_BASE             (0x90000000UL) //--- QUADSPI memories accessible over AHB base address

  #define QSPI_R_BASE           (0xA0001000UL) //--- QUADSPI control registers base address
  #define SRAM1_BB_BASE         (0x22000000UL) //--- SRAM1(96 KB) base address in the bit-band region
  #define PERIPH_BB_BASE        (0x42000000UL) //--- Peripheral base address in the bit-band region

  //--- Legacy defines
  #define SRAM_BASE             SRAM1_BASE
  #define SRAM_BB_BASE          SRAM1_BB_BASE

  #define SRAM1_SIZE_MAX        (0x0000C000UL) //--- maximum SRAM1 size (up to 48 KBytes)
  #define SRAM2_SIZE            (0x00004000UL) //--- SRAM2 size (16 KBytes)

  //--- Peripheral memory map
  #define APB1PERIPH_BASE       (PERIPH_BASE + 0x00000000UL)
  #define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
  #define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)
  #define AHB2PERIPH_BASE       (PERIPH_BASE + 0x08000000UL)

  //--- APB1 peripherals
  #define TIM2_BASE             (APB1PERIPH_BASE + 0x0000UL)
  #define TIM6_BASE             (APB1PERIPH_BASE + 0x1000UL)
  #define TIM7_BASE             (APB1PERIPH_BASE + 0x1400UL)
  #define RTC_BASE              (APB1PERIPH_BASE + 0x2800UL)
  #define WWDG_BASE             (APB1PERIPH_BASE + 0x2C00UL)
  #define IWDG_BASE             (APB1PERIPH_BASE + 0x3000UL)
  #define SPI2_BASE             (APB1PERIPH_BASE + 0x3800UL)
  #define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00UL)
  #define USART2_BASE           (APB1PERIPH_BASE + 0x4400UL)
  #define USART3_BASE           (APB1PERIPH_BASE + 0x4800UL)
  #define I2C1_BASE             (APB1PERIPH_BASE + 0x5400UL)
  #define I2C2_BASE             (APB1PERIPH_BASE + 0x5800UL)
  #define I2C3_BASE             (APB1PERIPH_BASE + 0x5C00UL)
  #define CRS_BASE              (APB1PERIPH_BASE + 0x6000UL)
  #define CAN1_BASE             (APB1PERIPH_BASE + 0x6400UL)
  #define USB_BASE              (APB1PERIPH_BASE + 0x6800UL)  //--- USB_IP Peripheral Registers base address
  #define USB_PMAADDR           (APB1PERIPH_BASE + 0x6C00UL)  //--- USB_IP Packet Memory Area base address
  #define PWR_R_BASE            (APB1PERIPH_BASE + 0x7000UL)
  #define DAC1_BASE             (APB1PERIPH_BASE + 0x7400UL)
  #define OPAMP_BASE            (APB1PERIPH_BASE + 0x7800UL)
  #define OPAMP1_BASE           (APB1PERIPH_BASE + 0x7800UL)
  #define LPTIM1_BASE           (APB1PERIPH_BASE + 0x7C00UL)
  #define LPUART1_BASE          (APB1PERIPH_BASE + 0x8000UL)
  #define SWPMI1_BASE           (APB1PERIPH_BASE + 0x8800UL)
  #define LPTIM2_BASE           (APB1PERIPH_BASE + 0x9400UL)

  //--- APB2 peripherals
  #define SYSCFG_BASE           (APB2PERIPH_BASE + 0x0000UL)
  #define VREFBUF_BASE          (APB2PERIPH_BASE + 0x0030UL)
  #define COMP1_BASE            (APB2PERIPH_BASE + 0x0200UL)
  #define COMP2_BASE            (APB2PERIPH_BASE + 0x0204UL)
  #define EXTI_BASE             (APB2PERIPH_BASE + 0x0400UL)
  #define FIREWALL_BASE         (APB2PERIPH_BASE + 0x1C00UL)
  #define SDMMC1_BASE           (APB2PERIPH_BASE + 0x2800UL)
  #define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00UL)
  #define SPI1_BASE             (APB2PERIPH_BASE + 0x3000UL)
  #define USART1_BASE           (APB2PERIPH_BASE + 0x3800UL)
  #define TIM15_BASE            (APB2PERIPH_BASE + 0x4000UL)
  #define TIM16_BASE            (APB2PERIPH_BASE + 0x4400UL)
  #define SAI1_BASE             (APB2PERIPH_BASE + 0x5400UL)
  #define SAI1_Block_A_BASE     (SAI1_BASE + 0x0004UL)
  #define SAI1_Block_B_BASE     (SAI1_BASE + 0x0024UL)

  //--- AHB1 peripherals
  #define DMA1_BASE             (AHB1PERIPH_BASE)
  #define DMA2_BASE             (AHB1PERIPH_BASE + 0x0400UL)
  #define RCC_BASE              (AHB1PERIPH_BASE + 0x1000UL)
  #define FLASH_R_BASE          (AHB1PERIPH_BASE + 0x2000UL)
  #define CRC_BASE              (AHB1PERIPH_BASE + 0x3000UL)
  #define TSC_BASE              (AHB1PERIPH_BASE + 0x4000UL)

  //--- DMA Definitions
  #define DMA1_Channel1_BASE    (DMA1_BASE + 0x0008UL)
  #define DMA1_Channel2_BASE    (DMA1_BASE + 0x001CUL)
  #define DMA1_Channel3_BASE    (DMA1_BASE + 0x0030UL)
  #define DMA1_Channel4_BASE    (DMA1_BASE + 0x0044UL)
  #define DMA1_Channel5_BASE    (DMA1_BASE + 0x0058UL)
  #define DMA1_Channel6_BASE    (DMA1_BASE + 0x006CUL)
  #define DMA1_Channel7_BASE    (DMA1_BASE + 0x0080UL)
  #define DMA1_CSELR_BASE       (DMA1_BASE + 0x00A8UL)

  #define DMA2_Channel1_BASE    (DMA2_BASE + 0x0008UL)
  #define DMA2_Channel2_BASE    (DMA2_BASE + 0x001CUL)
  #define DMA2_Channel3_BASE    (DMA2_BASE + 0x0030UL)
  #define DMA2_Channel4_BASE    (DMA2_BASE + 0x0044UL)
  #define DMA2_Channel5_BASE    (DMA2_BASE + 0x0058UL)
  #define DMA2_Channel6_BASE    (DMA2_BASE + 0x006CUL)
  #define DMA2_Channel7_BASE    (DMA2_BASE + 0x0080UL)
  #define DMA2_CSELR_BASE       (DMA2_BASE + 0x00A8UL)

  //--- AHB2 peripherals
  #define GPIOA_BASE            (AHB2PERIPH_BASE + 0x0000UL)
  #define GPIOB_BASE            (AHB2PERIPH_BASE + 0x0400UL)
  #define GPIOC_BASE            (AHB2PERIPH_BASE + 0x0800UL)
  #define GPIOD_BASE            (AHB2PERIPH_BASE + 0x0C00UL)
  #define GPIOE_BASE            (AHB2PERIPH_BASE + 0x1000UL)
  #define GPIOF_BASE            (AHB2PERIPH_BASE + 0x1400UL)
  #define GPIOG_BASE            (AHB2PERIPH_BASE + 0x1800UL)
  #define GPIOH_BASE            (AHB2PERIPH_BASE + 0x1C00UL)
  #define GPIOI_BASE            (AHB2PERIPH_BASE + 0x2000UL)
  #define GPIOJ_BASE            (AHB2PERIPH_BASE + 0x2400UL)
  #define GPIOK_BASE            (AHB2PERIPH_BASE + 0x2C00UL)

  #define ADC1_BASE             (AHB2PERIPH_BASE + 0x08040000UL)
  #define ADC1_COMMON_BASE      (AHB2PERIPH_BASE + 0x08040300UL)

  #define RNG_BASE              (AHB2PERIPH_BASE + 0x08060800UL)

  //--- Debug MCU registers base address
  #define DBGMCU_BASE           (0xE0042000UL)
  #define PACKAGE_BASE          (0x1FFF7500UL)    //--- Package data register base address
  #define UID_BASE              (0x1FFF7590UL)    //--- Unique device ID register base address
  #define FLASHSIZE_BASE        (0x1FFF75E0UL)    //--- Flash size data register base address

  //-------------------------------------------------------------------------------------------
  //      SysTick Configuration Registers  SYSTICK_BASE = 0xE000E010UL
  //-------------------------------------------------------------------------------------------
  #define SYSTICK_BASE          *(vu32*)(0xE000E010UL)            //--- SysTick Base Address
  //  0xE000E010
  #define STK_CTRL              *(vu32 *)(SYSTICK_BASE + 0x00000000)
  #define STK_LOAD              *(vu32 *)(SYSTICK_BASE + 0x00000004)
  #define STK_VAL               *(vu32 *)(SYSTICK_BASE + 0x00000008)
  #define STK_CALIB             *(vu32 *)(SYSTICK_BASE + 0x0000000C)

  //-------------------------------------------------------------------------------------------
  //      Power Configuration Registers
  //-------------------------------------------------------------------------------------------
  #define PWR_CR1               *(vu32 *)(PWR_R_BASE + 0x00000000)
  #define PWR_CR2               *(vu32 *)(PWR_R_BASE + 0x00000004)
  #define PWR_CR3               *(vu32 *)(PWR_R_BASE + 0x00000008)
  #define PWR_CR4               *(vu32 *)(PWR_R_BASE + 0x0000000C)
  #define PWR_SR1               *(vu32 *)(PWR_R_BASE + 0x00000010)
  #define PWR_SR2               *(vu32 *)(PWR_R_BASE + 0x00000014)
  #define PWR_SCR               *(vu32 *)(PWR_R_BASE + 0x00000018)
  #define PWR_PUCRA             *(vu32 *)(PWR_R_BASE + 0x00000020)
  #define PWR_PDCRA             *(vu32 *)(PWR_R_BASE + 0x00000024)
  #define PWR_PUCRB             *(vu32 *)(PWR_R_BASE + 0x00000028)
  #define PWR_PDCRB             *(vu32 *)(PWR_R_BASE + 0x0000002C)
  #define PWR_PUCRC             *(vu32 *)(PWR_R_BASE + 0x00000030)
  #define PWR_PDCRC             *(vu32 *)(PWR_R_BASE + 0x00000034)
  #define PWR_PUCRD             *(vu32 *)(PWR_R_BASE + 0x0000003C)
  #define PWR_PUCRE             *(vu32 *)(PWR_R_BASE + 0x00000040)
  #define PWR_PDCRE             *(vu32 *)(PWR_R_BASE + 0x00000044)

  //-------------------------------------------------------------------------------------------
  //      VREFBUF Voltage Control Registers
  //      VREFBUF_BASE           0x40010030
  //-------------------------------------------------------------------------------------------
  #define VREFBUF_CSR           *(vu32 *)(VREFBUF_BASE + 0x00000000UL)
  #define VREFBUF_CCR           *(vu32 *)(VREFBUF_BASE + 0x00000004UL)

 //-------------------------------------------------------------------------------------------
  //      FLASH Control Registers
  //-------------------------------------------------------------------------------------------
  #define FLASH_ACR             *(vu32 *)(FLASH_R_BASE + 0x00000000)
  #define FLASH_PDKEYR          *(vu32 *)(FLASH_R_BASE + 0x00000004)
  #define FLASH_KEYR            *(vu32 *)(FLASH_R_BASE + 0x00000008)
  #define FLASH_OPTKEYR         *(vu32 *)(FLASH_R_BASE + 0x0000000C)
  #define FLASH_SR              *(vu32 *)(FLASH_R_BASE + 0x00000010)
  #define FLASH_CR              *(vu32 *)(FLASH_R_BASE + 0x00000014)
  #define FLASH_ECCR            *(vu32 *)(FLASH_R_BASE + 0x00000018)
  #define FLASH_OPTR            *(vu32 *)(FLASH_R_BASE + 0x00000020)
  #define FLASH_PCROP1SR        *(vu32 *)(FLASH_R_BASE + 0x00000024)
  #define FLASH_PCROP1ER        *(vu32 *)(FLASH_R_BASE + 0x00000028)
  #define FLASH_WRP1AR          *(vu32 *)(FLASH_R_BASE + 0x0000002C)
  #define FLASH_WRB1PR          *(vu32 *)(FLASH_R_BASE + 0x00000030)

  //-------------------------------------------------------------------------------------------
  //      RCC Control Registers
  //-------------------------------------------------------------------------------------------
  #define RCC_CR                *(vu32 *)(RCC_BASE + 0x00000000)
  #define RCC_ICSCR             *(vu32 *)(RCC_BASE + 0x00000004)
  #define RCC_CFGR              *(vu32 *)(RCC_BASE + 0x00000008)
  #define RCC_PLLCFGR           *(vu32 *)(RCC_BASE + 0x0000000C)
  #define RCC_PLLSAI1CFGR       *(vu32 *)(RCC_BASE + 0x00000010)

  #define RCC_CIER              *(vu32 *)(RCC_BASE + 0x00000018)
  #define RCC_CIFR              *(vu32 *)(RCC_BASE + 0x0000001C)
  #define RCC_CICR              *(vu32 *)(RCC_BASE + 0x00000020)
  #define RCC_AHB1RSTR          *(vu32 *)(RCC_BASE + 0x00000028)
  #define RCC_AHB2RSTR          *(vu32 *)(RCC_BASE + 0x0000002C)
  #define RCC_AHB3RSTR          *(vu32 *)(RCC_BASE + 0x00000030)

  #define RCC_APB1RSTR1         *(vu32 *)(RCC_BASE + 0x00000038)
  #define RCC_APB1RSTR2         *(vu32 *)(RCC_BASE + 0x0000003C)

  #define RCC_APB2RSTR          *(vu32 *)(RCC_BASE + 0x00000040)

  #define RCC_AHB1ENR           *(vu32 *)(RCC_BASE + 0x00000048)
  #define RCC_AHB2ENR           *(vu32 *)(RCC_BASE + 0x0000004C)
  #define RCC_AHB3ENR           *(vu32 *)(RCC_BASE + 0x00000050)

  #define RCC_APB1ENR1          *(vu32 *)(RCC_BASE + 0x00000058)
  #define RCC_APB1ENR2          *(vu32 *)(RCC_BASE + 0x0000005C)

  #define RCC_APB2ENR           *(vu32 *)(RCC_BASE + 0x00000060)

  #define RCC_AHB1SMENR         *(vu32 *)(RCC_BASE + 0x00000068)
  #define RCC_AHB2SMENR         *(vu32 *)(RCC_BASE + 0x0000006C)
  #define RCC_AHB3SMENR         *(vu32 *)(RCC_BASE + 0x00000070)

  #define RCC_APB1SMENR1        *(vu32 *)(RCC_BASE + 0x00000078)
  #define RCC_APB1SMENR2        *(vu32 *)(RCC_BASE + 0x0000007C)

  #define RCC_APB2SMENR         *(vu32 *)(RCC_BASE + 0x00000080)

  #define RCC_CCIPR             *(vu32 *)(RCC_BASE + 0x00000088)
  #define RCC_BDCR              *(vu32 *)(RCC_BASE + 0x00000090)
  #define RCC_CSR               *(vu32 *)(RCC_BASE + 0x00000094)
  #define RCC_CRRCR             *(vu32 *)(RCC_BASE + 0x00000098)
  #define RCC_CCIPR2            *(vu32 *)(RCC_BASE + 0x0000009C)

  //-------------------------------------------------------------------------------------------
  //    GPIO Register Maps
  //-------------------------------------------------------------------------------------------
  //--- GPIO-A
  #define GPIOA_MODER           *(vu32 *)(GPIOA_BASE + 0x00000000)
  #define GPIOA_OTYPER          *(vu32 *)(GPIOA_BASE + 0x00000004)
  #define GPIOA_OSPEEDR         *(vu32 *)(GPIOA_BASE + 0x00000008)
  #define GPIOA_PUPDR           *(vu32 *)(GPIOA_BASE + 0x0000000C)
  #define GPIOA_IDR             *(vu32 *)(GPIOA_BASE + 0x00000010)
  #define GPIOA_ODR             *(vu32 *)(GPIOA_BASE + 0x00000014)
  #define GPIOA_BSRR            *(vu32 *)(GPIOA_BASE + 0x00000018)
  #define GPIOA_LCKR            *(vu32 *)(GPIOA_BASE + 0x0000001C)
  #define GPIOA_AFRL            *(vu32 *)(GPIOA_BASE + 0x00000020)
  #define GPIOA_AFRH            *(vu32 *)(GPIOA_BASE + 0x00000024)

  //--- GPIO-B
  #define GPIOB_MODER           *(vu32 *)(GPIOB_BASE + 0x00000000)
  #define GPIOB_OTYPER          *(vu32 *)(GPIOB_BASE + 0x00000004)
  #define GPIOB_OSPEEDR         *(vu32 *)(GPIOB_BASE + 0x00000008)
  #define GPIOB_PUPDR           *(vu32 *)(GPIOB_BASE + 0x0000000C)
  #define GPIOB_IDR             *(vu32 *)(GPIOB_BASE + 0x00000010)
  #define GPIOB_ODR             *(vu32 *)(GPIOB_BASE + 0x00000014)
  #define GPIOB_BSRR            *(vu32 *)(GPIOB_BASE + 0x00000018)
  #define GPIOB_LCKR            *(vu32 *)(GPIOB_BASE + 0x0000001C)
  #define GPIOB_AFRL            *(vu32 *)(GPIOB_BASE + 0x00000020)
  #define GPIOB_AFRH            *(vu32 *)(GPIOB_BASE + 0x00000024)

  //--- GPIO-C
  #define GPIOC_MODER           *(vu32 *)(GPIOC_BASE + 0x00000000)
  #define GPIOC_OTYPER          *(vu32 *)(GPIOC_BASE + 0x00000004)
  #define GPIOC_OSPEEDR         *(vu32 *)(GPIOC_BASE + 0x00000008)
  #define GPIOC_PUPDR           *(vu32 *)(GPIOC_BASE + 0x0000000C)
  #define GPIOC_IDR             *(vu32 *)(GPIOC_BASE + 0x00000010)
  #define GPIOC_ODR             *(vu32 *)(GPIOC_BASE + 0x00000014)
  #define GPIOC_BSRR            *(vu32 *)(GPIOC_BASE + 0x00000018)
  #define GPIOC_LCKR            *(vu32 *)(GPIOC_BASE + 0x0000001C)
  #define GPIOC_AFRL            *(vu32 *)(GPIOC_BASE + 0x00000020)
  #define GPIOC_AFRH            *(vu32 *)(GPIOC_BASE + 0x00000024)

  //--- GPIO-D
  #define GPIOD_MODER           *(vu32 *)(GPIOD_BASE + 0x00000000)
  #define GPIOD_OTYPER          *(vu32 *)(GPIOD_BASE + 0x00000004)
  #define GPIOD_OSPEEDR         *(vu32 *)(GPIOD_BASE + 0x00000008)
  #define GPIOD_PUPDR           *(vu32 *)(GPIOD_BASE + 0x0000000C)
  #define GPIOD_IDR             *(vu32 *)(GPIOD_BASE + 0x00000010)
  #define GPIOD_ODR             *(vu32 *)(GPIOD_BASE + 0x00000014)
  #define GPIOD_BSRR            *(vu32 *)(GPIOD_BASE + 0x00000018)
  #define GPIOD_LCKR            *(vu32 *)(GPIOD_BASE + 0x0000001C)
  #define GPIOD_AFRL            *(vu32 *)(GPIOD_BASE + 0x00000020)
  #define GPIOD_AFRH            *(vu32 *)(GPIOD_BASE + 0x00000024)

  //--- GPIO-E
  #define GPIOE_MODER           *(vu32 *)(GPIOE_BASE + 0x00000000)
  #define GPIOE_OTYPER          *(vu32 *)(GPIOE_BASE + 0x00000004)
  #define GPIOE_OSPEEDR         *(vu32 *)(GPIOE_BASE + 0x00000008)
  #define GPIOE_PUPDR           *(vu32 *)(GPIOE_BASE + 0x0000000C)
  #define GPIOE_IDR             *(vu32 *)(GPIOE_BASE + 0x00000010)
  #define GPIOE_ODR             *(vu32 *)(GPIOE_BASE + 0x00000014)
  #define GPIOE_BSRR            *(vu32 *)(GPIOE_BASE + 0x00000018)
  #define GPIOE_LCKR            *(vu32 *)(GPIOE_BASE + 0x0000001C)
  #define GPIOE_AFRL            *(vu32 *)(GPIOE_BASE + 0x00000020)
  #define GPIOE_AFRH            *(vu32 *)(GPIOE_BASE + 0x00000024)

  //--- GPIO-F
  #define GPIOF_MODER           *(vu32 *)(GPIOF_BASE + 0x00000000)
  #define GPIOF_OTYPER          *(vu32 *)(GPIOF_BASE + 0x00000004)
  #define GPIOF_OSPEEDR         *(vu32 *)(GPIOF_BASE + 0x00000008)
  #define GPIOF_PUPDR           *(vu32 *)(GPIOF_BASE + 0x0000000C)
  #define GPIOF_IDR             *(vu32 *)(GPIOF_BASE + 0x00000010)
  #define GPIOF_ODR             *(vu32 *)(GPIOF_BASE + 0x00000014)
  #define GPIOF_BSRR            *(vu32 *)(GPIOF_BASE + 0x00000018)
  #define GPIOF_LCKR            *(vu32 *)(GPIOF_BASE + 0x0000001C)
  #define GPIOF_AFRL            *(vu32 *)(GPIOF_BASE + 0x00000020)
  #define GPIOF_AFRH            *(vu32 *)(GPIOF_BASE + 0x00000024)

  //--- GPIO-G
  #define GPIOG_MODER           *(vu32 *)(GPIOG_BASE + 0x00000000)
  #define GPIOG_OTYPER          *(vu32 *)(GPIOG_BASE + 0x00000004)
  #define GPIOG_OSPEEDR         *(vu32 *)(GPIOG_BASE + 0x00000008)
  #define GPIOG_PUPDR           *(vu32 *)(GPIOG_BASE + 0x0000000C)
  #define GPIOG_IDR             *(vu32 *)(GPIOG_BASE + 0x00000010)
  #define GPIOG_ODR             *(vu32 *)(GPIOG_BASE + 0x00000014)
  #define GPIOG_BSRR            *(vu32 *)(GPIOG_BASE + 0x00000018)
  #define GPIOG_LCKR            *(vu32 *)(GPIOG_BASE + 0x0000001C)
  #define GPIOG_AFRL            *(vu32 *)(GPIOG_BASE + 0x00000020)
  #define GPIOG_AFRH            *(vu32 *)(GPIOG_BASE + 0x00000024)

  //--- GPIO-H
  #define GPIOH_MODER           *(vu32 *)(GPIOH_BASE + 0x00000000)
  #define GPIOH_OTYPER          *(vu32 *)(GPIOH_BASE + 0x00000004)
  #define GPIOH_OSPEEDR         *(vu32 *)(GPIOH_BASE + 0x00000008)
  #define GPIOH_PUPDR           *(vu32 *)(GPIOH_BASE + 0x0000000C)
  #define GPIOH_IDR             *(vu32 *)(GPIOH_BASE + 0x00000010)
  #define GPIOH_ODR             *(vu32 *)(GPIOH_BASE + 0x00000014)
  #define GPIOH_BSRR            *(vu32 *)(GPIOH_BASE + 0x00000018)
  #define GPIOH_LCKR            *(vu32 *)(GPIOH_BASE + 0x0000001C)
  #define GPIOH_AFRL            *(vu32 *)(GPIOH_BASE + 0x00000020)
  #define GPIOH_AFRH            *(vu32 *)(GPIOH_BASE + 0x00000024)

  //--- GPIO-I
  #define GPIOI_MODER           *(vu32 *)(GPIOI_BASE + 0x00000000)
  #define GPIOI_OTYPER          *(vu32 *)(GPIOI_BASE + 0x00000004)
  #define GPIOI_OSPEEDR         *(vu32 *)(GPIOI_BASE + 0x00000008)
  #define GPIOI_PUPDR           *(vu32 *)(GPIOI_BASE + 0x0000000C)
  #define GPIOI_IDR             *(vu32 *)(GPIOI_BASE + 0x00000010)
  #define GPIOI_ODR             *(vu32 *)(GPIOI_BASE + 0x00000014)
  #define GPIOI_BSRR            *(vu32 *)(GPIOI_BASE + 0x00000018)
  #define GPIOI_LCKR            *(vu32 *)(GPIOI_BASE + 0x0000001C)
  #define GPIOI_AFRL            *(vu32 *)(GPIOI_BASE + 0x00000020)
  #define GPIOI_AFRH            *(vu32 *)(GPIOI_BASE + 0x00000024)

  //--- GPIO-J
  #define GPIOJ_MODER           *(vu32 *)(GPIOJ_BASE + 0x00000000)
  #define GPIOJ_OTYPER          *(vu32 *)(GPIOJ_BASE + 0x00000004)
  #define GPIOJ_OSPEEDR         *(vu32 *)(GPIOJ_BASE + 0x00000008)
  #define GPIOJ_PUPDR           *(vu32 *)(GPIOJ_BASE + 0x0000000C)
  #define GPIOJ_IDR             *(vu32 *)(GPIOJ_BASE + 0x00000010)
  #define GPIOJ_ODR             *(vu32 *)(GPIOJ_BASE + 0x00000014)
  #define GPIOJ_BSRR            *(vu32 *)(GPIOJ_BASE + 0x00000018)
  #define GPIOJ_LCKR            *(vu32 *)(GPIOJ_BASE + 0x0000001C)
  #define GPIOJ_AFRL            *(vu32 *)(GPIOJ_BASE + 0x00000020)
  #define GPIOJ_AFRH            *(vu32 *)(GPIOJ_BASE + 0x00000024)

  //--- GPIO-K
  #define GPIOK_MODER           *(vu32 *)(GPIOK_BASE + 0x00000000)
  #define GPIOK_OTYPER          *(vu32 *)(GPIOK_BASE + 0x00000004)
  #define GPIOK_OSPEEDR         *(vu32 *)(GPIOK_BASE + 0x00000008)
  #define GPIOK_PUPDR           *(vu32 *)(GPIOK_BASE + 0x0000000C)
  #define GPIOK_IDR             *(vu32 *)(GPIOK_BASE + 0x00000010)
  #define GPIOK_ODR             *(vu32 *)(GPIOK_BASE + 0x00000014)
  #define GPIOK_BSRR            *(vu32 *)(GPIOK_BASE + 0x00000018)
  #define GPIOK_LCKR            *(vu32 *)(GPIOK_BASE + 0x0000001C)
  #define GPIOK_AFRL            *(vu32 *)(GPIOK_BASE + 0x00000020)
  #define GPIOK_AFRH            *(vu32 *)(GPIOK_BASE + 0x00000024)

  //------------------------------------------------------------------------------------------
  //  GPIO Pin Number Defines   - This gives each I/O Pin a Unique Number (00 to FF)
  //  The Hi Nibble = the Port (A - K)  the Lo Nibble = Port Pin Number (0 - 15) = (0 - F)
  //------------------------------------------------------------------------------------------
  #define PA00    0x00
  #define PA01    0x01
  #define PA02    0x02
  #define PA03    0x03
  #define PA04    0x04
  #define PA05    0x05
  #define PA06    0x06
  #define PA07    0x07
  #define PA08    0x08
  #define PA09    0x09
  #define PA10    0x0A
  #define PA11    0x0B
  #define PA12    0x0C
  #define PA13    0x0D
  #define PA14    0x0E
  #define PA15    0x0F

  #define PB00    0x10
  #define PB01    0x11
  #define PB02    0x12
  #define PB03    0x13
  #define PB04    0x14
  #define PB05    0x15
  #define PB06    0x16
  #define PB07    0x17
  #define PB08    0x18
  #define PB09    0x19
  #define PB10    0x1A
  #define PB11    0x1B
  #define PB12    0x1C
  #define PB13    0x1D
  #define PB14    0x1E
  #define PB15    0x1F

  #define PC00    0x20
  #define PC01    0x21
  #define PC02    0x22
  #define PC03    0x23
  #define PC04    0x24
  #define PC05    0x25
  #define PC06    0x26
  #define PC07    0x27
  #define PC08    0x28
  #define PC09    0x29
  #define PC10    0x2A
  #define PC11    0x2B
  #define PC12    0x2C
  #define PC13    0x2D
  #define PC14    0x2E
  #define PC15    0x2F

  #define PD00    0x30
  #define PD01    0x31
  #define PD02    0x32
  #define PD03    0x33
  #define PD04    0x34
  #define PD05    0x35
  #define PD06    0x36
  #define PD07    0x37
  #define PD08    0x38
  #define PD09    0x39
  #define PD10    0x3A
  #define PD11    0x3B
  #define PD12    0x3C
  #define PD13    0x3D
  #define PD14    0x3E
  #define PD15    0x3F

  #define PE00    0x40
  #define PE01    0x41
  #define PE02    0x42
  #define PE03    0x43
  #define PE04    0x44
  #define PE05    0x45
  #define PE06    0x46
  #define PE07    0x47
  #define PE08    0x48
  #define PE09    0x49
  #define PE10    0x4A
  #define PE11    0x4B
  #define PE12    0x4C
  #define PE13    0x4D
  #define PE14    0x4E
  #define PE15    0x4F

  #define PF00    0x50
  #define PF01    0x51
  #define PF02    0x52
  #define PF03    0x53
  #define PF04    0x54
  #define PF05    0x55
  #define PF06    0x56
  #define PF07    0x57
  #define PF08    0x58
  #define PF09    0x59
  #define PF10    0x5A
  #define PF11    0x5B
  #define PF12    0x5C
  #define PF13    0x5D
  #define PF14    0x5E
  #define PF15    0x5F

  #define PG00    0x60
  #define PG01    0x61
  #define PG02    0x62
  #define PG03    0x63
  #define PG04    0x64
  #define PG05    0x65
  #define PG06    0x66
  #define PG07    0x67
  #define PG08    0x68
  #define PG09    0x69
  #define PG10    0x6A
  #define PG11    0x6B
  #define PG12    0x6C
  #define PG13    0x6D
  #define PG14    0x6E
  #define PG15    0x6F

  #define PH00    0x70
  #define PH01    0x71
  #define PH02    0x72
  #define PH03    0x73
  #define PH04    0x74
  #define PH05    0x75
  #define PH06    0x76
  #define PH07    0x77
  #define PH08    0x78
  #define PH09    0x79
  #define PH10    0x7A
  #define PH11    0x7B
  #define PH12    0x7C
  #define PH13    0x7D
  #define PH14    0x7E
  #define PH15    0x7F

  #define PI00    0x80
  #define PI01    0x81
  #define PI02    0x82
  #define PI03    0x83
  #define PI04    0x84
  #define PI05    0x85
  #define PI06    0x86
  #define PI07    0x87
  #define PI08    0x88
  #define PI09    0x89
  #define PI10    0x8A
  #define PI11    0x8B
  #define PI12    0x8C
  #define PI13    0x8D
  #define PI14    0x8E
  #define PI15    0x8F

  #define PJ00    0x90
  #define PJ01    0x91
  #define PJ02    0x92
  #define PJ03    0x93
  #define PJ04    0x94
  #define PJ05    0x95
  #define PJ06    0x96
  #define PJ07    0x97
  #define PJ08    0x98
  #define PJ09    0x99
  #define PJ10    0x9A
  #define PJ11    0x9B
  #define PJ12    0x9C
  #define PJ13    0x9D
  #define PJ14    0x9E
  #define PJ15    0x9F

  #define PK00    0xA0
  #define PK01    0xA1
  #define PK02    0xA2
  #define PK03    0xA3
  #define PK04    0xA4
  #define PK05    0xA5
  #define PK06    0xA6
  #define PK07    0xA7
  #define PK08    0xA8
  #define PK09    0xA9
  #define PK10    0xAA
  #define PK11    0xAB
  #define PK12    0xAC
  #define PK13    0xAD
  #define PK14    0xAE
  #define PK15    0xAF

  //-------------------------------------------------------------------------------------------
  //      ADC REGISTERS
  //-------------------------------------------------------------------------------------------
  //--- ADC1 Registers
  #define ADC1_SR               *(vu32 *)(ADC1_BASE + 0x00000000)
  #define ADC1_CR1              *(vu32 *)(ADC1_BASE + 0x00000004)
  #define ADC1_CR2              *(vu32 *)(ADC1_BASE + 0x00000008)
  #define ADC1_SMPR1            *(vu32 *)(ADC1_BASE + 0x0000000C)
  #define ADC1_SMPR2            *(vu32 *)(ADC1_BASE + 0x00000010)
  #define ADC1_JOFR1            *(vu32 *)(ADC1_BASE + 0x00000014)
  #define ADC1_JOFR2            *(vu32 *)(ADC1_BASE + 0x00000018)
  #define ADC1_JOFR3            *(vu32 *)(ADC1_BASE + 0x0000001C)
  #define ADC1_JOFR4            *(vu32 *)(ADC1_BASE + 0x00000020)
  #define ADC1_HTR              *(vu32 *)(ADC1_BASE + 0x00000024)
  #define ADC1_LTR              *(vu32 *)(ADC1_BASE + 0x00000028)
  #define ADC1_SQR1             *(vu32 *)(ADC1_BASE + 0x0000002C)
  #define ADC1_SQR2             *(vu32 *)(ADC1_BASE + 0x00000030)
  #define ADC1_SQR3             *(vu32 *)(ADC1_BASE + 0x00000034)
  #define ADC1_JSQR             *(vu32 *)(ADC1_BASE + 0x00000038)
  #define ADC1_JDR1             *(vu32 *)(ADC1_BASE + 0x0000003C)
  #define ADC1_JDR2             *(vu32 *)(ADC1_BASE + 0x00000040)
  #define ADC1_JDR3             *(vu32 *)(ADC1_BASE + 0x00000044)
  #define ADC1_JDR4             *(vu32 *)(ADC1_BASE + 0x00000048)
  #define ADC1_DR               *(vu32 *)(ADC1_BASE + 0x0000004C)

  #define ADC_CSR               *(vu32 *)(ADC1_BASE + 0x00000300)
  #define ADC_CCR               *(vu32 *)(ADC1_BASE + 0x00000304)
  #define ADC_CDR               *(vu32 *)(ADC1_BASE + 0x00000304)

  //-------------------------------------------------------------------------------------------
  //      UART Registers
  //-------------------------------------------------------------------------------------------
  //--- UART # 1 Registers
  #define USART1_SR             *(vu32 *)(USART1_BASE + 0x00000000)
  #define USART1_DR             *(vu32 *)(USART1_BASE + 0x00000004)
  #define USART1_BRR            *(vu32 *)(USART1_BASE + 0x00000008)
  #define USART1_CR1            *(vu32 *)(USART1_BASE + 0x0000000C)
  #define USART1_CR2            *(vu32 *)(USART1_BASE + 0x00000010)
  #define USART1_CR3            *(vu32 *)(USART1_BASE + 0x00000014)
  #define USART1_GTPR           *(vu32 *)(USART1_BASE + 0x00000018)

  //--- UART # 2 Registers
  #define USART2_SR             *(vu32 *)(USART2_BASE + 0x00000000)
  #define USART2_DR             *(vu32 *)(USART2_BASE + 0x00000004)
  #define USART2_BRR            *(vu32 *)(USART2_BASE + 0x00000008)
  #define USART2_CR1            *(vu32 *)(USART2_BASE + 0x0000000C)
  #define USART2_CR2            *(vu32 *)(USART2_BASE + 0x00000010)
  #define USART2_CR3            *(vu32 *)(USART2_BASE + 0x00000014)
  #define USART2_GTPR           *(vu32 *)(USART2_BASE + 0x00000018)

  //--- UART # 3 Registers
  #define USART3_SR             *(vu32 *)(USART3_BASE + 0x00000000)
  #define USART3_DR             *(vu32 *)(USART3_BASE + 0x00000004)
  #define USART3_BRR            *(vu32 *)(USART3_BASE + 0x00000008)
  #define USART3_CR1            *(vu32 *)(USART3_BASE + 0x0000000C)
  #define USART3_CR2            *(vu32 *)(USART3_BASE + 0x00000010)
  #define USART3_CR3            *(vu32 *)(USART3_BASE + 0x00000014)
  #define USART3_GTPR           *(vu32 *)(USART3_BASE + 0x00000018)

  //-------------------------------------------------------------------------------------------
  //      I2C Registers
  //-------------------------------------------------------------------------------------------
  //--- I2C Driver #1 Registers
  #define I2C1_CR1              *(vu32 *)(I2C1_BASE + 0x00000000)
  #define I2C1_CR2              *(vu32 *)(I2C1_BASE + 0x00000004)
  #define I2C1_OAR1             *(vu32 *)(I2C1_BASE + 0x00000008)
  #define I2C1_OAR2             *(vu32 *)(I2C1_BASE + 0x0000000C)
  #define I2C1_DR               *(vu32 *)(I2C1_BASE + 0x00000010)
  #define I2C1_SR1              *(vu32 *)(I2C1_BASE + 0x00000014)
  #define I2C1_SR2              *(vu32 *)(I2C1_BASE + 0x00000018)
  #define I2C1_CCR              *(vu32 *)(I2C1_BASE + 0x0000001C)
  #define I2C1_TRISE            *(vu32 *)(I2C1_BASE + 0x00000020)
  #define I2C1_FLTR             *(vu32 *)(I2C1_BASE + 0x00000024)

  //--- I2C Driver #2 Registers
  #define I2C2_CR1              *(vu32 *)(I2C2_BASE + 0x00000000)
  #define I2C2_CR2              *(vu32 *)(I2C2_BASE + 0x00000004)
  #define I2C2_OAR1             *(vu32 *)(I2C2_BASE + 0x00000008)
  #define I2C2_OAR2             *(vu32 *)(I2C2_BASE + 0x0000000C)
  #define I2C2_DR               *(vu32 *)(I2C2_BASE + 0x00000010)
  #define I2C2_SR1              *(vu32 *)(I2C2_BASE + 0x00000014)
  #define I2C2_SR2              *(vu32 *)(I2C2_BASE + 0x00000018)
  #define I2C2_CCR              *(vu32 *)(I2C2_BASE + 0x0000001C)
  #define I2C2_TRISE            *(vu32 *)(I2C2_BASE + 0x00000020)
  #define I2C2_FLTR             *(vu32 *)(I2C2_BASE + 0x00000024)

  //--- I2C Driver #3 Registers
  #define I2C3_CR1              *(vu32 *)(I2C3_BASE + 0x00000000)
  #define I2C3_CR2              *(vu32 *)(I2C3_BASE + 0x00000004)
  #define I2C3_OAR1             *(vu32 *)(I2C3_BASE + 0x00000008)
  #define I2C3_OAR2             *(vu32 *)(I2C3_BASE + 0x0000000C)
  #define I2C3_DR               *(vu32 *)(I2C3_BASE + 0x00000010)
  #define I2C3_SR1              *(vu32 *)(I2C3_BASE + 0x00000014)
  #define I2C3_SR2              *(vu32 *)(I2C3_BASE + 0x00000018)
  #define I2C3_CCR              *(vu32 *)(I2C3_BASE + 0x0000001C)
  #define I2C3_TRISE            *(vu32 *)(I2C3_BASE + 0x00000020)
  #define I2C3_FLTR             *(vu32 *)(I2C3_BASE + 0x00000024)

  //--- I2C Driver #4 Registers
  #define I2C4_CR1              *(vu32 *)(I2C3_BASE + 0x00000000)
  #define I2C4_CR2              *(vu32 *)(I2C3_BASE + 0x00000004)
  #define I2C4_OAR1             *(vu32 *)(I2C3_BASE + 0x00000008)
  #define I2C4_OAR2             *(vu32 *)(I2C3_BASE + 0x0000000C)
  #define I2C4_DR               *(vu32 *)(I2C3_BASE + 0x00000010)
  #define I2C4_SR1              *(vu32 *)(I2C3_BASE + 0x00000014)
  #define I2C4_SR2              *(vu32 *)(I2C3_BASE + 0x00000018)
  #define I2C4_CCR              *(vu32 *)(I2C3_BASE + 0x0000001C)
  #define I2C4_TRISE            *(vu32 *)(I2C3_BASE + 0x00000020)
  #define I2C4_FLTR             *(vu32 *)(I2C3_BASE + 0x00000024)

  //-------------------------------------------------------------------------------------------
  //      SPI Interface Registers
  //-------------------------------------------------------------------------------------------
  //--- SPI Interface 1
  #define SPI1_CR1              *(vu32 *)(SPI1_BASE + 0x00000000)
  #define SPI1_CR2              *(vu32 *)(SPI1_BASE + 0x00000004)
  #define SPI1_SR               *(vu32 *)(SPI1_BASE + 0x00000008)
  #define SPI1_DR               *(vu32 *)(SPI1_BASE + 0x0000000C)
  #define SPI1_CRCPR            *(vu32 *)(SPI1_BASE + 0x00000010)
  #define SPI1_RXCRCR           *(vu32 *)(SPI1_BASE + 0x00000014)
  #define SPI1_TXCRCR           *(vu32 *)(SPI1_BASE + 0x00000018)
  #define SPI1_I2SCFGR          *(vu32 *)(SPI1_BASE + 0x0000001C)
  #define SPI1_SPR              *(vu32 *)(SPI1_BASE + 0x00000020)

  //-------------------------------------------------------------------------------------------
  //      CAN Interface Registers
  //-------------------------------------------------------------------------------------------
  //--- CAN 1 Registers
  #define CAN1_MCR              *(vu32 *)(CAN1_BASE + 0x00000000)
  #define CAN1_MSR              *(vu32 *)(CAN1_BASE + 0x00000004)
  #define CAN1_TSR              *(vu32 *)(CAN1_BASE + 0x00000008)
  #define CAN1_RF0R             *(vu32 *)(CAN1_BASE + 0x0000000C)
  #define CAN1_RF1R             *(vu32 *)(CAN1_BASE + 0x00000010)
  #define CAN1_IER              *(vu32 *)(CAN1_BASE + 0x00000014)
  #define CAN1_ESR              *(vu32 *)(CAN1_BASE + 0x00000018)
  #define CAN1_BTR              *(vu32 *)(CAN1_BASE + 0x0000001C)

  #define CAN1_TIR1             *(vu32 *)(CAN1_BASE + 0x00000180)
  #define CAN1_TDTR1            *(vu32 *)(CAN1_BASE + 0x00000184)
  #define CAN1_TDLR1            *(vu32 *)(CAN1_BASE + 0x00000188)
  #define CAN1_TDHR1            *(vu32 *)(CAN1_BASE + 0x0000018C)
  #define CAN1_TIR2             *(vu32 *)(CAN1_BASE + 0x00000190)
  #define CAN1_TDTR2            *(vu32 *)(CAN1_BASE + 0x00000194)
  #define CAN1_TDLR2            *(vu32 *)(CAN1_BASE + 0x00000198)
  #define CAN1_TDHR2            *(vu32 *)(CAN1_BASE + 0x0000019C)
  #define CAN1_TIR3             *(vu32 *)(CAN1_BASE + 0x000001A0)
  #define CAN1_TDTR3            *(vu32 *)(CAN1_BASE + 0x000001A4)
  #define CAN1_TDLR3            *(vu32 *)(CAN1_BASE + 0x000001A8)
  #define CAN1_TDHR3            *(vu32 *)(CAN1_BASE + 0x000001AC)

  #define CAN1_RIR1             *(vu32 *)(CAN1_BASE + 0x000001B0)
  #define CAN1_RDTR1            *(vu32 *)(CAN1_BASE + 0x000001B4)
  #define CAN1_RDLR1            *(vu32 *)(CAN1_BASE + 0x000001B8)
  #define CAN1_RDHR1            *(vu32 *)(CAN1_BASE + 0x000001BC)
  #define CAN1_RIR2             *(vu32 *)(CAN1_BASE + 0x000001C0)
  #define CAN1_RDTR2            *(vu32 *)(CAN1_BASE + 0x000001C4)
  #define CAN1_RDLR2            *(vu32 *)(CAN1_BASE + 0x000001C8)
  #define CAN1_RDHR2            *(vu32 *)(CAN1_BASE + 0x000001CC)

  #define CAN1_FMR              *(vu32 *)(CAN1_BASE + 0x00000200)
  #define CAN1_FM1R             *(vu32 *)(CAN1_BASE + 0x00000204)
  #define CAN1_FS1R             *(vu32 *)(CAN1_BASE + 0x0000020C)
  #define CAN1_FFA1R            *(vu32 *)(CAN1_BASE + 0x00000214)
  #define CAN1_FA1R             *(vu32 *)(CAN1_BASE + 0x0000021C)

  #define CAN1_FR1_00           *(vu32 *)(CAN1_BASE + 0x00000240)
  #define CAN1_FR2_00           *(vu32 *)(CAN1_BASE + 0x00000244)
  #define CAN1_FR1_01           *(vu32 *)(CAN1_BASE + 0x00000248)
  #define CAN1_FR2_01           *(vu32 *)(CAN1_BASE + 0x0000024C)
  #define CAN1_FR1_02           *(vu32 *)(CAN1_BASE + 0x00000250)
  #define CAN1_FR2_02           *(vu32 *)(CAN1_BASE + 0x00000254)
  #define CAN1_FR1_03           *(vu32 *)(CAN1_BASE + 0x00000258)
  #define CAN1_FR2_03           *(vu32 *)(CAN1_BASE + 0x0000025C)
  #define CAN1_FR1_04           *(vu32 *)(CAN1_BASE + 0x00000260)
  #define CAN1_FR2_04           *(vu32 *)(CAN1_BASE + 0x00000264)
  #define CAN1_FR1_05           *(vu32 *)(CAN1_BASE + 0x00000268)
  #define CAN1_FR2_05           *(vu32 *)(CAN1_BASE + 0x0000026C)
  #define CAN1_FR1_06           *(vu32 *)(CAN1_BASE + 0x00000270)
  #define CAN1_FR2_06           *(vu32 *)(CAN1_BASE + 0x00000274)
  #define CAN1_FR1_07           *(vu32 *)(CAN1_BASE + 0x00000278)
  #define CAN1_FR2_07           *(vu32 *)(CAN1_BASE + 0x0000027C)
  #define CAN1_FR1_08           *(vu32 *)(CAN1_BASE + 0x00000280)
  #define CAN1_FR2_08           *(vu32 *)(CAN1_BASE + 0x00000284)
  #define CAN1_FR1_09           *(vu32 *)(CAN1_BASE + 0x00000288)
  #define CAN1_FR2_09           *(vu32 *)(CAN1_BASE + 0x0000028C)
  #define CAN1_FR1_10           *(vu32 *)(CAN1_BASE + 0x00000290)
  #define CAN1_FR2_10           *(vu32 *)(CAN1_BASE + 0x00000294)
  #define CAN1_FR1_11           *(vu32 *)(CAN1_BASE + 0x00000298)
  #define CAN1_FR2_11           *(vu32 *)(CAN1_BASE + 0x0000029C)
  #define CAN1_FR1_12           *(vu32 *)(CAN1_BASE + 0x000002A0)
  #define CAN1_FR2_12           *(vu32 *)(CAN1_BASE + 0x000002A4)
  #define CAN1_FR1_13           *(vu32 *)(CAN1_BASE + 0x000002A8)
  #define CAN1_FR2_13           *(vu32 *)(CAN1_BASE + 0x000002AC)
  #define CAN1_FR1_14           *(vu32 *)(CAN1_BASE + 0x000002B0)
  #define CAN1_FR2_14           *(vu32 *)(CAN1_BASE + 0x000002B4)
  #define CAN1_FR1_15           *(vu32 *)(CAN1_BASE + 0x000002B8)
  #define CAN1_FR2_15           *(vu32 *)(CAN1_BASE + 0x000002BC)
  #define CAN1_FR1_16           *(vu32 *)(CAN1_BASE + 0x000002C0)
  #define CAN1_FR2_16           *(vu32 *)(CAN1_BASE + 0x000002C4)
  #define CAN1_FR1_17           *(vu32 *)(CAN1_BASE + 0x000002C8)
  #define CAN1_FR2_17           *(vu32 *)(CAN1_BASE + 0x000002CC)
  #define CAN1_FR1_18           *(vu32 *)(CAN1_BASE + 0x000002D0)
  #define CAN1_FR2_18           *(vu32 *)(CAN1_BASE + 0x000002D4)
  #define CAN1_FR1_19           *(vu32 *)(CAN1_BASE + 0x000002D8)
  #define CAN1_FR2_19           *(vu32 *)(CAN1_BASE + 0x000002DC)
  #define CAN1_FR1_20           *(vu32 *)(CAN1_BASE + 0x000002E0)
  #define CAN1_FR2_20           *(vu32 *)(CAN1_BASE + 0x000002E4)
  #define CAN1_FR1_21           *(vu32 *)(CAN1_BASE + 0x000002E8)
  #define CAN1_FR2_21           *(vu32 *)(CAN1_BASE + 0x000002EC)
  #define CAN1_FR1_22           *(vu32 *)(CAN1_BASE + 0x000002F0)
  #define CAN1_FR2_22           *(vu32 *)(CAN1_BASE + 0x000002F4)
  #define CAN1_FR1_23           *(vu32 *)(CAN1_BASE + 0x000002F8)
  #define CAN1_FR2_23           *(vu32 *)(CAN1_BASE + 0x000002FC)
  #define CAN1_FR1_24           *(vu32 *)(CAN1_BASE + 0x00000300)
  #define CAN1_FR2_24           *(vu32 *)(CAN1_BASE + 0x00000304)
  #define CAN1_FR1_25           *(vu32 *)(CAN1_BASE + 0x00000308)
  #define CAN1_FR2_25           *(vu32 *)(CAN1_BASE + 0x0000030C)
  #define CAN1_FR1_26           *(vu32 *)(CAN1_BASE + 0x00000310)
  #define CAN1_FR2_26           *(vu32 *)(CAN1_BASE + 0x00000314)
  #define CAN1_FR1_27           *(vu32 *)(CAN1_BASE + 0x00000318)
  #define CAN1_FR2_27           *(vu32 *)(CAN1_BASE + 0x0000031C)

  //-------------------------------------------------------------------------------------------
  //      DAC Interface Registers
  //-------------------------------------------------------------------------------------------
  //--- DAC #1 Registers
  #define DAC1_CR               *(vu32 *)(DAC1_BASE + 0x00000000)
  #define DAC1_SWTRIGR          *(vu32 *)(DAC1_BASE + 0x00000004)
  #define DAC1_DHR12R1          *(vu32 *)(DAC1_BASE + 0x00000008)
  #define DAC1_DHR12L1          *(vu32 *)(DAC1_BASE + 0x0000000C)
  #define DAC1_DHR8R1           *(vu32 *)(DAC1_BASE + 0x00000010)
  #define DAC1_DHR12R2          *(vu32 *)(DAC1_BASE + 0x00000014)
  #define DAC1_DHR12L2          *(vu32 *)(DAC1_BASE + 0x00000018)
  #define DAC1_DHR8R2           *(vu32 *)(DAC1_BASE + 0x0000001C)
  #define DAC1_DHR12RD          *(vu32 *)(DAC1_BASE + 0x00000020)
  #define DAC1_DHR12LD          *(vu32 *)(DAC1_BASE + 0x00000024)
  #define DAC1_DHR8RD           *(vu32 *)(DAC1_BASE + 0x00000028)
  #define DAC1_DOR1             *(vu32 *)(DAC1_BASE + 0x0000002C)
  #define DAC1_DOR2             *(vu32 *)(DAC1_BASE + 0x00000030)
  #define DAC1_SR               *(vu32 *)(DAC1_BASE + 0x00000034)

  //-------------------------------------------------------------------------------------------
  //      EXTI Interface Registers
  //-------------------------------------------------------------------------------------------
  #define EXTI_IMR              *(vu32 *)(EXTI_BASE + 0x00000000)
  #define EXTI_EMR              *(vu32 *)(EXTI_BASE + 0x00000004)
  #define EXTI_RTSR             *(vu32 *)(EXTI_BASE + 0x00000008)
  #define EXTI_FTSR             *(vu32 *)(EXTI_BASE + 0x0000000C)
  #define EXTI_SWIER            *(vu32 *)(EXTI_BASE + 0x00000010)
  #define EXTI_PR               *(vu32 *)(EXTI_BASE + 0x00000014)

  //-------------------------------------------------------------------------------------------
  //      DMA  Interface Registers
  //-------------------------------------------------------------------------------------------
  //--- DMA #1 Registers
  #define DMA1_LISR             *(vu32 *)(DMA1_BASE + 0x00000000)
  #define DMA1_HISR             *(vu32 *)(DMA1_BASE + 0x00000004)
  #define DMA1_LIFCR            *(vu32 *)(DMA1_BASE + 0x00000008)
  #define DMA1_HIFCR            *(vu32 *)(DMA1_BASE + 0x0000000C)

  #define DMA1_S0CR             *(vu32 *)(DMA1_BASE + 0x00000010)
  #define DMA1_S0NDTR           *(vu32 *)(DMA1_BASE + 0x00000014)
  #define DMA1_S0PAR            *(vu32 *)(DMA1_BASE + 0x00000018)
  #define DMA1_S0M0AR           *(vu32 *)(DMA1_BASE + 0x0000001C)
  #define DMA1_S0M1AR           *(vu32 *)(DMA1_BASE + 0x00000020)
  #define DMA1_S0FCR            *(vu32 *)(DMA1_BASE + 0x00000024)

  #define DMA1_S1CR             *(vu32 *)(DMA1_BASE + 0x00000028)
  #define DMA1_S1NDTR           *(vu32 *)(DMA1_BASE + 0x0000002C)
  #define DMA1_S1PAR            *(vu32 *)(DMA1_BASE + 0x00000030)
  #define DMA1_S1M0AR           *(vu32 *)(DMA1_BASE + 0x00000034)
  #define DMA1_S1M1AR           *(vu32 *)(DMA1_BASE + 0x00000038)
  #define DMA1_S1FCR            *(vu32 *)(DMA1_BASE + 0x0000003C)

  #define DMA1_S2CR             *(vu32 *)(DMA1_BASE + 0x00000040)
  #define DMA1_S2NDTR           *(vu32 *)(DMA1_BASE + 0x00000044)
  #define DMA1_S2PAR            *(vu32 *)(DMA1_BASE + 0x00000048)
  #define DMA1_S2M0AR           *(vu32 *)(DMA1_BASE + 0x0000004C)
  #define DMA1_S2M1AR           *(vu32 *)(DMA1_BASE + 0x00000050)
  #define DMA1_S2FCR            *(vu32 *)(DMA1_BASE + 0x00000054)

  #define DMA1_S3CR             *(vu32 *)(DMA1_BASE + 0x00000058)
  #define DMA1_S3NDTR           *(vu32 *)(DMA1_BASE + 0x0000005C)
  #define DMA1_S3PAR            *(vu32 *)(DMA1_BASE + 0x00000060)
  #define DMA1_S3M0AR           *(vu32 *)(DMA1_BASE + 0x00000064)
  #define DMA1_S3M1AR           *(vu32 *)(DMA1_BASE + 0x00000068)
  #define DMA1_S3FCR            *(vu32 *)(DMA1_BASE + 0x0000006C)

  #define DMA1_S4CR             *(vu32 *)(DMA1_BASE + 0x00000070)
  #define DMA1_S4NDTR           *(vu32 *)(DMA1_BASE + 0x00000074)
  #define DMA1_S4PAR            *(vu32 *)(DMA1_BASE + 0x00000078)
  #define DMA1_S4M0AR           *(vu32 *)(DMA1_BASE + 0x0000007C)
  #define DMA1_S4M1AR           *(vu32 *)(DMA1_BASE + 0x00000080)
  #define DMA1_S4FCR            *(vu32 *)(DMA1_BASE + 0x00000084)

  #define DMA1_S5CR             *(vu32 *)(DMA1_BASE + 0x00000088)
  #define DMA1_S5NDTR           *(vu32 *)(DMA1_BASE + 0x0000008C)
  #define DMA1_S5PAR            *(vu32 *)(DMA1_BASE + 0x00000090)
  #define DMA1_S5M0AR           *(vu32 *)(DMA1_BASE + 0x00000094)
  #define DMA1_S5M1AR           *(vu32 *)(DMA1_BASE + 0x00000098)
  #define DMA1_S5FCR            *(vu32 *)(DMA1_BASE + 0x0000009C)

  #define DMA1_S6CR             *(vu32 *)(DMA1_BASE + 0x000000A0)
  #define DMA1_S6NDTR           *(vu32 *)(DMA1_BASE + 0x000000A4)
  #define DMA1_S6PAR            *(vu32 *)(DMA1_BASE + 0x000000A8)
  #define DMA1_S6M0AR           *(vu32 *)(DMA1_BASE + 0x000000AC)
  #define DMA1_S6M1AR           *(vu32 *)(DMA1_BASE + 0x000000B0)
  #define DMA1_S6FCR            *(vu32 *)(DMA1_BASE + 0x000000B4)

  #define DMA1_S7CR             *(vu32 *)(DMA1_BASE + 0x000000B8)
  #define DMA1_S7NDTR           *(vu32 *)(DMA1_BASE + 0x000000BC)
  #define DMA1_S7PAR            *(vu32 *)(DMA1_BASE + 0x000000C0)
  #define DMA1_S7M0AR           *(vu32 *)(DMA1_BASE + 0x000000C4)
  #define DMA1_S7M1AR           *(vu32 *)(DMA1_BASE + 0x000000C8)
  #define DMA1_S7FCR            *(vu32 *)(DMA1_BASE + 0x000000CC)

  //--- DMA #2 Registers
  #define DMA2_LISR             *(vu32 *)(DMA2_BASE + 0x00000000)
  #define DMA2_HISR             *(vu32 *)(DMA2_BASE + 0x00000004)
  #define DMA2_LIFCR            *(vu32 *)(DMA2_BASE + 0x00000008)
  #define DMA2_HIFCR            *(vu32 *)(DMA2_BASE + 0x0000000C)

  #define DMA2_S0CR             *(vu32 *)(DMA2_BASE + 0x00000010)
  #define DMA2_S0NDTR           *(vu32 *)(DMA2_BASE + 0x00000014)
  #define DMA2_S0PAR            *(vu32 *)(DMA2_BASE + 0x00000018)
  #define DMA2_S0M0AR           *(vu32 *)(DMA2_BASE + 0x0000001C)
  #define DMA2_S0M1AR           *(vu32 *)(DMA2_BASE + 0x00000020)
  #define DMA2_S0FCR            *(vu32 *)(DMA2_BASE + 0x00000024)

  #define DMA2_S1CR             *(vu32 *)(DMA2_BASE + 0x00000028)
  #define DMA2_S1NDTR           *(vu32 *)(DMA2_BASE + 0x0000002C)
  #define DMA2_S1PAR            *(vu32 *)(DMA2_BASE + 0x00000030)
  #define DMA2_S1M0AR           *(vu32 *)(DMA2_BASE + 0x00000034)
  #define DMA2_S1M1AR           *(vu32 *)(DMA2_BASE + 0x00000038)
  #define DMA2_S1FCR            *(vu32 *)(DMA2_BASE + 0x0000003C)

  #define DMA2_S2CR             *(vu32 *)(DMA2_BASE + 0x00000040)
  #define DMA2_S2NDTR           *(vu32 *)(DMA2_BASE + 0x00000044)
  #define DMA2_S2PAR            *(vu32 *)(DMA2_BASE + 0x00000048)
  #define DMA2_S2M0AR           *(vu32 *)(DMA2_BASE + 0x0000004C)
  #define DMA2_S2M1AR           *(vu32 *)(DMA2_BASE + 0x00000050)
  #define DMA2_S2FCR            *(vu32 *)(DMA2_BASE + 0x00000054)

  #define DMA2_S3CR             *(vu32 *)(DMA2_BASE + 0x00000058)
  #define DMA2_S3NDTR           *(vu32 *)(DMA2_BASE + 0x0000005C)
  #define DMA2_S3PAR            *(vu32 *)(DMA2_BASE + 0x00000060)
  #define DMA2_S3M0AR           *(vu32 *)(DMA2_BASE + 0x00000064)
  #define DMA2_S3M1AR           *(vu32 *)(DMA2_BASE + 0x00000068)
  #define DMA2_S3FCR            *(vu32 *)(DMA2_BASE + 0x0000006C)

  #define DMA2_S4CR             *(vu32 *)(DMA2_BASE + 0x00000070)
  #define DMA2_S4NDTR           *(vu32 *)(DMA2_BASE + 0x00000074)
  #define DMA2_S4PAR            *(vu32 *)(DMA2_BASE + 0x00000078)
  #define DMA2_S4M0AR           *(vu32 *)(DMA2_BASE + 0x0000007C)
  #define DMA2_S4M1AR           *(vu32 *)(DMA2_BASE + 0x00000080)
  #define DMA2_S4FCR            *(vu32 *)(DMA2_BASE + 0x00000084)

  #define DMA2_S5CR             *(vu32 *)(DMA2_BASE + 0x00000088)
  #define DMA2_S5NDTR           *(vu32 *)(DMA2_BASE + 0x0000008C)
  #define DMA2_S5PAR            *(vu32 *)(DMA2_BASE + 0x00000090)
  #define DMA2_S5M0AR           *(vu32 *)(DMA2_BASE + 0x00000094)
  #define DMA2_S5M1AR           *(vu32 *)(DMA2_BASE + 0x00000098)
  #define DMA2_S5FCR            *(vu32 *)(DMA2_BASE + 0x0000009C)

  #define DMA2_S6CR             *(vu32 *)(DMA2_BASE + 0x000000A0)
  #define DMA2_S6NDTR           *(vu32 *)(DMA2_BASE + 0x000000A4)
  #define DMA2_S6PAR            *(vu32 *)(DMA2_BASE + 0x000000A8)
  #define DMA2_S6M0AR           *(vu32 *)(DMA2_BASE + 0x000000AC)
  #define DMA2_S6M1AR           *(vu32 *)(DMA2_BASE + 0x000000B0)
  #define DMA2_S6FCR            *(vu32 *)(DMA2_BASE + 0x000000B4)

  #define DMA2_S7CR             *(vu32 *)(DMA2_BASE + 0x000000B8)
  #define DMA2_S7NDTR           *(vu32 *)(DMA2_BASE + 0x000000BC)
  #define DMA2_S7PAR            *(vu32 *)(DMA2_BASE + 0x000000C0)
  #define DMA2_S7M0AR           *(vu32 *)(DMA2_BASE + 0x000000C4)
  #define DMA2_S7M1AR           *(vu32 *)(DMA2_BASE + 0x000000C8)
  #define DMA2_S7FCR            *(vu32 *)(DMA2_BASE + 0x000000CC)

  //-------------------------------------------------------------------------------------------
  //      RTC  Interface Registers
  //-------------------------------------------------------------------------------------------
  #define RTC_TR                *(vu32 *)(RTC_BASE + 0x00000000)
  #define RTC_DR                *(vu32 *)(RTC_BASE + 0x00000004)
  #define RTC_CR                *(vu32 *)(RTC_BASE + 0x00000008)
  #define RTC_ISR               *(vu32 *)(RTC_BASE + 0x0000000C)
  #define RTC_PRER              *(vu32 *)(RTC_BASE + 0x00000010)
  #define RTC_WUTR              *(vu32 *)(RTC_BASE + 0x00000014)
  #define RTC_CALIBR            *(vu32 *)(RTC_BASE + 0x00000018)
  #define RTC_ALRMAR            *(vu32 *)(RTC_BASE + 0x0000001C)
  #define RTC_ALRMBR            *(vu32 *)(RTC_BASE + 0x00000020)
  #define RTC_WPR               *(vu32 *)(RTC_BASE + 0x00000024)
  #define RTC_SSR               *(vu32 *)(RTC_BASE + 0x00000028)
  #define RTC_SHIFTR            *(vu32 *)(RTC_BASE + 0x0000002C)
  #define RTC_TSTR              *(vu32 *)(RTC_BASE + 0x00000030)
  #define RTC_TSDR              *(vu32 *)(RTC_BASE + 0x00000034)
  #define RTC_TSSSR             *(vu32 *)(RTC_BASE + 0x00000038)
  #define RTC_CALR              *(vu32 *)(RTC_BASE + 0x0000003C)
  #define RTC_TAFCR             *(vu32 *)(RTC_BASE + 0x00000040)
  #define RTC_ALRMASSR          *(vu32 *)(RTC_BASE + 0x00000044)
  #define RTC_ALRMBSSR          *(vu32 *)(RTC_BASE + 0x00000048)

  #define RTC_BKP0R             *(vu32 *)(RTC_BASE + 0x00000050)
  #define RTC_BKP1R             *(vu32 *)(RTC_BASE + 0x00000054)
  #define RTC_BKP2R             *(vu32 *)(RTC_BASE + 0x00000058)
  #define RTC_BKP3R             *(vu32 *)(RTC_BASE + 0x0000005C)
  #define RTC_BKP4R             *(vu32 *)(RTC_BASE + 0x00000060)
  #define RTC_BKP5R             *(vu32 *)(RTC_BASE + 0x00000064)
  #define RTC_BKP6R             *(vu32 *)(RTC_BASE + 0x00000068)
  #define RTC_BKP7R             *(vu32 *)(RTC_BASE + 0x0000006C)
  #define RTC_BKP8R             *(vu32 *)(RTC_BASE + 0x00000070)
  #define RTC_BKP9R             *(vu32 *)(RTC_BASE + 0x00000074)
  #define RTC_BKP10R            *(vu32 *)(RTC_BASE + 0x00000078)
  #define RTC_BKP11R            *(vu32 *)(RTC_BASE + 0x0000007C)
  #define RTC_BKP12R            *(vu32 *)(RTC_BASE + 0x00000080)
  #define RTC_BKP13R            *(vu32 *)(RTC_BASE + 0x00000084)
  #define RTC_BKP14R            *(vu32 *)(RTC_BASE + 0x00000088)
  #define RTC_BKP15R            *(vu32 *)(RTC_BASE + 0x0000008C)
  #define RTC_BKP16R            *(vu32 *)(RTC_BASE + 0x00000090)
  #define RTC_BKP17R            *(vu32 *)(RTC_BASE + 0x00000094)
  #define RTC_BKP18R            *(vu32 *)(RTC_BASE + 0x00000098)
  #define RTC_BKP19R            *(vu32 *)(RTC_BASE + 0x0000009C)

  //-------------------------------------------------------------------------------------------
  //    General Purpose Timers
  //-------------------------------------------------------------------------------------------
  //--- Timer #1 registers
  #define TIM1_CR1              *(vu32 *)(TIM1_BASE + 0x00000000)
  #define TIM1_CR2              *(vu32 *)(TIM1_BASE + 0x00000004)
  #define TIM1_SMCR             *(vu32 *)(TIM1_BASE + 0x00000008)
  #define TIM1_DIER             *(vu32 *)(TIM1_BASE + 0x0000000C)
  #define TIM1_SR               *(vu32 *)(TIM1_BASE + 0x00000010)
  #define TIM1_EGR              *(vu32 *)(TIM1_BASE + 0x00000014)
  #define TIM1_CCMR1            *(vu32 *)(TIM1_BASE + 0x00000018)
  #define TIM1_CCMR2            *(vu32 *)(TIM1_BASE + 0x0000001C)
  #define TIM1_CCER             *(vu32 *)(TIM1_BASE + 0x00000020)
  #define TIM1_CNT              *(vu32 *)(TIM1_BASE + 0x00000024)
  #define TIM1_PSC              *(vu32 *)(TIM1_BASE + 0x00000028)
  #define TIM1_ARR              *(vu32 *)(TIM1_BASE + 0x0000002C)
  #define TIM1_RCR              *(vu32 *)(TIM1_BASE + 0x00000030)
  #define TIM1_CCR1             *(vu32 *)(TIM1_BASE + 0x00000034)
  #define TIM1_CCR2             *(vu32 *)(TIM1_BASE + 0x00000038)
  #define TIM1_CCR3             *(vu32 *)(TIM1_BASE + 0x0000003C)
  #define TIM1_CCR4             *(vu32 *)(TIM1_BASE + 0x00000040)
  #define TIM1_BDTR             *(vu32 *)(TIM1_BASE + 0x00000044)
  #define TIM1_DCR              *(vu32 *)(TIM1_BASE + 0x00000048)
  #define TIM1_DMAR             *(vu32 *)(TIM1_BASE + 0x0000004C)

  //--- Timer #2 registers
  #define TIM2_CR1              *(vu32 *)(TIM2_BASE + 0x00000000)
  #define TIM2_CR2              *(vu32 *)(TIM2_BASE + 0x00000004)
  #define TIM2_SMCR             *(vu32 *)(TIM2_BASE + 0x00000008)
  #define TIM2_DIER             *(vu32 *)(TIM2_BASE + 0x0000000C)
  #define TIM2_SR               *(vu32 *)(TIM2_BASE + 0x00000010)
  #define TIM2_EGR              *(vu32 *)(TIM2_BASE + 0x00000014)
  #define TIM2_CCMR1            *(vu32 *)(TIM2_BASE + 0x00000018)
  #define TIM2_CCMR2            *(vu32 *)(TIM2_BASE + 0x0000001C)
  #define TIM2_CCER             *(vu32 *)(TIM2_BASE + 0x00000020)
  #define TIM2_CNT              *(vu32 *)(TIM2_BASE + 0x00000024)
  #define TIM2_PSC              *(vu32 *)(TIM2_BASE + 0x00000028)
  #define TIM2_ARR              *(vu32 *)(TIM2_BASE + 0x0000002C)
  #define TIM2_CCR1             *(vu32 *)(TIM2_BASE + 0x00000034)
  #define TIM2_CCR2             *(vu32 *)(TIM2_BASE + 0x00000038)
  #define TIM2_CCR3             *(vu32 *)(TIM2_BASE + 0x0000003C)
  #define TIM2_CCR4             *(vu32 *)(TIM2_BASE + 0x00000040)
  #define TIM2_DCR              *(vu32 *)(TIM2_BASE + 0x00000048)
  #define TIM2_DMAR             *(vu32 *)(TIM2_BASE + 0x0000004C)

  //--- Timer #3 registers
  #define TIM3_CR1              *(vu32 *)(TIM3_BASE + 0x00000000)
  #define TIM3_CR2              *(vu32 *)(TIM3_BASE + 0x00000004)
  #define TIM3_SMCR             *(vu32 *)(TIM3_BASE + 0x00000008)
  #define TIM3_DIER             *(vu32 *)(TIM3_BASE + 0x0000000C)
  #define TIM3_SR               *(vu32 *)(TIM3_BASE + 0x00000010)
  #define TIM3_EGR              *(vu32 *)(TIM3_BASE + 0x00000014)
  #define TIM3_CCMR1            *(vu32 *)(TIM3_BASE + 0x00000018)
  #define TIM3_CCMR2            *(vu32 *)(TIM3_BASE + 0x0000001C)
  #define TIM3_CCER             *(vu32 *)(TIM3_BASE + 0x00000020)
  #define TIM3_CNT              *(vu32 *)(TIM3_BASE + 0x00000024)
  #define TIM3_PSC              *(vu32 *)(TIM3_BASE + 0x00000028)
  #define TIM3_ARR              *(vu32 *)(TIM3_BASE + 0x0000002C)
  #define TIM3_CCR1             *(vu32 *)(TIM3_BASE + 0x00000034)
  #define TIM3_CCR2             *(vu32 *)(TIM3_BASE + 0x00000038)
  #define TIM3_CCR3             *(vu32 *)(TIM3_BASE + 0x0000003C)
  #define TIM3_CCR4             *(vu32 *)(TIM3_BASE + 0x00000040)
  #define TIM3_DCR              *(vu32 *)(TIM3_BASE + 0x00000048)
  #define TIM3_DMAR             *(vu32 *)(TIM3_BASE + 0x0000004C)

  //--- Timer #6 registers
  #define TIM6_CR1              *(vu32 *)(TIM6_BASE + 0x00000000)
  #define TIM6_CR2              *(vu32 *)(TIM6_BASE + 0x00000004)
  #define TIM6_SMCR             *(vu32 *)(TIM6_BASE + 0x00000008)
  #define TIM6_DIER             *(vu32 *)(TIM6_BASE + 0x0000000C)
  #define TIM6_SR               *(vu32 *)(TIM6_BASE + 0x00000010)
  #define TIM6_EGR              *(vu32 *)(TIM6_BASE + 0x00000014)
  #define TIM6_CCMR1            *(vu32 *)(TIM6_BASE + 0x00000018)
  #define TIM6_CCMR2            *(vu32 *)(TIM6_BASE + 0x0000001C)
  #define TIM6_CCER             *(vu32 *)(TIM6_BASE + 0x00000020)
  #define TIM6_CNT              *(vu32 *)(TIM6_BASE + 0x00000024)
  #define TIM6_PSC              *(vu32 *)(TIM6_BASE + 0x00000028)
  #define TIM6_ARR              *(vu32 *)(TIM6_BASE + 0x0000002C)
  #define TIM6_CCR1             *(vu32 *)(TIM6_BASE + 0x00000034)
  #define TIM6_CCR2             *(vu32 *)(TIM6_BASE + 0x00000038)
  #define TIM6_CCR3             *(vu32 *)(TIM6_BASE + 0x0000003C)
  #define TIM6_CCR4             *(vu32 *)(TIM6_BASE + 0x00000040)
  #define TIM6_DCR              *(vu32 *)(TIM6_BASE + 0x00000048)
  #define TIM6_DMAR             *(vu32 *)(TIM6_BASE + 0x0000004C)

  //--- Timer #7 registers
  #define TIM7_CR1              *(vu32 *)(TIM7_BASE + 0x00000000)
  #define TIM7_CR2              *(vu32 *)(TIM7_BASE + 0x00000004)
  #define TIM7_SMCR             *(vu32 *)(TIM7_BASE + 0x00000008)
  #define TIM7_DIER             *(vu32 *)(TIM7_BASE + 0x0000000C)
  #define TIM7_SR               *(vu32 *)(TIM7_BASE + 0x00000010)
  #define TIM7_EGR              *(vu32 *)(TIM7_BASE + 0x00000014)
  #define TIM7_CCMR1            *(vu32 *)(TIM7_BASE + 0x00000018)
  #define TIM7_CCMR2            *(vu32 *)(TIM7_BASE + 0x0000001C)
  #define TIM7_CCER             *(vu32 *)(TIM7_BASE + 0x00000020)
  #define TIM7_CNT              *(vu32 *)(TIM7_BASE + 0x00000024)
  #define TIM7_PSC              *(vu32 *)(TIM7_BASE + 0x00000028)
  #define TIM7_ARR              *(vu32 *)(TIM7_BASE + 0x0000002C)
  #define TIM7_CCR1             *(vu32 *)(TIM7_BASE + 0x00000034)
  #define TIM7_CCR2             *(vu32 *)(TIM7_BASE + 0x00000038)
  #define TIM7_CCR3             *(vu32 *)(TIM7_BASE + 0x0000003C)
  #define TIM7_CCR4             *(vu32 *)(TIM7_BASE + 0x00000040)
  #define TIM7_DCR              *(vu32 *)(TIM7_BASE + 0x00000048)
  #define TIM7_DMAR             *(vu32 *)(TIM7_BASE + 0x0000004C)

  //--- Timer #15 registers
  #define TIM15_CR1             *(vu32 *)(TIM15_BASE + 0x00000000)
  #define TIM15_CR2             *(vu32 *)(TIM15_BASE + 0x00000004)
  #define TIM15_SMCR            *(vu32 *)(TIM15_BASE + 0x00000008)
  #define TIM15_DIER            *(vu32 *)(TIM15_BASE + 0x0000000C)
  #define TIM15_SR              *(vu32 *)(TIM15_BASE + 0x00000010)
  #define TIM15_EGR             *(vu32 *)(TIM15_BASE + 0x00000014)
  #define TIM15_CCMR1           *(vu32 *)(TIM15_BASE + 0x00000018)
  #define TIM15_CCMR2           *(vu32 *)(TIM15_BASE + 0x0000001C)
  #define TIM15_CCER            *(vu32 *)(TIM15_BASE + 0x00000020)
  #define TIM15_CNT             *(vu32 *)(TIM15_BASE + 0x00000024)
  #define TIM15_PSC             *(vu32 *)(TIM15_BASE + 0x00000028)
  #define TIM15_ARR             *(vu32 *)(TIM15_BASE + 0x0000002C)
  #define TIM15_RCR             *(vu32 *)(TIM15_BASE + 0x00000030)
  #define TIM15_CCR1            *(vu32 *)(TIM15_BASE + 0x00000034)
  #define TIM15_CCR2            *(vu32 *)(TIM15_BASE + 0x00000038)
  #define TIM15_CCR3            *(vu32 *)(TIM15_BASE + 0x0000003C)
  #define TIM15_CCR4            *(vu32 *)(TIM15_BASE + 0x00000040)
  #define TIM15_BDTR            *(vu32 *)(TIM15_BASE + 0x00000044)
  #define TIM15_DCR             *(vu32 *)(TIM15_BASE + 0x00000048)
  #define TIM15_DMAR            *(vu32 *)(TIM15_BASE + 0x0000004C)

  //--- Timer #16 registers
  #define TIM16_CR1             *(vu32 *)(TIM16_BASE + 0x00000000)
  #define TIM16_CR2             *(vu32 *)(TIM16_BASE + 0x00000004)
  #define TIM16_SMCR            *(vu32 *)(TIM16_BASE + 0x00000008)
  #define TIM16_DIER            *(vu32 *)(TIM16_BASE + 0x0000000C)
  #define TIM16_SR              *(vu32 *)(TIM16_BASE + 0x00000010)
  #define TIM16_EGR             *(vu32 *)(TIM16_BASE + 0x00000014)
  #define TIM16_CCMR1           *(vu32 *)(TIM16_BASE + 0x00000018)
  #define TIM16_CCMR2           *(vu32 *)(TIM16_BASE + 0x0000001C)
  #define TIM16_CCER            *(vu32 *)(TIM16_BASE + 0x00000020)
  #define TIM16_CNT             *(vu32 *)(TIM16_BASE + 0x00000024)
  #define TIM16_PSC             *(vu32 *)(TIM16_BASE + 0x00000028)
  #define TIM16_ARR             *(vu32 *)(TIM16_BASE + 0x0000002C)
  #define TIM16_RCR             *(vu32 *)(TIM16_BASE + 0x00000030)
  #define TIM16_CCR1            *(vu32 *)(TIM16_BASE + 0x00000034)
  #define TIM16_CCR2            *(vu32 *)(TIM16_BASE + 0x00000038)
  #define TIM16_CCR3            *(vu32 *)(TIM16_BASE + 0x0000003C)
  #define TIM16_CCR4            *(vu32 *)(TIM16_BASE + 0x00000040)
  #define TIM16_BDTR            *(vu32 *)(TIM16_BASE + 0x00000044)
  #define TIM16_DCR             *(vu32 *)(TIM16_BASE + 0x00000048)
  #define TIM16_DMAR            *(vu32 *)(TIM16_BASE + 0x0000004C)

  //-------------------------------------------------------------------------------------------
  //    LP Timer  registers
  //    LP Timer  = 16 bit general timer
  //-------------------------------------------------------------------------------------------
  #define LPTIM_CR1             *(vu32 *)(LPTIM_BASE + 0x00000000)
  #define LPTIM_CR2             *(vu32 *)(LPTIM_BASE + 0x00000004)
  #define LPTIM_SMCR            *(vu32 *)(LPTIM_BASE + 0x00000008)
  #define LPTIM_DIER            *(vu32 *)(LPTIM_BASE + 0x0000000C)
  #define LPTIM_SR              *(vu32 *)(LPTIM_BASE + 0x00000010)
  #define LPTIM_EGR             *(vu32 *)(LPTIM_BASE + 0x00000014)
  #define LPTIM_CCMR1           *(vu32 *)(LPTIM_BASE + 0x00000018)
  #define LPTIM_CCMR2           *(vu32 *)(LPTIM_BASE + 0x0000001C)
  #define LPTIM_CCER            *(vu32 *)(LPTIM_BASE + 0x00000020)
  #define LPTIM_CNT             *(vu32 *)(LPTIM_BASE + 0x00000024)
  #define LPTIM_PSC             *(vu32 *)(LPTIM_BASE + 0x00000028)
  #define LPTIM_ARR             *(vu32 *)(LPTIM_BASE + 0x0000002C)
  #define LPTIM_RCR             *(vu32 *)(LPTIM_BASE + 0x00000030)
  #define LPTIM_CCR1            *(vu32 *)(LPTIM_BASE + 0x00000034)
  #define LPTIM_CCR2            *(vu32 *)(LPTIM_BASE + 0x00000038)
  #define LPTIM_CCR3            *(vu32 *)(LPTIM_BASE + 0x0000003C)
  #define LPTIM_CCR4            *(vu32 *)(LPTIM_BASE + 0x00000040)
  #define LPTIM_BDTR            *(vu32 *)(LPTIM_BASE + 0x00000044)
  #define LPTIM_DCR             *(vu32 *)(LPTIM_BASE + 0x00000048)
  #define LPTIM_DMAR            *(vu32 *)(LPTIM_BASE + 0x0000004C)

  //-------------------------------------------------------------------------------------------
  //    UART Register Maps
  //-------------------------------------------------------------------------------------------
  //--- UART # 1 Registers
  #define USART1_SR             *(vu32 *)(USART1_BASE + 0x00000000)
  #define USART1_DR             *(vu32 *)(USART1_BASE + 0x00000004)
  #define USART1_BRR            *(vu32 *)(USART1_BASE + 0x00000008)
  #define USART1_CR1            *(vu32 *)(USART1_BASE + 0x0000000C)
  #define USART1_CR2            *(vu32 *)(USART1_BASE + 0x00000010)
  #define USART1_CR3            *(vu32 *)(USART1_BASE + 0x00000014)
  #define USART1_GTPR           *(vu32 *)(USART1_BASE + 0x00000018)

  //--- UART # 2 Registers
  #define USART2_SR             *(vu32 *)(USART2_BASE + 0x00000000)
  #define USART2_DR             *(vu32 *)(USART2_BASE + 0x00000004)
  #define USART2_BRR            *(vu32 *)(USART2_BASE + 0x00000008)
  #define USART2_CR1            *(vu32 *)(USART2_BASE + 0x0000000C)
  #define USART2_CR2            *(vu32 *)(USART2_BASE + 0x00000010)
  #define USART2_CR3            *(vu32 *)(USART2_BASE + 0x00000014)
  #define USART2_GTPR           *(vu32 *)(USART2_BASE + 0x00000018)

  //-------------------------------------------------------------------------------------------
  //      QUADSPI Interface Registers
  //-------------------------------------------------------------------------------------------
  #define QUADSPI_CR            *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_DCR           *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_SR            *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_FCR           *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_DLR           *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_CCR           *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_AR            *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_ABR           *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_DR            *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_PSMKR         *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_PSMAR         *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_PIR           *(vu32 *)(QUADSPI_BASE + 0x00000000)
  #define QUADSPI_LPTR          *(vu32 *)(QUADSPI_BASE + 0x00000000)

  //-------------------------------------------------------------------------------------------
  //      Random Number Generator
  //-------------------------------------------------------------------------------------------
  #define RNG_CR                *(vu32 *)(RNG_BASE + 0x00000000)
  #define RNG_SR                *(vu32 *)(RNG_BASE + 0x00000004)
  #define RNG_DR                *(vu32 *)(RNG_BASE + 0x00000008)

  //-------------------------------------------------------------------------------------------
  //      USB Register Location Map
  //-------------------------------------------------------------------------------------------
  #define USB_DEVICE_BASE                  *(vu32 *)(USB_BASE + 0x0800U)
  #define USB_IN_ENDPOINT_BASE             *(vu32 *)(USB_BASE + 0x0900U)
  #define USB_OUT_ENDPOINT_BASE            *(vu32 *)(USB_BASE + 0x0B00U)
  #define USB_HOST_BASE                    *(vu32 *)(USB_BASE + 0x0400U)
  #define USB_HOST_PORT_BASE               *(vu32 *)(USB_BASE + 0x0440U)
  #define USB_HOST_CHANNEL_BASE            *(vu32 *)(USB_BASE + 0x0500U)
  #define USB_PCGCCTL_BASE                 *(vu32 *)(USB_BASE + 0x0E00U)
  #define USB_FIFO_BASE                    *(vu32 *)(USB_BASE + 0x1000U)

  #define USB_EP_REG_SIZE                  ((u32 )0x20U)
  #define USB_HOST_CHANNEL_SIZE            ((u32 )0x20U)
  #define USB_FIFO_SIZE                    ((u32 )0x1000U)

  #define USB_EP0R                         USB_BASE                           //--- endpoint 0 register address
  #define USB_EP1R                         *(vu32 *)(USB_BASE + 0x00000004UL) //--- endpoint 1 register address
  #define USB_EP2R                         *(vu32 *)(USB_BASE + 0x00000008UL) //--- endpoint 2 register address
  #define USB_EP3R                         *(vu32 *)(USB_BASE + 0x0000000CUL) //--- endpoint 3 register address
  #define USB_EP4R                         *(vu32 *)(USB_BASE + 0x00000010UL) //--- endpoint 4 register address
  #define USB_EP5R                         *(vu32 *)(USB_BASE + 0x00000014UL) //--- endpoint 5 register address
  #define USB_EP6R                         *(vu32 *)(USB_BASE + 0x00000018UL) //--- endpoint 6 register address
  #define USB_EP7R                         *(vu32 *)(USB_BASE + 0x0000001CUL) //--- endpoint 7 register address

  //-------------------------------------------------------------------------------------------
  //      USB Device FS General registers
  //-------------------------------------------------------------------------------------------
  #define USB_CNTR                         *(vu32 *)(USB_BASE + 0x00000040UL) //--- Control register
  #define USB_ISTR                         *(vu32 *)(USB_BASE + 0x00000044UL) //--- Interrupt status register
  #define USB_FNR                          *(vu32 *)(USB_BASE + 0x00000048UL) //--- Frame number register
  #define USB_DADDR                        *(vu32 *)(USB_BASE + 0x0000004CUL) //--- Device address register
  #define USB_BTABLE                       *(vu32 *)(USB_BASE + 0x00000050UL) //--- Buffer Table address register
  #define USB_LPMCSR                       *(vu32 *)(USB_BASE + 0x00000054UL) //--- LPM Control and Status register
  #define USB_BCDR                         *(vu32 *)(USB_BASE + 0x00000058UL) //--- Battery Charging detector register

  //-------------------------------------------------------------------------------------------
  //    Windowed Watch Dog
  //-------------------------------------------------------------------------------------------
  #define WWDG_CR                          *(vu32 *)(WWDG_BASE + 0x00000000)
  #define WWDG_CFR                         *(vu32 *)(WWDG_BASE + 0x00000004)
  #define WWDG_SR                          *(vu32 *)(WWDG_BASE + 0x00000008)

  //-------------------------------------------------------------------------------------------
  //    Idependant Watch Dog
  //-------------------------------------------------------------------------------------------
  #define IWDG_KR                          *(vu32 *)(IWDG_BASE + 0x00000000)
  #define IWDG_PR                          *(vu32 *)(IWDG_BASE + 0x00000004)
  #define IWDG_RLR                         *(vu32 *)(IWDG_BASE + 0x00000008)
  #define IWDG_SR                          *(vu32 *)(IWDG_BASE + 0x0000000C)

  //-------------------------------------------------------------------------------------------
  //    SDIO Interface
  //-------------------------------------------------------------------------------------------
  #define SDIO_POWER                       *(vu32 *)(SDIO_BASE + 0x00000000)
  #define SDIO_CLKCR                       *(vu32 *)(SDIO_BASE + 0x00000004)
  #define SDIO_ARG                         *(vu32 *)(SDIO_BASE + 0x00000008)
  #define SDIO_CMD                         *(vu32 *)(SDIO_BASE + 0x0000000C)
  #define SDIO_RESPCMD                     *(vu32 *)(SDIO_BASE + 0x00000010)
  #define SDIO_RESP1                       *(vu32 *)(SDIO_BASE + 0x00000014)
  #define SDIO_RESP2                       *(vu32 *)(SDIO_BASE + 0x00000018)
  #define SDIO_RESP3                       *(vu32 *)(SDIO_BASE + 0x0000001C)
  #define SDIO_RESP4                       *(vu32 *)(SDIO_BASE + 0x00000020)
  #define SDIO_DTIMER                      *(vu32 *)(SDIO_BASE + 0x00000024)
  #define SDIO_DLEN                        *(vu32 *)(SDIO_BASE + 0x00000028)
  #define SDIO_DCTRL                       *(vu32 *)(SDIO_BASE + 0x0000002C)
  #define SDIO_DCOUNT                      *(vu32 *)(SDIO_BASE + 0x00000030)
  #define SDIO_STA                         *(vu32 *)(SDIO_BASE + 0x00000034)
  #define SDIO_ICR                         *(vu32 *)(SDIO_BASE + 0x00000038)
  #define SDIO_MASK                        *(vu32 *)(SDIO_BASE + 0x0000003C)
  #define SDIO_FIFOCNT                     *(vu32 *)(SDIO_BASE + 0x00000048)
  #define SDIO_FIFO                        *(vu32 *)(SDIO_BASE + 0x00000080)

  //-------------------------------------------------------------------------------------------
  //    Serial Audio Interface
  //-------------------------------------------------------------------------------------------




//  #ifdef __cplusplus
//    }
//  #endif
#endif

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

    //-----------------------------------------------------------------------------------------
    //
    //-----------------------------------------------------------------------------------------

      //---------------------------------------------------------------------------------------
      //
      //---------------------------------------------------------------------------------------
