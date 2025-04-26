//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

extern  u32 ulValue;
extern  u16 uwValue;
extern  u08 ubValue;
extern  u32 volatile ulSystemFlags;                         //--- ulSystemFlags

int main (void);

//--- Recursive Routine Sample Function
u16   tkRecursion (union DFLWB16 unTD);

//--- If you write any functions in PROJECT.c, place their signatures here.
