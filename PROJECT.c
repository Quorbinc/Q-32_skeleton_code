//--------------------------------------------------------------------------------------------
//  "main" entry point
//--------------------------------------------------------------------------------------------

#include "projectdefs.h"

//-=- Global Variables available to every function

u32 ulValue;                                      //--- Global Long (32 Bit)
u16 uwValue;                                      //--- Global Word (16 Bit)
u08 ubValue;                                      //--- Global Byte ( 8 Bit)

#define ReleaseVersion 0x0100                     //--- Release 1.0

u32 volatile ulSystemFlags;                       //--- ulSystemFlags

//---------------------------------------------------------------------------------------------
//    Main Program Entry Point Add your user code
//---------------------------------------------------------------------------------------------
int main (void)
{
    //--- Main Infinite Loop entry point calls Dispatcher and any polled actions
    while (1)
    {
        //--- The Dispatcher is called from the main endless loop
        fnDispatcher();

        //-----------------------------------------------------------------------------------------
        //    Add Any Polled Loop Functions Here
        //
        //    If required add a function call for any activities that are required to be handled
        //    in the "main" loop.
        //-----------------------------------------------------------------------------------------
    }
}

//---------------------------------------------------------------------------------------------
//  Task To Flip Test LED on PA00 & PA01 from Red to Green
//  This Task Recursivily scheduels it self at 1000 mSec Intervals
//  Feel free to remove it if you see fit.
//---------------------------------------------------------------------------------------------

//--- changed DFLWB to DFLWB16 to accomidate task date size.
u16  tkRecursion (union DFLWB16 unTD)
{
    struct  Task stWork;

    //--- Reverse Polarity to Solve Task
    if (unTD.ubByte[0] != 0)
    {
        //--- Red Light On
        SET_PA00;
        CLR_PA01;
        ulSystemFlags &= 0xFFFFFFFE;                    //--- Clear Recursive Flag
        unTD.ubByte[0] = 0;
    }
    else
    {
        //--- Green Light On
        CLR_PA00;
        SET_PA01;
        ulSystemFlags |= 0x00000001;                    //--- Set Recursive Flag
        unTD.ubByte[0] = 0xFF;
    }

    //--- Print String to UART#2
    //fnStringOut_2 ("OkiDoki Message Out\r\n");        //--- 21 Characters

    //--- Reschedule This Once / Second
    stWork.uwTimer = 333;                             //--- Timer Delay = 333 mSec
    stWork.ptrTask = &tkRecursion;                    //--- Reschedule This Task
    stWork.uwFlags = 0;                               //--- No Flags
    stWork.unTaskData = unTD;                         //--- Reverse Color Flag

    uwReturnVal = fnScheduleTask (stWork);
    return uwReturnVal;                               //--- Return Schedule Error
}
