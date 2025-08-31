/*
 * AVR_twi.h
 *
 * Created: 6/12/2020
 * Author: Lakmal Weerasinghe
 *
 * AVR TWI (I2C) master driver interface.
 */

#ifndef AVR_TWI_H_
#define AVR_TWI_H_

#include <avr/io.h>
#include <util/atomic.h>
#include "AVR_uart.h"

// Operation result status
#define TWI_SUCCESS             0x00
#define TWI_FAILURE             0x01

// Transfer termination flags
#define TWI_TERMINATE           0x00
#define TWI_DO_NOT_TERMINATE    0x01

// Address mode flags
#define TWI_SLAVE_WRITE_FLAG    0x00
#define TWI_SLAVE_READ_FLAG     0x01

// Prescaler mask for TWSR
#define TWI_PRESCALER_MASK      0xF8

// Status codes
#define TWI_STATUS_CODE_START               0x08
#define TWI_STATUS_CODE_REPEATED_START      0x10
#define TWI_STATUS_CODE_MT_SLAW_ACK         0x18
#define TWI_STATUS_CODE_MT_SLAW_NACK        0x20
#define TWI_STATUS_CODE_MT_DATA_ACK         0x28
#define TWI_STATUS_CODE_MT_DATA_NACK        0x30
#define TWI_STATUS_CODE_MR_SLAR_ACK         0x40
#define TWI_STATUS_CODE_MR_SLAR_NACK        0x48
#define TWI_STATUS_CODE_MR_DATA_ACK         0x50
#define TWI_STATUS_CODE_MR_DATA_NACK        0x58

// Initialize TWI interface
void Configure_TWI(void);

// Write data to slave device
uint8_t TWI_Master_Write(uint8_t address, uint8_t *data, uint8_t length, uint8_t terminate);

// Read data from slave device
uint8_t TWI_Master_Read(uint8_t address, uint8_t *buffer, uint8_t length);

#endif /* AVR_TWI_H_ */
