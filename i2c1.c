//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                          I2C Interface Functions Processing Code
//                          ---------------------------------------
//
//    This code is for use on the STM32L432 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32FXXX Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//         Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#include "projectdefs.h"

//---------------------------------------------------------------------------------------------
//                    Initialize I2C1 Interface #1 As Master Mode
//
//    ubSpeed = I2C Speed Value
//              0x00 = 100 KHz      //--- Standard Speed @ 100 KHz    1 TXBYTE Time = 90 uSec
//              0x01 = 400 KHz      //--- Typical I2C Clock = 400 KHz 1 TXBYTE Time = 45 uSec
//              0x02 = 1   MHz      //--- Fast I2C                    1 TxByte Time =  9 uSec
//              0x03 = 100 KHz      //--- Default
//
//--- I2C Runs from HSI Clock at 16 MHz
//
//    I2C Register Map
//    ----------------
//    #define I2C1_CR1              *(vu32 *)(I2C1_BASE + I2C_CR1_O)
//    #define I2C1_CR2              *(vu32 *)(I2C1_BASE + I2C_CR2_O)
//    #define I2C1_OAR1             *(vu32 *)(I2C1_BASE + I2C_OAR1_O)
//    #define I2C1_OAR2             *(vu32 *)(I2C1_BASE + I2C_OAR2_O)
//    #define I2C1_TIMING           *(vu32 *)(I2C1_BASE + I2C_TIMING_O)
//    #define I2C1_TIMEOUT          *(vu32 *)(I2C1_BASE + I2C_TIMEOUT_O)
//    #define I2C1_ISR              *(vu32 *)(I2C1_BASE + I2C_ISR_O)
//    #define I2C1_ICR              *(vu32 *)(I2C1_BASE + I2C_ICR_O)
//    #define I2C1_PECR             *(vu32 *)(I2C1_BASE + I2C_PECR_O)
//    #define I2C1_RXDR             *(vu32 *)(I2C1_BASE + I2C_RXDR_O)
//    #define I2C1_TXDR             *(vu32 *)(I2C1_BASE + I2C_TXDR_O)
//---------------------------------------------------------------------------------------------

//--- Define the DEBUG Method
// #define I2C1DEBUG

//--- Defined in "commonheader.h"
//  union DFLWB16                     //--- 32 Bytes Variable
//    {
//      dbl   dfFlt[2];               //--- 4 Double Precision Float
//      u64   uxBig[2];               //--- 4 Unsigned 64 Bit Integer
//      s64   sxBig[2];               //--- 4 Signed 64 Bit Integer
//      flt   sfFlt[4];               //--- 8 Single Precision Floats
//      u32   ulLong[4];              //--- 8 Unsigned Long
//      s32   slLong[4];              //--- 8 Signed Long
//      u16   uwWord[8];              //--- 16 Unsigned Words
//      s16   swWord[8];              //--- 16 Signed Words
//      u08   ubByte[16];             //--- 32 Unsigned Bytes
//      s08   sbByte[16];             //--- 32 Signed Bytes
//      u08*  ubPtr[4];               //--- 8 General Purpose Pointers (byte)
//      void* vPntr[4];               //--- 8 Void Type Pointers
//    };

//---------------------------------------------------------------------------------------------
//    Initialize I2C1 for 400 KHz as Master
//
//    Init Configuration:
//    1.  Port Pins:  PB06 as SCL signal
//    2.  Port Pin:   PB07 as SDA signal
//    3.  I2C Drive Clock = HSI-16MHz
//    4.  SCL Speed: 0 = 100 KHz, 1 = 400 KHz  2 = 1 MHz
//---------------------------------------------------------------------------------------------

u08   ubI2C1_TXB [I2C1_BLEN];                     //--- Global TX FIFO Buffer

u16   uwI2C1_TXIP;                                //--- FIFO In Pointer
u16   uwI2C1_TXOP;                                //--- FIFO In Pointer
u16   uwI2C1_TXC;                                 //--- FIFO In Pointer

u08   ubI2C1_RXB [I2C1_BLEN];                     //--- Global RX FIFO Buffer

u16   uwI2C1_RXIP;                                //--- FIFO In Pointer
u16   uwI2C1_RXOP;                                //--- FIFO In Pointer
u16   uwI2C1_RXC;                                 //--- FIFO In Pointer

// u16   uwI2C1_TX_Count;

//--- Driver Data Pointers
u08*  ubI2C1_TXptr;                               //--- Tx Data Pointer
u08*  ubI2C1_RXptr;                               //--- Rx Data Pointer


//---------------------------------------------------------------------------------------------
//  Test for and Retrive Next Byte from I2C1_RX FIFO Buffer
//---------------------------------------------------------------------------------------------
u16   fnI2C1_Get_Next_RX (void)
{
    union WB unRetU;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- If Counter > 0 then extract Next Byte of Data
    if (uwI2C1_RXC > 0)
    {
        unRetU.ubByte[0] = ubI2C1_RXB[uwI2C1_RXOP];   //--- Lo Byte = Data
        unRetU.ubByte[1] = 0x80;                      //--- Hi Byte = Flag 80 Bit
        uwI2C1_RXC--;                                 //--- Decrement Counter
        uwI2C1_RXOP++;                                //--- Adjust Out Pointer
        uwI2C1_RXOP %= I2C1_BLEN;
        return unRetU.uwWord;                         //--- Return Value and/or Flag
    }
    else
    {
        return 0;                                     //--- Nothing Available
    }
}


//---------------------------------------------------------------------------------------------
//    Define I2C1 Master on Port PB06 as SCL and PB07 as SDA
//    Define Clock Source & Speed
//---------------------------------------------------------------------------------------------
u08   fnInitI2C1_Master_Port (void)
{
    u32 ulWork;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //--- Force Reset of I2C1 Peripherial
    RCC_APB1RSTR1 |= 0x00200000;
    nop32;
    RCC_APB1RSTR1 &= 0xFFDFFFFF;

    //--- Define I2C1 Clock Source
    RCC_CCIPR &= 0xFFFFC0FF;                        //--- Reset any old source definitions
    RCC_CCIPR |= 0x00002000;                        //--- Select HSI-16 as I2C1 Clock Source

    //--- Enable I2C1 Peripherial Clock on APB1 for HSI16
    RCC_APB1ENR1 |= 0x10200000;
    RCC_APB1SMENR1 |= 0x10200000;

    //--- Clear All pending interrupts
    I2C1_ICR = 0x00003F38;                          //--- Clear All I2C Flags
    fnClrIntPend (I2C1_EV_IRQn);                    //--- Clear I2C interrupts pending in NVIC

    //-------------------------------------------------------------------------------------------
    //      Configure I2C1 to Operate on PB06 & PB07 GPIO_B Port Pins PB06=SCL PB07=SDA
    //-------------------------------------------------------------------------------------------
    //      GPIO MODE  00=Input  01=Output  10=AltFun  11=Analog
    //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
    //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
    //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
    //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
    //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
    //      00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    //      -- --.-- --.-- --.-- --.10 10.-- --.-- --.-- --
    //  GPIOB 06 & 07 Set as Alternate Function
    GPIOB_MODER &= 0xFFFF0FFF;        //--- Clear B6 & B7 Bits First
    nop4;
    GPIOB_MODER |= 0x0000A000;        //--- Set Bits Next for AF04

    //      SET GPIO PB06 = I2C1_SCL
    //      SET GPIO PB07 = I2C1_SDA
    //      GPIO AFRL
    //      3322 2222 2222 1111 1111 1100 0000 0000
    //      1098 7654 3210 9876 5432 1098 7654 3210
    //      .... .... .... .... .... .... .... ....
    //      0100 0100 0000 0000 0000 0000 0000 0000
    ulWork = GPIOB_AFRL;              //--- Read Original Setup
    ulWork &= 0x00FFFFFF;             //--- Clear B6 & B7 AFRL
    ulWork |= 0x44000000;             //--- Set B6 & B7 AFRL to AF4 (I2C1 SCL & SDA)
    GPIOB_AFRL = ulWork;              //--- Update GPIOB
    nop4;

    //      GPIO AFRH
    //      3322 2222 2222 1111 1111 1100 0000 0000
    //      1098 7654 3210 9876 5432 1098 7654 3210
    //      .... .... .... .... .... .... .... ....
    //      0000 0000 0000 0000 0000 0000 0000 0000
    GPIOB_AFRH = 0x00000000;

    //      GPIO OTYPE
    //      3322 2222 2222 1111 1111 1100 0000 0000
    //      1098 7654 3210 9876 5432 1098 7654 3210
    //      .... .... .... .... .... .... .... ....
    //      0000 0000 0000 0000 0000 0000 1100 0000
    //
    //  GPIOB 6&7 = Open Drain
    GPIOB_OTYPER |= 0x000000C0;

    //--- Set all GPIOB Pins to Super Speed
    //      GPIO OSPEED
    //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
    //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
    //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
    //      11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11
    //      VH VH VH VH VH VH VH VH VH VH VH VH VH VH VH VH
    //  GPIOB Pins 6 & 7 = Pins Very High Speed
    GPIOB_OSPEEDR |= 0x0000F000;

    //--- Set GPIO PB06 and PB07 as Open Drain with Pullup
    //      GPIO INPUT PUPD RESISTORS
    //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
    //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
    //      .. ..|.. ..|.. ..|.. ..|.. ..|.. ..|.. ..|.. ..
    //      00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    //      NP NP NP NP NP NP NP NP NP NP NP NP NP NP NP NP
    //  GPIOB Pins 6 & 7 Have Pullups
    GPIOB_PUPDR &= 0xFFFF0FFF;
    nop4;
    GPIOB_PUPDR |= 0x00005000;
}

//*********************************************************************************************
//    Start of I2C1 peripherial device operating configuration for MASTER
//*********************************************************************************************
void  fnInitI2C1_Master_Ops (u08 ubSpeed)
{
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- Preset I2C1 Control Register 1
    //
    //      3322 2222 2222 1111 1111 1100 0000 0000
    //      1098 7654 3210 9876 5432 1098 7654 3210
    // USED .... .... wwww wwww ww.w wwww wwww wwww
    // S/C  0000 0000 0000 0000 0000 0000 1100 0110
    //      Name             Bit#  On/Off
    //      -------------    ----   ---
    //      . Unused          31    Off
    //      . Unused          30    Off
    //      . Unused          29    Off
    //      . Unused          28    Off
    //      . Unused          27    Off
    //      . Unused          26    Off
    //      . Unused          25    Off
    //      . Unused          24    Off
    //      . PEC_EN          23    Off
    //      . ALERT_EN        22    Off
    //      . SMBD_EN         21    Off
    //      . SMBH_EN         20    Off
    //      . GC_EN           19    Off
    //      . WUP_EN          18    Off
    //      . NOSTRETCH       17    Off
    //      . SBC             16    Off
    //      . RXDMA_EN        15    Off
    //      . TXDMA_EN        14    Off
    //      . Unused          13    Off
    //      . ANF_OFF         12    Off             //--- Analog NF NOT Disabled (Backward Logic)
    //      . DNF-3           11    Off             //--- Digital Filter Disabled
    //      . DNF-2           10    Off
    //      . DNF-1           09    Off
    //      . DNF-0           08    Off
    //      . ERR_IE          07    Off             //--- Error Interrupts Disabled
    //      . TC_IE           06    Off             //--- Transfer Complete
    //      . STOP_IE         05    Off             //--- Not USED in MASTER Mode
    //      . NACK_IE         04    Off             //--- Not USED in MASTER Mode
    //      . ADDR_IE         03    Off             //--- Not USED in MASTER Mode
    //      . RX_IE           02    Off             //--- RX Interrupt
    //      . TX_IE           01    Off             //--- TX Interrupt
    //      . PERIPH_ENABLE   00    Off             //--- Enable Device
    //

    I2C1_CR1 = 0x00000006;                          //--- Note: PE NOT Enabled at this time
    nop4;                                           //--- Dead Time

    //--- Set Up I2C Timing Register FOR 16MHz I2CCLK AND 400KHz OPERATION
    //--- I2C Timing Register
    //      3322 2222 2222 1111 1111 1100 0000 0000
    //      1098 7654 3210 9876 5432 1098 7654 3210
    // USED wwww .... wwww wwww wwww wwww wwww wwww
    // S/C  0011 0000 0000 0000 0000 1111 0001 0011
    //      Name             Bit#  On/Off
    //      -------------    ----   ---
    //      . PRESC 3         31    OFF
    //      . PRESC 2         30    OFF
    //      . PRESC 1         29    ON
    //      . PRESC 0         28    ON
    //      . Unused          27    OFF
    //      . Unused          26    OFF
    //      . Unused          25    OFF
    //      . Unused          24    OFF
    //      . SCLDLY 3        23    OFF
    //      . SCLDLY 2        22    ON
    //      . SCLDLY 1        21    OFF
    //      . SCLDLY 0        20    OFF
    //      . SDADLY 3        19    OFF
    //      . SDADLY 2        18    OFF
    //      . SDADLY 1        17    ON
    //      . SDADLY 0        16    OFF
    //      . SCLH 7          15    OFF
    //      . SCLH 6          14    OFF
    //      . SCLH 5          13    OFF
    //      . SCLH 4          12    OFF
    //      . SCLH 3          11    ON
    //      . SCLH 2          10    ON
    //      . SCLH 1          09    ON
    //      . SCLH 0          08    ON
    //      . SCLL 7          07    Off
    //      . SCLL 6          06    Off
    //      . SCLL 5          05    Off
    //      . SCLL 4          04    Off
    //      . SCLL 3          03    On
    //      . SCLL 2          02    Off
    //      . SCLL 1          01    Off
    //      . SCLL 0          00    On
    //
    //  Setup for I2CCLK = HSI 16MHz SCL Freq = 100KHz
    //    PRESC   = 0x3
    //    SDADLY  = 0x02
    //    SCLDLY  = 0x04
    //    SCLH    = 0x0F
    //    SCLL    = 0x13
    //
    //      3322 2222 2222 1111 1111 1100 0000 0000
    //      1098 7654 3210 9876 5432 1098 7654 3210
    //      .... .... .... .... .... .... .... ....
    //      0011 0000 0100 0010 0000 1111 0001 0011
    //         3    0    4    2    0    F    1    3           0x30420F13
    //
    //  Setup for I2CCLK = HSI 16MHz SCL Freq = 400KHz
    //    PRESC   = 0x1
    //    SDADLY  = 0x02
    //    SCLDLY  = 0x03
    //    SCLH    = 0x03
    //    SCLL    = 0x09
    //
    //      3322 2222 2222 1111 1111 1100 0000 0000
    //      1098 7654 3210 9876 5432 1098 7654 3210
    //      .... .... .... .... .... .... .... ....
    //      0001 0000 0100 0010 0000 0011 0000 1001
    //         1    0    4    2    0    3    0    9
    //
    //  Setup for I2CCLK = HSI 16MHz SCL Freq = 1 MHz       0x10420309
    //    PRESC   = 0x0
    //    SDADLY  = 0x00
    //    SCLDLY  = 0x02
    //    SCLH    = 0x02
    //    SCLL    = 0x04
    //
    //      3322 2222 2222 1111 1111 1100 0000 0000
    //      1098 7654 3210 9876 5432 1098 7654 3210
    //      .... .... .... .... .... .... .... ....
    //      0000 0000 0100 0010 0000 0010 0000 0100         0x00420204
    //         0    0    4    2    0    2    0    4
    //

    //--- Select Timing for different SCL Speeds
    //     0x00 = 100 KHz    0x01 = 400 KHz   0x10 = 1 MHz

    ubJunk = I2C1_RXDR;                             //--- Clear Rx Register
    I2C1_ICR |= 0x00000001;                         //--- Flush Tx Trgister

    //------------------------------------------
    //    Set up Timing as per Speed request
    //------------------------------------------
    switch (ubSpeed & 0x03)
    {
        case 0:
            I2C1_TIMINGR = 0x30420F13;                  //--- Set for 100 KHz Default
            break;

        case 1:
            I2C1_TIMINGR = 0x10420309;                  //--- Set for 400 KHz
            break;

        case 2:
            I2C1_TIMINGR = 0x00420204;                  //--- Set for 1 MHz
            break;

        case 3:
            I2C1_TIMINGR = 0x30420F13;                  //--- Default = 100 KHz
            break;
    }

    nop4;                                           //--- Register setteling time

    //--- Initialize Data Buffer Pointers
    //  ubI2C1_TXptr = &ubI2C1_TXB;                     //--- TX Buffer Default Location
    //  ubI2C1_RXptr = &ubI2C1_RXB;                     //--- RX Buffer Default Location

    //--- Enable TXIS & RXNE Interrupts
    //--- Enable the I2C Interface
    I2C1_CR1 = 0x00000007;                          //--- Note: Enable PE, TIE, RIE Only
    nop4;                                           //--- Dead Time
}


//---------------------------------------------------------------------------------------------
//    Function to Reset the I2C Device
//---------------------------------------------------------------------------------------------
void  fnResetI2C1 (void)
{
    I2C1_CR1 &= 0x00000000;                          //--- Release Enable And All Interrupts

    //--- Wait for PE to Go Low
    while (I2C1_CR1 & 0x00000001)
    {
        nop4;
    }

    ulBusyFlags &= 0xF7FFFFFF;                        //--- Clear the I2C1 Busy Flag
}

//---------------------------------------------------------------------------------------------
//    I2C1 Control Register 2 Note : Nbytes > 0 for Active Transaction
//---------------------------------------------------------------------------------------------
//
//      3322 2222 2222 1111 1111 1100 0000 0000
//      1098 7654 3210 9876 5432 1098 7654 3210
// USED .... .www wwww wwww wwww wwww wwww wwww
// S/C  0000 0000 0000 0000 0000 0000 1100 0110
//      Name             Bit#  On/Off
//      -------------    ----   ---
//      . Unused          31    0
//      . Unused          30    0
//      . Unused          29    0
//      . Unused          28    0
//      . Unused          27    0
//      . PECBYTE         26    0               //--- PEC Control Unused
//      . AUTOEND         25    1/0             //--- Set if AUTOEND Desired
//      . RELOAD          24    1/0             //--- Set if RELOAD Desired
//      . NBYTES_7        23    1/0   //----+
//      . NBYTES_6        22    1/0   //    |
//      . NBYTES_5        21    1/0   //    |
//      . NBYTES_4        20    1/0   //    |   Number of Bytes to Transfer
//      . NBYTES_3        19    1/0   //    |   0 to 255
//      . NBYTES_2        18    1/0   //    |
//      . NBYTES_1        17    1/0   //    |
//      . NBYTES_0        16    1/0   //----+
//      . NACK_GEN        15    1/0             //--- Enable NACK Generation in Slave Mode
//      . STOP_DET        14    1/0             //--- Stop Condition Detected
//      . START_GEN       13    1/0             //--- Generate the START Condition
//      . HEAD10R         12    1/0             //--- Master Sends 10 Bit Address
//      . ADD10_ENA       11    1/0             //--- Enable 10 Bit Addressing
//      . RD1/WR0         10    1/0             //--- READ / WRITE MODE
//      . SADD_9           9    1/0   //--- 10 Bit Address 9
//      . SADD_8           8    1/0   //--- 10 Bit Address 8
//      . SADD_7           7    1/0   //---  7 Bit Address 7
//      . SADD_6           6    1/0   //---  7 Bit Address 6
//      . SADD_5           5    1/0   //---  7 Bit Address 5
//      . SADD_4           4    1/0   //---  7 Bit Address 4
//      . SADD_3           3    1/0   //---  7 Bit Address 3
//      . SADD_2           2    1/0   //---  7 Bit Address 2
//      . SADD_1           1    1/0   //---  7 Bit Address 1
//      . SADD_0           0    1/0   //--- 10 Bit Address 0
//
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//      I2C1_ISR Interrupt Status Register Bit Definitions
//---------------------------------------------------------------------------------------------
//      33222222222211111111110000000000
//      10987654321098765432109876543210
// USED ........rrrrrrrrrrrrrrrrrrrrrrww
// S/C  00000000000000000000000000000000
//      Name             Bit#  On/Off
//      -------------    ----   ---
//      . Unused          31    OFF
//      . Unused          30    OFF
//      . Unused          29    OFF
//      . Unused          28    OFF
//      . Unused          27    OFF
//      . Unused          26    OFF
//      . Unused          25    OFF
//      . Unused          24    OFF
//      . RXADD_7         23    OFF   //--- Our Slave ADDRESS Value
//      . RXADD_6         22    OFF
//      . RXADD_5         21    OFF
//      . RXADD_4         20    OFF
//      . RXADD_3         19    OFF
//      . RXADD_2         18    OFF
//      . RXADD_1         17    OFF
//      . RX_DIR          16    OFF   //--- Our Slave Data Direction
//      . BUSY            15    1/0   //--- Transaction Busy Flag
//      . Unused          14    OFF
//      . ALERT FLAG      13    OFF
//      . TIME_OUT FLAG   12    OFF   //--- Transaction Timeout Flag
//      . PEC ERROR FLAG  11    OFF   //--- PEC Error Flag
//      . OVR ERROR FLAG  10    OFF   //--- Over Write Error
//      . ARLO_ERROR FLAG 09    OFF   //--- Arbitration Lost Flag
//      . BUS ERROR FLAG  08    OFF   //--- Bus Activity Error
//      . TCR ERROR       07    Off   //--- Transfer Complete Reload
//      . TC STATUS       06    Off   //--- Transfer Complete Master Mode
//  !   . STOP FLAG       05    Off   //--- STOP Condition Detected
//  !   . NACK FLAG       04    Off   //--- NACK Received Flag
//  !   . ADDR_FLAG       03    Off   //--- Slave Mode Incomming ADDRESS Match
//  !   . RXNE FLAG       02    Off   //--- Received Data Register Full
//  !   . TXIS FLAG       01    Off   //--- TXIS TXD Empty
//  !   . TXE FLAG        00    Off   //--- Tx Buffer Empty
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//  Creates an I2C Transaction Task and Scheduels it into the Task FIFO
//---------------------------------------------------------------------------------------------
//
//  Function Returna 0 if Successful or
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Input Variables: for fnMake_I2C_Task Function: Variable Map for fnMake_I2C_Task Function
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//  uwDelay = Task Delay Time Value if necessary
//
//  ubI2C_Adds = TrueAddress (As seen in I2C Address Register (Shifted Address (0 - 127))
//               True address is defined as the 7 bit device address already shifted left by 1
//
//  ubNbytes   = Number of Data Transaction Bytes (0 - 255)
//              Note: > 255 Bytes NOT currently Supported
//
//  ubTT       = Transaction Type Code Bit Map
//                 Bit   Function
//                 ---   ----------------------------------
//                  0    Transaction Type Code Bit 0
//                  1    Transaction Type Code Bit 1
//                  2    Transaction Type Code Bit 2
//                  3    Unused
//                  4    Unused
//                  5    Unused
//                  6    Unused
//                  7    Unused
//
//               ------------------------------
//               Transaction Type Codes:
//                  0 = N Byte Write (No Reg/Add Required)
//                  1 = N Byte Write (With 1 Byte Reg/Add)
//                  2 = N Byte Write (With 2 Byte Reg/Add)
//                  3 = N Byte Write (With 3 Byte Reg/Add)
//                  4 = N Byte Read  (No Reg/Add Required)
//                  5 = N Byte Read  (With 1 Byte Reg/Add)
//                  6 = N Byte Read  (With 2 Byte Reg/Add)
//                  7 = N Byte Read  (With 3 Byte Reg/Add)
//
//  ubSpeed    =   Transaction Speed
//                 Bit   Function
//                 ---   ----------------------------------
//                  0    Speed Lo Bit '00':100 KHz  '01':400 KHz   '10': 1 MHz
//                  1    Speed Hi Bit
//                  2-7  Unused
//
//  *ubDptr    = Pointer to Data Buffer or String Tx or Rx
//
//  ulRegAdd   = Register or Address Value (0,1-3 Bytes in ulLong Format)
//---------------------------------------------------------------------------------------------

//--- Function to Create an I2C Transfer Task
u16  fnMake_I2C1_Task (u16 uwDelay, u08 ubI2C_Adds, u08 ubTT, u16 uwNbytes, u08* ptDptr, union LWB unRegAdd)
{
    //u32     ulRetVal;
    struct  Task stI2C_Task;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //--- Create an I2C Task & Schedule It
    stI2C_Task.uwTimer = uwDelay;                   //--- Set any Delays necessary
    stI2C_Task.uwFlags = 0;                         //--- Ignore Task Flags
    stI2C_Task.ptrTask = &tkI2C1_Task;              //--- Set Task Address

    //--- Fill In the Data
    stI2C_Task.unTaskData.ubByte[0] = ubI2C_Adds;   //--- Set I2C Device Address            8 Bit
    stI2C_Task.unTaskData.ubByte[1] = ubTT;         //--- Low Nibble = Transaction Type     8 Bit
    stI2C_Task.unTaskData.uwWord[1] = uwNbytes;     //--- Set Number of Bytes to Transfer  16 Bit

    stI2C_Task.unTaskData.ubPtr[1] = ptDptr;        //--- Set Pointer for Transfer         32 Bit
    stI2C_Task.unTaskData.ulLong[2] = unRegAdd.ulLong;     //--- Register Number or Address

    //--- Schedule the Task
    uwReturnVal = fnScheduleTask (stI2C_Task);         //--- Schedule the task
    return 0;
}

//---------------------------------------------------------------------------------------------
//  Generic Task for I2C Communications
//  Note the Initalization Functions are regular C code functions and are not scheduable
//---------------------------------------------------------------------------------------------
//  Task Data Definition for I2C Execution Task
//  -------------------------------------------
//  Data Union Definition:
//    0.  ubByte[0] : ubI2C_Adds        I2C Preshifted Address (I2C TrueAdds)
//                                        HI Adds = 0X, 1X, 2X, 3X, 4X, 5X, 6X, 7X
//                                                  8X, 9X, AX, BX, CX, DX, EX, FX
//                                        Lo Adds = X0, X2, X4, X6, X8, XA, XC, XE
//
//    1.  ubByte[1] : ubTTF             Transaction Type Flags
//                                      ------------------------------
//                                      Bit   Function
//                                       0    Type Code LSB
//                                       1    TYPE Code ...
//                                       2    Type Code MSB
//                                        |
//                                        |      ------------------------------
//                                        |      Transaction Type Cods:
//                                        |      0 = N Byte Write (No Reg/Add Required)
//                                        |      1 = N Byte Write (With 1 Byte Reg/Add)
//                                        |      2 = N Byte Write (With 2 Byte Reg/Add)
//                                        |      3 = N Byte Write (With 3 Byte Reg/Add)
//                                        |      4 = N Byte Read  (No Reg/Add Required)
//                                        |      5 = N Byte Read  (With 1 Byte Reg/Add)
//                                        |      6 = N Byte Read  (With 2 Byte Reg/Add)
//                                        |      7 = N Byte Read  (With 3 Byte Reg/Add)
//                                        |
//                                       3    Unused
//                                       4    Unused
//                                       5    Unused
//                                       6    Unused
//                                       7    Unused
//
//    2.  uwWord[1] : uwDlen            Number of Data Bytes (0 to 65535) in Transaction
//
//    4.  ubPntr[1]           Pointer to Transaction Buffer TX or RX (4 Bytes)
//
//    5.  ulLong[2]           Device Internal Address Value Offset Bytes 8,9,10,11
//
//    6.  Bytes [12]-[15]     Unused
//
//  NOTE: The I2C1_Busy Bit in ulBusy_Flags
//
//---------------------------------------------------------------------------------------------
u32  tkI2C1_Task (union DFLWB16 unTD)             //--- unTD = Passed Data
{
    //  u32     ulRet = 0;                              //--- Return Code
    //  u32     ulWork = 0;                             //--- Working ulVlaue
    //  u16     uwCntr = 0;                             //--- Working Counter (u16)

    u08     ubDevAdd = 0;                           //--- I2C Device Address
    u08     ubTranType = 0;                         //--- Transaction Type Code (0-7)
    u16     uwDlen = 0;                             //--- Transaction Data Length
    u16     uwAdsLen = 0;                           //--- Length of Internal Address Field

    union   LWB unAddBfr;                           //--- Buffer Containing Internal Address

    p08     ptDptr;                                 //--- Transaction Data Pointer (Byte)
    p08     ptTptr;                                 //--- Temporary Pointer(Byte)
    u16     uwNb;                                   //--- Number of Data Bytes to Transfer

    struct  Task stI2C_Task;                        //--- For recursion of Task if necessary

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //--- Is there another I2C Transaction Busy?  If "YES" then reschedule this task 1 mSec
    if ((ulBusyFlags & 0x08000000) != 0)
    {
        //--- Copy Task & 1 mSec Delay
        stI2C_Task.uwTimer = 2;                       //--- Set any Delays to 2 mSec
        stI2C_Task.uwFlags = 0;                       //--- Ignore Flags
        stI2C_Task.ptrTask = &tkI2C1_Task;            //--- Set Task Address for Reschedule
        stI2C_Task.unTaskData = unTD;                       //--- Copy the Data Block

        //--- ReSchedule this Task Again
        uwReturnVal = fnScheduleTask (stI2C_Task);          //--- Call Schedueler & Return Flags
        return uwReturnVal;
    }

    //--- Ok to Execute Task - Set Busy Flag
    ulBusyFlags |= 0x08000000;                    //--- Set the I2C1 Busy Flag in PBusy

    //--- I2C1 not busy so extract Info from Input Data Union TD
    ubDevAdd = unTD.ubByte[0];                      //--- Device I2C Physical Address
    uwDlen = (u16)unTD.uwWord[1];                   //--- Number of Transfer Bytes
    ubTranType = unTD.ubByte[2] & 0x07;             //--- Transaction Type Code
    unAddBfr.ulLong = unTD.ulLong[2];               //--- Internal Device Reg/Add

    //--- Resident Data Pointer to Tx Data
    ptDptr = unTD.ubPtr[1];                         //--- Get Source Pointer from TD.Pntr[1]

    //--- Transaction Temporary Write Data Pointer
    ptTptr = &ubI2C1_TempTX;

    //--- Isolate Speed Value & Initialize I2C for Master transfer
    fnInitI2C1_Master_Ops (unTD.ubByte[3] & 0x03);

    //-------------------------------------------------------------------------------------------
    //    Preset I2C Transaction Types
    //-------------------------------------------------------------------------------------------
    //   Transaction Type Cods:
    //   ::::::::::::::::::::::::::::::::::::::::::::::
    //   0 = N Byte Write (No Reg/Add Required)     Just Write No Internal Address Required
    //   1 = N Byte Write (With 1 Byte Reg/Add)     Using Device Internal Address of 1 Byte
    //   2 = N Byte Write (With 2 Byte Reg/Add)     Using Device Internal Address of 2 Byte
    //   3 = N Byte Write (With 3 Byte Reg/Add)     Using Device Internal Address of 3 Byte
    //   4 = N Byte Read  (No Reg/Add Required)     Just Read  No Internal Address Required
    //   5 = N Byte Read  (With 1 Byte Reg/Add)     Using Device Internal Address of 1 Byte
    //   6 = N Byte Read  (With 2 Byte Reg/Add)     Using Device Internal Address of 2 Byte
    //   7 = N Byte Read  (With 3 Byte Reg/Add)     Using Device Internal Address of 3 Byte
    //-------------------------------------------------------------------------------------------
    switch (ubTypeCode)
    {
        //--- Write Direct Data without Reg or Add #
        case 0:
            ubJunk = I2C1_RXDR;                         //--- Clear any waiting RX Data

            //--- Copy Data to TempTX Buffer
            for (uwNb = 0; uwNb < ubDataLen; uwNb ++)
            {
                *ubTptr++ = *ubDptr++;                    //--- Copy Data from Source to TempTX
            }

            ubI2C1_TXptr = &ubI2C1_TempTX;              //--- Final Tx Pointer Address = Temp Buffer

            //--- Create Start and Write Command to Slave
            //----------------- I2C_CR2 ---------------
            //  3322 2222 2222 1111 1111 1100 0000 0000
            //  1098 7654 3210 9876 5432 1098 7654 3210
            //  .... .... .... .... .... .... .... ....
            //  0000 0000 #### #### 0011 0W00 AAAA AAA0
            ulWork = 0x00003000;                        //--- Set Up Start Condition
            ulWork |= (u32)ubTrueAdds;                  //--- Left Justified 7 Bit Address
            ulWork &= 0xFF00FBFF;                       //--- Set the WT0/RD1 to Write
            ulWork |= (u32) (ubNb << 16);               //--- Shift Byte Count into position
            ulWork |= 0x02000000;                       //--- Set Auto End for this transaction
            ulWork &= 0xFFFFFBFF;                       //--- This is a WRITE Transaction

            //--- Send Start & Command Sequence to I2C Device for Write with Auto End
            I2C1_CR1 |= 0x00000043;                     //--- TCI,TXI Int Enable & Periph Ena
            I2C1_CR2 = ulWork;                          //--- Write to CR2 to Start Transaction

            //--- Test if TXIE Interrupt generated when CR2 command Generated
            I2C1_TXDR = *ubI2C1_TxPtr++;                //--- Send First Data & Increment Pointer
            ubTxNbytes--;                               //--- Decrement Number of Bytes Remaining
            return 0;                                   //--- Exit
            break;

            //--- Write Transaction with 1 Reg/Add Byte
        case 1:
            ubJunk = I2C1_RXDR;                         //--- Clear any waiting RX Data
            *ubTptr++ = unTD.ubByte[8];                 //--- LSB Register Value
            ubAdsLen++;                                 //--- Bump # Bytes Address

            //--- Copy Remaining Data to TX Buffer
            for (uwNb = 0; uwNb < ubDataLen; uwNb ++)
            {
                *ubTptr++ = *ubDptr++;                    //--- Copy Data @ Pointers
            }

            //--- Create Start and Write Command to Slave
            //----------------- I2C_CR2 ---------------
            //  3322 2222 2222 1111 1111 1100 0000 0000
            //  1098 7654 3210 9876 5432 1098 7654 3210
            //  .... .... .... .... .... .... .... ....
            //  0000 0000 #### #### 0011 0W00 AAAA AAA0
            ulWork = 0x00003000;                        //--- Set Up Start Condition
            ulWork |= (u32)ubTrueAdds;                  //--- Left Justified 7 Bit Address
            ulWork &= 0xFFFFFBFF;                       //--- Set the WT0/RD1 to Write
            ulWork |= (u32) ((u32)ubDataLen + (u32)ubAdsLen)) << 16;  //--- Set Nbytes
            ulWork |= 0x02000000;                       //--- Set Auto End for this transaction
            ulWork &= 0xFFFFFBFF;                       //--- This is a WRITE Transaction

            //--- Send Start & Command Sequence to I2C Device for Write with Auto End
            I2C1_CR2 = ulWork;                          //--- Write to CR2 to Start Transaction
            I2C1_CR1 |= 0x00000043;                     //--- TCI,TXI Int Enable & Periph Ena
            return 0;                                   //--- Exit
            break;

            //--- Write Transaction with 2 Reg/Add Byte
        case 2:
            ubJunk = I2C1_RXDR;                         //--- Clear any waiting RX Data
            *ubTptr++ = unTD.ubByte[8];           //--- LSB Register Value
            ubAdsLen++;                                 //--- Bump # Bytes Address
            *ubTptr++ = unTD.ubByte[9];           //--- Next Register Value
            ubAdsLen++;                                 //--- Bump # Bytes Address

            //--- Copy Remaining Data to TX Buffer
            for (uwNb = 0; uwNb < ubDataLen; uwNb ++)
            {
                *ubTptr++ = *ubDptr++;                    //--- Copy Data @ Pointers
            }

            //--- Create Start and Write Command to Slave
            //----------------- I2C_CR2 ---------------
            //  3322 2222 2222 1111 1111 1100 0000 0000
            //  1098 7654 3210 9876 5432 1098 7654 3210
            //  .... .... .... .... .... .... .... ....
            //  0000 0000 #### #### 0011 0W00 AAAA AAA0
            ulWork = 0x00003000;                        //--- Set Up Start Condition
            ulWork |= (u32)ubTrueAdds;                  //--- Left Justified 7 Bit Address
            ulWork &= 0xFFFFFBFF;                       //--- Set the WT0/RD1 to Write
            ulWork |= (u32) ((u32)ubDataLen + (u32)ubAdsLen)) << 16;  //--- Set Nbytes
            ulWork |= 0x02000000;                       //--- Set Auto End for this transaction
            ulWork &= 0xFFFFFBFF;                       //--- This is a WRITE Transaction

            //--- Send Start & Command Sequence to I2C Device for Write with Auto End
            I2C1_CR2 = ulWork;                          //--- Write to CR2 to Start Transaction
            I2C1_CR1 |= 0x00000043;                     //--- TCI,TXI Int Enable & Periph Ena
            return 0;                                   //--- Exit
            break;

            //--- Write Transaction with 3 Reg/Add Byte
        case 3:
            ubJunk = I2C1_RXDR;                         //--- Clear any waiting RX Data
            *ubTptr++ = unTD.ubByte[8];           //--- LSB Register Value
            ubAdsLen++;                                 //--- Bump # Bytes Address
            *ubTptr++ = unTD.ubByte[9];           //--- Next Register Value
            ubAdsLen++;                                 //--- Bump # Bytes Address
            *ubTptr++ = unTD.ubByte[10];          //--- Next Register Value
            ubAdsLen++;                                 //--- Bump # Bytes Address

            //--- Copy Remaining Data to TX Buffer
            for (uwNb = 0; uwNb < ubDataLen; uwNb ++)
            {
                *ubTptr++ = *ubDptr++;                    //--- Copy Data @ Pointers
            }

            //--- Create Start and Write Command to Slave
            //----------------- I2C_CR2 ---------------
            //  3322 2222 2222 1111 1111 1100 0000 0000
            //  1098 7654 3210 9876 5432 1098 7654 3210
            //  .... .... .... .... .... .... .... ....
            //  0000 0000 #### #### 0011 0W00 AAAA AAA0
            ulWork = 0x00003000;                        //--- Set Up Start Condition
            ulWork |= (u32)ubTrueAdds;                  //--- Left Justified 7 Bit Address
            ulWork &= 0xFFFFFBFF;                       //--- Set the WT0/RD1 to Write
            ulWork |= (u32) ((u32)ubDataLen + (u32)ubAdsLen)) << 16; //--- Calc Write Nbytes
            ulWork |= 0x02000000;                       //--- Set Auto End for this transaction
            ulWork &= 0xFFFFFBFF;                       //--- This is a WRITE Transaction

            //--- Send Start & Command Sequence to I2C Device for Write with Auto End
            I2C1_CR2 = ulWork;                          //--- Write to CR2 to Start Transaction
            I2C1_CR1 |= 0x00000043;                     //--- TCI,TXI Int Enable & Periph Ena
            return 0;                                   //--- Exit
            break;

            //--- Read Transaction with No Reg/Add Bytes
        case 4:
            ubJunk = I2C1_RXDR;                         //--- Clear any waiting RX Data
            ubI2C1_RXptr = unTD.ubPntr[1];              //--- Set RX Data Pointer Address

            //--- Create Start and Write Command to Slave
            //----------------- I2C_CR2 ---------------
            //  3322 2222 2222 1111 1111 1100 0000 0000
            //  1098 7654 3210 9876 5432 1098 7654 3210
            //  .... .... .... .... .... .... .... ....
            //  0000 0000 #### #### 0011 0R00 AAAA AAA0
            ulWork = 0x00003000;                        //--- Set Up Start Condition
            ulWork |= (u32)ubTrueAdds;                  //--- Left Justified 7 Bit Address
            ulWork |= 0x00000400;                       //--- Set the WT0/RD1 to READ Transaction
            ulWork |= (u32) (ubDataLen << 16);          //--- Shift byte count into position
            ulWork |= 0x02000000;                       //--- Set Auto End for this transaction

            //--- Send Start & Command Sequence to I2C Device for Read with Auto End
            I2C1_CR2 = ulWork;                          //--- Write to CR2 to Start Transaction
            I2C1_CR1 |= 0x00000045;                     //--- TCI,RXI Int Enable & Periph Ena
            break;

            //--- Read Transaction with 1 Reg/Add Bytes
        case 5:
            ubJunk = I2C1_RXDR;                         //--- Clear any waiting RX Data
            //--- Start by sending a 1 Byte Register Sddress
            ubI2C1_RXptr = unTD.ubPntr[1];              //--- Set RX Data Pointer Address
            ubAdsLen = 0x1;                             //--- Only 1 Address Byte

            //--- Create Start and Write Command to Slave
            //----------------- I2C_CR2 ---------------
            //  3322 2222 2222 1111 1111 1100 0000 0000
            //  1098 7654 3210 9876 5432 1098 7654 3210
            //  .... .... .... .... .... .... .... ....
            //  0000 0000 #### #### 0011 0W00 AAAA AAA0
            ulWork = 0x00003000;                        //--- Set Up Start Condition
            ulWork |= (u32)ubTrueAdds;                  //--- Left Justified 7 Bit Address
            ulWork |= (u32) (ubDataLen << 16);          //--- Shift Byte Count into position
            ulWork |= 0xFDFFFFFF;                       //--- Clr Auto End for this transaction
            ulWork |= 0x00000400;                       //--- This is a READ Transaction

            //--- Send Start & Command Sequence to I2C Device for Read with Address e with Auto End
            I2C1_CR2 = ulWork;                          //--- Write to CR2 to Start Transaction
            I2C1_CR1 |= 0x00000047;                     //--- TCI,TXI,RX Int Enable & Periph Ena

            //--- Send Start & Command Sequence to I2C Device for Write with Auto End
            I2C1_CR2 = ulWork;                          //--- Write to CR2 to Start Transaction
            I2C1_CR1 |= 0x00000047;                     //--- TC,TX,RX Int Enable & Periph Ena
            break;

            //--- Read Transaction with 2 Reg/Add Bytes
        case 6:
            break;

            //--- Read Transaction with 3 Reg/Add Bytes
        case 7:
            break;

    }

    //--- If you get here you are doing a addressed READ function

}


//---------------------------------------------------------------------------------------------
//  I2C SetUp Routine for I2C Straight Write
//  ----------------------------------------
//  ubTrueAddress = I2C Address << 1 (Shifted Address (0 - 127))
//  ulReg_Add=  Register # or Address inside device
//  ubRegLen =  Length of Register Bytes
//  ubNbytes =  Total number of Bytes to Send
//  ubSpeed  =  0 for 100 KHz Clock       1 for 400 KHz Clock
//  *ubDptr  = Pointer to Xmit Buffer / String
//
//  Sequence =  START + DEVICE ADDRESS + WRITE + Nbytes + AutoEnd
//              Writes N Bytes to I2C Port
//---------------------------------------------------------------------------------------------
u08   fnI2C1_Write (u08 ubTrueAdds, u32 ulReg_Add, u08 RegLen, u08 ubNbytes, u08 ubSpeed, u08* ubDptr)
{
    u32 ulI2C_CR2 = 0;
    u08 ubFlag = 0;
    u08 ubNextData;
    u16 uwNb;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //--- Wait for I2C Driver to Finish previous action
    if (ubI2C1_Flags & 0x01)
    {
        return 0x80;                                  //--- Another Activity is Busy
    }
    else
    {
        ubI2C1_Flags |= 0x01;                         //--- Set Transaction Active Flag
    }

    //--- Is another Byte transaction busy?
    while (I2C1_ISR & 0x00008000)
    {
        nop4;
    }

    //--- Initialize MASTER Port & Bus Speed
    fnInitI2C1_Master_Ops (ubSpeed & 0x01);

    ubI2C1_TXptr = ubDptr;                          //---Set the I2C1 Pointer to Data

    //--- Send Start and Command to Slave
    //----------------- I2C_CR2 ---------------
    //  3322 2222 2222 1111 1111 1100 0000 0000
    //  1098 7654 3210 9876 5432 1098 7654 3210
    //  .... .... .... .... .... .... .... ....
    //  0000 0000 ---- ---- 0011 0W00 AAAA AAA0
    ulI2C_CR2 = 0x02003000;                         //--- Set Up Start Condition W/AutoEnd
    ulI2C_CR2 |= (u32)ubTrueAdds;                   //--- Left Justified 7 Bit Address
    ulI2C_CR2 &= 0xFFFFFBFF;                        //--- Set the Write (0) Flag
    ulI2C_CR2 |= (u32)(ubNbytes << 16);             //--- Shift Byte Count into position
    ulI2C_CR2 |= 0x02000000;                        //--- Set Auto End True

    //--- Send Start & Command Sequence to I2C Device + AUTOEND
    I2C1_CR2 = ulI2C_CR2;

    //--- Loop while Not NACK and NOT TXIS = 1
    while (!(I2C1_ISR & 0x00000012))
    {
        nop4;
    }

    //--- Was NACK Received?
    if (I2C1_ISR & 0x00000010)
    {
        return -1;                                    //--- NACK Received Error Exit
    }

    //--- Set Nbytes Loop Counter
    uwNb = (u16)ubNbytes;

    //--- If TXIS not set then loop for upto 200 uSec on fast timer #3
    while (uwNb)
    {
        ulI2C1_Pause = 2;

        //--- Loop While not TXIS ready and Transaction Timer still active
        while (!(I2C1_ISR & 0x00000002) && ulI2C1_Pause)
        {
            nop4;
        }

        //--- If we timed out then Exit with Error
        if !ulI2C1_Pause
        {
            fnResetI2C1;
            return -1;
        }

        //--- Send next byte pointed to by ubDptr
        I2C1_TXDR = *ubDptr++;                        //--- Get Data to TXDR
        uwNb--;                                       //--- Decrement Number of Bytes
    }

    ubI2C1_Flags &= 0xFE  ;                         //--- Clear Transaction Active Flag
    return 0;                                       //--- Success Exit
}

//---------------------------------------------------------------------------------------------
//  I2C SetUp Routine for I2C Memory Read
//  -------------------------------------
//  ubTrueAddress = I2C Address << 1 (Shifted Address (0 - 127))
//  Sequence =  START + DEVICE ADDRESS + READ + Nbytes + AutoEnd
//              Reads From Device each time RXNE is set to 1
//---------------------------------------------------------------------------------------------

u08 fnI2C1_Read (u08 ubTrueAdds, u08 ubNbytes, u08* ubDptr)
{
    u32 ulI2C_CR2 = 0;
    u08 ubFlag = 0;
    u08 ubNextData;
    u16 uwNb;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- Is another transaction busy?
    while (I2C1_ISR & 0x00008000)
    {
        nop4;
    }

    //--- Send Start and Command to Slave
    //----------------- I2C_CR2 ---------------
    //  3322 2222 2222 1111 1111 1100 0000 0000
    //  1098 7654 3210 9876 5432 1098 7654 3210
    //  .... .... .... .... .... .... .... ....
    //  0000 0000 ---- ---- 0011 0W00 AAAA AAA0
    ulI2C_CR2 = 0x02003000;                         //--- Set Up Start Condition W/AutoEnd
    ulI2C_CR2 |= (u32)ubTrueAdds;                   //--- Left Justified 7 Bit Address
    ulI2C_CR2 |= 0x00000400;                        //--- Set the Read (1) Flag
    ulI2C_CR2 |= (u32)(ubNbytes << 16);             //--- Shift Byte Count into position
    ulI2C_CR2 |= 0x02000000;                        //--- Set Auto End True

    //--- Send Start & Command Sequence to I2C Device + AUTOEND
    I2C1_CR2 = ulI2C_CR2;

    //--- Loop while Not NACK and RXNE = 0
    ulFastTimeCount[3] = 2;                       //--- Set 100 uSec Delay Count
    while (!(I2C1_ISR & 0x00000014) && ulFastTimeCount[3])
    {
        nop4;
    }

    //--- Was NACK Received?
    if (I2C1_ISR & 0x00000010)
    {
        ulFastTimeCount[3] = 0;                       //--- Clear Timer
        return -1;                                    //--- NACK Received
    }

    //--- Set Nbytes Loop Counter
    uwNb = (u16)ubNbytes;

    //--- If RXNE not set then loop for upto 200 uSec on fast timer #3
    while (uwNb)
    {
        ulFastTimeCount[3] = 2;                       //--- Set 100 uSec Delay Count
        while (!(I2C1_ISR & 0x00000004) && ulFastTimeCount[3])
        {
            nop12;
        }

        //--- If we timed out then Exit with Error
        if !ulFastTimeCount[3]
        {
            fnResetI2C1;
            return -1;
        }
        //--- Read next byte pointed to by ubDptr
        *ubDptr = I2C1_RXD;                           //--- Get RXDATA Data to Buffer++
        *ubDptr++;
        uwNb--;                                       //--- Decrement Number of Bytes
    }

    ulFastTimeCount[3] = 0;                         //--- Clear Timer
    return 0;                                       //--- Success Exit
}

//---------------------------------------------------------------------------------------------
//  Function Name  : I2C1_EV_IRQ          I2C1 Interrupt Event Service
//---------------------------------------------------------------------------------------------
u08  ubTxNbytes;                                  //--- Remaining # of Bytes to TX
u08  ubRxNbytes;                                  //--- Remaining # of Bytes to RX

void fnI2C1_Event(void)                           //--- IRQ_31
{
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- Test if (TXIE or TXE is TRUE) && (!TC Flag) && (ubNbytes > 0)
    //
    //--- If TRUE Then Get Next Byte at TX Pointer to the TXDR
    if (((I2C1_ISR & 0x00000003)!= 0) && (!(I2C1_ISR & 0x00000040)) && (ubNbytes > 0))
    {
        I2C1_TXDR = *ubI2C1_TxPtr++;                  //--- Send Data & Increment Pointer
        ubI2C1_Tx_Cntr--:                             //--- Decrement Number of Bytes Remaining
    }

    //--- Test if RXNE is TRUE
    //--- Just in case Check the I2C RX Data Register
    if ((I2C1_ISR & 0x00000004) > 0)
    {
        *ubI2C1_RxPtr++ = I2C1_RXDR;                  //--- Save Data & Increment Pointer
        ubRxNbytes--;
    }
}

//---------------------------------------------------------------------------------------------
//  Function Name  : I2C1_ER_IRQ        I2C1_Error Service
//---------------------------------------------------------------------------------------------
void   fnI2C1_Error(void)                        //--- IRQ_32
{
    //--- Your code goes here.
}
