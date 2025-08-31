/*
 * AVR_uart.h
 *
 * Created: 6/12/2020
 * Author: Lakmal Weerasinghe
 *
 * AVR UART transmit driver interface.
 */

#ifndef AVR_UART_H_
#define AVR_UART_H_

#include <stdio.h>
#include <avr/io.h>

// Shorthand macros for string and integer output
#define UW(x) UARTWriteString((char *) x)
#define UI(x) UARTWriteInt(x)

// Initialize UART at 9600 baud, 8N1
void UART_Initialize(void);

// Transmit a single character
void UARTWriteChar(char c);

// Transmit a null-terminated string
void UARTWriteString(char *str);

// Transmit an unsigned long as ASCII
void UARTWriteInt(unsigned long d);

#endif /* AVR_UART_H_ */
