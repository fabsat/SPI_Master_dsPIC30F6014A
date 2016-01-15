/******************************************************************************************
 * spi_master.h
 * ver1.00
 * Hirofumi Hamada
 *=========================================================================================
 * dsPIC30F6014A用SPI通信(Master)用ライブラリヘッダファイル
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
#ifndef _SPI_MASTER_H
#define _SPI_MASTER_H

#include <xc.h>

/* Select SS Pin */
#define SS_PIN PORTAbits.RA14


/* Prototype of function */
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
void spi_master_init(void);


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
void spi_master_send(char byte_data);
    

#endif
