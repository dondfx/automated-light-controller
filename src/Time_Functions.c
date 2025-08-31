/*
 * Time_Functions.c
 *
 * Created: 6/21/2020
 * Author: Lakmal Weerasinghe
 *
 * Implementation of time utilities for managing alarms and light timing logic.
 */

#include "Time_Functions.h"
#include "AVR_UART.h"

//-----------------------------------------------------------------------------
// Return the next upcoming alarm time based on current time and light schedule.
//-----------------------------------------------------------------------------
Time_Object Get_Next_Alarm(Time_Object *Current_Time,
                           Light_Object *Inside,
                           Light_Object *Frontside,
                           Light_Object *Backside) {
	Time_Object TR = {0};

	if (Time_Comparator(Current_Time, &Inside->On_Time) NEQ 0xFF) {
		if (Time_Comparator(Current_Time, &Frontside->On_Time) EEQ 0xFF) {
			TR = Frontside->On_Time;
			return TR;
		}
	}
	if (Time_Comparator(Current_Time, &Frontside->On_Time) NEQ 0xFF) {
		if (Time_Comparator(Current_Time, &Inside->Off_Time) EEQ 0xFF) {
			TR = Inside->Off_Time;
			return TR;
		}
	}
	if (Time_Comparator(Current_Time, &Inside->Off_Time) NEQ 0xFF) {
		if (Time_Comparator(Current_Time, &Frontside->Off_Time) EEQ 0xFF) {
			TR = Frontside->Off_Time;
			return TR;
		}
	}
	if (Time_Comparator(Current_Time, &Frontside->Off_Time) NEQ 0xFF) {
		if (Time_Comparator(Current_Time, &Inside->On_Time) NEQ 0xFF) {
			TR = Inside->On_Time;
			return TR;
		}
	}
	if (Time_Comparator(Current_Time, &Frontside->Off_Time) EEQ 0xFF) {
		if (Time_Comparator(Current_Time, &Inside->On_Time) EEQ 0xFF) {
			TR = Inside->On_Time;
			return TR;
		}
	}
	return TR;
}
