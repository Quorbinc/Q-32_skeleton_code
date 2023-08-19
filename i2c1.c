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
//              0x00 = 100 KHz
//              0x01 = 400 KHz      //--- Typical I2C Clock = 400 KHz
//              0x02 = 1   MHz      //--- Fast I2C
//              0x03 = 5   MHz      //--- Super Fast I2C
//
//--- I2C Runs from HSI Clock at 16 MHz
//
//    I2C Register Map
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
#define I2C1DEBUG

//--- Defined in "commonheader.h"
//  union DFLWB32                     //--- 32 Bytes Variable
//    {
//      dbl   dfFlt[4];               //--- 4 Double Precision Float
//      u64   uxBig[4];               //--- 4 Unsigned 64 Bit Integer
//      s64   sxBig[4];               //--- 4 Signed 64 Bit Integer
//      flt   sfFlt[8];               //--- 8 Single Precision Floats
//      u32   ulLong[8];              //--- 8 Unsigned Long
//      s32   slLong[8];              //--- 8 Signed Long
//      u16   uwWord[16];             //--- 16 Unsigned Words
//      s16   swWord[16];             //--- 16 Signed Words
//      u08   ubByte[32];             //--- 32 Unsigned Bytes
//      s08   sbByte[32];             //--- 32 Signed Bytes
//      u08*  ubPtr[8];               //--- 8 General Purpose Pointers (byte)
//      void* vPntr[8];               //--- 8 Void Type Pointers
//    };

//---------------------------------------------------------------------------------------------
//    Initialize I2C1 for 400 KHz as Master
//
//    Init Configuration:
//    1.  Port Pins:  PB06 as SCL signal
//    2.  Port Pin:   PB07 as SDA signal
//    3.  I2C Drive Clock = HSI-16MHz
//    4.  SCL Speed = 400 KHz
//---------------------------------------------------------------------------------------------
u08   fnInitI2C1_Master (u32 ulSpeed)
{
  u32 ulWork:

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  //--- Force Reset of I2C1 Peripherial
  RCC_APB1RSTR |= 0x00010000;
  nop32;
  RCC_APB1RSTR &= 0xFFFEFFFF;

  //--- Define I2C1 Clock Source
  RCC_CCIPR &= 0xFFFFC0FF;                        //--- Reset any old source definitions
  RCC_CCIPR |= 0x00002000;                        //--- Select HSI-16 as I2C1 Clock Source

  //--- Enable I2C1 Peripherial Clock on APB1 for HSI16
  RCC_APB1ENR1 |= 0x10200000;
  RCC_APB1SMENR1 |= 0x10200000;

  //--- Clear All pending interrupts
  ISR1_ICR = 0x00003F38;                          //--- Clear All I2C Flags
  fnClrIntPend (I2C1_IRQn);                       //--- Clear I2C interrupts pending in NVIC

  //-------------------------------------------------------------------------------------------
  //      Configure GPIO_B Port Pins PB06=SCL PB07=SDA
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
  //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
  //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
  //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
  //      .. .. .. .. .. .. .. .. .. .. .. .. .. .. .. ..
  //      11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11
  //      VH VH VH VH VH VH VH VH VH VH VH VH VH VH VH VH
  //  GPIOB Pins 6 & 7 = Pins Very High Speed
  GPIOB_OSPEEDR |= 0x0000F000;

  //--- Set GPIO PB06 and PB07 as Open Drain with Pullup
  //      GPIO INPUT PUPD RESISTORS
  //      15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
  //      33 22 22 22 22 22 11 11 11 11 11 00 00 00 00 00
  //      10 98 76 54 32 10 98 76 54 32 10 98 76 54 32 10
  //      .. ..|.. ..|.. ..|.. ..|.. ..|.. ..|.. ..|.. ..
  //      00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  //      NP NP NP NP NP NP NP NP NP NP NP NP NP NP NP NP
  //  GPIOB Pins 6 & 7 Have Pullups
  GPIOB_PUPDR &= 0xFFFF0FFF;
  nop4;
  GPIOB_PUPDR &= 0x00005000;

  #ifdef I2C1DEBUG
    fnMsgOut_2 ("\r\nINIT I2C1 as Master @ 400 KHz Complete.\r\n");
  #endif

  //--- Clear Everything when starting
  I2C1_CR1 = 0x00000000;
  nop4;                                          //--- Dead Time

  //*******************************************************************************************
  //    Start of I2C1 Peripherial Initialization
  //*******************************************************************************************

  //--- Preset I2C1 Control Register 1
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
  //      . ERR_IE          07    On              //--- Error Interrupts Enabled
  //      . TC_IE           06    On              //--- Transfer Complete Enabled
  //      . STOP_IE         05    Off
  //      . NACK_IE         04    Off
  //      . ADDR_IE         03    Off
  //      . RX_IE           02    On              //--- RX Interrupt Enabled
  //      . TX_IE           01    On              //--- TX Interrupt Enabled
  //      . PERIPH_ENABLE   00    Off
  //
  I2C1_CR1 = 0x000000C6;                          //--- Note: PE NOT Enabled at this time
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
  //      . SCLL 3          03    Off
  //      . SCLL 2          02    Off
  //      . SCLL 1          01    Off
  //      . SCLL 0          00    Off
  //
  //  Setup for I2CCLK = HSI 16MHz SCL Freq = 400KHz
  //    PRESC   = 3
  //    SCLL    = 0x13
  //    SCLH    = 0x0F
  //    SDADLY  = 0X02
  //    SCLDLY  = 0x04
  //
  //      3322 2222 2222 1111 1111 1100 0000 0000
  //      1098 7654 3210 9876 5432 1098 7654 3210
  //      .... .... .... .... .... .... .... ....
  //      0011 0000 0100 0010 0000 1111 0001 0011
  //         3    0    4    2    0    F    1    3
  I2C1_TIMINGR = 0x30420F13;
  nop4;

  //--- Enable the I2C Interface
  I2C1_CR1 = 0x000000C7;                          //--- Note: Enable PE Bit Set
  nop4;                                           //--- Dead Time
}

//---------------------------------------------------------------------------------------------
//    I2C1 Reset Device
//---------------------------------------------------------------------------------------------
void  fnResetI2C1 (void)
{
  I2C1_CR1 &= 0xFFFFFFFE;                         //--- Release the Enable Bit

  //--- Wait for PE to Go Low
  While (I2C1_CR1 & 0x00000001)
  {
    nop4;
  }
}


  //---Send I2C Start Condition                              (Wait for Start Confirm)


//        . Set Start Bit in CR2
//        . Send I2C Address with R/W* bit set to 0 (Write)       (Wait for ACK)
//        . Send Byte Address Hi                                  (Wait for ACK)
//        . Send Byte Address Lo                                  (Wait for ACK)
//        . Send Data from Buffer Location "0"                    (Wait for ACK)
//        . Repeat For Buffer Addresses 1 to 31                   (Wait for ACK)
//    4.  Send STOP
//

//---------------------------------------------------------------------------------------------
//    Send I2C1 Addressing Command Sequence to slave
//    TrueAdds = Already shifted 7 bit address
//---------------------------------------------------------------------------------------------
u08   fnI2C1_Cmd_Seq (u08 ubTrueAdds, u08 ubRWflag)
{
  u32 ulI2C_CR2 = 0;
  u08 ubFlag = 0;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //--- Send Start and Command to Slave

  //----------------- I2C_CR2 ---------------
  //  3322 2222 2222 1111 1111 1100 0000 0000
  //  1098 7654 3210 9876 5432 1098 7654 3210
  //  .... .... .... .... .... .... .... ....
  //  0000 0000 ---- ---- 0011 0R00 AAAA AAA0
  //                            W
  ulI2C_CR2 = 0x00003000;                         //--- Set Up Start Condition
  ulI2C_CR2 |= ubTrueAdds;                        //--- Left Justified 7 Bit Address

  //--- Set the Read (1) Write (0) Flag
  if (ubRWflag)
    ulI2C_CR2 |= 0x00000400;
  else
    ulI2C_CR2 &= 0xFFFFFBFF;

  //--- Send Start & Command Sequence to I2C Device
  I2C1_CR2 = ulI2C_CR2;

  //--- Wait for response (ACK) up to 200 uSec
  ulFastTimeCount[3] = 2;
  while ulFastTimeCount[3]
  {
    if

}

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
//  !   . TXIS FLAG       01    Off   //--- TXIS TXD Enpty
//  !   . TXE FLAG        00    Off   //--- Tx Buffer Enpty
//---------------------------------------------------------------------------------------------

//--- Buffer and Pointer Definitions

//--- Sequence for Read 1 Byte















//--- EEPROM Always Accessed in "Page - 32 Byte" Format only

union DFLWB32 unI2C1_RXD;                         //--- Page Data Union
u32   ulI2C1_IP;                                  //--- In Buffer Byte Pointer
u08   ubI2C1_IC;                                  //--- In Buffer Byte Counter

u08*  I2CRX_PTR = &unI2C1_RXD.ubByte[0];

union DFLWB32 unI2C1_TXD;                         //--- Page Data Union
u32   ulI2C1_OP;                                  //--- Out Buffer Byte Pointer
u08   ubI2C1_OC;                                  //--- Out Buffer Byte Counter

u08*  I2CTX_PTR = &unI2C1_RXD.ubByte[0];

//---------------------------------------------------------------------------------------------
//  I2C Routine for I2C Page Memory Read (Onboard EEPROM)
//  EEPROM Address = 0x1010000R
//  Sequence =  START
//              DEVICE ADDRESS + WRITE(0)
//              ADDRESS HI BYTE - 000AAAAA
//              ADDRESS LO BYTE - AAAAAAAA
//
//---------------------------------------------------------------------------------------------

u08 fnReadI2C1_Page (u16 uwPageCount)
{
  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

}


//---------------------------------------------------------------------------------------------
//  I2C SetUp Routine for I2C Memory Read (Onboard EEPROM)
//  EEPROM Address = 0x1010000R
//  Sequence =  START
//              DEVICE ADDRESS + WRITE(0)
//              ADDRESS HI BYTE - 000AAAAA
//              ADDRESS LO BYTE - AAAAAAAA
//
//---------------------------------------------------------------------------------------------

u08 fnReadI2C1_Byte (u32 ulMadds, u16 uwCount)
{
  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

}



//---------------------------------------------------------------------------------------------
//    I2C1 Event Interrupt Services
//---------------------------------------------------------------------------------------------
void  fnI2C1_EV_IRQ (void)
{

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //--- Select What Kind of Interrupt Event this is

  //--- Is This an RXNE Condition?
  if (I2C1_ISR & 0x00000004)
  {
    //--- Reading the RXD REGISTER Clears the Interrupt
    ubI2C1RXD[ulI2C1_IP] = I2C1_RXDR;             //--- Read the Data to the buffer
    ulI2C1_IP++;                                  //--- Bump the Input Pointer
    ubI2C1_IC++;                                  //--- Bump the RX Counter
    //--- Clear Master I2C1 Interrupt Flags
    fnClrIntPend (I2C1_EV_IRQn);                  //--- Clear Master I2C Event Interrupt
    return;
  }

  //--- Is This a TX Empty Status Interrupt
  if (I2C1_ISR & 0x00000003)
  {
    if (ubI2C1_OC)                                //--- Are there still Bytes to Transmit
    {
      I2C1_TXDR = ubI2C1TXD[ubI2C1_OP];           //--- Write Next I2C Byte from TX Buffer
      ubI2C1_OP++;                                //--- Point to Next Character
      ubI2C1_OC--;                                //--- Decrement the counter
    }
    //--- Clear Master I2C1 Interrupt Flags
    fnClrIntPend (I2C1_EV_IRQn);                    //--- Clear Master I2C Event Interrupt
  }
}

//---------------------------------------------------------------------------------------------
//    I2C1 Error Interrupt Service Routine
//---------------------------------------------------------------------------------------------
void  fnI2C1_ER_IRQ (void)
{

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  //--- Select What Kind of Error Interrupt Happened

  //--- Is This An ALERT Error?
  //               33222222222211111111110000000000
  //               10987654321098765432109876543210
  if (I2C1_ISR & 0b00000000000000000010000000000000)
  {
    //--- Clear the ALERT ERROR
    I2C1_ICR |=  0b00000000000000000010000000000000;
  }

  //--- Is This An TIMEOUT Error?
  //               33222222222211111111110000000000
  //               10987654321098765432109876543210
  if (I2C1_ISR & 0b00000000000000000001000000000000)
  {
    //--- Clear the TIMEOUT ERROR
    I2C1_ICR |=  0b00000000000000000001000000000000;
  }

  //--- Is This A PEC Error?
  //               33222222222211111111110000000000
  //               10987654321098765432109876543210
  if (I2C1_ISR & 0b00000000000000000000100000000000)
  {
    //--- Clear the PEC ERROR
    I2C1_ICR |=  0b00000000000000000000100000000000;
  }

  //--- Is This An OverRun Error?
  //               33222222222211111111110000000000
  //               10987654321098765432109876543210
  if (I2C1_ISR & 0b00000000000000000000010000000000)
  {
    //--- Clear the OVERRUN ERROR
    I2C1_ICR |=  0b00000000000000000000010000000000;
  }

  //--- Is This A Arbitration Lost ERROR
  //               33222222222211111111110000000000
  //               10987654321098765432109876543210
  if (I2C1_ISR & 0b00000000000000000000001000000000)
  {
    //--- Clear the Arbitration Lost ERROR
    I2C1_ICR |=  0b00000000000000000000001000000000;
  }

  //--- Is This A BUSS ERROR?
  //               33222222222211111111110000000000
  //               10987654321098765432109876543210
  if (I2C1_ISR & 0b00000000000000000000000100000000)
  {
    //--- Clear the BUSS ERROR
    I2C1_ICR |=  0b00000000000000000000000100000000;
  }

  //--- Is This A STOP Detected Event
  //               33222222222211111111110000000000
  //               10987654321098765432109876543210
  if (I2C1_ISR & 0b00000000000000000000000100000000)
  {
    //--- Clear the NACK ERROR
    I2C1_ICR |=  0b00000000000000000000000100000000;
  }

  //--- Is This A ADDRESS Event?
  //               33222222222211111111110000000000
  //               10987654321098765432109876543210
  if (I2C1_ISR & 0b00000000000000000000000100000000)
  {
    //--- Clear the BUSS ERROR
    I2C1_ICR |=  0b00000000000000000000000100000000;
  }

  //--- Is This A BUSS ERROR?
  //               33222222222211111111110000000000
  //               10987654321098765432109876543210
  if (I2C1_ISR & 0b00000000000000000000000100000000)
  {
    //--- Clear the BUSS ERROR
    I2C1_ICR |=  0b00000000000000000000000100000000;
  }

  if (I2C_ISR & 0x0000 0000     //---!!! If statement is closed and has no condition code

  //--- Is This an RXNE Condition?
  if (I2C1_ISR & 0x00000004)
  {
    ubI2C1RXD[ubI2C1_IP] = I2C1_RXDR;             //--- Read the Data to the buffer
  }

  //--- TX Empty status Interrupt
  if (I2C1_ISR & 0x00000003)
  {
    if (ubI2C1_OC)                                //--- Are there Bytes to Transmit Still
    {
      I2C1_TXDR = ubI2C1TXD[ubI2C1_OP - 1];       //--- Write Next I2C Byte
      ubI2C1_OP++;                                //--- Point to Next Character
      ubI2C1_OC--;                                //--- Decrement the counter
    }

  }
  //--- Clear Master I2C1 Interrupt Flags to clear ERROR
  fnClrIntPend (I2C1_ER_IRQn);                    //--- Clear Master I2C Event Interrupt
}




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
