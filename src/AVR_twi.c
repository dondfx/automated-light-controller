/*
 * AVR_twi.c
 *
 * Created: 6/12/2020
 * Author: Lakmal Weerasinghe
 *
 * AVR TWI (I2C) master driver implementation.
 */

#include "AVR_twi.h"

void Configure_TWI(void) {
    PRR &= ~_BV(PRTWI);      // Enable TWI module
    TWBR = 18;               // Bit rate for 100kHz
    TWSR |= _BV(TWPS0);      // Prescaler = 4
}

uint8_t TWI_Master_Write(uint8_t address, uint8_t *data, uint8_t length, uint8_t terminate) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);  // Send START
        while (!(TWCR & _BV(TWINT)));
        if ((TWSR & TWI_PRESCALER_MASK) != TWI_STATUS_CODE_START) goto Error;

        TWDR = (address << 1) | TWI_SLAVE_WRITE_FLAG; // Send address + write
        TWCR = _BV(TWINT) | _BV(TWEN);
        while (!(TWCR & _BV(TWINT)));
        if ((TWSR & TWI_PRESCALER_MASK) != TWI_STATUS_CODE_MT_SLAW_ACK) goto Error;

        for (uint8_t i = 0; i < length; i++) {
            TWDR = data[i];                     // Write data byte
            TWCR = _BV(TWINT) | _BV(TWEN);
            while (!(TWCR & _BV(TWINT)));
            if ((TWSR & TWI_PRESCALER_MASK) != TWI_STATUS_CODE_MT_DATA_ACK) goto Error;
        }

        if (terminate == TWI_TERMINATE) {
            TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO); // Send STOP
        }
    }
    return TWI_SUCCESS;

Error:
    UARTWriteString("Transmission Error\n");
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO); // Send STOP
    return TWI_FAILURE;
}

uint8_t TWI_Master_Read(uint8_t address, uint8_t *buffer, uint8_t length) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // Send START
        while (!(TWCR & _BV(TWINT)));
        uint8_t status = TWSR & TWI_PRESCALER_MASK;
        if (status != TWI_STATUS_CODE_START && status != TWI_STATUS_CODE_REPEATED_START) goto Error;

        TWDR = (address << 1) | TWI_SLAVE_READ_FLAG; // Send address + read
        TWCR = _BV(TWINT) | _BV(TWEN);
        while (!(TWCR & _BV(TWINT)));
        if ((TWSR & TWI_PRESCALER_MASK) != TWI_STATUS_CODE_MR_SLAR_ACK) goto Error;

        for (uint8_t i = 0; i < length; i++) {
            TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA); // Read with ACK
            while (!(TWCR & _BV(TWINT)));
            buffer[i] = TWDR;
            if ((TWSR & TWI_PRESCALER_MASK) != TWI_STATUS_CODE_MR_DATA_ACK) goto Error;
        }

        TWCR = _BV(TWINT) | _BV(TWEN); // Final NACK
        while (!(TWCR & _BV(TWINT)));
        if ((TWSR & TWI_PRESCALER_MASK) != TWI_STATUS_CODE_MR_DATA_NACK) goto Error;
    }

    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO); // Send STOP
    return TWI_SUCCESS;

Error:
    UARTWriteString("Reception Error\n");
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO); // Send STOP
    return TWI_FAILURE;
}
