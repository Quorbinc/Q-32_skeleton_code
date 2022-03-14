//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

//-=- Global Variables available to every function

struct Task stGlobalTask;                         //--- Global Task for schedueling

//---------------------------------------------------------------------------------------------
//   System Flags Bit Map Definition
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
//  29    EEPROM Write Busy               0 = Not Busy              1 = EEPROM Write Busy
//  30    Boot Complete Flag              0 = Booting               1 = Boot Complete
//  31    LED Flag for Min/Max PACER LED BRIGHTNESS Flag Bit
//---------------------------------------------------------------------------------------------

//
//  //--- 24 Bytes / Task
//  struct Task
//  {
//    u32     ulTimer;                            //--- Timer delay Value (0000 - 4G milliseconds)
//    void    (*ptrTask);                         //--- Address Pointer to Task
//    struct  PassData stPassData;                //--- Generic stPassData Structure
//      8 Bytes Time Stamp;                       //--- .uxTimeStamp
//      union DFLWB                               //--- Data Union unTaskData
//  };
//
//
//  Task Function Definition:
//  fnFunctionName (struct PassData stTaskData)
//

//---------------------------------------------------------------------------------------------
//    Main Program Entry Point
//---------------------------------------------------------------------------------------------
int main (void)
{
  struct Task stWorkTask;                         //--- Disposable Temp Task Definition

  //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  //--- If Testing Enabled then schedule recursive timer Task
  #ifdef TESTHELP_FLAG
    //--- Schedule the recursive timer funtion
    stWorkTask.ulTimer = 333;                       //--- Schedule once per 333 mSec
    stWorkTask.ptrTask = &fnRecursive;
    stWorkTask.stPassData = fnEmptyData();
    fnScheduleTask (stWorkTask);
  #endif



  //--- Main Infinite Loop Entry Point Calls DispatchCall
  while (1)
  {
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- The Dispatcher is called from the main endless loop

    fnDispatcher();

    #ifdef TESTHELP_FLAG
      fnPulseLongOut (ulSystemFlags);
    #endif


    //-----------------------------------------------------------------------------------------
    //--- Add Any Polled or Loop Functions Here
    //-----------------------------------------------------------------------------------------

  }
}


//---------------------------------------------------------------------------------------------
//    Recursive Timer Task for testing 3 times / second
//    This is an example routine for recursivly scheduling a recurring task
//---------------------------------------------------------------------------------------------
#ifdef TESTHELP_FLAG
  void fnRecursive (struct PassData stPassData)
  {
    struct Task stWorkTask;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    stWorkTask.ulTimer = 333;                           //--- Schedule once per 333 mSec
    stWorkTask.ptrTask = &fnRecursive;

    //--- Is the Color Red (1) or Green (0)
    if (stPassData.unTaskData.ulLong[0] & 0x00000001)
    {
      //--- Illuminate the RED LED
      stPassData.unTaskData.ulLong[0] = 0x00000000;
      SET_PA04;
      CLR_PA05;
    }
    else
    {
      //--- Illuminate the GREEN
      stPassData.unTaskData.ulLong[0] = 0x00000001;
      SET_PA05;
      CLR_PA04;
    }

    stWorkTask.stPassData = stPassData;               //--- Pass the data basc to the new task
    fnScheduleTask (stWorkTask);                      //--- Schedule it
  }
#endif

//=============================================================================================
//     Standardized comment blocks
//=============================================================================================

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
