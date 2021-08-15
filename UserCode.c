//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

  u32 ulValue;
  u16 uwValue;
  u08 ubValue;

void timeDelay (u32 uwDelay)
{
  for (int i = 0; i < uwDelay; i++)
  {
    nop100;
  }
}

int main (void)
{
  u32 uwDelay; //was a u16 changed to u32

  //--- Main Infinite Loop Entry Point
  while (1)
  {
    SET_PB00;
    timeDelay(100000);
    CLR_PB00;
    timeDelay(100000);

    //----------below is old code I was using----------//
    /*
    //--- Turn On the Pacer LED pin to GND
    CLR_PC15;

    for (uwDelay = 0; uwDelay < 320000; uwDelay++) //uwdelay was 16000
    {
      SET_PB01;
      nop100;
      CLR_PB01;
      nop100;
    }

    //--- Turn off PACER LED
    SET_PC15;

    for (uwDelay = 0; uwDelay < 320000; uwDelay++) //uwdelay was 16000
    {
      SET_PB01;
      nop100;
      CLR_PB01;
      nop100;
    */
    //----------above is old code I was using----------//
  }
}
