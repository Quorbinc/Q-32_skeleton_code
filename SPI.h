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

#ifndef SPI_H
    #define SPI_H
    #ifdef SPI1_FLAG
        #define SPI1_ENA SPI1_CR1 |= 0x0040;     //--- Enable SPI
        #define SPI1_DIS SPI1_CR1 &= 0xFFBF;     //--- Disable SPI

        void fnInitSPI1_SSM(void);
        void fnSPI1_TX(u08 ubData);
        u08 fnSPI1_RX(void);
    #endif

    #ifdef SPI3_FLAG
        #define SPI3_ENA SPI3_CR1 |= 0x0040;     //--- Enable SPI
        #define SPI3_DIS SPI3_CR1 &= 0xFFBF;     //--- Disable SPI

        void fnInitSPI3_SSM(void);
        void fnSPI3_TX(u08 ubData);
        u08 fnSPI3_RX(void);
    #endif
#endif
