//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

//-=- Global Variables available to every function

u32 ulValue;                                      //--- Global Long (32 Bit)
u16 uwValue;                                      //--- Global Word (16 Bit)
u08 ubValue;                                      //--- Global Byte ( 8 Bit)

struct Task stGlobalTask;                         //--- Global Task for schedueling

#define ReleaseVersion 0x0100                     //--- Release 1.0

u32 volatile ulSystemFlags;                       //--- ulSystemFlags
//---------------------------------------------------------------------------------------------
//   System Flags Bit Map Definition 28 Bits of assignable System Flags
//---------------------------------------------------------------------------------------------
//  Bit   Function
//  ---   -------------------------------------------------------------------------------------
//  00                                    0 =                       1 =
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

struct Task stWorkTask;                         //--- Disposable Temp Task Definition


//---------------------------------------------------------------------------------------------
//    Main Program Entry Point Add your user code
//---------------------------------------------------------------------------------------------
int main (void)
{
  u32  ulC;

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //--- Main Infinite Loop entry point calls Dispatcher and any polled actions
  while (1)
  {
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    #ifdef TESTHELP_FLAG
      // fnPulseLongOut (fnReadCPUregister(20));     //--- Show System CONTROL
      fnPulseLongOut (0x00FF0F35);     //--- Pulse Out Orientation
    #endif

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

    //--- The Dispatcher is called from the main endless loop

    //--- Spacing Delay
    for (ulC = 0; ulC < 10; ulC++)
    {
      nop4;
    }

    fnDispatcher();

    //-----------------------------------------------------------------------------------------
    //    Add Any Polled Loop Functions Here
    //
    //    If required add a function call for any activities that are required to be handled
    //    in the "main" loop.
    //-----------------------------------------------------------------------------------------

  }
}
