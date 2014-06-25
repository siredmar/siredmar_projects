/*
 * dio.c
 *
 *  Created on: Nov 6, 2012
 *      Author: armin
 */
#include "dio.h"

// I/O access
volatile unsigned *gpio;
int mem_fd;
void *gpio_map;


static dio_configType *lcfgConfigPtr_ps;

static Std_ReturnType dio_openGpioMemory()
{
   Std_ReturnType returnValue = E_NOT_OK;
   if ((mem_fd = open ("/dev/mem", O_RDWR | O_SYNC)) < 0U)
     {
       printf ("can't open /dev/mem \n");
       exit (-1);
     }

#if DEBUG_DIO_ENABLED
   printf ("mem_fd = %d\n", mem_fd);
   printf ("getpagesize() -> %d\n", getpagesize ());
#endif

   gpio_map = mmap (NULL,
                    getpagesize(),
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED,
                    mem_fd,
                    GPIO_BASE);

   close (mem_fd);    //No need to keep mem_fd open after mmap

   if (gpio_map == MAP_FAILED)
   {
         printf ("mmap error %d\n", errno);
         exit (-1);
   }
   else
   {
#if DEBUG_DIO_ENABLED
      printf ("(DBG): dio_openGpioMemory(): gpio_memory = 0x%x\n", (unsigned int) gpio_map);
#endif
   }

   // Always use volatile pointer!
   gpio = (volatile unsigned *) gpio_map;
   returnValue = E_OK;
   return returnValue;
}

Std_ReturnType dio_init (void)
{
  Std_ReturnType returnValue = E_NOT_OK;
  dio_channelType dio_pinNumberLocal_ui8 = DIO_CHANNEL_0;
  dio_pinDirectionType dio_pinDirectionLocal_ui8 = DIO_PIN_OUTPUT;
  dio_pinInitialValueType dio_pinInitialValueLocal_ui8 = DIO_LOW;
  uint8 dio_iterator_ui8 = 0U;

  lcfgConfigPtr_ps = (dio_configType *) dio_getlcfgdata ();

  dio_openGpioMemory();

  for (dio_iterator_ui8 = 0U; dio_iterator_ui8 < NUMBER_OF_CONFIGURED_PINS; dio_iterator_ui8++)
    {
      dio_pinNumberLocal_ui8 =       lcfgConfigPtr_ps->dio_pinConfig_s[dio_iterator_ui8].dio_pinNumber_e;
      dio_pinDirectionLocal_ui8 =    lcfgConfigPtr_ps->dio_pinConfig_s[dio_iterator_ui8].dio_pinDirection_e;
      dio_pinInitialValueLocal_ui8 = lcfgConfigPtr_ps->dio_pinConfig_s[dio_iterator_ui8].dio_pinInitialValue_e;

      /* Use INP_GPIO() first before use OUT_GPIO()! */
      INP_GPIO (dio_pinNumberLocal_ui8);

      if (dio_pinDirectionLocal_ui8 == DIO_PIN_OUTPUT)
      {
         OUT_GPIO (dio_pinNumberLocal_ui8);
         if (dio_pinInitialValueLocal_ui8 == DIO_PIN_INIT_LOW)
         {
            GPIO_SET = (1U << dio_pinNumberLocal_ui8);
#if DEBUG_DIO_ENABLED
            printf("(DBG): dio_init(): %d\tis OUTPUT LOW\n", dio_pinNumberLocal_ui8);
#endif
         }
         else
         {
            GPIO_CLR = (1U << dio_pinNumberLocal_ui8);
#if DEBUG_DIO_ENABLED
            printf("(DBG): dio_init(): %d\tis OUTPUT HIGH\n", dio_pinNumberLocal_ui8);
#endif
         }
      }
      else
      {
         /* Already set to input mode */
      }
    }
  returnValue = E_OK;
  return returnValue;
}

void inline dio_writeChannel (dio_channelType dio_pin_ui8, dio_pinLevelType dio_output_ui8)
{
  if (dio_output_ui8 == DIO_HIGH)
    {
      GPIO_SET = (1U << dio_pin_ui8);
#if DEBUG_DIO_ENABLED
      printf("(DBG): dio_writeChannel(): %d\tis HIGH\n", dio_pin_ui8);
#endif
    }
  else
    {
      GPIO_CLR = (1U << dio_pin_ui8);
#if DEBUG_DIO_ENABLED
      printf("(DBG): dio_writeChannel(): %d\tis LOW\n", dio_pin_ui8);
#endif
    }
}

void dio_writePortGroup (uint16 dio_data_ui16)
{
#if DEBUG_PORT_GRP_ENABLED
  int i;
  printf("(DBG): dio_writePortGroup(): \t0b");
  for(i = 0; i < 16; i++)
  {
     printf("%d", (dio_data_ui16 >> i)  & 0x01);
  }
  printf("\n");
#endif
  dio_writeChannel (DIO_CHANNEL_18, (dio_data_ui16 >> 0U)  & 0x0001);
  dio_writeChannel (DIO_CHANNEL_17, (dio_data_ui16 >> 1U)  & 0x0001);
  dio_writeChannel (DIO_CHANNEL_20, (dio_data_ui16 >> 2U)  & 0x0001);
  dio_writeChannel (DIO_CHANNEL_19, (dio_data_ui16 >> 3U)  & 0x0001);
  dio_writeChannel (DIO_CHANNEL_2,  (dio_data_ui16 >> 4U)  & 0x0001);
  dio_writeChannel (DIO_CHANNEL_8,  (dio_data_ui16 >> 5U)  & 0x0001);
  dio_writeChannel (DIO_CHANNEL_10, (dio_data_ui16 >> 6U)  & 0x0001);
  dio_writeChannel (DIO_CHANNEL_16, (dio_data_ui16 >> 7U)  & 0x0001);
  dio_writeChannel (DIO_CHANNEL_9,  (dio_data_ui16 >> 8U)  & 0x0001);
  dio_writeChannel (DIO_CHANNEL_11, (dio_data_ui16 >> 9U)  & 0x0001);
  dio_writeChannel (DIO_CHANNEL_12, (dio_data_ui16 >> 10U) & 0x0001);
  dio_writeChannel (DIO_CHANNEL_13, (dio_data_ui16 >> 11U) & 0x0001);
  dio_writeChannel (DIO_CHANNEL_14, (dio_data_ui16 >> 12U) & 0x0001);
  dio_writeChannel (DIO_CHANNEL_6,  (dio_data_ui16 >> 13U) & 0x0001);
  dio_writeChannel (DIO_CHANNEL_15, (dio_data_ui16 >> 14U) & 0x0001);
  dio_writeChannel (DIO_CHANNEL_5,  (dio_data_ui16 >> 15U) & 0x0001);
}

void dio_writePortGroup_8(uint8 dio_data_ui8)
{

#if DEBUG_PORT_GRP_ENABLED
  int i;
  printf("(DBG): dio_writePortGroup(): \t0b");
  for(i = 0; i < 8; i++)
  {
     printf("%d", (dio_data_ui8 >> i)  & 0x01);
  }
  printf("\n");
#endif
   dio_writeChannel (DIO_CHANNEL_18, (dio_data_ui8 >> 0U)  & 0x01);
   dio_writeChannel (DIO_CHANNEL_17, (dio_data_ui8 >> 1U)  & 0x01);
   dio_writeChannel (DIO_CHANNEL_20, (dio_data_ui8 >> 2U)  & 0x01);
   dio_writeChannel (DIO_CHANNEL_19, (dio_data_ui8 >> 3U)  & 0x01);
   dio_writeChannel (DIO_CHANNEL_2,  (dio_data_ui8 >> 4U)  & 0x01);
   dio_writeChannel (DIO_CHANNEL_8,  (dio_data_ui8 >> 5U)  & 0x01);
   dio_writeChannel (DIO_CHANNEL_10, (dio_data_ui8 >> 6U)  & 0x01);
   dio_writeChannel (DIO_CHANNEL_16, (dio_data_ui8 >> 7U)  & 0x01);
}

