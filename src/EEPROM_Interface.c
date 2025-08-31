/*
 * EEPROM_Interface.c
 *
 * Created: 7/5/2020
 * Author: Lakmal Weerasinghe
 *
 * Implementation of EEPROM time-logging interface.
 */

#include "EEPROM_Interface.h"

// Internal function declarations
static void _write(EEPROM_Entry *entry);
static void _read(EEPROM_Entry *entry);
static void _clear(uint8_t start_address);
static void _print(EEPROM_Entry *entry);

// Global EEPROM interface object
EEPROM_Object eeprom;

void EEPROM_Initialize(void) {
    eeprom.Clear = _clear;
    eeprom.Write = _write;
    eeprom.Read  = _read;
    eeprom.Print = _print;

    UART_Initialize();
}

// Write state and time to EEPROM
static void _write(EEPROM_Entry *entry) {
    uint8_t data[4] = {
        entry->State,
        entry->Time.Hour,
        entry->Time.Minute,
        entry->Time.Second
    };

    EEPROM_Write_Data(entry->Address, data, 4);
}

// Read state and time from EEPROM
static void _read(EEPROM_Entry *entry) {
    uint8_t data[4] = {0};

    EEPROM_Read_Data(entry->Address, data, 4);

    entry->State       = data[0];
    entry->Time.Hour   = data[1];
    entry->Time.Minute = data[2];
    entry->Time.Second = data[3];
}

// Clear entry at specified address
static void _clear(uint8_t start_address) {
    uint8_t data[4] = {0};
    EEPROM_Write_Data(start_address, data, 4);
}

// Print entry to UART
static void _print(EEPROM_Entry *entry) {
    UW("State - ");
    UI(entry->State);

    UW(" Time: ");
    UI(entry->Time.Hour);   UW("H ");
    UI(entry->Time.Minute); UW("M ");
    UI(entry->Time.Second); UW("S\n\n");
}
