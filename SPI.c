//=============================================================================================
//                                        Quorb Inc.
//                                -------------------------
//
//                                   SPI communications
//
//                           Written By:  Ethan James Fredsti
//
//                                Created: 11 March 2025
//
//               Code based on tutorials and sourcecode by cntrollerstech and z-the-programmer
//               https://controllerstech.com/spi-using-registers-in-stm32/
//               https://github.com/Z-The-Programmer
//
//=============================================================================================

#include "projectdefs.h"

#ifdef SPI1_FLAG

    void fnInitSPI1_SSM(void) //---Initialize SPI1
    {
        //--- Set all SPI registers that can be software written to reset
        SPI1_CR1 = 0x0000;
        SPI1_CR2 = 0x0700;
        SPI1_DR = 0x0000;
        SPI1_CRCPR = 0x0007;

        //--- configure GPIO pins for SPI
        PA04_OUT;    //--- PA04 set to output mode
        PA04_VHS;    //--- Set to very high speed

        PA05_ALT;    //--- PA05 set to alternate function mode.
        PA05_AF05;   //--- set PA05 to AF5 for SPI_SCK
        PA05_VHS;

        PA06_ALT;    //--- PA06 set to alternate function mode.
        PA06_AF05;   //--- set PA06 to AF5 for SPI_MISO
        PA06_VHS;

        PA07_ALT;    //--- PA07 set to alternate function mode.
        PA07_AF05;   //--- set PA07 to AF5 for SPI_MOSI
        PA07_VHS;

        SPI1_CR1 |= 0x033C;     //--- MSTR, MSBFIRST, SSM, and SSI bits are enabled BR set to 111 for 281.25 KHz

        SPI1_CR2 = 0x1700;      //--- FRXTh bit enabled, Data size set to 8 bits.

        SPI1_ENA;

        nop4;
    }

    void fnSPI1_TX(u08 ubData)
    {
        while(((SPI1_SR)&(1 << 7)) || (!((SPI1_SR)&(1 << 1)))) {}   //--- Wait for SPI to not be busy and TX buffer to clear.
        *(vu08*)&SPI1_DR = ubData;                                  //--- Treat SPI1_DR as a volatile 8 bit number, and write the target data to it.
        ubData = (u08)SPI1_DR;                                      //--- Read SPI1_DR back to clear RXFIFO.  having ubData read SPI1_DR avoids unused variable warning.
    }

    u08 fnSPI1_RX(void)
    {
        u08 ubRxData = 0;               //--- Define return data variable
        fnSPI1_TX(0x00);                //--- Transfer a dummy byte
        while(!((SPI1_SR)&(1 << 0))){}  //--- Waitfor the RX buffer to fill.
        ubRxData = SPI1_DR;
        return ubRxData;
    }

#endif



#ifdef SPI3_FLAG

    void fnInitSPI3_SSM(void) //---Initialize SPI3
    {
        //--- Set all SPI registers that can be software written to reset
        SPI3_CR1 = 0x0000;
        SPI3_CR2 = 0x0700;
        SPI3_DR = 0x0000;
        SPI3_CRCPR = 0x0007;

        //--- configure GPIO pins for SPI
        PA15_OUT;    //--- PA15 set to output mode
        PA15_VHS;    //--- Set to very high speed

        PB03_ALT;    //--- PB03 set to alternate function mode.
        PB03_AF06;   //--- set PB03 to AF5 for SPI_SCK
        PB03_VHS;

        PB04_ALT;    //--- PB04 set to alternate function mode.
        PB04_AF06;   //--- set PB04 to AF5 for SPI_MISO
        PB04_VHS;

        PB05_ALT;    //--- PB05 set to alternate function mode.
        PB05_AF06;   //--- set PB05 to AF5 for SPI_MOSI
        PB05_VHS;

        SPI3_CR1 |= 0x033C;     //--- MSTR, MSBFIRST, SSM, and SSI bits are enabled BR set to 111 for 281.25 KHz

        SPI3_CR2 = 0x1700;      //--- Enable the FRXth bit.  Set data size to 8 bits

        SPI3_ENA;

        nop4;
    }

    void fnSPI3_TX(u08 ubData)
    {
        while(((SPI3_SR)&(1 << 7)) || (!((SPI3_SR)&(1 << 1))));     //--- Wait for SPI to not be busy and TX buffer to clear.
        *(vu08*)&SPI3_DR = ubData;                                  //--- Treat SPI3_DR as a volatile 8 bit number, and write the target data to it.
        ubData = (u08)SPI3_DR;                                      //--- Read SPI1_DR back to clear RXFIFO.  having ubData read SPI1_DR avoids unused variable warning.
    }

    u08 fnSPI3_RX(void)
    {
        u08 ubRxData = 0;               //--- Define return data variable
        fnSPI3_TX(0x00);                //--- Transfer a dummy byte
        while(!((SPI3_SR)&(1 << 0))){}  //--- Waitfor the RX buffer to fill.
        ubRxData = SPI3_DR;
        return ubRxData;
    }

#endif
