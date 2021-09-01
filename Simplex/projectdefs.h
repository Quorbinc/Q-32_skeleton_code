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

  //-------------------------------------------------------------------------------------------
  //    System Control Block Register Position and Mask Definitions
  //    This set of definitions has been previously defined by
  //    ST Microelectronics(R) in "core_cmr.h"
  //-------------------------------------------------------------------------------------------

  //  SCB CPUID Register Definitions
  #define SCB_CPUID_IMPLEMENTER_Pos          24U                                   //--- SCB CPUID: IMPLEMENTER Position
  #define SCB_CPUID_IMPLEMENTER_Msk          (0xFFUL << SCB_CPUID_IMPLEMENTER_Pos) //--- SCB CPUID: IMPLEMENTER Mask

  #define SCB_CPUID_VARIANT_Pos              20U                                   //--- SCB CPUID: VARIANT Position
  #define SCB_CPUID_VARIANT_Msk              (0xFUL << SCB_CPUID_VARIANT_Pos)      //--- SCB CPUID: VARIANT Mask

  #define SCB_CPUID_ARCHITECTURE_Pos         16U                                   //--- SCB CPUID: ARCHITECTURE Position
  #define SCB_CPUID_ARCHITECTURE_Msk         (0xFUL << SCB_CPUID_ARCHITECTURE_Pos) //--- SCB CPUID: ARCHITECTURE Mask

  #define SCB_CPUID_PARTNO_Pos                4U                                   //--- SCB CPUID: PARTNO Position
  #define SCB_CPUID_PARTNO_Msk               (0xFFFUL << SCB_CPUID_PARTNO_Pos)     //--- SCB CPUID: PARTNO Mask

  #define SCB_CPUID_REVISION_Pos              0U                                   //--- SCB CPUID: REVISION Position
  #define SCB_CPUID_REVISION_Msk             (0xFUL << SCB_CPUID_REVISION_Pos*/)   //--- SCB CPUID: REVISION Mask

  //  SCB Interrupt Control State Register Definitions
  #define SCB_ICSR_NMIPENDSET_Pos            31U                                   //--- SCB ICSR: NMIPENDSET Position
  #define SCB_ICSR_NMIPENDSET_Msk            (1UL << SCB_ICSR_NMIPENDSET_Pos)      //--- SCB ICSR: NMIPENDSET Mask

  #define SCB_ICSR_PENDSVSET_Pos             28U                                   //--- SCB ICSR: PENDSVSET Position
  #define SCB_ICSR_PENDSVSET_Msk             (1UL << SCB_ICSR_PENDSVSET_Pos)       //--- SCB ICSR: PENDSVSET Mask

  #define SCB_ICSR_PENDSVCLR_Pos             27U                                   //--- SCB ICSR: PENDSVCLR Position
  #define SCB_ICSR_PENDSVCLR_Msk             (1UL << SCB_ICSR_PENDSVCLR_Pos)       //--- SCB ICSR: PENDSVCLR Mask

  #define SCB_ICSR_PENDSTSET_Pos             26U                                   //--- SCB ICSR: PENDSTSET Position
  #define SCB_ICSR_PENDSTSET_Msk             (1UL << SCB_ICSR_PENDSTSET_Pos)       //--- SCB ICSR: PENDSTSET Mask

  #define SCB_ICSR_PENDSTCLR_Pos             25U                                   //--- SCB ICSR: PENDSTCLR Position
  #define SCB_ICSR_PENDSTCLR_Msk             (1UL << SCB_ICSR_PENDSTCLR_Pos)       //--- SCB ICSR: PENDSTCLR Mask

  #define SCB_ICSR_ISRPREEMPT_Pos            23U                                   //--- SCB ICSR: ISRPREEMPT Position
  #define SCB_ICSR_ISRPREEMPT_Msk            (1UL << SCB_ICSR_ISRPREEMPT_Pos)      //--- SCB ICSR: ISRPREEMPT Mask

  #define SCB_ICSR_ISRPENDING_Pos            22U                                   //--- SCB ICSR: ISRPENDING Position
  #define SCB_ICSR_ISRPENDING_Msk            (1UL << SCB_ICSR_ISRPENDING_Pos)      //--- SCB ICSR: ISRPENDING Mask

  #define SCB_ICSR_VECTPENDING_Pos           12U                                   //--- SCB ICSR: VECTPENDING Position
  #define SCB_ICSR_VECTPENDING_Msk           (0x1FFUL << SCB_ICSR_VECTPENDING_Pos) //--- SCB ICSR: VECTPENDING Mask

  #define SCB_ICSR_RETTOBASE_Pos             11U                                   //--- SCB ICSR: RETTOBASE Position
  #define SCB_ICSR_RETTOBASE_Msk             (1UL << SCB_ICSR_RETTOBASE_Pos)       //--- SCB ICSR: RETTOBASE Mask

  #define SCB_ICSR_VECTACTIVE_Pos             0U                                   //--- SCB ICSR: VECTACTIVE Position
  #define SCB_ICSR_VECTACTIVE_Msk            (0x1FFUL << SCB_ICSR_VECTACTIVE_Pos)  //--- SCB ICSR: VECTACTIVE Mask

  //  SCB Vector Table Offset Register Definitions
  #define SCB_VTOR_TBLOFF_Pos                 7U                                   //--- SCB VTOR: TBLOFF Position
  #define SCB_VTOR_TBLOFF_Msk                (0x1FFFFFFUL << SCB_VTOR_TBLOFF_Pos)  //--- SCB VTOR: TBLOFF Mask

  //  SCB Application Interrupt and Reset Control Register Definitions
  #define SCB_AIRCR_VECTKEY_Pos              16U                                   //--- SCB AIRCR: VECTKEY Position
  #define SCB_AIRCR_VECTKEY_Msk              (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)   //--- SCB AIRCR: VECTKEY Mask

  #define SCB_AIRCR_VECTKEYSTAT_Pos          16U                                   //--- SCB AIRCR: VECTKEYSTAT Position
  #define SCB_AIRCR_VECTKEYSTAT_Msk          (0xFFFFUL << SCB_AIRCR_VECTKEYSTAT_Pos)        //--- SCB AIRCR: VECTKEYSTAT Mask

  #define SCB_AIRCR_ENDIANESS_Pos            15U                                   //--- SCB AIRCR: ENDIANESS Position
  #define SCB_AIRCR_ENDIANESS_Msk            (1UL << SCB_AIRCR_ENDIANESS_Pos)      //--- SCB AIRCR: ENDIANESS Mask

  #define SCB_AIRCR_PRIGROUP_Pos              8U                                   //--- SCB AIRCR: PRIGROUP Position
  #define SCB_AIRCR_PRIGROUP_Msk             (7UL << SCB_AIRCR_PRIGROUP_Pos)       //--- SCB AIRCR: PRIGROUP Mask

  #define SCB_AIRCR_SYSRESETREQ_Pos           2U                                   //--- SCB AIRCR: SYSRESETREQ Position
  #define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos)    //--- SCB AIRCR: SYSRESETREQ Mask

  #define SCB_AIRCR_VECTCLRACTIVE_Pos         1U                                   //--- SCB AIRCR: VECTCLRACTIVE Position
  #define SCB_AIRCR_VECTCLRACTIVE_Msk        (1UL << SCB_AIRCR_VECTCLRACTIVE_Pos)  //--- SCB AIRCR: VECTCLRACTIVE Mask

  #define SCB_AIRCR_VECTRESET_Pos             0U                                   //--- SCB AIRCR: VECTRESET Position
  #define SCB_AIRCR_VECTRESET_Msk            (1UL << SCB_AIRCR_VECTRESET_Pos)      //--- SCB AIRCR: VECTRESET Mask

  //  SCB System Control Register Definitions
  #define SCB_SCR_SEVONPEND_Pos               4U                                   //--- SCB SCR: SEVONPEND Position
  #define SCB_SCR_SEVONPEND_Msk              (1UL << SCB_SCR_SEVONPEND_Pos)        //--- SCB SCR: SEVONPEND Mask

  #define SCB_SCR_SLEEPDEEP_Pos               2U                                   //--- SCB SCR: SLEEPDEEP Position
  #define SCB_SCR_SLEEPDEEP_Msk              (1UL << SCB_SCR_SLEEPDEEP_Pos)        //--- SCB SCR: SLEEPDEEP Mask

  #define SCB_SCR_SLEEPONEXIT_Pos             1U                                   //--- SCB SCR: SLEEPONEXIT Position
  #define SCB_SCR_SLEEPONEXIT_Msk            (1UL << SCB_SCR_SLEEPONEXIT_Pos)      //--- SCB SCR: SLEEPONEXIT Mask

  //  SCB Configuration Control Register Definitions
  #define SCB_CCR_STKALIGN_Pos                9U                                   //--- SCB CCR: STKALIGN Position
  #define SCB_CCR_STKALIGN_Msk               (1UL << SCB_CCR_STKALIGN_Pos)         //--- SCB CCR: STKALIGN Mask

  #define SCB_CCR_BFHFNMIGN_Pos               8U                                   //--- SCB CCR: BFHFNMIGN Position
  #define SCB_CCR_BFHFNMIGN_Msk              (1UL << SCB_CCR_BFHFNMIGN_Pos)        //--- SCB CCR: BFHFNMIGN Mask

  #define SCB_CCR_DIV_0_TRP_Pos               4U                                   //--- SCB CCR: DIV_0_TRP Position
  #define SCB_CCR_DIV_0_TRP_Msk              (1UL << SCB_CCR_DIV_0_TRP_Pos)        //--- SCB CCR: DIV_0_TRP Mask

  #define SCB_CCR_UNALIGN_TRP_Pos             3U                                   //--- SCB CCR: UNALIGN_TRP Position
  #define SCB_CCR_UNALIGN_TRP_Msk            (1UL << SCB_CCR_UNALIGN_TRP_Pos)      //--- SCB CCR: UNALIGN_TRP Mask

  #define SCB_CCR_USERSETMPEND_Pos            1U                                   //--- SCB CCR: USERSETMPEND Position
  #define SCB_CCR_USERSETMPEND_Msk           (1UL << SCB_CCR_USERSETMPEND_Pos)     //--- SCB CCR: USERSETMPEND Mask

  #define SCB_CCR_NONBASETHRDENA_Pos          0U                                   //--- SCB CCR: NONBASETHRDENA Position
  #define SCB_CCR_NONBASETHRDENA_Msk         (1UL << SCB_CCR_NONBASETHRDENA_Pos)   //--- SCB CCR: NONBASETHRDENA Mask

  //  SCB System Handler Control and State Register Definitions
  #define SCB_SHCSR_USGFAULTENA_Pos          18U                                   //--- SCB SHCSR: USGFAULTENA Position
  #define SCB_SHCSR_USGFAULTENA_Msk          (1UL << SCB_SHCSR_USGFAULTENA_Pos)    //--- SCB SHCSR: USGFAULTENA Mask

  #define SCB_SHCSR_BUSFAULTENA_Pos          17U                                   //--- SCB SHCSR: BUSFAULTENA Position
  #define SCB_SHCSR_BUSFAULTENA_Msk          (1UL << SCB_SHCSR_BUSFAULTENA_Pos)    //--- SCB SHCSR: BUSFAULTENA Mask

  #define SCB_SHCSR_MEMFAULTENA_Pos          16U                                   //--- SCB SHCSR: MEMFAULTENA Position
  #define SCB_SHCSR_MEMFAULTENA_Msk          (1UL << SCB_SHCSR_MEMFAULTENA_Pos)    //--- SCB SHCSR: MEMFAULTENA Mask

  #define SCB_SHCSR_SVCALLPENDED_Pos         15U                                   //--- SCB SHCSR: SVCALLPENDED Position
  #define SCB_SHCSR_SVCALLPENDED_Msk         (1UL << SCB_SHCSR_SVCALLPENDED_Pos)   //--- SCB SHCSR: SVCALLPENDED Mask

  #define SCB_SHCSR_BUSFAULTPENDED_Pos       14U                                   //--- SCB SHCSR: BUSFAULTPENDED Position
  #define SCB_SHCSR_BUSFAULTPENDED_Msk       (1UL << SCB_SHCSR_BUSFAULTPENDED_Pos) //--- SCB SHCSR: BUSFAULTPENDED Mask

  #define SCB_SHCSR_MEMFAULTPENDED_Pos       13U                                   //--- SCB SHCSR: MEMFAULTPENDED Position
  #define SCB_SHCSR_MEMFAULTPENDED_Msk       (1UL << SCB_SHCSR_MEMFAULTPENDED_Pos) //--- SCB SHCSR: MEMFAULTPENDED Mask

  #define SCB_SHCSR_USGFAULTPENDED_Pos       12U                                   //--- SCB SHCSR: USGFAULTPENDED Position
  #define SCB_SHCSR_USGFAULTPENDED_Msk       (1UL << SCB_SHCSR_USGFAULTPENDED_Pos) //--- SCB SHCSR: USGFAULTPENDED Mask

  #define SCB_SHCSR_SYSTICKACT_Pos           11U                                   //--- SCB SHCSR: SYSTICKACT Position
  #define SCB_SHCSR_SYSTICKACT_Msk           (1UL << SCB_SHCSR_SYSTICKACT_Pos)     //--- SCB SHCSR: SYSTICKACT Mask

  #define SCB_SHCSR_PENDSVACT_Pos            10U                                   //--- SCB SHCSR: PENDSVACT Position
  #define SCB_SHCSR_PENDSVACT_Msk            (1UL << SCB_SHCSR_PENDSVACT_Pos)      //--- SCB SHCSR: PENDSVACT Mask

  #define SCB_SHCSR_MONITORACT_Pos            8U                                   //--- SCB SHCSR: MONITORACT Position
  #define SCB_SHCSR_MONITORACT_Msk           (1UL << SCB_SHCSR_MONITORACT_Pos)     //--- SCB SHCSR: MONITORACT Mask

  #define SCB_SHCSR_SVCALLACT_Pos             7U                                   //--- SCB SHCSR: SVCALLACT Position
  #define SCB_SHCSR_SVCALLACT_Msk            (1UL << SCB_SHCSR_SVCALLACT_Pos)      //--- SCB SHCSR: SVCALLACT Mask

  #define SCB_SHCSR_USGFAULTACT_Pos           3U                                   //--- SCB SHCSR: USGFAULTACT Position
  #define SCB_SHCSR_USGFAULTACT_Msk          (1UL << SCB_SHCSR_USGFAULTACT_Pos)    //--- SCB SHCSR: USGFAULTACT Mask

  #define SCB_SHCSR_BUSFAULTACT_Pos           1U                                   //--- SCB SHCSR: BUSFAULTACT Position
  #define SCB_SHCSR_BUSFAULTACT_Msk          (1UL << SCB_SHCSR_BUSFAULTACT_Pos)    //--- SCB SHCSR: BUSFAULTACT Mask

  #define SCB_SHCSR_MEMFAULTACT_Pos           0U                                   //--- SCB SHCSR: MEMFAULTACT Position
  #define SCB_SHCSR_MEMFAULTACT_Msk          (1UL << SCB_SHCSR_MEMFAULTACT_Pos)    //--- SCB SHCSR: MEMFAULTACT Mask

  //  SCB Configurable Fault Status Register Definitions
  #define SCB_CFSR_USGFAULTSR_Pos            16U                                   //--- SCB CFSR: Usage Fault Status Register Position
  #define SCB_CFSR_USGFAULTSR_Msk            (0xFFFFUL << SCB_CFSR_USGFAULTSR_Pos) //--- SCB CFSR: Usage Fault Status Register Mask

  #define SCB_CFSR_BUSFAULTSR_Pos             8U                                   //--- SCB CFSR: Bus Fault Status Register Position
  #define SCB_CFSR_BUSFAULTSR_Msk            (0xFFUL << SCB_CFSR_BUSFAULTSR_Pos)   //--- SCB CFSR: Bus Fault Status Register Mask

  #define SCB_CFSR_MEMFAULTSR_Pos             0U                                   //--- SCB CFSR: Memory Manage Fault Status Register Position
  #define SCB_CFSR_MEMFAULTSR_Msk            (0xFFUL << SCB_CFSR_MEMFAULTSR_Pos)   //--- SCB CFSR: Memory Manage Fault Status Register Mask

  //  MemManage Fault Status Register (part of SCB Configurable Fault Status Register)
  #define SCB_CFSR_MMARVALID_Pos             (SCB_SHCSR_MEMFAULTACT_Pos + 7U)      //--- SCB CFSR (MMFSR): MMARVALID Position
  #define SCB_CFSR_MMARVALID_Msk             (1UL << SCB_CFSR_MMARVALID_Pos)       //--- SCB CFSR (MMFSR): MMARVALID Mask

  #define SCB_CFSR_MLSPERR_Pos               (SCB_SHCSR_MEMFAULTACT_Pos + 5U)      //--- SCB CFSR (MMFSR): MLSPERR Position
  #define SCB_CFSR_MLSPERR_Msk               (1UL << SCB_CFSR_MLSPERR_Pos)         //--- SCB CFSR (MMFSR): MLSPERR Mask

  #define SCB_CFSR_MSTKERR_Pos               (SCB_SHCSR_MEMFAULTACT_Pos + 4U)      //--- SCB CFSR (MMFSR): MSTKERR Position
  #define SCB_CFSR_MSTKERR_Msk               (1UL << SCB_CFSR_MSTKERR_Pos)         //--- SCB CFSR (MMFSR): MSTKERR Mask

  #define SCB_CFSR_MUNSTKERR_Pos             (SCB_SHCSR_MEMFAULTACT_Pos + 3U)      //--- SCB CFSR (MMFSR): MUNSTKERR Position
  #define SCB_CFSR_MUNSTKERR_Msk             (1UL << SCB_CFSR_MUNSTKERR_Pos)       //--- SCB CFSR (MMFSR): MUNSTKERR Mask

  #define SCB_CFSR_DACCVIOL_Pos              (SCB_SHCSR_MEMFAULTACT_Pos + 1U)      //--- SCB CFSR (MMFSR): DACCVIOL Position
  #define SCB_CFSR_DACCVIOL_Msk              (1UL << SCB_CFSR_DACCVIOL_Pos)        //--- SCB CFSR (MMFSR): DACCVIOL Mask

  #define SCB_CFSR_IACCVIOL_Pos              (SCB_SHCSR_MEMFAULTACT_Pos + 0U)      //--- SCB CFSR (MMFSR): IACCVIOL Position
  #define SCB_CFSR_IACCVIOL_Msk              (1UL << SCB_CFSR_IACCVIOL_Pos)        //--- SCB CFSR (MMFSR): IACCVIOL Mask

  //  BusFault Status Register (part of SCB Configurable Fault Status Register)
  #define SCB_CFSR_BFARVALID_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 7U)         //--- SCB CFSR (BFSR): BFARVALID Position
  #define SCB_CFSR_BFARVALID_Msk            (1UL << SCB_CFSR_BFARVALID_Pos)        //--- SCB CFSR (BFSR): BFARVALID Mask

  #define SCB_CFSR_LSPERR_Pos               (SCB_CFSR_BUSFAULTSR_Pos + 5U)         //--- SCB CFSR (BFSR): LSPERR Position
  #define SCB_CFSR_LSPERR_Msk               (1UL << SCB_CFSR_LSPERR_Pos)           //--- SCB CFSR (BFSR): LSPERR Mask

  #define SCB_CFSR_STKERR_Pos               (SCB_CFSR_BUSFAULTSR_Pos + 4U)         //--- SCB CFSR (BFSR): STKERR Position
  #define SCB_CFSR_STKERR_Msk               (1UL << SCB_CFSR_STKERR_Pos)           //--- SCB CFSR (BFSR): STKERR Mask

  #define SCB_CFSR_UNSTKERR_Pos             (SCB_CFSR_BUSFAULTSR_Pos + 3U)         //--- SCB CFSR (BFSR): UNSTKERR Position
  #define SCB_CFSR_UNSTKERR_Msk             (1UL << SCB_CFSR_UNSTKERR_Pos)         //--- SCB CFSR (BFSR): UNSTKERR Mask

  #define SCB_CFSR_IMPRECISERR_Pos          (SCB_CFSR_BUSFAULTSR_Pos + 2U)         //--- SCB CFSR (BFSR): IMPRECISERR Position
  #define SCB_CFSR_IMPRECISERR_Msk          (1UL << SCB_CFSR_IMPRECISERR_Pos)      //--- SCB CFSR (BFSR): IMPRECISERR Mask

  #define SCB_CFSR_PRECISERR_Pos            (SCB_CFSR_BUSFAULTSR_Pos + 1U)         //--- SCB CFSR (BFSR): PRECISERR Position
  #define SCB_CFSR_PRECISERR_Msk            (1UL << SCB_CFSR_PRECISERR_Pos)        //--- SCB CFSR (BFSR): PRECISERR Mask

  #define SCB_CFSR_IBUSERR_Pos              (SCB_CFSR_BUSFAULTSR_Pos + 0U)         //--- SCB CFSR (BFSR): IBUSERR Position
  #define SCB_CFSR_IBUSERR_Msk              (1UL << SCB_CFSR_IBUSERR_Pos)          //--- SCB CFSR (BFSR): IBUSERR Mask

  //  UsageFault Status Register (part of SCB Configurable Fault Status Register)
  #define SCB_CFSR_DIVBYZERO_Pos            (SCB_CFSR_USGFAULTSR_Pos + 9U)         //--- SCB CFSR (UFSR): DIVBYZERO Position
  #define SCB_CFSR_DIVBYZERO_Msk            (1UL << SCB_CFSR_DIVBYZERO_Pos)        //--- SCB CFSR (UFSR): DIVBYZERO Mask

  #define SCB_CFSR_UNALIGNED_Pos            (SCB_CFSR_USGFAULTSR_Pos + 8U)         //--- SCB CFSR (UFSR): UNALIGNED Position
  #define SCB_CFSR_UNALIGNED_Msk            (1UL << SCB_CFSR_UNALIGNED_Pos)        //--- SCB CFSR (UFSR): UNALIGNED Mask

  #define SCB_CFSR_NOCP_Pos                 (SCB_CFSR_USGFAULTSR_Pos + 3U)         //--- SCB CFSR (UFSR): NOCP Position
  #define SCB_CFSR_NOCP_Msk                 (1UL << SCB_CFSR_NOCP_Pos)             //--- SCB CFSR (UFSR): NOCP Mask

  #define SCB_CFSR_INVPC_Pos                (SCB_CFSR_USGFAULTSR_Pos + 2U)         //--- SCB CFSR (UFSR): INVPC Position
  #define SCB_CFSR_INVPC_Msk                (1UL << SCB_CFSR_INVPC_Pos)            //--- SCB CFSR (UFSR): INVPC Mask

  #define SCB_CFSR_INVSTATE_Pos             (SCB_CFSR_USGFAULTSR_Pos + 1U)         //--- SCB CFSR (UFSR): INVSTATE Position
  #define SCB_CFSR_INVSTATE_Msk             (1UL << SCB_CFSR_INVSTATE_Pos)         //--- SCB CFSR (UFSR): INVSTATE Mask

  #define SCB_CFSR_UNDEFINSTR_Pos           (SCB_CFSR_USGFAULTSR_Pos + 0U)         //--- SCB CFSR (UFSR): UNDEFINSTR Position
  #define SCB_CFSR_UNDEFINSTR_Msk           (1UL << SCB_CFSR_UNDEFINSTR_Pos)       //--- SCB CFSR (UFSR): UNDEFINSTR Mask

  //  SCB Hard Fault Status Register Definitions
  #define SCB_HFSR_DEBUGEVT_Pos              31U                                   //--- SCB HFSR: DEBUGEVT Position
  #define SCB_HFSR_DEBUGEVT_Msk              (1UL << SCB_HFSR_DEBUGEVT_Pos)        //--- SCB HFSR: DEBUGEVT Mask

  #define SCB_HFSR_FORCED_Pos                30U                                   //--- SCB HFSR: FORCED Position
  #define SCB_HFSR_FORCED_Msk                (1UL << SCB_HFSR_FORCED_Pos)          //--- SCB HFSR: FORCED Mask

  #define SCB_HFSR_VECTTBL_Pos                1U                                   //--- SCB HFSR: VECTTBL Position
  #define SCB_HFSR_VECTTBL_Msk               (1UL << SCB_HFSR_VECTTBL_Pos)         //--- SCB HFSR: VECTTBL Mask

  //  SCB Debug Fault Status Register Definitions
  #define SCB_DFSR_EXTERNAL_Pos               4U                                   //--- SCB DFSR: EXTERNAL Position
  #define SCB_DFSR_EXTERNAL_Msk              (1UL << SCB_DFSR_EXTERNAL_Pos)        //--- SCB DFSR: EXTERNAL Mask

  #define SCB_DFSR_VCATCH_Pos                 3U                                   //--- SCB DFSR: VCATCH Position
  #define SCB_DFSR_VCATCH_Msk                (1UL << SCB_DFSR_VCATCH_Pos)          //--- SCB DFSR: VCATCH Mask

  #define SCB_DFSR_DWTTRAP_Pos                2U                                   //--- SCB DFSR: DWTTRAP Position
  #define SCB_DFSR_DWTTRAP_Msk               (1UL << SCB_DFSR_DWTTRAP_Pos)         //--- SCB DFSR: DWTTRAP Mask

  #define SCB_DFSR_BKPT_Pos                   1U                                   //--- SCB DFSR: BKPT Position
  #define SCB_DFSR_BKPT_Msk                  (1UL << SCB_DFSR_BKPT_Pos)            //--- SCB DFSR: BKPT Mask

  #define SCB_DFSR_HALTED_Pos                 0U                                   //--- SCB DFSR: HALTED Position
  #define SCB_DFSR_HALTED_Msk                (1UL << SCB_DFSR_HALTED_Pos)          //--- SCB DFSR: HALTED Mask

  //-------------------------------------------------------------------------------------------
  //    Useful Constants for angular computations
  //-------------------------------------------------------------------------------------------
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

  //-------------------------------------------------------------------------------------------
  //    Define Timing parameters
  //    QMX-32 uses the MSI 4.000 MHz Default Clock as the Oscillator
  //    The MSI Clock is phase locked to an external 32768Hz precision oscillator
  //    In turn, the main system clock is supplied by the STML32 internal PLL with a final
  //    Frequecny of 72.000 MHz.  This allows operation of the USB and System peripherals.
  //-------------------------------------------------------------------------------------------
  #define SystemCoreClock ((u32) 72000000)        //--- 72.000 MHz
  #define RTC_FREQ        ((u32) 32768)           //--- 32768 Hz
  #define LSE_FREQ        ((u32) 32768)           //--- 32768 Hz
  #define MSI_FREQ        ((u32) 4000000)         //--- 4.000 MHz
  #define SYS_FREQ        ((u32) 72000000)        //--- 72.000 MHz
  #define AHB_FREQ        ((u32) 72000000)        //--- 72.000 MHz
  #define APB1_FREQ       ((u32) 72000000)        //--- 72.000 MHz
  #define APB2_FREQ       ((u32) 72000000)        //--- 72.000 MHz

  //--- SYSCLK = (XTALOSC * 3)
  #define SYSCLK    ((u32) 72000000)              //--- System Clock 72.0000MHz
  #define AHBCLK    SYSCLK                        //--- Derived from SYSCLK
  #define PCLK1     SYSCLK                        //--- Derived from SYSCLK
  #define PCLK2     SYSCLK                        //--- Derived from SYSCLK

  //--- Define Memory Sizes
  #define RAM_SIZE    65536                       //--- 64K of RAM
  #define FLASH_SIZE  262144                      //--- 256K of Flash Memory
  #define I2C_EEPROM  8192                        //--- 8192 Bytes of EEPROM 64K Bits
  #define STACK_SIZE  4096                        //--- Stack Size = 4K By Default

  //--- Numeric Port Number Values
  //    Starting from PORT PA00 thru PORT PC15 these are numbered in sequence
  #define PA00  0x00        // 00 Decimal
  #define PA01  0x01        // 01 Decimal
  #define PA02  0x02        // 02 Decimal      //--- Also Can Be Used as USART2 TXD
  #define PA03  0x03        // 03 Decimal      //--- Also Can Be Used as USART2 RXD
  #define PA04  0x04        // 04 Decimal
  #define PA05  0x05        // 05 Decimal
  #define PA06  0x06        // 06 Decimal
  #define PA07  0x07        // 07 Decimal
  #define PA08  0x08        // 08 Decimal
  #define PA09  0x09        // 09 Decimal      //--- Also Can Be Used as USART1 TXD
  #define PA10  0x0A        // 10 Decimal      //--- Also Can Be Used as USART1 RXD
  #define PA11  0x0B        // 11 Decimal      //--- Also Can Be Used as USB DM
  #define PA12  0x0C        // 12 Decimal      //--- Also Can Be Used as USB DP
  #define PA13  0x0D        // 13 Decimal
  #define PA14  0x0E        // 14 Decimal
  #define PA15  0x0F        // 15 Decimal

  #define PB00  0x10        // 16 Decimal
  #define PB01  0x11        // 17 Decimal
  #define PB02  0x12        // 18 Decimal      //--- Unassigned in 432 Devices
  #define PB03  0x13        // 19 Decimal
  #define PB04  0x14        // 20 Decimal
  #define PB05  0x15        // 21 Decimal
  #define PB06  0x16        // 22 Decimal      //--- Also Can Be Used as I2C Data
  #define PB07  0x17        // 23 Decimal      //--- Also Can Be Used as I2C Clock

  #define PC14  0x2E        // 46 Decimal      //--- LSE Clock Input  (Allways)
  #define PC15  0x2F        // 47 Decimal      //--- Used to Drive Pacer LED (Allways)

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
