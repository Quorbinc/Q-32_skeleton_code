//=============================================================================================
//                                        Quorb Inc.
//                                       ------------
//
//                                Error Handeling Routines
//                               --------------------------
//
//       This code is for use on the QUORB QMX Processor Series of Micro Controllers
//
//                             Written By:  Sancar James Fredsti
//
//                                  (C) 2021 Quorb Inc
//=============================================================================================

#ifndef ERRORS_H
  #define ERRORS_H

  //--- Error Queue (FIFO) pointers & counters
  #define ERROR_QUEUE_SIZE  32

  extern    u16 volatile  uwErrIptr;
  extern    u16 volatile  uwErrOptr;
  extern    u16 volatile  uwErrCntr;

  struct ErrorS
  {
    u16   uwErrorNum;
    u32   ulTime;
  };

  //--- 32 Most Recent Error FIFO

  extern  struct ErrorS ErrFIFO [32];

  //                                              // 0  0000 = Unknown
  //                                              // 1  0001 = CORTEX CORE Error
  //                                              // 2  0010 = System Control Block
  //                                              // 3  0011 = Memory Protection Error
  //                                              // 4  0100 = FPU Error
  //                                              // 5  0101 = STACK Over/Under Flow
  //                                              // 6  0110 = Math HW (+-*\)
  //                                              // 7  0111 = Math SW Library
  //                                              // 8  1000 = Peripherial HW Error
  //                                              // 9  1001 = User SW Error
  //                                              // A  1010 = RTOS Error
  //                                              // B  1011 = NMI Fault
  //                                              // C  1100 = SysTick Error
  //                                              // D  1101 = Hard Fault Error
  //                                              // E  1110 = System Timer (SysTick) Error
  //                                              // F  1111 =

  #define NO_ERROR                    0x0000      //--- NO Error = 0x0000
  #define ERR_RTOS_SCHED_QUEUE_FULL   0xF001      //--- No Queue Slots Available
  #define ERR_RTOS_SCHED_NO_TIMER     0xF002      //--- No Timers Available

  #define UNKN_ERR          0x8000
  #define CORTEX_ERR        0x8001
  #define SCB_ERR           0x8002
  #define MEM_ERR           0x8003
  #define FPU_ERR           0x8004
  #define STK_ERR           0x8005
  #define MATH_HW_ERR       0x8006
  #define MARH_SW_ERR       0x8007
  #define PERIPH_ERR        0x8008
  #define USER_SW_ERR       0x8009
  #define RTOS_ERR          0x800A
  #define NMI_ERR           0x800B
  #define SYSTIK_ERR        0x800C
  #define HARDFAULT_ERR     0x800D
  #define OPSYS_ERR         0x800E
  #define GENERIC_ERR       0x800F

  //--- Error Quantity Counters
  extern  u16 uwCore_Errs;                        //--- CorTex Errors
  extern  u16 uwSCB_Errs;                         //--- System Control Block Errors
  extern  u16 uwSysTick_Errs;                     //--- SysTick Errors
  extern  u16 uwMemory_Errs;                      //--- Memory Errors
  extern  u16 uwFPU_Errs;                         //--- FPU Errors
  extern  u16 uwMath_Usage_Errs;                  //--- Math Usage Errors
  extern  u16 uwMath_Hardware_Errs;               //--- Math Hardware Errors
  extern  u16 uwRTOS_Errs;                        //--- RTOS Error
  extern  u16 uwSched_Errs;                       //--- Scheduling Errors
  extern  u16 uwNoTimer_Errs;                     //--- No Timers Available
  extern  u16 uwQueueFull_Errs;                   //--- Task Queue Full Errors
  extern  u16 uwDisp_Errs;                        //--- Dispatching Errors

  extern  u16 uwMath_Errs;                        //--- Number of Math Errors
  extern  u16 uwCom_Errs;                         //--- Number of Communications Errors
  extern  u16 uwUSART1_Errs;                      //--- Number of USART-1 Errors
  extern  u16 uwUSART2_Errs;                      //--- Number of USART-2 Errors
  extern  u16 uwUnkn_Errs;                        //--- Number of Unknown Errors

  void  fnError (u16 uwErrCode);                  //--- Error Function Prototype

#endif

 
