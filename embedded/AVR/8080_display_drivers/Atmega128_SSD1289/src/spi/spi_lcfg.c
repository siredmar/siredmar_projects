#include "spi_lcfg.h"
#include "spi.h"

const spi_configType spi_initialConfiguration_s =
{
		SPI_MODULE_ENABLED,
		SPI_MASTER_MODE,
		SPI_INTERRUPT_DISABLED,
		NULL,
		SPI_LSB_FIRST,
		SPI_CPOL_1,
		SPI_CPHA_1,
		SPI_CLOCK_PRESCALER_DIV_4,
		SPI_DOUBLE_SPEED_ENABLED
};

const void *spi_getlcfgdata(void)
{
   return ((void*) &spi_initialConfiguration_s);
}
