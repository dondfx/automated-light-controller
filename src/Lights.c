/*
 * lights.c
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * Light control implementation for scheduled ON/OFF using RTC time.
 */

#include "Lights.h"

// Initialize light object and default on/off times
void Initialize_Lights(void) {
    RTC_Initialize();
    Initialize_Triac();

    gate_light.Turn_On     = triac.Turn_On;
    gate_light.Turn_Off    = triac.Turn_Off;
    gate_light.Toggle      = _Toggle;
    gate_light.Get_State   = _Get_State;
    gate_light.Invoke      = _Invoke;
    gate_light.Set_State   = _Set_State;

    gate_light.On_Time.Hour     = 19;
    gate_light.On_Time.Minute   = 0;
    gate_light.On_Time.Second   = 0;

    gate_light.Off_Time.Hour    = 22;
    gate_light.Off_Time.Minute  = 30;
    gate_light.Off_Time.Second  = 0;
}

// Toggle light ON or OFF based on current state
void _Toggle(void) {
    if (_Get_State()) {
        gate_light.Turn_Off();
    } else {
        gate_light.Turn_On();
    }
}

// Set light state (1 = ON, 0 = OFF)
void _Set_State(uint8_t state) {
    if (state) {
        gate_light.Turn_On();
    } else {
        gate_light.Turn_Off();
    }
}

// Return light state from pin (1 = ON, 0 = OFF)
uint8_t _Get_State(void) {
    return (PIND & _BV(PIND4)) ? 1 : 0;
}

// Determine and invoke ON/OFF callback based on current time
void _Invoke(
    Time_Object *t_On,
    Time_Object *t_Off,
    Time_Object t_Now,
    void (*callback_On)(void),
    void (*callback_Off)(void)
) {
    uint8_t flag = Get_Process_Flag(t_On, t_Off, &t_Now);
    if (flag) {
        callback_On();
    } else {
        callback_Off();
    }
}
