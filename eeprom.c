//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                       I2C EEPROM Interface Functions Processing Code
//                       ----------------------------------------------
//
//         This code is for use on the QMX_32 (STM32L432) Series of Micro Controllers
//
//                             Written By:  Sancar James Fredsti
//                                   (C) 2022 QUORB Inc.
//=============================================================================================

//--- Include projectdefs.h
#include projectdefs.h

#define EEPROM_ADDS 0xA0

u08   ubEEPROMdata[32];                             //--- Active EEPROM Read/Write Page
u32   ulEEPROMadds;                                 //--- Byte Address inside EEPROM
u16   uwEEPROMpage;                                 //--- Page number
u16   uwEEPROMoffset;                               //--- Byte Location within Page

//  struct EEPROM_Adds
//  {
//    u32 ulByteAddr;
//    u16 uwPageNum;
//    u16 uwBufferOffset;
//  };

//--- Driver Functions:
//      Read EEPROM Page    u08 fnReadEEPROMpage (u32 ulPageNumber)
//      Returns 0 if successful   !0 if Error

//      Write EEPROM Page  u08 fnWriteEEPROMpage (u32 ulPageNumber)
//      Returns 0 if successful   !0 if Error

//      Write_Page_Wait
//

//---------------------------------------------------------------------------------------------
//  EEPROM Page Write Page Numbers represent 32 Byte Pages (0 to 1023)(0x03FF)
//  Note: For Byte Address to Page Address conversion divide Byte Address by 32 (Shift >> 5)
//        It takes equal time to write 1 Byte to EEPROM as 32 Bytes
//
//  Upon Entry (uwPageNumber) contains Desired Page Number Value
//    0.  Shift and Mask Page Number Value into Byte Address Value
//    1.  Read EEPROM to obtain current Page Data in EEPROM Buffer
//                        OR
//    1.  Write New Page Data to EEPROM Buffer
//
//    2.  Modify EEPROM Buffer to change Data if necessary
//
//    3.  Start the EEPROM Write Sequence
//        . Send I2C Start Condition                              (Wait for Start Confirm)
//        . Send I2C Address with R/W* bit set to 0 (Write)       (Wait for ACK)
//        . Send Byte Address Hi                                  (Wait for ACK)
//        . Send Byte Address Lo                                  (Wait for ACK)
//        . Send Data from Buffer Location "0"                    (Wait for ACK)
//        . Repeat For Buffer Addresses 1 to 31                   (Wait for ACK)
//    4.  Send STOP
//
//  Wait for Write Cycle to Stop
//    5.  Send I2C Start Condition                                (Wait for Start Confirm)
//    6.  Send I2C Address with R/W = 0
//        Check ACK return After Write if OK (LOW) then
//        . Wait 1 mSec
//    7.  Repeat Steps 6 & 7 for upto 6 mSec
//    8.  Wait for ACK About
//
//  Optional Write Static Delay time of 6mSec
//
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//    EEPROM Page Write Function
//    --------------------------
//    This function assumes that the EEPROM Buffer already contains Data Page to be written
//---------------------------------------------------------------------------------------------

u08 fnWrite_EEPROM_Page (u16 uwPageNumber)
{
  u16 uwPageAddress;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //--- Shift Page Number into Page Address Start Position
  uwPageAddress = (uwPageNumber << 5) & 0x1FE0;

  //---Send I2C Start Condition                              (Wait for Start Confirm)


//        . Send I2C Address with R/W* bit set to 0 (Write)       (Wait for ACK)
//        . Send Byte Address Hi                                  (Wait for ACK)
//        . Send Byte Address Lo                                  (Wait for ACK)
//        . Send Data from Buffer Location "0"                    (Wait for ACK)
//        . Repeat For Buffer Addresses 1 to 31                   (Wait for ACK)
//    4.  Send STOP
//
}


//---------------------------------------------------------------------------------------------
//    EEPROM Page Write Function Wait
//---------------------------------------------------------------------------------------------
struct TaskRet tkEEPROMwait (union DFLWB unTD)
{
  struct  Task stWork;                              //--- Reschedueling Task Model
  struct  TaskRet stTaskRet;                        //--- Return Structure

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //--- First Test if EEPROM Write Timed Out


  //  1.0 Write Command Sequence to EEPROM via I2C Bus
  //  2.0 Did we get an ACK Bit?
  //
  //      Yes = Write Complete so exit with no errors
  //
  //      No  = Decrement unTD.ubByte[0]
  //            Is unTD.ubByte[0] == 0?
  //
  //            Yes = Failure of EEPROM Write
  //                  Return Error from Task
  //
  //            No =  Reschedule This Task


  //  2.0 Wait 8 nops
  //    Is unTD.ubByte[0] == 0?
  //      Yes = Failure of EEPROM Write
  //      No =
  //--- Reschedule This in 5 mSec
  stWork.uwTimer = 5;                               //--- Timer Delay = 5 mSec
  stWork.ptrTask = &tkEEPROMwait;                   //--- Reschedule This Task
  stWork.uwFlags = 0;                               //--- No Flags
  stWork.unTaskData = unTD;                         //--- Reverse Color Flag
  uwReturnVal = fnScheduleTask (stWork);

  if (uwReturnVal <> 0)
  {
    //--- Error in Schedueling
  }



  if (!unTD.ubByte[0])
  {
    //--- Red Light On
    CLR_PA01;
    ulSystemFlags &= 0xFFFFFFFE;                    //--- Clear Recursive Flag
    unTD.ubByte[0] = 0;
  }
  else
  {
    //--- Green Light On
    CLR_PA00;
    SET_PA01;
    ulSystemFlags |= 0x00000001;                    //--- Set Recursive Flag
    unTD.ubByte[0] = 0xFF;
  }

  //--- Reschedule This Once / Second
  stWork.uwTimer = 5;                               //--- Timer Delay = 5 mSec
  stWork.ptrTask = &tkRecursion;                    //--- Reschedule This Task
  stWork.uwFlags = 0;                               //--- No Flags
  stWork.unTaskData = unTD;                         //--- Reverse Color Flag
  uwReturnVal = fnScheduleTask (stWork);

  stTaskRet.uwErrorCode = 0;
  return stTaskRet;                                 //--- Return Schedule Error



}

//---------------------------------------------------------------------------------------------
//  EEPROM Page Read
//    3.  Input EEPROM PAGE Number 000PPPPP  PPP00000 as Byte in Page Address
//    4.  Start the EEPROM Write Sequence
//        . Send I2C Start Condition                              (Wait for Start Confirm)
//        . Send I2C Address with R/W* bit set to 0               (Wait for ACK)
//        . Send Byte Address Hi                                  (Wait for ACK)
//        . Send Byte Address Lo                                  (Wait for ACK)
//        . Send Data from Buffer Location "0"                    (Wait for ACK)
//        .   For Buffer Addresses 1 to 31 Repeat Transmit &      (Wait for ACK)
//    5.  Send STOP
//    6.  Send I2C Start Condition                              (Wait for Start Confirm)
//    7.  Send I2C Address with R/W = 0
//        Check ACK return if OK then
//        . Wait 1 mSec
//    8.  Repeat Steps 6 & 7 for upto
//    7.  Wait for ACK About
//
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//    EEPROM Page Read Function
//---------------------------------------------------------------------------------------------

u08 Read_EEPROM_Page (u16 uwPageNumber)
{

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

}









//---------------------------------------------------------------------------------------------
//    Schedueled Wait for EEPROM Write to conclude
//---------------------------------------------------------------------------------------------

u08 fnEEPROM_Page_Wait (void)
{
  if (ubEEPROM_Count)
  {
    ubEEPROM_Count--;
    if (!ubEEPROM_Count) return -1;           //--- Timeout Error Return

    //--- Send Start Sequence & Address & read
    SEND_START;

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
