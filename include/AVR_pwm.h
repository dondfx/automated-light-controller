/*
 * AVR_pwm.h
 *
 * Created: 6/11/2020
 * Author: Lakmal Weerasinghe
 *
 * PWM control using Timer0 on OC0A (PD6) and OC0B (PD5).
 */

#ifndef AVR_PWM_H_
#define AVR_PWM_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

// Initialize Timer0 for Fast PWM on PD6 and PD5
void PWM_Initialize(void);

// Write PWM value to Green indicator (OC0B)
void PWM_Write_Indicator_Green(uint8_t Value);

// Write PWM value to Red indicator (OC0A)
void PWM_Write_Indicator_Red(uint8_t Value);

// Enable Timer0 overflow interrupt
void Timer_0_Enable_OVF_Int(void);

// Disable Timer0 overflow interrupt
void Timer_0_Disable_OVF_Int(void);

#endif /* AVR_PWM_H_ */
