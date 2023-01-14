//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

extern  u32 ulValue;
extern  u16 uwValue;
extern  u08 ubValue;
extern  struct Task stGlobalTask;                           //--- Global Task for schedueling
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
//  30    Unhandled Error                 0 = All Errors Clear      1 = Pending Error Event
//  31    LED Flag for Min/Max PACER LED BRIGHTNESS Flag Bit
//---------------------------------------------------------------------------------------------

extern  u32 volatile ulSystemFlags;                         //--- ulSystemFlags

int main (void);

//--- Recursive Routine Sample Function
//void fnRecursive (union DFLWB unTaskData);
