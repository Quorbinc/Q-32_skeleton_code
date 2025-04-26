//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                    Real Time Clock Driver Code using STM32L4XX Proc
//                  -----------------------------------------------------
//
//    This code is for use on the STM32L432 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32FXXX Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//
//=============================================================================================

#include "projectdefs.h"

//--- Set Real Time Clock to supplied Time, Date, Seconds, Type
void  fnSetRTC (struct TimeStamp stNewTime)
{
    //--- insert code if needed.
}

//--- Read current time from RTCand  return value based on Type Requested
//    0 = UTC / GMT
//    1 = Local STD Standard Time
//    2 = Local DST Day Light Savings
//    3 = Sideral Time
//    4 = Moscow Standard Time
//    5 = Special Format Time
struct TimeStamp fnReadTime (u08 ubType)
{
    //--- insert code if needed.
}
