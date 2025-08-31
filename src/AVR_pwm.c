/*
 * AVR_pwm.c
 *
 * Created: 6/11/2020
 * Author: Lakmal Weerasinghe
 *
 * PWM control implementation using Timer0 Fast PWM mode.
 */

#include "AVR_pwm.h"

// Set up Timer0 in Fast PWM mode and configure output pins
void PWM_Initialize(void) {
    cli();

    DDRD |= _BV(DDD5) | _BV(DDD6);   // Set PD5, PD6 as outputs
    PRR &= ~_BV(PRTIM0);             // Enable Timer0

    TCCR0A |= _BV(WGM00) | _BV(WGM01); // Fast PWM mode

    OCR0A = 0;
    OCR0B = 0;

    TCCR0B |= _BV(CS00);             // No prescaler

    sei();
}

// Set PWM value on OC0B (PD5) or disable if zero
void PWM_Write_Indicator_Green(uint8_t Value) {
    if (Value) {
        TCCR0A |= _BV(COM0B1);
        OCR0B = Value;
    } else {
        TCCR0A &= ~_BV(COM0B1);
        OCR0B = 0;
        PORTD &= ~_BV(DDD5);
    }
}

// Set PWM value on OC0A (PD6) or disable if zero
void PWM_Write_Indicator_Red(uint8_t Value) {
    if (Value) {
        TCCR0A |= _BV(COM0A1);
        OCR0A = Value;
    } else {
        TCCR0A &= ~_BV(COM0A1);
        OCR0A = 0;
        PORTD &= ~_BV(DDD6);
    }
}

// Enable Timer0 overflow interrupt
void Timer_0_Enable_OVF_Int(void) {
    TIMSK0 |= _BV(TOIE0);
    TIFR0  |= _BV(TOV0);
}

// Disable Timer0 overflow interrupt
void Timer_0_Disable_OVF_Int(void) {
    TIMSK0 &= ~_BV(TOIE0);
}
