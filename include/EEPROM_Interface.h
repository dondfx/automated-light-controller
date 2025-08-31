/*
 * EEPROM_Interface.h
 *
 * Created: 7/5/2020
 * Author: Lakmal Weerasinghe
 *
 * EEPROM abstraction for logging time-stamped states.
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

#include <stdint.h>
#include "AVR_EEPROM.h"
#include "RTC_Interface.h"
#include "AVR_uart.h"

// EEPROM entry format: 1-byte state + 3-byte time
typedef struct {
    uint8_t     Address;
    uint8_t     State : 1;
    Time_Object Time;
} EEPROM_Entry;

// EEPROM object with function pointers
typedef struct {
    void (*Clear)(uint8_t);
    void (*Read)(EEPROM_Entry *);
    void (*Write)(EEPROM_Entry *);
    void (*Print)(EEPROM_Entry *);
} EEPROM_Object;

// Global instance
extern EEPROM_Object eeprom;

// Initialize EEPROM interface
void EEPROM_Initialize(void);

#endif /* EEPROM_INTERFACE_H_ */
