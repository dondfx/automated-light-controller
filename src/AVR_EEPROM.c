/*
 * AVR_EEPROM.c
 *
 * Created: 6/19/2020
 * Author: Lakmal Weerasinghe
 *
 * Implements EEPROM read/write operations using direct register access.
 * Ensures atomic access and safe timing.
 */

#include "AVR_EEPROM.h"

// Read a byte from EEPROM at given address
uint8_t readEEPROM(uint16_t ADDR) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        while (EECR & _BV(EEPE)); // Wait for any write to finish

        EEARH = ADDR >> 8;
        EEARL = ADDR & 0xFF;

        EECR |= _BV(EERE); // Start read

        return EEDR;       // Return read data
    }
    return 0;
}

// Write a byte to EEPROM if it differs from existing value
void writeEEPROM(uint16_t ADDR, uint8_t EEPROM_DATA) {
    if (readEEPROM(ADDR) == EEPROM_DATA) return;

    while ((EECR & _BV(EEPE)) || (SPMCSR & _BV(SPMEN))); // Wait for ready

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        EEARH = ADDR >> 8;
        EEARL = ADDR & 0xFF;
        EEDR  = EEPROM_DATA;

        EECR &= ~_BV(EEPE);    // Ensure EEPE is clear
        EECR |= _BV(EEMPE);    // Enable master write
        EECR |= _BV(EEPE);     // Start write

        while (EECR & _BV(EEPE)); // Wait for write to complete
    }
}

// Write an array of bytes to EEPROM
void EEPROM_Write_Data(uint16_t start_address, uint8_t *data, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        writeEEPROM(start_address + i, data[i]);
    }
}

// Read an array of bytes from EEPROM
void EEPROM_Read_Data(uint16_t start_address, uint8_t *buffer, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        buffer[i] = readEEPROM(start_address + i);
    }
}

// Clear EEPROM range by writing 0 to each byte
void clearEEPROM(uint16_t start, uint16_t length) {
    for (uint16_t i = 0; i < length; i++) {
        writeEEPROM(start + i, 0);
    }
}
