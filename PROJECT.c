//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

//-=- Global Variables available to every function

u32 ulValue;                                      //--- Global Long (32 Bit)
u16 uwValue;                                      //--- Global Word (16 Bit)
u08 ubValue;                                      //--- Global Byte ( 8 Bit)

#define ReleaseVersion 0x0100                     //--- Release 1.0

u32 volatile ulSystemFlags;                       //--- ulSystemFlags
//---------------------------------------------------------------------------------------------
//   System Flags Bit Map Definition 28 Bits of assignable System Flags
//---------------------------------------------------------------------------------------------
//  Bit   Function
//  ---   -------------------------------------------------------------------------------------
//  00    Recursion Mode Flag             0 = Flash Red             1 = Flash Green
//  01                                    0 =                       1 =
//  02                                    0 =                       1 =
//  03                                    0 =                       1 =
//
//  04                                    0 =                       1 =
//  05                                    0 =                       1 =
//  06                                    0 =                       1 =
//  07                                    0 =                       1 =
//
//  08                                    0 =                       1 =
//  09                                    0 =                       1 =
//  10                                    0 =                       1 =
//  11                                    0 =                       1 =
//
//  12                                    0 =                       1 =
//  13                                    0 =                       1 =
//  14                                    0 =                       1 =
//  15                                    0 =                       1 =
//
//  16                                    0 =                       1 =
//  17                                    0 =                       1 =
//  18                                    0 =                       1 =
//  19                                    0 =                       1 =
//
//  20                                    0 =                       1 =
//  21                                    0 =                       1 =
//  22                                    0 =                       1 =
//  23                                    0 =                       1 =
//
//  24                                    0 =                       1 =
//  25                                    0 =                       1 =
//  26                                    0 =                       1 =
//  27                                    0 =                       1 =
//
//  28    SysTick Error Flag              0 = Everything is OK      1 = Something screwed UP
//  29    EEPROM Busy                     0 = Not Busy              1 = EEPROM Write Busy
//  30                                    0 =                       1 =
//  31    LED Flag for Min/Max PACER LED BRIGHTNESS Flag Bit
//---------------------------------------------------------------------------------------------

//
//  //--- 24 Bytes / Task
//  struct Task
//  {
//    u32     ulTimer;                            //--- Timer delay Value (0 - 4G milliseconds)
//    void    (*ptrTask);                         //--- Address Pointer to Task
//    struct  TaskData stTaskData;                //--- Generic stPassData Structure
//      8 Bytes Time Stamp;                       //--- .uxTimeStamp
//      union DFLWB                               //--- Data Union unTaskData
//  };
//
//
//  Task Function Definition:
//  fnFunctionName (struct PassData stTaskData)
//

//---------------------------------------------------------------------------------------------
//    Main Program Entry Point Add your user code
//---------------------------------------------------------------------------------------------
int main (void)
{

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


  //--- Output Start Message on USART #2
  fnStringOut_2 ("\r\nQuorb is Alive, Mu Ah Ah Ah! \r\n Ready --> ");


  //--- Main Infinite Loop entry point calls Dispatcher and any polled actions
  while (1)
  {
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    #ifdef TESTHELP_FLAG
      u32   ulC;

      // fnPulseLongOut (fnReadCPUregister(20));     //--- Show System CONTROL
      fnPulseLongOut (0x00FF0F35);     //--- Pulse Out Orientation

      //--- Spacing Delay
      for (ulC = 0; ulC < 10; ulC++)
      {
        nop4;
      }

    //--- Output the STK_CTRL Value to PA06 & PA07
      fnPulseLongOut (STK_CTRL);

      //--- Spacing Delay
      for (ulC = 0; ulC < 10; ulC++)
      {
        nop4;
      }

    //--- Pulse Out STK_LOAD Value
      fnPulseLongOut (STK_LOAD);

      //--- Spacing Delay
      for (ulC = 0; ulC < 10; ulC++)
      {
        nop4;
      }
    #endif

    //--- The Dispatcher is called from the main endless loop
    fnDispatcher();

    //-----------------------------------------------------------------------------------------
    //    Add Any Polled Loop Functions Here
    //
    //    If required add a function call for any activities that are required to be handled
    //    in the "main" loop.
    //-----------------------------------------------------------------------------------------

    //--- Process the USART1 Rx
    #ifdef USART1_FLAG
      u16   uwRX1;                                //--- Local storage for USART1

      uwRX1 = fnGetNextUSART1();                  //--- Test to see if RX Data Ready on USART1
      //--- Data Ready if Bit 15 is Set
      if (uwRX1 & 0x8000)
      {
        //--- Call or Schedule Rx Processing for USART #1
      }
    #endif

    //--- Process the USART2 Rx
    #ifdef USART2_FLAG
      u16   uwRX2;                                //--- Local storage for USART2

      uwRX2 = fnGetNextUSART2();                  //--- Test to see if RX Data Ready on USART2
      //--- Data Ready if Bit 15 is Set
      if (uwRX2 & 0x8000)
      {
        //--- Call or Schedule Rx Processing for USART #2
      }
    #endif

  }
}


  //-------------------------------------------------------------------------------------------
  //  Task Definition
  //-------------------------------------------------------------------------------------------
  //
  //  //--- 16 Bytes / Task
  //  struct Task
  //  {
  //    u16     uwTimer;                            //--- Task Timer delay value (0 - 65535 mSec)
  //    u16     uwFlags;                            //--- Temporary Flags to Pass
  //    void    (*ptrTask);                         //--- Address Pointer of Task
  //    union DFLWB unTaskData;                     //--- Generic unDFLB Data Union
  //  };
  //
  //  Task Function Definition:
  //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //  ALL Tasks MUST use this Function Definition
  //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //
  //  (u16) uwRetCode fnFunctionName (u32 ulTimeStamp, union DFLWB unTaskData)
  //
  //-------------------------------------------------------------------------------------------
  //  Task Data Union Definition
  //-------------------------------------------------------------------------------------------
  //
  //  union DFLWB                                   //--- 8 Bytes Binary / Integer Storage
  //  {
  //    dbl   dfFlt;                                //--- 1 Double Precision Float
  //    u64   uxLL;                                 //--- 1 Unsigned 64 Bit Long Long Integer
  //    s64   sxLL;                                 //--- 1 Signed 64 Bit Long Long Integer
  //    u08*  ubPtr[2];                             //--- 2 General Purpose Byte Pointers
  //    void* vPntr[2];                             //--- 2 Void Type Pointers
  //    flt   sfFlt[2];                             //--- 2 Single Precision Floats
  //    u32   ulLong[2];                            //--- 2 Unsigned Long
  //    s32   slLong[2];                            //--- 2 Signed Long
  //    u16   uwWord[4];                            //--- 4 Unsigned Words (16 Bit)
  //    s16   swWord[4];                            //--- 4 Signed Words (16 Bit)
  //    u08   ubByte[8];                            //--- 8 Unsigned Bytes
  //    s08   sbByte[8];                            //--- 8 Signed Bytes
  //  };
  //
  //
  //-------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//  Task To Flip Test LED on PA00 & PA01 from Red to Green
//  This Task Recursivily scheduels it self at 1000 mSec Intervals
//---------------------------------------------------------------------------------------------
u16  tkRecursion (union DFLWB unTD)
{
  struct  Task stWork;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //--- Reverse Polarity to Solve Task
  if (unTD.ubByte[0] != 0)
  {
    //--- Red Light On
    SET_PA00;
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

  //--- Print String to UART#2
  fnStringOut_2 ("OkiDoki Message Out\r\n");        //--- 21 Characters

  //--- Reschedule This Once / Second
  stWork.uwTimer = 333;                             //--- Timer Delay = 333 mSec
  stWork.ptrTask = &tkRecursion;                    //--- Reschedule This Task
  stWork.uwFlags = 0;                               //--- No Flags
  stWork.unTaskData = unTD;                         //--- Reverse Color Flag

  uwReturnVal = fnScheduleTask (stWork);
  return uwReturnVal;                               //--- Return Schedule Error
}


//|....|....|....*....|....|....*....|....|....^....|....|....*....|....|....*....|....|....|..

//=============================================================================================
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------

  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //-------------------------------------------------------------------------------------------
  //
  //-------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------
    //
    //-----------------------------------------------------------------------------------------

      //---------------------------------------------------------------------------------------
      //
      //---------------------------------------------------------------------------------------

