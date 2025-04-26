
//=============================================================================================
//                                Fredsti Industries,  Ltd.
//                                -------------------------
//
//                      USART and Communications Including USB C2102
//
//                           Written By:  Sancar James Fredsti
//
//                                Created: 01 August 2007
//
//=============================================================================================

//---------------------------------------------------------------------------------------------
//                        Program Defines and RAM Storage Definitions
//---------------------------------------------------------------------------------------------

#ifndef USART_H
    #define USART_H

    //-------------------------------------------------------------------------------------------
    //                        USART Peripheral Driver Definitions
    //-------------------------------------------------------------------------------------------
    #ifdef USART1_FLAG
        #define USART1_RX_SIZE        1024              //--- Up to 1024 Characters for RX FIFO
        #define USART1_TX_SIZE        1024              //--- Up to 1024 Characters for TX FIFO
        #define USART1_MAX_TX_IN      1022              //--- Up to 1022 Characters ready to go out

        //--- Define USART Set-Up
        #define USART1_PARITY         0                 //--- Typically no Parity
        #define USART1_LEN            8                 //--- Typically 8 Bits Data Len
        #define USART1_BAUD           4800            //--- Typically 115200 Baudrate

        //--- Systick XMIT Delay
        #define XMIT_1_DELAY (u16)(SYS_TICK_FREQ / (USART1_BAUD / 10)) + 1;

        //--- USART Channel #1 Definitions
        extern    u16   uwUSART1TxCntr;                 //--- Tx Chr Cntr
        extern    u16   uwUSART1TxIptr;                 //--- Tx In Pointer
        extern    u16   uwUSART1TxOptr;                 //--- Tx Out Pointer
        extern    u08   ubUSART1TxFIFO[USART1_TX_SIZE]; //--- Tx Data FIFO

        extern    u16   uwUSART1RxCntr;                 //--- Rx Chr Cntr
        extern    u16   uwUSART1RxIptr;                 //--- Rx In Pointer
        extern    u16   uwUSART1RxOptr;                 //--- Rx Out Pointer
        extern    u08   ubUSART1RxFIFO[USART1_RX_SIZE]; //--- Rx Data FIFO

        extern    u16   uwUSART1_DelCnt;                //--- Baud Rate Delay Counter

        extern    u08   ubTxt_1[256];                     //--- Generic Message Constructor String
        extern    u08   ubStr_1[128];                     //--- Sub Constructor String

        //--- USART Control Functions
        void fnInitUSART1 (u32 ulBaud);                   //--- Initialize USART1 Communications
        u16  fnGetNextUSART1 (void);
        void  fnXmitSvc_1 (void);
        void  fnByteToFIFO_1 (u08 ubChar);
        u16 fnStringOut_1 (u08 ubOut[]);
        u16 fnArrayOut_1 (u08 ubOut[], u16 uwArraySize);
        void fnUsart1_Recieve(void);
    #endif

    //-----------------------------------------------------------------------------------------
    //            IF USART #2 is defined
    //-----------------------------------------------------------------------------------------
    #ifdef USART2_FLAG
        #define USART2_RX_SIZE       1024               //--- 1024 Bytes
        #define USART2_TX_SIZE       1024               //--- 1024 Bytes
        #define USART2_MAX_TX_IN     1022               //--- Up to 1022 Characters ready to go out

        //--- Define USART Set-Up
        #define USART2_PARITY         0                 //--- Typically no Parity
        #define USART2_LEN            8                 //--- Typically 8 Bits Data Len
        #define USART2_BAUD           4800            //--- Typically 115200 Baudrate

        //--- Systick XMIT Delay
        #define XMIT_2_DELAY (u16)(SYS_TICK_FREQ / (USART2_BAUD / 10)) + 1;

        //--- USART Channel #1 Definitions
        extern    u16   uwUSART2TxCntr;                 //--- Tx Chr Cntr
        extern    u16   uwUSART2TxIptr;                 //--- Tx In Pointer
        extern    u16   uwUSART2TxOptr;                 //--- Tx Out Pointer
        extern    u08   ubUSART2TxFIFO[USART2_TX_SIZE]; //--- Tx Character FIFO

        extern    u16   uwUSART2RxCntr;                 //--- Rx Chr Cntr
        extern    u16   uwUSART2RxIptr;                 //--- Rx In Pointer
        extern    u16   uwUSART2RxOptr;                 //--- Rx Out Pointer
        extern    u08   ubUSART2RxFIFO[USART2_RX_SIZE]; //--- Rx Character FIFO

        extern    u16   uwUSART2_DelCnt;                //--- Character Spacing Delay 100uSec

        extern    u08   ubTxt_2[256];                   //--- Generic Message Constructor String
        extern    u08   ubStr_2[128];                   //--- Sub Constructor String

        //--- USART Control Functions
        void  fnInitUSART2 (u32 ulBaud);                   //--- Initialize USART2 Communications
        u16   fnGetNextUSART2 (void);
        void  fnUSART2_XmitSvc (void);
        void  fnByteToFIFO_2 (u08 ubChar);
        u16 fnStringOut_2 (u08 ubOut[]);
        u16 fnArrayOut_2 (u08 ubOut[], u16 uwArraySize);
        void fnUsart2_Recieve(void);
    #endif
#endif
