/******************************************************************************************
 * spi_master.c
 * ver1.00
 * Hirofumi Hamada
 *=========================================================================================
 * dsPIC30F6014A用SPI通信(Master)用ライブラリソースファイル
 *
 *=========================================================================================
 * ・ver1.00 || 初版作成 || 2016/01/04 || Hirofumi Hamada
 *   初版作成
 *=========================================================================================
 * dsPIC30F6014A
 * XC16(v1.25/MacOSX)
 * MPLAB X IDE(v3.15/MacOSX)
 *=========================================================================================
 * Created by fabsat Project(Tokai university Satellite Project[TSP])
 *****************************************************************************************/
#include <xc.h>
#include "spi_master.h"


/*=====================================================
 * @brief
 *     Initialize SPI(Master)
 * @param
 *     none:
 * @return
 *     none:
 * @note
 *     Enable SPI1
 *     Pin45:SCK1(EMUC3/INT0/RF6) -> OUTPUT
 *     Pin43:SDO1(EMUD3/RF8)      -> OUTPUT
 *     Pin44:SDI1(RF7)            -> INPUT
 *     Pin52:SS(RA14/INT3)        -> OUTPUT
 *===================================================*/
void spi_master_init(void)
{
    /* SPI Pin configuration */
    TRISFbits.TRISF6    = 0;     // SCK1 -> OUTPTU
    TRISFbits.TRISF8    = 0;     // SDO1 -> OUTPUT
    TRISFbits.TRISF7    = 1;     // SDI1 -> OUTPUT
    TRISAbits.TRISA14   = 0;     // SS   -> INPUT
    
    /* Allow to configure SPI */
    SPI1STATbits.SPIEN  = 0;

    /* Clear overflow flag */
    SPI1STATbits.SPIROV = 0;

    /* Framed SPI support */
    SPI1CONbits.FRMEN   = 0;     // Not support
    SPI1CONbits.SPIFSD  = 0;     // Master(Frame support function)

    /* Disable SDO */
    SPI1CONbits.DISSDO  = 0;     // Enable SDO function

    /* Select 16bit or 8bit Mode */
    SPI1CONbits.MODE16  = 0;     // 8bits Mode

    /* Configure SPI Mode */
    SPI1CONbits.SMP     = 0;     // Input data sampled at middle of data output time
    SPI1CONbits.CKE     = 0;     // Serial output data changes on transition fromm Idle clock state to active clock state
    SPI1CONbits.CKP     = 0;     // Idle state for clock is a low level; active state is a high level

    /* Master Mode Enable */
    SPI1CONbits.MSTEN   = 1;     // Master mode

    /* Prescaler (Configure Max speed) */
    SPI1CONbits.PPRE    = 0b11;  // Primary Prescaler -> 1:1
    SPI1CONbits.SPRE    = 0b111; // Secondary Prescaler -> 1:1

    /* SS pin set High */
    SS_PIN              = 1;
    
    /* Enable SPI */
    SPI1STATbits.SPIEN  = 1;
}


/*=====================================================
 * @brief
 *     SPI Master transmit 1 byte data
 * @param
 *     byte_data:Transmit data
 * @return
 *     none:
 * @note
 *     none
 *===================================================*/
void spi_master_send(char byte_data)
{
    unsigned char dummy;
    
    dummy = SPI1BUF;
    
    while(SPI1STATbits.SPITBF == 1)
    {
        ;
    }
    
    SS_PIN = 0;
    SPI1BUF = byte_data;

    /* Wait for  */
    while(SPI1STATbits.SPITBF == 1)
    {
        ;
    }

    /* Wait for  */
    while(SPI1STATbits.SPIRBF == 0)
    {
        ;
    }

    SS_PIN = 1;
    
    dummy = SPI1BUF;    
}



