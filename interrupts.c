//=============================================================================================
//                                       Quorb Inc.
//                               -------------------------
//
//                              Interrupt Service Routines
//                              ---------------------------
//
//                           Written By:  Sancar James Fredsti
//=============================================================================================

#include  "projectdefs.h"

//--- Priority Table Flash Image Image Size = 256
u08 const ubNVIC_Ptable_Image [0x100];

//---------------------------------------------------------------------------------------------
// Interrupt Vector Table, Flash at Base Address0x00000000 Table Len = (96 + 16) * 4 = 1C8
//---------------------------------------------------------------------------------------------
__attribute__ ((section(".isr_vector"))) void (* const g_pfnVectors[]) (void) =
{
    _estack,               //--- Points to Top of Stack location in RAM  0x20010000

    //--- System Interrupts
    //    System Function Interrupt Vectors

    //--- Function_Name IRQ#  Dec  HEX     TITLE                                NVIC Table Offset
    //-------------------- ------ . ---     -------------------------           ------------
    fnReset_IRQ,           //-15 . 0xF1    Reset IRQ                            0x00000004
    fnNMI_IRQ,             //-14 . 0xF2    NMI IRQ                              0x00000008
    fnHardFault_IRQ,       //-13 . 0xF3    Hard Fault IRQ                       0x0000000C
    fnMemManage_IRQ,       //-12 . 0xF4    Memory Management Fault              0x00000010
    fnBusFault_IRQ,        //-11 . 0xF5    Bus Fault                            0x00000014
    fnIllegal_IRQ,         //-10 . 0xF6    Bad Instruction                      0x00000018

    fnNull_IRQ,            // -9 . 0xF7    Blank                                0x0000001C
    fnNull_IRQ,            // -8 . 0xF8    Blank                                0x00000020
    fnNull_IRQ,            // -7 . 0xF9    Blank                                0x00000024
    fnNull_IRQ,            // -6 . 0xFA    Blank                                0x00000028

    fnSVC_IRQ,             // -5 . 0xFB    SVCall IRQ                           0x0000002C
    fnDebug_IRQ,           // -4 . 0xFC    Debug IRQ                            0x00000030
    fnNull_IRQ,            // -3 . 0xFD    Blank                                0x00000034
    fnPendSVC_IRQ,         // -2 . 0xFE    PendSV IRQ                           0x00000038
    fnSysTick_IRQ,         // -1 . 0xFF    SysTick IRQ Non Maskable Tick        0x0000003C

    //--- Peripherial Interrupts
    fnWWDG_IRQ,            // 00 . 0x00  - Window Watchdog                      0x00000040
    fnPVD_IRQ,             // 01 . 0x01  - PVD through EXTI Line detect         0x00000044
    fnRTC_IRQ,             // 02 . 0x02  - RTC Time Stamp                       0x00000048
    fnRTC_WKUP_IRQ,        // 03 . 0x03  - RTC Wake Up                          0x0000004C
    fnFLASH_IRQ,           // 04 . 0x04  - Flash                                0x00000050

    fnRCC_IRQ,             // 05 . 0x05  - RCC                                  0x00000050
    fnEXTI_0_IRQ,          // 06 . 0x06  - EXTI Line 0                          0x00000054
    fnEXTI_1_IRQ,          // 07 . 0x07  - EXTI Line 1                          0x00000058
    fnEXTI_2_IRQ,          // 08 . 0x08  - EXTI Line 2                          0x0000005C
    fnEXTI_3_IRQ,          // 09 . 0x09  - EXTI Line 3                          0x00000060
    fnEXTI_4_IRQ,          // 10 . 0x0A  - EXTI Line 4                          0x00000068

    fnDMA_11_IRQ,          // 11 . 0x0B  - DMA1 Channel 1                       0x0000006C
    fnDMA_12_IRQ,          // 12 . 0x0C  - DMA1 Channel 2                       0x00000070
    fnDMA_13_IRQ,          // 13 . 0x0D  - DMA1 Channel 3                       0x00000074
    fnDMA_14_IRQ,          // 14 . 0x0E  - DMA1 Channel 4                       0x00000078
    fnDMA_15_IRQ,          // 15 . 0x0F  - DMA1 Channel 5                       0x0000007C
    fnDMA_16_IRQ,          // 16 . 0x10  - DMA1 Channel 6                       0x00000080
    fnDMA_17_IRQ,          // 17 . 0x11  - DMA1 Channel 7                       0x00000084

    fnADC_IRQ,             // 18 . 0x12  . 0x00  - ADC1 & ADC2                  0x00000088

    fnCAN1_TX_IRQ,         // 19 . 0x13  - CAN1 TX                              0x0000008C
    fnCAN1_RX0_IRQ,        // 20 . 0x14  - CAN1 RX0                             0x00000090
    fnCAN1_RX1_IRQ,        // 21 . 0x15  - CAN1 RX1                             0x00000094
    fnCAN1_SCE_IRQ,        // 22 . 0x16  - CAN1 SCE                             0x00000098

    fnEXTI_5_9_IRQ,        // 23 . 0x17  - EXTI Line 5_9                        0x0000009C

    fnTIM1_BK_TIM15_IRQ,   // 24 . 0x18  - TIM1 Break                           0x000000A0
    fnTIM1_UP_TIM16_IRQ,   // 25 . 0x19  - TIM1 Update                          0x000000A4
    fnTIM1_TRG_COM_IRQ,    // 26 . 0x1A  - TIM1 Trigger                         0x000000A8
    fnTIM1_CC_IRQ,         // 27 . 0x1B  - TIM1 Capture Compare                 0x000000AC

    fnTIM2_IRQ,            // 28 . 0x1C  - TIM2 Global                          0x000000B0
    fnTIM3_IRQ,            // 29 . 0x1D  - TIM3 Global                          0x000000B4
    fnTIM4_IRQ,            // 30 . 0x1E  - TIM4 Global                          0x000000B8

    fnI2C1_EV_IRQ,         // 31 . 0x1F  - I2C1 Event                           0x000000BC
    fnI2C1_ER_IRQ,         // 32 . 0x20  - I2C1 Error                           0x000000C0

    fnI2C2_EV_IRQ,         // 33 . 0x21  - I2C2 Event                           0x000000C4
    fnI2C2_ER_IRQ,         // 34 . 0x22  - I2C2 Error                           0x000000C8

    fnSPI1_IRQ,            // 35 . 0x23  - SPI1 General Interrupt               0x000000CC

    fnSPI2_IRQ,            // 36 . 0x24  - SPI2 General Interrupt               0x000000D0

    fnUSART1_IRQ,          // 37 . 0x25  - USART1 General Interrupt             0x000000D4
    fnUSART2_IRQ,          // 38 . 0x26  - USART2 General Interrupt             0x000000D8
    fnUSART3_IRQ,          // 39 . 0x27  - USART3 General Interrupt             0x000000DC

    fnEXTI_10_15_IRQ,      // 40 . 0x28  - EXTI Lines 10-15                     0x000000E0
    fnRTC_ALARM_IRQ,       // 41 . 0x29  - RTC Alarm+                           0x000000E4

    fnNull_IRQ,            // 42 . 0x2A  - Blank                                0x000000E8
    fnNull_IRQ,            // 43 . 0x2B  - Blank                                0x000000EC
    fnNull_IRQ,            // 44 . 0x2C  - Blank                                0x000000F0
    fnNull_IRQ,            // 45 . 0x2D  - Blank                                0x000000F4
    fnNull_IRQ,            // 46 . 0x2E  - Blank                                0x000000F8
    fnNull_IRQ,            // 47 . 0x2F  - Blank                                0x000000FC
    fnNull_IRQ,            // 48 . 0x30  - Blank                                0x00000100

    fnSDMMC1_IRQ,          // 49 . 0x31  - SDMMC1 IRQ                           0x00000104

    fnNull_IRQ,            // 50 . 0x32  - Blank                                0x00000108

    fnSPI3_IRQ,            // 51 . 0x33  - SPI3 General Interrupt               0x0000010C
    fnUSART4_IRQ,          // 52 . 0x34  - USART4 General Interrupt             0x00000110

    fnNull_IRQ,            // 53 . 0x35  - Blank                                0x00000114

    fnTIM6_IRQ,            // 54 . 0x36  - TIM6 Global DAC Under                0x00000118
    fnTIM7_IRQ,            // 55 . 0x37  - TIM7 Global                          0x0000011C

    fnDMA_21_IRQ,          // 56 . 0x38  - DMA1 Channel 0                       0x00000120
    fnDMA_22_IRQ,          // 57 . 0x39  - DMA1 Channel 1                       0x00000124
    fnDMA_23_IRQ,          // 58 . 0x3A  - DMA1 Channel 2                       0x00000128
    fnDMA_24_IRQ,          // 59 . 0x3B  - DMA1 Channel 3                       0x0000012C
    fnDMA_25_IRQ,          // 60 . 0x3C  - DMA1 Channel 4                       0x00000130

    fnNull_IRQ,            // 61 . 0x3D  - Blank                                0x00000134
    fnNull_IRQ,            // 62 . 0x3E  - Blank                                0x00000138
    fnNull_IRQ,            // 63 . 0x3F  - Blank                                0x0000013C

    fnCOMP_IRQ,            // 64 . 0x40  - Analog Compare                       0x00000140
    fnLPTIM1_IRQ,          // 65 . 0x41  - Low Power Timer 1                    0x00000144
    fnLPTIM2_IRQ,          // 66 . 0x42  - Low Power Timer 2                    0x00000148

    fnUSB_FS_IRQ,          // 67 . 0x43  - Full Speed USB OTG                   0x0000014C

    fnDMA_26_IRQ,          // 68 . 0x44  - DMA2 Channel 6                       0x00000150
    fnDMA_27_IRQ,          // 69 . 0x45  - DMA1 Channel 7                       0x00000154
    fnLPUART1_IRQ,         // 70 . 0x46  - Low Power UART 1                     0x00000158
    fnQUADSPI_IRQ,         // 71 . 0x47  - QUAD SPI                             0x0000015C

    fnI2C3_EV_IRQ,         // 72 . 0x48  - I2C3 Event                           0x00000160
    fnI2C3_ER_IRQ,         // 73 . 0x49  - I2C3 Error                           0x00000164
    fnSAI_IRQ,             // 74 . 0x4A  - SAI Event                            0x00000168
    fnNull_IRQ,            // 75 . 0x4B  - Blank                                0x0000016C
    fnSWPMI1_IRQ,          // 76 . 0x4C  - SWPMI1 Event                         0x00000170
    fnTSC_IRQ,             // 77 . 0x4D  - TSC Event                            0x00000174

    fnNull_IRQ,            // 78 . 0x4E  - Blank                                0x00000178
    fnNull_IRQ,            // 79 . 0x4F  - Blank                                0x0000017C

    fnRNG_IRQ,             // 80 . 0x50  - Random Number Generator              0x00000180
    fnFPU_IRQ,             // 81 . 0x51  - Floating Point Interrupt             0x00000184
    fnCRS_IRQ,             // 82 . 0x52  - CRS Interrupt                        0x00000188
    fnNull_IRQ,            // 83 . 0x53  - Blank                                0x0000018C
    fnNull_IRQ,            // 84 . 0x54  - Blank                                0x00000190
    fnNull_IRQ,            // 85 . 0x55  - Blank                                0x00000194
    fnNull_IRQ,            // 86 . 0x56  - Blank                                0x00000198
    fnNull_IRQ,            // 87 . 0x57  - Blank                                0x0000019C
    fnNull_IRQ,            // 88 . 0x58  - Blank                                0x000001A0
    fnNull_IRQ,            // 89 . 0x59  - Blank                                0x000001A4
    fnNull_IRQ,            // 90 . 0x5A  - Blank                                0x000001A8
    fnNull_IRQ,            // 91 . 0x5B  - Blank                                0x000001AC
    fnNull_IRQ,            // 92 . 0x5C  - Blank                                0x000001B0
    fnNull_IRQ,            // 93 . 0x5D  - Blank                                0x000001B4
    fnNull_IRQ,            // 94 . 0x5E  - Blank                                0x000001B8
    fnNull_IRQ,            // 95 . 0x5F  - Blank                                0x000001BC

    fnNull_IRQ,            // 96 . 0x60  - Blank                                0x000001C0
    fnNull_IRQ,            // 97 . 0x61  - Blank                                0x000001C4
    fnNull_IRQ,            // 98 . 0x62  - Blank                                0x000001C8
    fnNull_IRQ,            // 99 . 0x63  - Blank                                0x000001CC
    fnNull_IRQ,            //100 . 0x64  - Blank                                0x000001D0
    fnNull_IRQ,            //101 . 0x65  - Blank                                0x000001D4
    fnNull_IRQ,            //102 . 0x66  - Blank                                0x000001D8
    fnNull_IRQ,            //103 . 0x67  - Blank                                0x000001DC
    fnNull_IRQ,            //104 . 0x68  - Blank                                0x000001E0
    fnNull_IRQ,            //105 . 0x69  - Blank                                0x000001E4
    fnNull_IRQ,            //106 . 0x6A  - Blank                                0x000001E8
    fnNull_IRQ,            //107 . 0x6B  - Blank                                0x000001EC
    fnNull_IRQ,            //108 . 0x6C  - Blank                                0x000001F0
    fnNull_IRQ,            //109 . 0x6D  - Blank                                0x000001F4
    fnNull_IRQ,            //110 . 0x6E  - Blank                                0x000001F8
    fnNull_IRQ,            //111 . 0x6F  - Blank                                0x000001FC

    fnNull_IRQ,            //112 . 0x70  - Blank                                0x00000200
    fnNull_IRQ,            //113 . 0x71  - Blank                                0x00000204
    fnNull_IRQ,            //114 . 0x72  - Blank                                0x00000208
    fnNull_IRQ,            //115 . 0x73  - Blank                                0x0000020C
    fnNull_IRQ,            //116 . 0x74  - Blank                                0x00000210
    fnNull_IRQ,            //117 . 0x75  - Blank                                0x00000214
    fnNull_IRQ,            //118 . 0x76  - Blank                                0x00000218
    fnNull_IRQ,            //119 . 0x77  - Blank                                0x0000021C
    fnNull_IRQ,            //120 . 0x78  - Blank                                0x00000220
    fnNull_IRQ,            //121 . 0x79  - Blank                                0x00000224
    fnNull_IRQ,            //122 . 0x7A  - Blank                                0x00000228
    fnNull_IRQ,            //123 . 0x7B  - Blank                                0x0000022C
    fnNull_IRQ,            //124 . 0x7C  - Blank                                0x00000230
    fnNull_IRQ,            //125 . 0x7D  - Blank                                0x00000234
    fnNull_IRQ,            //126 . 0x7E  - Blank                                0x00000238
    fnNull_IRQ,            //127 . 0x7F  - Blank                                0x0000023C

    fnNull_IRQ,            //128 . 0x80  - Blank                                0x00000240
    fnNull_IRQ,            //129 . 0x81  - Blank                                0x00000244
    fnNull_IRQ,            //130 . 0x82  - Blank                                0x00000248
    fnNull_IRQ,            //131 . 0x83  - Blank                                0x0000024C
    fnNull_IRQ,            //132 . 0x84  - Blank                                0x00000250
    fnNull_IRQ,            //133 . 0x85  - Blank                                0x00000254
    fnNull_IRQ,            //134 . 0x86  - Blank                                0x00000258
    fnNull_IRQ,            //135 . 0x87  - Blank                                0x0000025C
    fnNull_IRQ,            //136 . 0x88  - Blank                                0x00000260
    fnNull_IRQ,            //137 . 0x89  - Blank                                0x00000264
    fnNull_IRQ,            //138 . 0x8A  - Blank                                0x00000268
    fnNull_IRQ,            //139 . 0x8B  - Blank                                0x0000026C
    fnNull_IRQ,            //140 . 0x8C  - Blank                                0x00000270
    fnNull_IRQ,            //141 . 0x8D  - Blank                                0x00000274
    fnNull_IRQ,            //142 . 0x8E  - Blank                                0x00000278
    fnNull_IRQ,            //143 . 0x8F  - Blank                                0x0000027C

    fnNull_IRQ,            //144 . 0x90  - Blank                                0x00000280
    fnNull_IRQ,            //145 . 0x91  - Blank                                0x00000284
    fnNull_IRQ,            //146 . 0x92  - Blank                                0x00000288
    fnNull_IRQ,            //147 . 0x93  - Blank                                0x0000028C
    fnNull_IRQ,            //148 . 0x94  - Blank                                0x00000290
    fnNull_IRQ,            //149 . 0x95  - Blank                                0x00000294
    fnNull_IRQ,            //150 . 0x96  - Blank                                0x00000298
    fnNull_IRQ,            //151 . 0x97  - Blank                                0x0000029C
    fnNull_IRQ,            //152 . 0x98  - Blank                                0x000002A0
    fnNull_IRQ,            //153 . 0x99  - Blank                                0x000002A4
    fnNull_IRQ,            //154 . 0x9A  - Blank                                0x000002A8
    fnNull_IRQ,            //155 . 0x9B  - Blank                                0x000002AC
    fnNull_IRQ,            //156 . 0x9C  - Blank                                0x000002B0
    fnNull_IRQ,            //157 . 0x9D  - Blank                                0x000002B4
    fnNull_IRQ,            //158 . 0x9E  - Blank                                0x000002B8
    fnNull_IRQ,            //159 . 0x9F  - Blank                                0x000002BC

    fnNull_IRQ,            //160 . 0xA0  - Blank                                0x000002C0
    fnNull_IRQ,            //161 . 0xA1  - Blank                                0x000002C4
    fnNull_IRQ,            //162 . 0xA2  - Blank                                0x000002C8
    fnNull_IRQ,            //163 . 0xA3  - Blank                                0x000002CC
    fnNull_IRQ,            //164 . 0xA4  - Blank                                0x000002D0
    fnNull_IRQ,            //165 . 0xA5  - Blank                                0x000002D4
    fnNull_IRQ,            //166 . 0xA6  - Blank                                0x000002D8
    fnNull_IRQ,            //167 . 0xA7  - Blank                                0x000002DC
    fnNull_IRQ,            //168 . 0xA8  - Blank                                0x000002E0
    fnNull_IRQ,            //169 . 0xA9  - Blank                                0x000002E4
    fnNull_IRQ,            //170 . 0xAA  - Blank                                0x000002E8
    fnNull_IRQ,            //171 . 0xAB  - Blank                                0x000002EC
    fnNull_IRQ,            //172 . 0xAC  - Blank                                0x000002F0
    fnNull_IRQ,            //173 . 0xAD  - Blank                                0x000002F4
    fnNull_IRQ,            //174 . 0xAE  - Blank                                0x000002F8
    fnNull_IRQ,            //175 . 0xAF  - Blank                                0x000002FC

    fnNull_IRQ,            //176 . 0xB0  - Blank                                0x00000300
    fnNull_IRQ,            //177 . 0xB1  - Blank                                0x00000304
    fnNull_IRQ,            //178 . 0xB2  - Blank                                0x00000308
    fnNull_IRQ,            //179 . 0xB3  - Blank                                0x0000030C
    fnNull_IRQ,            //180 . 0xB4  - Blank                                0x00000310
    fnNull_IRQ,            //181 . 0xB5  - Blank                                0x00000314
    fnNull_IRQ,            //182 . 0xB6  - Blank                                0x00000318
    fnNull_IRQ,            //183 . 0xB7  - Blank                                0x0000031C
    fnNull_IRQ,            //184 . 0xB8  - Blank                                0x00000320
    fnNull_IRQ,            //185 . 0xB9  - Blank                                0x00000324
    fnNull_IRQ,            //186 . 0xBA  - Blank                                0x00000328
    fnNull_IRQ,            //187 . 0xBB  - Blank                                0x0000032C
    fnNull_IRQ,            //188 . 0xBC  - Blank                                0x00000330
    fnNull_IRQ,            //189 . 0xBD  - Blank                                0x00000334
    fnNull_IRQ,            //190 . 0xBE  - Blank                                0x00000338
    fnNull_IRQ,            //191 . 0xBF  - Blank                                0x0000033C

    fnNull_IRQ,            //192 . 0xC0  - Blank                                0x00000340
    fnNull_IRQ,            //193 . 0xC1  - Blank                                0x00000344
    fnNull_IRQ,            //194 . 0xC2  - Blank                                0x00000348
    fnNull_IRQ,            //195 . 0xC3  - Blank                                0x0000034C
    fnNull_IRQ,            //196 . 0xC4  - Blank                                0x00000350
    fnNull_IRQ,            //197 . 0xC5  - Blank                                0x00000354
    fnNull_IRQ,            //198 . 0xC6  - Blank                                0x00000358
    fnNull_IRQ,            //199 . 0xC7  - Blank                                0x0000035C
    fnNull_IRQ,            //200 . 0xC8  - Blank                                0x00000360
    fnNull_IRQ,            //201 . 0xC9  - Blank                                0x00000364
    fnNull_IRQ,            //202 . 0xCA  - Blank                                0x00000368
    fnNull_IRQ,            //203 . 0xCB  - Blank                                0x0000036C
    fnNull_IRQ,            //204 . 0xCC  - Blank                                0x00000370
    fnNull_IRQ,            //205 . 0xCD  - Blank                                0x00000374
    fnNull_IRQ,            //206 . 0xCE  - Blank                                0x00000378
    fnNull_IRQ,            //207 . 0xCF  - Blank                                0x0000037C

    fnNull_IRQ,            //208 . 0xD0  - Blank                                0x00000380
    fnNull_IRQ,            //209 . 0XD1  - Blank                                0x00000384
    fnNull_IRQ,            //210 . 0xD2  - Blank                                0x00000388
    fnNull_IRQ,            //211 . 0xD3  - Blank                                0x0000038C
    fnNull_IRQ,            //212 . 0xD4  - Blank                                0x00000390
    fnNull_IRQ,            //213 . 0xD5  - Blank                                0x00000394
    fnNull_IRQ,            //214 . 0xD6  - Blank                                0x00000398
    fnNull_IRQ,            //215 . 0xD7  - Blank                                0x0000039C
    fnNull_IRQ,            //216 . 0xD8  - Blank                                0x000003A0
    fnNull_IRQ,            //217 . 0xD9  - Blank                                0x000003A4
    fnNull_IRQ,            //218 . 0xDA  - Blank                                0x000003A8
    fnNull_IRQ,            //229 . 0xDB  - Blank                                0x000003AC
    fnNull_IRQ,            //220 . 0xDC  - Blank                                0x000003B0
    fnNull_IRQ,            //221 . 0xDD  - Blank                                0x000003B4
    fnNull_IRQ,            //222 . 0xDE  - Blank                                0x000003B8
    fnNull_IRQ,            //223 . 0xDF  - Blank                                0x000003BC

    fnNull_IRQ,            //224 . 0xE0  - Blank                                0x000003C0
    fnNull_IRQ,            //225 . 0xE1  - Blank                                0x000003C4
    fnNull_IRQ,            //226 . 0xE2  - Blank                                0x000003C8
    fnNull_IRQ,            //227 . 0xE3  - Blank                                0x000003CC
    fnNull_IRQ,            //228 . 0xE4  - Blank                                0x000003D0
    fnNull_IRQ,            //229 . 0xE5  - Blank                                0x000003D4
    fnNull_IRQ,            //230 . 0xE6  - Blank                                0x000003D8
    fnNull_IRQ,            //231 . 0xE7  - Blank                                0x000003DC
    fnNull_IRQ,            //232 . 0xE8  - Blank                                0x000003E0
    fnNull_IRQ,            //233 . 0xE9  - Blank                                0x000003E4
    fnNull_IRQ,            //234 . 0xEA  - Blank                                0x000003E8
    fnNull_IRQ,            //235 . 0xEB  - Blank                                0x000003EC
    fnNull_IRQ,            //236 . 0xEC  - Blank                                0x000003F0
    fnNull_IRQ,            //237 . 0xED  - Blank                                0x000003F4
    fnNull_IRQ,            //238 . 0xEE  - Blank                                0x000003F8
    fnNull_IRQ,            //239 . 0xEF  - Blank                                0x000003FC

    //--- NOTE! Table Wraps back to Top for Negative IRQ Numbers 0xF0 to 0xFF
};

//---------------------------------------------------------------------------------------------
//                    Initialize Interrupt Structure and NVIC Registers
//---------------------------------------------------------------------------------------------

void  fnInitNVIC (void)
{
    u16   uwA;                                      //--- Work Word
    u08   ubA;                                      //--- Work Byte
    u08   ubP;

    GID;                                            //--- Kill All Interrupts

    SCB_AIRCR = 0x05FA0000;                         //--- Reset NVIC to no priority grouping.  Reads Back as 0xFA05

    //--- First Initialize All Priority Registers & Enable Interrupts Byte by Byte
    //    Note: Priority Level of 0 = Interrupt OFF
    for (uwA = 0; uwA < 128; uwA++)
    {
        ubA = ubNVIC_Ptable_Image[uwA];               //--- Get Interrupt Priority and Enable
        ubP = ubA & 0x0F;                             //--- Filter Table Entry for Priority
        fnSetIntPriority (uwA, ubP);                  //--- Set Priority in NVIC Table
    }

    GIE;                                            //--- Restore Interrrupt Enable
}

//---------------------------------------------------------------------------------------------
//--- Note: Priority Level of 0 = Interrupt OFF
//
//    Interrupt Priority Table is defined for all 256 Possible Interrupt Numbers
//
//    Interrupts IRQn # 0 to 239 are at top of table
//    Interrupts with offsets of -1 to -15 are located
//    at bottom of table in reverse order ie.  -1 = 0xFF and -15 = 0xF0
//
//    Lowest Priority = 15  Highest Priority = 1  Off = 0
//---------------------------------------------------------------------------------------------

const u08 ubNVIC_Ptable_Image [0x100] =
{
    //Int0-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //Int1-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //Int2-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15, 7,15,15,15,15,15,15,15,15,15,

    //Int3-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //Int4-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //Int5-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //Int6-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //Int7-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //Int8-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //Int9-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //IntA-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //IntB-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //IntC-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //IntD-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //IntE-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,

    //Int-0  0 -F -E -D -C -B -A -9 -8 -7 -6 -5 -4 -3 -2 -1
    //IntF-  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
            15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15
};


//=============================================================================================
//    Interrupt Handeling Functions
//=============================================================================================


//---------------------------------------------------------------------------------------------
//  Function Name  : Do Nothing IRQ
//---------------------------------------------------------------------------------------------
void fnNull_IRQ(void)                           //--- IRQ_XX
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : Do Nothing IRQ Service
//---------------------------------------------------------------------------------------------
void fnNMI_IRQ(void)                            //--- IRQ_-14
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : HardFaultException Error
//---------------------------------------------------------------------------------------------
void fnHardFault_IRQ(void)                      //--- IRQ_-13
{
    GID;                                          //--- Kill Interrupts

    //--- Enter Endless Loop Pulsing PB03, PB04, PB05
    while (1)
    {
        SET_PB03;
        SET_PB04;
        SET_PB05;
        nop16;
        CLR_PB03;
        CLR_PB04;
        CLR_PB05;
        nop16;
        nop16;
    }
}

//---------------------------------------------------------------------------------------------
//  Function Name  : Memory Manager
//---------------------------------------------------------------------------------------------
void fnMemManage_IRQ(void)                      //--- IRQ_-12
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : BusFault
//---------------------------------------------------------------------------------------------
void fnBusFault_IRQ(void)                       //--- IRQ_-11
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : Illegal Instruction
//---------------------------------------------------------------------------------------------
void fnIllegal_IRQ(void)                        //--- IRQ_-10
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//   UnUsed NVIC Table Entries                  //--- IRQ_ -9, -8, -7, -6
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//  Function Name  : SVCIRQ
//  -----------------------
//  Up to 256 individual SVC Request Types can be executed The first 16 are covered here
//  SVC Calls are automaticall raised to CPU Privileged State.
//
//  SVC Call Type Code is placed in ubSVCn prior to the actual call code
//---------------------------------------------------------------------------------------------


void fnSVC_IRQ(void)                            //--- IRQ # -5
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : Debugger
//---------------------------------------------------------------------------------------------
void fnDebug_IRQ(void)                          //--- IRQ_ -4
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//   UnUsed NVIC Table Entriy                   //--- IRQ_ -3
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//  Function Name  : Pending SVC Interrupt Request
//---------------------------------------------------------------------------------------------
void fnPendSVC_IRQ(void)                        //--- IRQ_ -2
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : SysTickIRQ This function MUST be defined for RTOS
//  Typically this function runs at 1mSec to 0.1 mSec This is a VERY High priority
//---------------------------------------------------------------------------------------------
void fnSysTick_IRQ(void)                        //--- IRQ_- 1
{
    #ifdef SYSTICK_TEST
        //--- Set Test Pulse Hi   OUTPUT PB03
        SET_PB03;                                     //--- Pacer Test Pulse Hi
    #endif

    fnSysTick();                                  //--- Call the SysTick Interrupt Handler

    #ifdef SYSTICK_TEST
        //--- Clr Pulse Hi   OUTPUT PB03
        CLR_PB03;                                     //--- Pacer Test Pulse Hi
    #endif
}

//=============================================================================================
//    Maskable Hardware Interrupt Service Routines
//=============================================================================================

//---------------------------------------------------------------------------------------------
//  Function Name  : WWDG_IRQ
//---------------------------------------------------------------------------------------------
void fnWWDG_IRQ(void)                           //--- IRQ_00
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : PVD_IRQ
//---------------------------------------------------------------------------------------------
void fnPVD_IRQ(void)                            //--- IRQ_01
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : RTC_IRQ
//---------------------------------------------------------------------------------------------
void fnRTC_IRQ(void)                            //--- IRQ_02
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : RTC Wakeup
//---------------------------------------------------------------------------------------------
void fnRTC_WKUP_IRQ(void)                       //--- IRQ_03
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : FLASH_IRQ
//---------------------------------------------------------------------------------------------
void fnFLASH_IRQ(void)                          //--- IRQ_04
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : RCC_IRQ
//---------------------------------------------------------------------------------------------
void fnRCC_IRQ(void)                            //--- IRQ_05
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : EXTI0_IRQ
//---------------------------------------------------------------------------------------------
void fnEXTI_0_IRQ(void)                         //--- IRQ_06
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : EXTI1_IRQ
//---------------------------------------------------------------------------------------------
void fnEXTI_1_IRQ(void)                         //--- IRQ_07
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : EXTI0_IRQ
//---------------------------------------------------------------------------------------------
void fnEXTI_2_IRQ(void)                         //--- IRQ_08
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : EXTI0_IRQ
//---------------------------------------------------------------------------------------------
void fnEXTI_3_IRQ(void)                         //--- IRQ_09
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : EXTI2_IRQ
//---------------------------------------------------------------------------------------------
void fnEXTI_4_IRQ(void)                         //--- IRQ_10
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  DMA #1 Channel 1
//---------------------------------------------------------------------------------------------
void fnDMA_11_IRQ(void)                         //--- IRQ_11
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  DMA #1 Channel 2
//---------------------------------------------------------------------------------------------
void fnDMA_12_IRQ(void)                         //--- IRQ_12
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  DMA #1 Channel 3
//---------------------------------------------------------------------------------------------
void fnDMA_13_IRQ(void)                         //--- IRQ_13
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  DMA #1 Channel 4
//---------------------------------------------------------------------------------------------
void fnDMA_14_IRQ(void)                         //--- IRQ_14
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  DMA #1 Channel 5
//---------------------------------------------------------------------------------------------
void fnDMA_15_IRQ(void)                         //--- IRQ_15
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  DMA #1 Channel 6
//---------------------------------------------------------------------------------------------
void fnDMA_16_IRQ(void)                         //--- IRQ_16
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  DMA #1 Channel 7
//---------------------------------------------------------------------------------------------
void fnDMA_17_IRQ(void)                         //--- IRQ_17
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : ADC_IRQ
//---------------------------------------------------------------------------------------------
void fnADC_IRQ(void)                            //--- IRQ_18
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : CAN1_TX
//---------------------------------------------------------------------------------------------
void fnCAN1_TX_IRQ(void)                        //--- IRQ_19
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : CAN1_RX0
//---------------------------------------------------------------------------------------------
void fnCAN1_RX0_IRQ(void)                       //--- IRQ_20
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : CAN1_RX1
//---------------------------------------------------------------------------------------------
void fnCAN1_RX1_IRQ(void)                       //--- IRQ_21
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : CAN1_SCE
//---------------------------------------------------------------------------------------------
void fnCAN1_SCE_IRQ(void)                       //--- IRQ_22
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : EXTI_5_9
//---------------------------------------------------------------------------------------------
void fnEXTI_5_9_IRQ(void)                       //--- IRQ_23
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : TIM1_BK_TIM15_IRQ
//---------------------------------------------------------------------------------------------
void fnTIM1_BK_TIM15_IRQ(void)                  //--- IRQ_24
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : TIM1_UP_TIM16_IRQ
//---------------------------------------------------------------------------------------------
void fnTIM1_UP_TIM16_IRQ(void)                  //--- IRQ_25
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : TIM1_TRG_COM_IRQ
//---------------------------------------------------------------------------------------------
void fnTIM1_TRG_COM_IRQ(void)                   //--- IRQ_26
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : TIM1_CC_IRQ
//---------------------------------------------------------------------------------------------
void fnTIM1_CC_IRQ(void)                        //--- IRQ_27
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : TIM2_IRQ
//---------------------------------------------------------------------------------------------
void fnTIM2_IRQ(void)                           //--- IRQ_28
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : TIM3_IRQ
//---------------------------------------------------------------------------------------------
void fnTIM3_IRQ(void)                           //--- IRQ_29
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : TIM4_IRQ
//---------------------------------------------------------------------------------------------
void fnTIM4_IRQ(void)                           //--- IRQ_30
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : I2C1_EV_IRQ I2C1 Event
//---------------------------------------------------------------------------------------------
void fnI2C1_EV_IRQ(void)                        //--- IRQ_31
{
  //fnI2C1_Event();
}

//---------------------------------------------------------------------------------------------
//  Function Name  : I2C1_ER_IRQ
//---------------------------------------------------------------------------------------------
void fnI2C1_ER_IRQ(void)                        //--- IRQ_32
{
  //fnI2C1_Error();
}

//---------------------------------------------------------------------------------------------
//  Function Name  : I2C1_EV_IRQ
//---------------------------------------------------------------------------------------------
void fnI2C2_EV_IRQ(void)                        //--- IRQ_33
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : I2C1_EV_IRQ
//---------------------------------------------------------------------------------------------
void fnI2C2_ER_IRQ(void)                        //--- IRQ_34
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : SPI1_IRQ
//---------------------------------------------------------------------------------------------
void fnSPI1_IRQ(void)                           //--- IRQ_35
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : SPI2_IRQ
//---------------------------------------------------------------------------------------------
void  fnSPI2_IRQ(void)                          //--- IRQ_36
{
    //--- insert code if needed.
}

//-------------------------------------------------------------------------------------------
//  Function Name  : USART_1 Rx Interrupt Handler
//
//  After initialization, any data sent to USART1 is captured and stored in a FIFO buffer
//  The FIFO Pointers, Counters and Status flags are automatically handled by the Interrupt
//-------------------------------------------------------------------------------------------

void  fnUSART1_IRQ(void)     // 37 - USART1 General Interrupt              0x000000D4
{
    #ifdef USART1_FLAG
        fnUsart1_Recieve();
    #endif
}


//-------------------------------------------------------------------------------------------
//  Function Name  : USART_2 Rx Interrupt Handler //--- 38 - USART2 General Interrupt
//-------------------------------------------------------------------------------------------
void  fnUSART2_IRQ(void)
{
    #ifdef USART2_FLAG
        fnUsart2_Recieve();
    #endif
}

//---------------------------------------------------------------------------------------------
//  Function Name  : USART3_IRQ  Defined in UART_COM Source & Header Files
//---------------------------------------------------------------------------------------------
void fnUSART3_IRQ(void)                         //--- IRQ_39
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : EXTI_10_15_IRQ
//---------------------------------------------------------------------------------------------
void fnEXTI_10_15_IRQ(void)                     //--- IRQ_40
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : RTC_ALARM_IRQ
//---------------------------------------------------------------------------------------------
void fnRTC_ALARM_IRQ(void)                      //--- IRQ_41
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//   UnUsed NVIC Table Entries                  //--- IRQ_- 42 to 48
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//  Function Name  :
//---------------------------------------------------------------------------------------------
void fnSDMMC1_IRQ(void)                         //--- IRQ_49
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//   UnUsed NVIC Table Entries                  //--- IRQ_50
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//  Function Name  :
//---------------------------------------------------------------------------------------------
void fnSPI3_IRQ(void)                           //--- IRQ_51
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : USART4_IRQ  Defined in UART_COM Source & Header Files
//---------------------------------------------------------------------------------------------
void fnUSART4_IRQ(void)                         //--- IRQ_52
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//   UnUsed NVIC Table Entries                  //--- IRQ_53
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//  Function Name  :
//---------------------------------------------------------------------------------------------
void fnTIM6_IRQ(void)                           //--- IRQ_54
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  :
//---------------------------------------------------------------------------------------------
void fnTIM7_IRQ(void)                           //--- IRQ_55
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  :
//---------------------------------------------------------------------------------------------
void  fnDMA_21_IRQ(void)                        //--- IRQ_56
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  :
//---------------------------------------------------------------------------------------------
void  fnDMA_22_IRQ(void)                        //--- IRQ_57
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  :
//---------------------------------------------------------------------------------------------
void  fnDMA_23_IRQ(void)                        //--- IRQ_58
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  :
//---------------------------------------------------------------------------------------------
void  fnDMA_24_IRQ(void)                        //--- IRQ_59
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  :
//---------------------------------------------------------------------------------------------
void  fnDMA_25_IRQ(void)                        //--- IRQ_60
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : Unused IRQ 61, 62, 63
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//  Function Name  : COMParator IRQ
//---------------------------------------------------------------------------------------------
void fnCOMP_IRQ(void)                           //--- IRQ_64
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : LPTIM1 IRQ
//---------------------------------------------------------------------------------------------
void fnLPTIM1_IRQ(void)                         //--- IRQ_65
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : LPTIM2 IRQ
//---------------------------------------------------------------------------------------------
void fnLPTIM2_IRQ(void)                         //--- IRQ_66
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : USB Full Speed IRQ
//---------------------------------------------------------------------------------------------
void fnUSB_FS_IRQ(void)                         //--- IRQ_67
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : DMA_26_IRQ
//---------------------------------------------------------------------------------------------
void fnDMA_26_IRQ(void)                         //--- IRQ_68
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : DMA_27_IRQ
//---------------------------------------------------------------------------------------------
void fnDMA_27_IRQ(void)                         //--- IRQ_69
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : Low Power UART 1
//---------------------------------------------------------------------------------------------
void fnLPUART1_IRQ(void)                        //--- IRQ_70
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : QUAD SPI
//---------------------------------------------------------------------------------------------
void fnQUADSPI_IRQ(void)                        //--- IRQ_71
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : I2C3 Event
//---------------------------------------------------------------------------------------------
void fnI2C3_EV_IRQ(void)                        //--- IRQ_72
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : I2C3 Error
//---------------------------------------------------------------------------------------------
void fnI2C3_ER_IRQ(void)                        //--- IRQ_73
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : SAI Event
//---------------------------------------------------------------------------------------------
void fnSAI_IRQ(void)                            //--- IRQ_74
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : Unused                     //--- IRQ 75
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//  Function Name  : SWPMI1 Event
//---------------------------------------------------------------------------------------------
void fnSWPMI1_IRQ(void)                         //--- IRQ_76
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : TSC Event
//---------------------------------------------------------------------------------------------
void fnTSC_IRQ(void)                            //--- IRQ_77
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : Unused                     //--- IRQ 78, 79
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//  Function Name  : Random Number Generator
//---------------------------------------------------------------------------------------------
void fnRNG_IRQ(void)                            //--- IRQ_80
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : Floating Point Processor
//---------------------------------------------------------------------------------------------
void fnFPU_IRQ(void)                            //--- IRQ_81
{
    //--- insert code if needed.
}

//---------------------------------------------------------------------------------------------
//  Function Name  : CRS Event
//---------------------------------------------------------------------------------------------
void fnCRS_IRQ(void)                            //--- IRQ_82
{
    //--- insert code if needed.
}

//=============================================================================================
//    Functions for interrupt Controller
//=============================================================================================

//---------------------------------------------------------------------------------------------
//    Enable Individual Interrupts  (0 to 96) (97 Total Interrupts)
//---------------------------------------------------------------------------------------------
void  fnEnaInt (u16 uwIntNum)
{
    GID;                                            //--- Kill Other Interrupts
    NVIC_EnableIRQ(uwIntNum);
    GIE;                                            //--- Enable Other Interrupts
}

//---------------------------------------------------------------------------------------------
//    Disable Individual Interrupt (0 to 96)
//---------------------------------------------------------------------------------------------
void  fnDisInt (u16 uwIntNum)
{
    GID;                                            //--- Kill Other Interrupts
    NVIC_EnableIRQ(uwIntNum);
    GIE;                                            //--- Enable Other Interrupts
}


//---------------------------------------------------------------------------------------------
//    Set an Interrupt Bit in the Interrupts Mask
//---------------------------------------------------------------------------------------------
void  fnSetIntPend (u16 uwIntNum)
{
    GID;                                            //--- Kill Other Interrupts
    NVIC_DisableIRQ(uwIntNum);
    GIE;                                            //--- Enable Other Interrupts
}

//---------------------------------------------------------------------------------------------
//    Clear an Interrupt Bit in the Interrupts Pending Mask
//---------------------------------------------------------------------------------------------
void  fnClrIntPend (u16 uwIntNum)
{
    GID;                                            //--- Kill Other Interrupts
    NVIC_ClearPendingIRQ(uwIntNum);
    GIE;                                            //--- Enable Other Interrupts
}

//---------------------------------------------------------------------------------------------
//    Set Interrupt Priority in the Interrupts Mask
//
//    uwIntNum = Interrupt Number (0 . 0x00  - 96)
//    ubPri = Priority Level (0 . 0x00  - 15) Higher Number = Weaker priority
//---------------------------------------------------------------------------------------------
void  fnSetIntPriority (u16 uwIntNum, u08 ubPri)
{
    GID;
    NVIC_SetPriority(uwIntNum, ubPri);
    GIE;
}
