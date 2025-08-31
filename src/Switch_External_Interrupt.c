/*
 * Switch_External_Interrupt.c
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * Implementation for handling external interrupt on PD3 (INT1).
 */

#include <avr/interrupt.h>
#include "Switch_External_Interrupt.h"

//-----------------------------------------------------------------------------
// Initialize INT1 (PD3) as input with pull-up and rising-edge interrupt.
//-----------------------------------------------------------------------------
void Switch_External_Interrupt_Initialize(void) {
	DDRD  &= ~_BV(DDD3);  // Set PD3 as input
	PORTD |=  _BV(DDD3);  // Enable internal pull-up on PD3

	cli(); // Disable global interrupts

	EIMSK &= ~_BV(INT1);   // Disable INT1
	EICRA |=  _BV(ISC11);  // Rising edge trigger (ISC11 = 1, ISC10 = 0)
	EIMSK |=  _BV(INT1);   // Enable INT1
	EIFR  |=  _BV(INTF1);  // Clear INT1 interrupt flag

	sei(); // Re-enable global interrupts
}

//-----------------------------------------------------------------------------
// Disable INT1.
//-----------------------------------------------------------------------------
void Switch_Disable_External_Interrupt(void) {
	EIMSK &= ~_BV(INT1);
}

//-----------------------------------------------------------------------------
// Enable INT1.
//-----------------------------------------------------------------------------
void Switch_Enable_External_Interrupt(void) {
	EIMSK |=  _BV(INT1);
	EIFR  |=  _BV(INTF1); // Clear any pending INT1 interrupt
}
