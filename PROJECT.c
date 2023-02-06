//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

//-=- Global Variables available to every function

u32 ulValue;                                      //--- Global Long (32 Bit)
u16 uwValue;                                      //--- Global Word (16 Bit)
u08 ubValue;                                      //--- Global Byte ( 8 Bit)
u08 testvalue = 0;

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
  //--- setup for your program or initial tasks will be set here before the main loop
  
  //--- Main Infinite Loop entry point calls Dispatcher and any polled actions
  while (1)
  {
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- Output the STK_CTRL Value to PA06 & PA07

    fnDispatcher();

    //-----------------------------------------------------------------------------------------
    //    Add Any Polled Loop Functions Here
    //
    //    If required add a function call for any activities that are required to be handled
    //    in the "main" loop.
    //-----------------------------------------------------------------------------------------
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
