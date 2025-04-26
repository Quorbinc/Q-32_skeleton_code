//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                        Pacer Interrupt and Pacer Dependant Tasks
//
//                           Written By:  Sancar James Fredsti
//
//===========================================================================================--

#ifndef SYSTICK_H
    #define SYSTICK_H
    #define SYS_TICK_FREQ 10000

    //--- Define Test Pulse Output
    #define SYSTICK_TEST

    //--- Initialize SYS_TICK
                              //--- Point to STK_CTRL Base Address
    #define INIT_SYSTICK  asm ( "MOV    R0, #0xE010\n\t" \
                                "MOVT   R0, #0xE000\n\t" \
                                "MOV    R1, #0x0004\n\t" \
                                "MOVT   R1, #0x0000\n\t" \
                                "STR    R1, [R0]\n\t" \
                                "nop\n\t" \
                                "MOV    R0, #0xE014\n\t" \
                                "MOVT   R0, #0xE000\n\t" \
                                "MOV    R1, #0x1C1F\n\t" \
                                "MOVT   R1, #0x0000\n\t" \
                                "STR    R1, [R0]\n\t"  \
                                "nop\n\t" \
                                "MOV    R0, #0xE014\n\t" \
                                "MOVT   R0, #0xE000\n\t" \
                                "MOV    R1, #0x1C1F\n\t" \
                                "MOVT   R1, #0x0000\n\t" \
                                "STR    R1, [R0]\n\t" \
                                "nop\n\t" \
                                "MOV    R0, #0xE010\n\t" \
                                "MOVT   R0, #0xE000\n\t" \
                                "MOV    R1, #0x0007\n\t" \
                                "MOVT   R1, #0x0000\n\t" \
                                "STR    R1, [R0]\n\t" \
                                "nop\n\t" ::)

    //-------------------------------------------------------------------------------------------
    //                     Program Defines and RAM Storage Definitions
    //-------------------------------------------------------------------------------------------

    extern  u32   ulFastTimeCount[4];               //--- Handy Delay.  General Delay Timer @ 100 uSec
    extern  u64   uxSysTick;                        //--- Master Tick Timer 2^64 100 uSec Ticks

    extern  u16   uwPacerPhase;                     //--- Pacer Phase Counter
    extern  u16   uwPacerTick;                      //--- Pacer Slow Tick Count
    extern  u16   uwLEDcntr;                        //--- LED On Period
    extern  u16   uwLEDtime;                        //--- LED period time

    //-------------------------------------------------------------------------------------------
    //                          Function Prototypes & Definitions
    //    This function is called from the systick Hardware Injterrupt
    //-------------------------------------------------------------------------------------------

    void  fnInitSysTick (void);                       //--- Initialize SysTick
    void  fnSysTick(void);                        //--- IRQ_- 1 //--- From interrupts.c
    u32   fnReadFastCounter(u08 ubCntrNum);
    void  fnClearFastCounter(u08 ubCntrNum);
    void  fnSetFastCounter(u08 ubCntrNum, u32 ulDownCount);
#endif
