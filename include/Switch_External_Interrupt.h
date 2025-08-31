/*
 * Switch_External_Interrupt.h
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * Interface for handling external interrupt setup and control on PD3 (INT1).
 */

#ifndef SWITCH_EXTERNAL_INTERRUPT_H_
#define SWITCH_EXTERNAL_INTERRUPT_H_

#include <avr/io.h>
#include <util/atomic.h>

#ifdef __cplusplus
extern "C" {
#endif

// Function prototypes
void Switch_External_Interrupt_Initialize(void);
void Switch_Disable_External_Interrupt(void);
void Switch_Enable_External_Interrupt(void);

#ifdef __cplusplus
}
#endif

#endif /* SWITCH_EXTERNAL_INTERRUPT_H_ */
