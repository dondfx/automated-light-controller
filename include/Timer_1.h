/*
 * Timer_1.h
 *
 * Created: 7/1/2020
 * Author: Lakmal Weerasinghe
 *
 * Interface for Timer1 configuration and utility functions.
 */

#ifndef TIMER_1_H_
#define TIMER_1_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void Timer_1_Initialize(void);
void Timer_1_Reset(void);
uint16_t Get_Timer_1_Count(void);

#endif /* TIMER_1_H_ */
