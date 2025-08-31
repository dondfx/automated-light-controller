/*
 * Timer_2.h
 *
 * Created: 7/1/2020
 * Author: Lakmal Weerasinghe
 *
 * Interface for Timer2 setup and control.
 */

#ifndef TIMER_2_H_
#define TIMER_2_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define TIMER_2_100MS_OVERFLOW_COUNT   12
#define TIMER_2_100MS_REMAINDER_COUNT  53

#ifdef __cplusplus
extern "C" {
#endif

void Timer_2_Initialize(void);
void Timer_2_Reset(void);
void Enable_Timer_2_Interrupts(void);
void Disable_Timer_2_Interrupts(void);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_2_H_ */
