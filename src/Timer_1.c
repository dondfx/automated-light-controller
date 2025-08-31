/*
 * Timer_1.c
 *
 * Created: 7/1/2020
 * Author: Lakmal Weerasinghe
 *
 * Implementation of Timer1 configuration and operations.
 */

#include "Timer_1.h"

//-----------------------------------------------------------------------------
// Initialize Timer1 with CLK/8 prescaler and overflow interrupt enabled.
//-----------------------------------------------------------------------------
void Timer_1_Initialize(void) {
	PRR &= ~_BV(PRTIM1);        // Enable Timer1 module (power reduction register)
	TCCR1B |= _BV(CS11);        // Set prescaler to CLK/8
	TIMSK1 |= _BV(TOIE1);       // Enable overflow interrupt
	TIFR1  |= _BV(TOV1);        // Clear overflow interrupt flag
}

//-----------------------------------------------------------------------------
// Reset Timer1 count to zero.
//-----------------------------------------------------------------------------
void Timer_1_Reset(void) {
	TCNT1 = 0;
}

//-----------------------------------------------------------------------------
// Return current Timer1 count value.
//-----------------------------------------------------------------------------
uint16_t Get_Timer_1_Count(void) {
	return TCNT1;
}
