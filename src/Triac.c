/*
 * Triac.c
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * Implementation of TRIAC control and EEPROM-based state logging.
 */

#include "Triac.h"
#include "RTC_Interface.h"
#include "AVR_uart.h"

Triac_Object triac;

//-----------------------------------------------------------------------------
// Initialize TRIAC control and supporting peripherals.
//-----------------------------------------------------------------------------
void Initialize_Triac(void) {
	Initialize_PWM_Interface();
	EEPROM_Initialize();

	DDRD |= _BV(DDD4);     // Set PD4 as output
	PORTD &= ~_BV(DDD4);   // Ensure TRIAC is off initially

	triac.Turn_On  = _Turn_on_triac;
	triac.Turn_Off = _Turn_off_triac;
}

//-----------------------------------------------------------------------------
// Turn on TRIAC, update EEPROM and indicate via green LED.
//-----------------------------------------------------------------------------
void _Turn_on_triac(void) {
	PORTD |= _BV(DDD4);
	green_led.Turn_On();

	EEPROM_Entry e;
	e.Address = EEPROM_ADDRESS;
	e.State   = ON;
	e.Time    = rtc.Get_Time();
	eeprom.Write(&e);

	UW("TRIAC ON - ");
	eeprom.Print(&e);
}

//-----------------------------------------------------------------------------
// Turn off TRIAC, update EEPROM and indicate via green LED.
//-----------------------------------------------------------------------------
void _Turn_off_triac(void) {
	PORTD &= ~_BV(DDD4);
	green_led.Turn_Off();

	EEPROM_Entry e;
	e.Address = EEPROM_ADDRESS;
	e.State   = OFF;
	e.Time    = rtc.Get_Time();
	eeprom.Write(&e);

	UW("TRIAC OFF - ");
	eeprom.Print(&e);
}
