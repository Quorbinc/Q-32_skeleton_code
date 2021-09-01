//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

//-=- Global Variables available to every function

u32 ulValue;                                      //--- Global Long (32 Bit)
u16 uwValue;                                      //--- Global Word (16 Bit)
u08 ubValue;                                      //--- Global Byte ( 8 Bit)

struct Task stWorkTask;                           //--- Global Task for schedueling

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
//  28                                    0 =                       1 =
//  29    EEPROM Write Busy               0 = Not Busy              1 = EEPROM Write Busy
//  30    Boot Complete Flag              0 = Booting               1 = Boot Complete
//  31    LED Flag for Min/Max PACER LED BRIGHTNESS Flag Bit
//---------------------------------------------------------------------------------------------


int main (void)
{

  //--- Main Infinite Loop Entry Point Calls DispatchCall
  while (1)
  {
    // u16 uwRxData;                                 //--- Data to be processed from GetNextUSART1

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //--- The Dispatcher is called from the main endless loop

    SET_PA05;
    fnDispatcher();
    CLR_PA05;

    nop12;
    //--- Add Any Polled or Loop Functions Here

    //-----------------------------------------------------------------------------------------
    //    Test if there are bytes waiting in RX FIFO for USART1
    //    If data is waiting it can be either Processes Now or Processed as a Task
    //-----------------------------------------------------------------------------------------
//    uwRxData = fnGetNextUSART1 ();                  //--- See if Rx Data Available

    //--- If RX Data Ready then Immediately process it
//    if (uwRxData & 0x8000)
//    {
//      GIE;
      //--- Add Call to Rx Processing Routine
      //    Or process as a Task

      // fnRxProcessUSART1();
//      nop4;                                         //--- Code Place Holder delete this
//      GID;
//    }
  }
}


