/*
 * Triac.h
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * Interface for TRIAC control logic and state storage.
 */

#ifndef TRIAC_H_
#define TRIAC_H_

#include <avr/io.h>
#include "PWM_Interface.h"
#include "EEPROM_Interface.h"

#define TRUE  1
#define FALSE 0

#define ON    1
#define OFF   0

#define EEPROM_ADDRESS  0

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TRIAC_OBJECT {
	void (*Turn_On)(void);
	void (*Turn_Off)(void);
} Triac_Object;

extern Triac_Object triac;

void Initialize_Triac(void);
void _Turn_on_triac(void);
void _Turn_off_triac(void);

#ifdef __cplusplus
}
#endif

#endif /* TRIAC_H_ */
