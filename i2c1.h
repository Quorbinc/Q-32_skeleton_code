//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                          I2C Interface Functions Processing Code
//                  -----------------------------------------------------
//
//    This code is for use on the STM32F446 Processor Series of Micro Controllers it is
//    It is not fully compatible with other STM32FXXX Series Micro Controller Products
//
//                             Written By:  Sancar James Fredsti
//
//=============================================================================================

//------------------------------------------------------------------------------------------//
//                       Program Defines and RAM Storage Definitions                        //
//------------------------------------------------------------------------------------------//

//--- Master Mode Set-Up

#ifndef I2C1_DVR_H
    #define I2C1_DVR_H
    #define EEPROM                                  //--- Automatic EEPROM Definition
    #define I2C1_BLEN   128                         //--- Useable TX & RX Buffer Length

    //          Bit Number  33222222222211111111110000000000
    //          MSB -> LSB  10987654321098765432109876543210
    //                    0b................................
    #define I2C1_BUSY     0b00001000000000000000000000000000  //--- I2C1 Transaction Busy
    #define I2C1_IDLE     ~I2C1_BUSY                          //--- I2C1 Transaction Not Busy

    extern u08   ubI2C1_TXB [I2C1_BLEN];            //--- Global TX FIFO Buffer
    extern u16   uwI2C1_TXIP;
    extern u16   uwI2C1_TXOP;
    extern u16   uwI2C1_TXC;

    extern u08   ubI2C1_RXB [I2C1_BLEN];            //--- Global RX FIFO Buffer
    extern u16   uwI2C1_RXIP;
    extern u16   uwI2C1_RXOP;
    extern u16   uwI2C1_RXC;

    extern u16   uwI2C1_TX_Count;

    extern u08*  ubI2C1_TXptr;                      //--- Tx Data Pointer
    extern u08*  ubI2C1_RXptr;                      //--- Rx Data Pointer

    //    extern u08 ubI2C1_TxNbytes;                     //--- Remaining # of Bytes to TX
    //    extern u08 ubI2C1_RxNbytes;                     //--- Remaining # of Bytes to RX


    //--- RTOS I2C1 Function Prototypes
    u16  fnMake_I2C1_Task (u16 uwDelay, u08 ubI2C_Adds, u08 ubTT, u16 uwNbytes, u08* ptDptr, union LWB unRegAdd);

    u32   tkI2C1_Task (union DFLWB16 unTD);

    u08   fnI2C1_Write (u08 ubTrueAdds, u32 ulReg_Add, u08 RegLen, u08 ubNbytes, u08 ubSpeed, u08* ubDptr);

    u08   fnI2C1_Read (u08 ubTrueAdds, u08 ubNbytes, u08* ubDptr);

    u16   fnI2C1_Get_Next_RX (void);

    void  fnInitI2C1_Master_Ops (u08 ubSpeed);
    void  fnResetI2C1 (void);

    void  fnI2C1_Event(void);                       //--- IRQ_31
    void  fnI2C1_Error(void);                       //--- IRQ_32

#endif
