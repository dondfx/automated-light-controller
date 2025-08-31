/*
 * Support_Functions.c
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * Implementation of utility functions for time logic and RTC display.
 */

#include "Support_Functions.h"
#include "RTC_Interface.h"
#include "AVR_uart.h"

//-----------------------------------------------------------------------------
// Compare two time objects:
// Return 1 if t1 > t2
// Return 0 if t1 == t2
// Return 0xFF if t1 < t2
//-----------------------------------------------------------------------------
uint8_t Time_Comparator(Time_Object *t1, Time_Object *t2) {
	if (t1->Hour > t2->Hour) return 1;

	if ((t1->Hour == t2->Hour) && (t1->Minute > t2->Minute)) return 1;

	if ((t1->Hour == t2->Hour) &&
	    (t1->Minute == t2->Minute) &&
	    (t1->Second > t2->Second)) return 1;

	if ((t1->Hour == t2->Hour) &&
	    (t1->Minute == t2->Minute) &&
	    (t1->Second == t2->Second)) return 0;

	return 0xFF;
}

//-----------------------------------------------------------------------------
// Check whether a saved time and current time fall in the same ON-OFF window.
//-----------------------------------------------------------------------------
uint8_t Match_Time_Zone(Time_Object *Current_Time, Time_Object *EEPROM_Time, Light_Object *light) {
	if ((EEPROM_Time->Hour == 0) &&
	    (EEPROM_Time->Minute == 0) &&
	    (EEPROM_Time->Second == 0)) {
		return FALSE;
	}

	uint8_t t_zone = 0;
	uint8_t e_zone = 0;

	// Current time within ON and OFF range
	if ((Time_Comparator(Current_Time, &light->On_Time) NEQ 0xFF) &&
	    (Time_Comparator(Current_Time, &light->Off_Time) EEQ 0xFF)) {
		t_zone = 1;
	}

	// EEPROM time within ON and OFF range
	if ((Time_Comparator(EEPROM_Time, &light->On_Time) NEQ 0xFF) &&
	    (Time_Comparator(EEPROM_Time, &light->Off_Time) EEQ 0xFF)) {
		e_zone = 1;
	}

	return (t_zone == e_zone);
}

//-----------------------------------------------------------------------------
// Print current RTC time in human-readable format.
//-----------------------------------------------------------------------------
void Display_Time(uint8_t Carriage_Return) {
	Time_Object t = rtc.Get_Time();

	UW("Time - ");
	UI(t.Hour); UW("H - ");
	UI(t.Minute); UW("M - ");

	if (Carriage_Return) {
		UI(t.Second); UW("S\n\n");
	} else {
		UI(t.Second); UW("S -- ");
	}
}

//-----------------------------------------------------------------------------
// Print any Time_Object.
//-----------------------------------------------------------------------------
void Print_Time_Object(Time_Object *t) {
	UW("Time ++++ ");
	UI(t->Hour); UW("H - ");
	UI(t->Minute); UW("M - ");
	UI(t->Second); UW("S\n");
}

//-----------------------------------------------------------------------------
// Returns 1 if t_Now is between t_On and t_Off.
//-----------------------------------------------------------------------------
uint8_t Get_Process_Flag(Time_Object *t_On, Time_Object *t_Off, Time_Object *t_Now) {
	if ((Time_Comparator(t_Now, t_On) NEQ 0xFF) &&
	    (Time_Comparator(t_Off, t_Now) EEQ 0x1)) {
		return 1;
	}
	return 0;
}
