/*
 * uart.c
 *
 *  Created on: Nov 11, 2012
 *      Author: armin
 */


#ifndef UART_C_
#define UART_C_
#include <avr/io.h>

void USART_Init( unsigned int ubrr )
{
                //Baudrate setzen
                UBRR0H = (unsigned char)(ubrr>>8); // Schreibt die ersten vier bits in das UBRR0H register
                UBRR0L = (unsigned char)ubrr;      // Schreibt die letzen vier bits in das UBRR0L register

                //Sender aktivieren
                UCSR0B = (1<<TXEN0) | (1<<RXEN0); //TXEN0 setzt den Sender Aktive - RXEN0 Setzt den Empfaenger aktive

                //Frame Format setzen: 8data, 2stop bit */
                UCSR0C = (1<<USBS0)|(3<<UCSZ0);

        }
//*******************************************************************************************************************
        void USART_Transmit( unsigned char data )
        {

        //warten bis Sendepuffer leer
        while ( !( UCSR0A & (1<<UDRE0)) );

                //Daten in Puffer und senden
                UDR0 = data;
        }

        void uart_puts(const char *s) {
           while (*s ) {
              USART_Transmit(*s);
              s++;
           }
        }


        void uart_porta( )
        {
        //warten bis Sendepuffer leer
        while ( !( UCSR0A & (1<<UDRE0)) );

                //Daten in Puffer und senden
                UDR0 = PORTD;
        }

        void uart_ddra( )
        {
        //warten bis Sendepuffer leer
        while ( !( UCSR0A & (1<<UDRE0)) );

                //Daten in Puffer und senden
                UDR0 = DDRD;
        }
#endif /* UART_C_ */
