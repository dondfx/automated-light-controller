/*
 * AVR_EEPROM.h
 *
 * Created: 6/19/2020
 * Author: Lakmal Weerasinghe
 *
 * EEPROM access routines for AVR microcontrollers.
 * All functions are interrupt-safe.
 */

#ifndef AVR_EEPROM_H_
#define AVR_EEPROM_H_

#include <avr/io.h>
#include <util/atomic.h>

// Write a single byte to EEPROM
void writeEEPROM(uint16_t ADDR, uint8_t EEPROM_DATA);

// Read a single byte from EEPROM
uint8_t readEEPROM(uint16_t ADDR);

// Write multiple bytes to EEPROM
void EEPROM_Write_Data(uint16_t start_address, uint8_t *data, uint8_t length);

// Read multiple bytes from EEPROM
void EEPROM_Read_Data(uint16_t start_address, uint8_t *buffer, uint8_t length);

// Clear EEPROM range by writing 0s
void clearEEPROM(uint16_t start, uint16_t length);

#endif /* AVR_EEPROM_H_ */
