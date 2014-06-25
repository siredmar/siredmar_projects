#ifndef I2C_CFG_H_
#define I2C_CFG_H_

#define I2C_I2CE_BIT_POSITION_UI8  ((uint8)7)
#define I2C_SPE_BIT_POSITION_UI8   ((uint8)6)
#define I2C_DORD_BIT_POSITION_UI8  ((uint8)5)
#define I2C_MSTR_BIT_POSITION_UI8  ((uint8)4)
#define I2C_CPOL_BIT_POSITION_UI8  ((uint8)3)
#define I2C_CPHA_BIT_POSITION_UI8  ((uint8)2)
#define I2C_SPR_BIT_POSITION_UI8   ((uint8)0)

#define I2C_I2C2X_BIT_POSITION_UI8 ((uint8)0)

#define PORT_I2C    PORTB
#define DDR_I2C     DDRB
#define DD_MISO     DDB3
#define DD_MOSI     DDB2
#define DD_SS       DDB0
#define DD_SCK      DDB1

#endif /* I2C_CFG_H_ */
