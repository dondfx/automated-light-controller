/*
 * PWM_Interface.c
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * Implementation of PWM interface for LED control.
 */

#include "PWM_Interface.h"

// Internal prototypes
static void _green_led_turn_on(void);
static void _green_led_turn_off(void);

// Global instances
PWM_Object_Red red_led;
PWM_Object_Green green_led;

// Initialize PWM control for red and green indicators
void Initialize_PWM_Interface(void) {
    PWM_Initialize();

    red_led.pwm_value         = 0;
    red_led.pwm_Direction     = 1;
    red_led.pwm_on_state      = 1;
    red_led.pwm_blink_enabled = 1;
    red_led.pwm_delay         = 0;
    red_led.pwm_timer_value   = 0;
    red_led.write             = PWM_Write_Indicator_Red;

    green_led.Turn_On         = _green_led_turn_on;
    green_led.Turn_Off        = _green_led_turn_off;
}

// Turn on green LED with fixed brightness
static void _green_led_turn_on(void) {
    PWM_Write_Indicator_Green(GREEN_LED_PWM_VALUE);
}

// Turn off green LED
static void _green_led_turn_off(void) {
    PWM_Write_Indicator_Green(0);
}
