//============================================================================================
//                                        QUORB Inc.
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

  //-------------------------------------------------------------------------------------------
  //--- Define System Clock Values Here
  //-------------------------------------------------------------------------------------------
  //    See Project Defs
  //
  //  System Normally operates from HSI16 Clock
  //  #define sfCPU_FREQ = (flt)80000000.0           /1
  //  #define sfAHB_CLK =  (flt)80000000.0           /1
  //  #define sfAHB_TCLK = (flt)80000000.0           /1
  //
  //  #define sfAPB1_CLK = (flt)80000000.0           /1
  //  #define sfAPB2_CLK = (flt)80000000.0           /1
  //

  extern  u32     ulT;
  extern  u16     uwReturnVal;

  //--- Function Prototypes
  void  fnReset_IRQ(void);

#endif
