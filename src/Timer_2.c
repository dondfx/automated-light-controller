/*
 * Timer_2.c
 *
 * Created: 7/1/2020
 * Author: Lakmal Weerasinghe
 *
 * Implementation of Timer2 configuration and interrupt control.
 */

#include "Timer_2.h"

//-----------------------------------------------------------------------------
// Initialize Timer2 with compare match value but no prescaler.
//-----------------------------------------------------------------------------
void Timer_2_Initialize(void) {
	PRR &= ~_BV(PRTIM2); // Enable Timer2 module (power reduction register)

	// Set compare match value (used to create 100ms timing base)
	OCR2A = TIMER_2_100MS_REMAINDER_COUNT;
}

//-----------------------------------------------------------------------------
// Reset Timer2 counter value.
//-----------------------------------------------------------------------------
void Timer_2_Reset(void) {
	TCNT2 = 0;
}

//-----------------------------------------------------------------------------
// Enable Timer2 with overflow and compare match interrupts.
//-----------------------------------------------------------------------------
void Enable_Timer_2_Interrupts(void) {
	// Enable interrupts
	TIMSK2 |= _BV(OCIE2A); // Output compare match A interrupt
	TIMSK2 |= _BV(TOIE2);  // Timer overflow interrupt

	// Start Timer2 with CLK/256 prescaler
	TCCR2B |= _BV(CS22) | _BV(CS21);

	// Clear any pending interrupt flags
	TIFR2 |= _BV(OCF2A) | _BV(TOV2);

	Timer_2_Reset();
}

//-----------------------------------------------------------------------------
// Disable Timer2 and all its interrupts.
//-----------------------------------------------------------------------------
void Disable_Timer_2_Interrupts(void) {
	// Stop Timer2 by clearing prescaler bits
	TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));

	// Disable interrupts
	TIMSK2 &= ~_BV(OCIE2A);
	TIMSK2 &= ~_BV(TOIE2);
}
