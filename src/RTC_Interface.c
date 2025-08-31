/*
 * RTC_Interface.c
 *
 * Created: 6/15/2020
 * Author: Lakmal Weerasinghe
 *
 * Implementation of high-level RTC interface.
 */

#include "RTC_Interface.h"
#include "AVR_UART.h"

// Internal function declarations
static Time_Object _Get_Time(void);
static void _Set_Time(Time_Object *t);
static void _Set_Primary_Alarm(Time_Object *t);
static void _Set_Secondary_Alarm(Time_Object *t);
static void _Clear_Primary_Alarm_Flag(void);
static void _Clear_Secondary_Alarm_Flag(void);

// Global interface object
RTC_Interface rtc;

// Dummy time array for simulation/testing
Time_Object t_test[18];
uint8_t t_test_count = 0;

// Initialize RTC and bind interface functions
void RTC_Initialize(void) {
    Configure_RTC();

    rtc.Get_Time                 = _Get_Time;
    rtc.Set_Time                 = _Set_Time;
    rtc.Set_Primary_Alarm        = _Set_Primary_Alarm;
    rtc.Set_Secondary_Alarm      = _Set_Secondary_Alarm;
    rtc.Clear_Primary_Alarm_Flag = _Clear_Primary_Alarm_Flag;
    rtc.Clear_Secondary_Alarm_Flag = _Clear_Secondary_Alarm_Flag;
}

// Return current time as Time_Object
static Time_Object _Get_Time(void) {
    RTC_get_time(&RTC_Time);

    Time_Object t;
    t.Hour   = RTC_Time.Hours;
    t.Minute = RTC_Time.Minutes;
    t.Second = RTC_Time.Seconds;

    // Uncomment below to simulate dummy time
    // t = Get_Dummy_Time();

    return t;
}

// Set RTC time from Time_Object
static void _Set_Time(Time_Object *t) {
    RTC_Time.Hours   = t->Hour;
    RTC_Time.Minutes = t->Minute;
    RTC_Time.Seconds = t->Second;

    RTC_set_time(&RTC_Time);
}

// Set Alarm 1 from Time_Object
static void _Set_Primary_Alarm(Time_Object *t) {
    RTC_Alarm_1.Hours   = t->Hour;
    RTC_Alarm_1.Minutes = t->Minute;
    RTC_Alarm_1.Seconds = t->Second;

    RTC_set_alarm_one(&RTC_Alarm_1);
}

// Set Alarm 2 from Time_Object
static void _Set_Secondary_Alarm(Time_Object *t) {
    RTC_Alarm_2.Hours   = t->Hour;
    RTC_Alarm_2.Minutes = t->Minute;
    RTC_Alarm_2.Seconds = t->Second;

    RTC_set_alarm_two(&RTC_Alarm_2);
}

// Clear Alarm 1 flag
static void _Clear_Primary_Alarm_Flag(void) {
    RTC_clear_alarm_one_flag();
}

// Clear Alarm 2 flag
static void _Clear_Secondary_Alarm_Flag(void) {
    RTC_clear_alarm_two_flag();
}

// Return dummy time (for simulation/testing)
Time_Object Get_Dummy_Time(void) {
    if (t_test_count > 17) {
        t_test_count = 0;
    }

    UI(t_test_count);
    UW(" - ");

    return t_test[t_test_count++];
}
