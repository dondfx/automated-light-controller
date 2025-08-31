/*
 * Lights.h
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * Light control logic using time-based scheduling.
 */

#ifndef LIGHTS_H_
#define LIGHTS_H_

#include <stdint.h>
#include <avr/io.h>
#include "Support_Functions.h"
#include "Light_Definitions.h"

// Initialize gate light configuration
void Initialize_Lights(void);

// Toggle light state
void _Toggle(void);

// Get current light state
uint8_t _Get_State(void);

// Invoke light state change based on current time
void _Invoke(
    Time_Object *t_On,
    Time_Object *t_Off,
    Time_Object t_Now,
    void (*callback_On)(void),
    void (*callback_Off)(void)
);

// Set light state directly
void _Set_State(uint8_t state);

#endif /* LIGHTS_H_ */
