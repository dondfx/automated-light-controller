/*
 * Hardware.h
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * Hardware initialization and control interface.
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include "Timer_1.h"
#include "Switch_External_Interrupt.h"
#include "Lights.h"

// Initialize peripherals and restore state
void Hardware_Initialize(void);

// Restore light state from EEPROM
void Restore_Previous_State(void);

// Set RTC alarms for light control
void Set_Alarms(void);

#endif /* HARDWARE_H_ */
