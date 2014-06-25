/*
 * uart.h
 *
 *  Created on: Nov 11, 2012
 *      Author: armin
 */

#ifndef UART_H_
#define UART_H_

void USART_Init( unsigned int ubrr );
void USART_Transmit( unsigned char data );
void uart_puts(const char *s);

void uart_porta( );
void uart_ddra( );
#endif /* UART_H_ */
