/*
 * dio.c
 *
 *  Created on: Nov 6, 2012
 *      Author: armin
 */
#include "dio.h"

#include "../uart/uart.h"


static dio_configType* lcfgConfigPtr_ps;


void dio_init(void)
{
   dio_portType               dio_pinPortLocal_ui8 = DIO_PORT_A;
   dio_pinNumberType          dio_pinNumberLocal_ui8 = DIO_CHANNEL_0;
   dio_pinDirectionType       dio_pinDirectionLocal_ui8 = DIO_PIN_OUTPUT;
   dio_pinModeType            dio_pinModeLocal_ui8 = DIO_PIN_MODE_STANDARD;
   dio_pinInitialValueType    dio_pinInitialValueLocal_ui8 = DIO_PIN_INIT_LOW;
   uint8                      dio_iterator_ui8 = 0;


   uint8 buf[40] = { 0 };
   uart_puts("\n\rdio_init()\n\r");

  lcfgConfigPtr_ps = (dio_configType*)dio_getlcfgdata();


   for(dio_iterator_ui8 = 0; dio_iterator_ui8 < NUMBER_OF_CONFIGURED_PINS; dio_iterator_ui8++)
      {
         dio_pinPortLocal_ui8         = lcfgConfigPtr_ps->dio_pinConfig_s[dio_iterator_ui8].dio_pinPort_ui8;
         dio_pinNumberLocal_ui8       = lcfgConfigPtr_ps->dio_pinConfig_s[dio_iterator_ui8].dio_pinNumber_ui8;
         dio_pinDirectionLocal_ui8    = lcfgConfigPtr_ps->dio_pinConfig_s[dio_iterator_ui8].dio_pinDirection_ui8;
         dio_pinModeLocal_ui8         = lcfgConfigPtr_ps->dio_pinConfig_s[dio_iterator_ui8].dio_pinMode_ui8;
         dio_pinInitialValueLocal_ui8 = lcfgConfigPtr_ps->dio_pinConfig_s[dio_iterator_ui8].dio_pinInitialValue_ui8;

         switch(dio_pinPortLocal_ui8)
         {
            case DIO_PORT_A:
            {
               PORTA |= ((uint8)dio_pinInitialValueLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               DDRA  |= ((uint8)dio_pinDirectionLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               break;
            }
            case DIO_PORT_B:
            {
               PORTB |= ((uint8)dio_pinInitialValueLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               DDRB  |= ((uint8)dio_pinDirectionLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               break;
            }
            case DIO_PORT_C:
            {
               PORTC |= ((uint8)dio_pinInitialValueLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               DDRC  |= ((uint8)dio_pinDirectionLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               break;
            }
            case DIO_PORT_D:
            {

               sprintf(buf, "InitVal: %d, PinNumber: %d, DataDirection: %d\r\n", dio_pinInitialValueLocal_ui8, dio_pinNumberLocal_ui8, dio_pinDirectionLocal_ui8);
               uart_puts(buf);

               //*(dio_registerAdress_as.dio_portd_pui8) |= ((uint8)dio_pinInitialValueLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               PORTD |= ((uint8)dio_pinInitialValueLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               //*(dio_registerAdress_as.dio_ddrd_pui8)  |= ((uint8)dio_pinDirectionLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               DDRD  |= ((uint8)dio_pinDirectionLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               break;
            }
            case DIO_PORT_E:
            {
               PORTE |= ((uint8)dio_pinInitialValueLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               DDRE  |= ((uint8)dio_pinDirectionLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               break;
            }
            case DIO_PORT_F:
            {
               PORTF |= ((uint8)dio_pinInitialValueLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               DDRF  |= ((uint8)dio_pinDirectionLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               break;
            }
            case DIO_PORT_G:
            {
               PORTG |= ((uint8)dio_pinInitialValueLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               DDRG  |= ((uint8)dio_pinDirectionLocal_ui8 << (uint8)dio_pinNumberLocal_ui8);
               break;
            }
            default:
            {
               /* should never been reached - nothing to do here */
               break;
            }
         }
      }
}

void dio_writeChannel(dio_channelType dio_pin_ui8, dio_pinLevelType dio_output_ui8)
{
   dio_portType      dio_portNo_e = (dio_portType)0;
   dio_pinNumberType dio_pinNo_e  = (dio_pinNumberType)0;
   dio_portNo_e = (dio_portType)((dio_pin_ui8 & MASK_16BIT_HI_UI16) >> 8);
   dio_pinNo_e  = (dio_pinNumberType)(dio_pin_ui8 & MASK_16BIT_LO_UI16);

   switch(dio_portNo_e)
            {
               case DIO_PORT_A:
               {
                  if(dio_output_ui8 == DIO_HIGH)
                     PORTA |= ((uint8)1 << (uint8)dio_pinNo_e);
                  else
                     PORTA &= ~((uint8)1 << (uint8)dio_pinNo_e);
                  break;
               }
               case DIO_PORT_B:
               {
                  if(dio_output_ui8 == DIO_HIGH)
                     PORTB |= ((uint8)1 << (uint8)dio_pinNo_e);
                  else
                     PORTB &= ~((uint8)1 << (uint8)dio_pinNo_e);
                  break;
               }
               case DIO_PORT_C:
               {
                  if(dio_output_ui8 == DIO_HIGH)
                     PORTC |= ((uint8)1 << (uint8)dio_pinNo_e);
                  else
                     PORTC &= ~((uint8)1 << (uint8)dio_pinNo_e);
                  break;
               }
               case DIO_PORT_D:
               {
                  if(dio_output_ui8 == DIO_HIGH)
                     PORTD |= ((uint8)1 << (uint8)dio_pinNo_e);
                  else
                     PORTD &= ~((uint8)1 << (uint8)dio_pinNo_e);
                  break;
               }
               case DIO_PORT_E:
               {
                  if(dio_output_ui8 == DIO_HIGH)
                     PORTE |= ((uint8)1 << (uint8)dio_pinNo_e);
                  else
                     PORTE &= ~((uint8)1 << (uint8)dio_pinNo_e);
                  break;
               }
               case DIO_PORT_F:
               {
                  if(dio_output_ui8 == DIO_HIGH)
                     PORTF |= ((uint8)1 << (uint8)dio_pinNo_e);
                  else
                     PORTF &= ~((uint8)1 << (uint8)dio_pinNo_e);
                  break;
               }
               case DIO_PORT_G:
               {
                  if(dio_pinNo_e < (dio_pinNumberType)5) /* only Pins [0-4] on Port G */
                  {
                     if(dio_output_ui8 == DIO_HIGH)
                        PORTG |= ((uint8)1 << (uint8)dio_pinNo_e);
                     else
                        PORTG &= ~((uint8)1 << (uint8)dio_pinNo_e);
                     break;
                  }
                  break;
               }
               default:
               {
                  /* should never been reached - nothing to do here */
                  break;
               }
            }

}


dio_pinLevelType dio_readChannel(dio_channelType dio_pin_ui8)
{
   dio_pinLevelType retVal = DIO_LOW;
   dio_portType      dio_portNo_e = (dio_portType)0;
   dio_pinNumberType dio_pinNo_e  = (dio_pinNumberType)0;
   dio_portNo_e = (dio_portType)((dio_pin_ui8 & MASK_16BIT_HI_UI16) >> 8);
   dio_pinNo_e  = (dio_pinNumberType)(dio_pin_ui8 & MASK_16BIT_LO_UI16);

   switch(dio_portNo_e)
            {
               case DIO_PORT_A:
               {
                     retVal = (dio_pinLevelType)((((PINA) & 1 << (uint8)dio_pinNo_e)) >> dio_pinNo_e);
                     break;
               }
               case DIO_PORT_B:
               {
                  retVal = (dio_pinLevelType)((((PINB) & 1 << (uint8)dio_pinNo_e)) >> dio_pinNo_e);
                     break;
               }
               case DIO_PORT_C:
               {
                  retVal = (dio_pinLevelType)((((PINC) & 1 << (uint8)dio_pinNo_e)) >> dio_pinNo_e);
                     break;
               }
               case DIO_PORT_D:
               {
                  retVal = (dio_pinLevelType)((((PIND) & 1 << (uint8)dio_pinNo_e)) >> dio_pinNo_e);
                     break;
               }
               case DIO_PORT_E:
               {
                  retVal = (dio_pinLevelType)((((PINE) & 1 << (uint8)dio_pinNo_e)) >> dio_pinNo_e);
                     break;
               }
               case DIO_PORT_F:
               {
                  retVal = (dio_pinLevelType)((((PINF) & 1 << (uint8)dio_pinNo_e)) >> dio_pinNo_e);
                     break;
               }
               case DIO_PORT_G:
               {
                  if(dio_pinNo_e < DIO_CHANNEL_5) /* only Pins [0-4] on Port G */
                  {
                     retVal = (dio_pinLevelType)((((PING) & 1 << (uint8)dio_pinNo_e)) >> dio_pinNo_e);
                        break;
                  }
                  break;
               }
               default:
               {
                  /* should never been reached - nothing to do here */
                  break;
               }
            }

   return retVal;
}

void dio_writePort(dio_portType dio_port_ui8, uint8 dio_data_ui8)
{
      switch(dio_port_ui8)
               {
                  case DIO_PORT_A:
                  {
                     PORTA = (uint8)dio_data_ui8;
                     break;
                  }
                  case DIO_PORT_B:
                  {
                     PORTB = (uint8)dio_data_ui8;
                     break;
                  }
                  case DIO_PORT_C:
                  {
                     PORTC = (uint8)dio_data_ui8;
                     break;
                  }
                  case DIO_PORT_D:
                  {
                     PORTD = (uint8)dio_data_ui8;
                     break;
                  }
                  case DIO_PORT_E:
                  {
                     PORTE = (uint8)dio_data_ui8;
                     break;
                  }
                  case DIO_PORT_F:
                  {
                     PORTF = (uint8)dio_data_ui8;
                     break;
                  }
                  case DIO_PORT_G:
                  {
                     PORTG = (uint8)dio_data_ui8;
                     break;
                  }
                  default:
                  {
                     /* should never been reached - nothing to do here */
                     break;
                  }
               }

}
dio_portValue_ui8 dio_readPort(dio_portType dio_port_ui8)
{
   dio_portValue_ui8 retVal = 0;
   /* TODO */

   return retVal;

}

void dio_writePortGroup(dio_portGroupNoType dio_portGroup_e, uint16 dio_data_ui16)
{
   uint8 dio_iterator_ui8 = 0;

   for(dio_iterator_ui8 = 0; dio_iterator_ui8 < (lcfgConfigPtr_ps->dio_portGroupConfig_s.dio_portGroup[dio_portGroup_e].dio_numberOfConfiguredPins_ui8); dio_iterator_ui8++)
   {

      dio_writeChannel((lcfgConfigPtr_ps->dio_portGroupConfig_s.dio_portGroup[dio_portGroup_e].dio_portGroupChannel[dio_iterator_ui8]), (dio_data_ui16 >> dio_iterator_ui8) & 0x01 );
   }

}

dio_portGroupValueType dio_readPortGroup(dio_portGroupNoType dio_portGroup_e)
{
   dio_portGroupValueType dio_tempValue_ui16 = 0;
   uint8 dio_pinVal_ui8 = 0;
   uint8 dio_iterator_ui8 = 0;

   for(dio_iterator_ui8 = 0; dio_iterator_ui8 < (lcfgConfigPtr_ps->dio_portGroupConfig_s.dio_portGroup[dio_portGroup_e].dio_numberOfConfiguredPins_ui8); dio_iterator_ui8++)
      {
         dio_pinVal_ui8 = dio_readChannel((lcfgConfigPtr_ps->dio_portGroupConfig_s.dio_portGroup[dio_portGroup_e].dio_portGroupChannel[dio_iterator_ui8]));
         dio_tempValue_ui16 |= (uint16)(dio_pinVal_ui8 << dio_iterator_ui8);
      }
return dio_tempValue_ui16;
}
