/*
 * PWM_Interface.h
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * PWM LED control interface for red and green indicators.
 */

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

#include <stdint.h>
#include "AVR_PWM.h"

// Green LED brightness (0–255)
#define GREEN_LED_PWM_VALUE  10

// Red LED control structure
typedef struct {
    uint8_t  pwm_value;
    uint8_t  pwm_Direction      : 1;
    uint8_t  pwm_on_state       : 1;
    uint8_t  pwm_blink_enabled  : 1;
    uint16_t pwm_delay;
    volatile uint16_t pwm_timer_value;
    void (*write)(uint8_t);
} PWM_Object_Red;

// Green LED control structure
typedef struct {
    void (*Turn_On)(void);
    void (*Turn_Off)(void);
} PWM_Object_Green;

// Global instances
extern PWM_Object_Red red_led;
extern PWM_Object_Green green_led;

// Initialize PWM interface and bindings
void Initialize_PWM_Interface(void);

#endif /* PWM_INTERFACE_H_ */
