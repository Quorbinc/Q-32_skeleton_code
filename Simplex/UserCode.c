//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

u32 ulValue;
u16 uwValue;
u08 ubValue;

u64 uxNextTime;


int main (void)
{
  //--- Main Infinite Loop Entry Point
  while (1)
  {
    GIE;
    if (uxNextTime < uxSysTicker)
    {
      uxNextTime = uxSysTicker + (u64) 10000;
      if (ubValue & 0x01)
      {
        SET_PA11;
      }
      else
      {
        CLR_PA11;
      }

      ubValue++;
    }

    SET_PA04;
    nop24;
    CLR_PA04;

    //--- Add any Polling Loop type functions here

  }
}

