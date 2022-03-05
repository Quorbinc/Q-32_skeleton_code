//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

int main (void)
{
    PC15_OUT; //--- Set output pin
    
    //--- Main Infinite Loop Entry Point
    while (1)
    {
        //--- Add any Polling Loop type functions here
        
        //--- a demo code snippet.  Feel free to delete the below 4 lines of code.
        SET_PC15; //--- Set pc15 high
        fnSimpleDelay(2500);
        CLR_PC15; //--- Set pc15 low
        fnSimpleDelay(2500);
    }
}

