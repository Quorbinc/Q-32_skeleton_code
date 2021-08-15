//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

u32 ulValue;
u16 uwValue;
u08 ubValue;

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
//  31    LED Flag for Min/Max PACER LED BRIGHTNESS
//---------------------------------------------------------------------------------------------


int main (void)
{

  //--- Main Infinite Loop Entry Point Calls Dispatch_Call
  while (1)
  {
    if (uwTaskCntr > 0)
    {
      fnDispatchCall ();
    }

    //--- Add Any Polled functions Here
    //-------------------------------------------------------------------------------------------
    //    Test if there are bytes waiting in RX FIFO for USART1
    //-------------------------------------------------------------------------------------------
    uwRxData = fnGetNextUSART1 ();                  //--- See if Rx Data Available

    //--- If RX Data Ready then Immediately process it
    if (uwRxData & 0x8000)
    {
      GIE;
      //--- Add Call to Rx Processing Routine
      //--- fnRxProcessUSART1();
      nop4;                                         //--- Code Place Holder delete this
      GID;
    }
  }
}


