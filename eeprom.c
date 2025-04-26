//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                       I2C EEPROM Interface Functions Processing Code
//                       ----------------------------------------------
//
//         This code is for use on the QMX_32 (STM32L432) Series of Micro Controllers
//
//                             Written By:  Sancar James Fredsti
//                                   (C) 2022 QUORB Inc.
//=============================================================================================

//--- Include projectdefs.h
#include projectdefs.h

u08   ubEEPROM_Count;


union DFLWB32 unEEPROMpage;                         //--- Multiuse Union for EEPROM Page

//--- Functions:
//      Read EEPROM Page
//      Write EEPROM Page
//      Write_Page_Wait
//

//---------------------------------------------------------------------------------------------
//  EEPROM Page Write Page Numbers represent 32 Byte Pages (0 to 1023)(0x03FF)
//  Note: For Byte Address to Page Address conversion divide Byte Address by 32 (Shift >> 5)
//        It takes equal time to write 1 Byte to EEPROM as 32 Bytes
//
//  Upon Entry (uwPageNumber) contains Desired Page Number Value
//    0.  Shift and Mask Page Number Value into Byte Address Value
//    1.  Read EEPROM to obtain current Page Data in EEPROM Buffer
//                        OR
//    1.  Write New Page Data to EEPROM Buffer
//
//    2.  Modify EEPROM Buffer to change Data if necessary
//
//    3.  Start the EEPROM Write Sequence
//        . Send I2C Start Condition                              (Wait for Start Confirm)
//        . Send I2C Address with R/W* bit set to 0 (Write)       (Wait for ACK)
//        . Send Byte Address Hi                                  (Wait for ACK)
//        . Send Byte Address Lo                                  (Wait for ACK)
//        . Send Data from Buffer Location "0"                    (Wait for ACK)
//        . Repeat For Buffer Addresses 1 to 31                   (Wait for ACK)
//    4.  Send STOP
//
//  Wait for Write Cycle to Stop
//    5.  Send I2C Start Condition                                (Wait for Start Confirm)
//    6.  Send I2C Address with R/W = 0
//        Check ACK return After Write if OK (LOW) then
//        . Wait 1 mSec
//    7.  Repeat Steps 6 & 7 for upto 6 mSec
//    8.  Wait for ACK About
//
//  Optional Write Static Delay time of 6mSec
//
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//  EEPROM Page Write Function
//  --------------------------
//
//
//---------------------------------------------------------------------------------------------
u08 fnEEPROM_Page_Write (u16 uwMemoryPageAdds, u08* pubDptr);
{
    u16 uwCntr;
    u08 ubWriteBuffer[34];
    union WB unPageAdds;
    u08 ubRetVal;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- Process EEPROM Location Address
    unPageAdds.Word = uwMemoryPageAdds & 0xFFE0;
    ubWriteBuffer[0] = unPageAdds.Byte[1];          //--- Set Hi Address in Buffer
    ubWriteBuffer[1] = unPageAdds.Byte[0];          //--- Set Lo Address in Buffer

    //--- Copy Data to Write Data Buffer & Bump Pointer
    for (uwCntr = 0, uwCntr < 32, uwCntr++)
    {
        ubWriteBuffer[uwCntr + 2] = *pubDptr++;
    }

    //---------------------------------------------------------------------------------------------
    //    Send I2C1 Write Command Sequence to Slave
    //    TrueAdds = Already shifted 7 bit address
    //    ubNbytes = Number of Bytes to Transfer
    //    ubDptr   = Pointer to Data Source Location
    //
    //    EEPROM I2C True Adds = 0xA0
    //    Data Length = 2 Bytes Address + 32 Bytes
    //---------------------------------------------------------------------------------------------
    ubRetVal = fnI2C1_Write (EEPROM_ADDS , 34, &ubWriteBuffer);

    //--- If Wtite Command successful then pause 6 Msec
    if (!ubRetVal)
    {
        ulFastTimeCount[2] = 50;                      //--- Set Fast Time Counter for 5 mSec

        //--- Wait for 5.5 mSec for write to complete
        //    Execute Dispatcher While Waiting
        while (ulFastTimeCount[2])
        {
            //--- Cycle until Page Write Completes Default of 5 mSec
            fnDispatcher ();
            nop12;
        }
    }

    return ubRetVal;                                //--- Return 0 for success else error
}


//---------------------------------------------------------------------------------------------
//    EEPROM Page Read Function
//
//    This function reads 32 Bytes from the EEPROM located at the address in the EEPROM
//    designated by the address uwMemoryReadAdds & 0xFFE0.
//    0.  Read I2C1_RXD to Clear
//    1.  Write Start Configuration for Write of EEPROM Memory Address, 2 Bytes,Autoend = False
//    2.  Write 2 Bytes to EEPROM for Address
//    3.  Send Restart, for READ of 32 Bytes, AutoEnd = True
//    4.  Wait for RXNE
//    5.  Read I2C1_RXD and place byte @ pointer ubDptr++
//    6.  EEPROM Read Function will terminate after 32 Bytes are received
//---------------------------------------------------------------------------------------------

u08 fnEEPROM_Page_Read (u16 uwMemoryReadAdds, u08* ubDptr);
{
    u16 uwCntr;
    union WB unPageAdds;
    u08 ubRetVal;

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    //--- Process EEPROM Location Address
    unPageAdds.Word = uwMemoryReadAdds & 0xFFE0;    //--- Mask for page boundry
    ubWriteBuffer[0] = unPageAdds.Byte[1];          //--- Set Hi Address in Buffer
    ubWriteBuffer[1] = unPageAdds.Byte[0];          //--- Set Lo Address in Buffer

    //--- Copy Data to Write Data Buffer & Bump Pointer
    for (uwCntr = 0, uwCntr < 32, uwCntr++)
    {
        ubWriteBuffer[uwCntr + 2] = *pubDptr++;
    }

    //---------------------------------------------------------------------------------------------
    //    Send I2C1 Write Command Sequence to Slave
    //    TrueAdds = Already shifted 7 bit address
    //    ubNbytes = Number of Bytes to Transfer
    //    ubDptr   = Pointer to Data Source Location
    //
    //    EEPROM I2C True Adds = 0xA0
    //    Data Length = 2 Bytes Address + 32 Bytes
    //---------------------------------------------------------------------------------------------
    ubRetVal = fnI2C1_Write (EEPROM_ADDS , 34, &ubWriteBuffer);

    ubRetVal = fnI2C1_Write (EEPROM_ADDS , 34, &ubWriteBuffer);
}
