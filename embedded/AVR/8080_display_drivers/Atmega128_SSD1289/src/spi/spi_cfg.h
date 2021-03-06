#ifndef SPI_CFG_H_
#define SPI_CFG_H_

#define SPI_SPIE_BIT_POSITION_UI8  ((uint8)7)
#define SPI_SPE_BIT_POSITION_UI8   ((uint8)6)
#define SPI_DORD_BIT_POSITION_UI8  ((uint8)5)
#define SPI_MSTR_BIT_POSITION_UI8  ((uint8)4)
#define SPI_CPOL_BIT_POSITION_UI8  ((uint8)3)
#define SPI_CPHA_BIT_POSITION_UI8  ((uint8)2)
#define SPI_SPR_BIT_POSITION_UI8   ((uint8)0)

#define SPI_SPI2X_BIT_POSITION_UI8 ((uint8)0)

#define PORT_SPI    PORTB
#define DDR_SPI     DDRB
#define DD_MISO     DDB3
#define DD_MOSI     DDB2
#define DD_SS       DDB0
#define DD_SCK      DDB1

#endif /* SPI_CFG_H_ */
