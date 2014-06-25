#include "i2c_lcfg.h"
#include "i2c.h"

const i2c_configType i2c_initialConfiguration_s =
{
		I2C_MODULE_ENABLED,
		I2C_MASTER_MODE,
		I2C_INTERRUPT_DISABLED,
		NULL,
		I2C_LSB_FIRST,
		I2C_CPOL_1,
		I2C_CPHA_1,
		I2C_CLOCK_PRESCALER_DIV_4,
		I2C_DOUBLE_SPEED_ENABLED
};

const void *i2c_getlcfgdata(void)
{
   return ((void*) &i2c_initialConfiguration_s);
}
