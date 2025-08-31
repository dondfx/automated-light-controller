/*
 * AVR_uart.c
 *
 * Created: 6/12/2020
 * Author: Lakmal Weerasinghe
 *
 * AVR UART transmit-only implementation.
 */

#include "AVR_UART.h"

void UART_Initialize(void) {
    // Set character size to 8-bit
    UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);

    // Set baud rate to 9600 (UBRR = 103)
    UBRR0L = 103;

    // Enable transmitter
    UCSR0B |= _BV(TXEN0);

    // Mark TX buffer as ready
    UCSR0A |= _BV(UDRE0);
}

void UARTWriteChar(char c) {
    // Wait until TX buffer is ready
    while (!(UCSR0A & _BV(UDRE0)));
    UDR0 = c;
}

void UARTWriteString(char *str) {
    while (*str != '\0') {
        UARTWriteChar(*str++);
    }
}

void UARTWriteInt(unsigned long d) {
    char arr[11];
    sprintf(arr, "%lu", d); // Convert integer to ASCII

    for (int i = 0; i < 11 && arr[i] != '\0'; i++) {
        UARTWriteChar(arr[i]);
    }
}
