/*
 * Hardware.c
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * Hardware initialization and EEPROM-based state restoration.
 */

#include "Hardware.h"
#include "EEPROM_Interface.h"
#include "RTC_Interface.h"

// Initialize timers, switches, lights, alarms, and restore state
void Hardware_Initialize(void) {
    DDRB |= _BV(DDB5);         // Configure PB5 as output
    PORTB &= ~_BV(DDB5);       // Set PB5 low

    Timer_1_Initialize();
    Switch_External_Interrupt_Initialize();
    Switch_Enable_External_Interrupt();

    Initialize_Lights();
    Set_Alarms();
    Restore_Previous_State();
}

// Restore light state using saved EEPROM entry
void Restore_Previous_State(void) {
    EEPROM_Entry e;
    e.Address = EEPROM_ADDRESS;

    eeprom.Read(&e);
    UW("Restore State - ");
    eeprom.Print(&e);

    Time_Object current_time = rtc.Get_Time();
    uint8_t time_zone = Match_Time_Zone(&current_time, &e.Time, &gate_light);

    if (time_zone) {
        gate_light.Set_State(e.State);
    } else {
        uint8_t flag = Get_Process_Flag(&gate_light.On_Time, &gate_light.Off_Time, &current_time);
        gate_light.Set_State(flag);
        eeprom.Clear(EEPROM_ADDRESS);
    }
}

// Set alarms using configured light ON/OFF times
void Set_Alarms(void) {
    rtc.Set_Primary_Alarm(&gate_light.On_Time);
    rtc.Set_Secondary_Alarm(&gate_light.Off_Time);

    rtc.Clear_Primary_Alarm_Flag();
    rtc.Clear_Secondary_Alarm_Flag();
}
