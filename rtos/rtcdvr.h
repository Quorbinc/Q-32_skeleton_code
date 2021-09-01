//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                    Real Time Clock Driver Header using STM32L4XX Proc
//                  -----------------------------------------------------
//
//    This code is for use on the STM32L432 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32FXXX Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//
//=============================================================================================

//--- Mulitdefine trap
#ifndef RTC_H
  #define RTC_H

  //--- NOTE: All Time is referenced to UTC.  Local Time Settings and DST are derived


  //--- Clock Time Structure Used for Time Stamps +in Milliseconds
  struct TimeDate                 //--- 10 Bytes
  {
    u08   ubType;                 //--- Type --> 0=UTC, 1=Local Std, 2=Local DST, 3=Sideral
    u08   ubYrs;                  //--- Year 00-99 Value
    u08   ubMth;                  //--- Month 01-12 Value
    u08   ubDay;                  //--- Date 01-31 Day of Month
    u08   ubDOW;                  //--- Day of the Week (1-7) = Mon-Sun (0) = unknown
    u08   ubHrs;                  //--- Hour of day 00-23
    u08   ubMin;                  //--- Minute of hour 00-59
    u08   ubSec;                  //--- Seconds of minute 00-59
    u16   uwMsec;                 //--- Milli Seconds of Current Second (000 - 999)
  };

  struct TimeDate stUTCTime;      //--- UTC Time
  struct TimeDate stLOCTime;      //--- Local Time
  struct TimeDate stSIDTime;      //--- Sideral Time
  struct TimeDate stJULTime;      //--- Julian Time

  //--- Set the RTC Depending on Type
  void  fnSetRTC (struct TimeDate stNewTime);

  //--- Read RTC to Structure
  struct TimeDate fnReadTime (u08 ubType);

#endif

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
