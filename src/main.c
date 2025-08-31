/*
 * main.c
 *
 * Created: 6/24/2020
 * Author: Lakmal Weerasinghe
 *
 * Main control logic for automated gate lighting system.
 */

#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

#include "Hardware.h"
#include "Timer_1.h"
#include "AVR_uart.h"

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
#define TIMER1_TICKS_2MS    4000
#define TIMER1_TICKS_4S     1000  // In terms of 2ms ticks
#define TIMER1_TICKS_2S      500  // In terms of 2ms ticks

//-----------------------------------------------------------------------------
// Global State Flags
//-----------------------------------------------------------------------------
volatile uint8_t Button_Pressed     = 0;
volatile uint8_t Alarm_Interrupt    = 0;

uint8_t Switch_Interrupt_Disabled   = 0;
uint16_t Switch_Interrupt_Timer_Value = 0;
uint16_t Switch_Interrupt_Delay_Counter = 0;

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
void LED_Handler(void);
void Switch_Handler(void);
void Process_Alarm_Interrupt(void);

//-----------------------------------------------------------------------------
// Main Entry Point
//-----------------------------------------------------------------------------
int main(void) {
	Hardware_Initialize();

	// Uncomment to manually set RTC time for debugging
	#if 0
	Time_Object t = {12, 11, 0};
	rtc.Set_Time(&t);
	#endif

	_delay_ms(1000);
	Button_Pressed = 0;
	Alarm_Interrupt = 0;

	while (1) {
		if ((Get_Timer_1_Count() - red_led.pwm_timer_value) > TIMER1_TICKS_2MS) {
			LED_Handler();
		}

		if (Switch_Interrupt_Disabled) {
			if ((Get_Timer_1_Count() - Switch_Interrupt_Timer_Value) > TIMER1_TICKS_2MS) {
				Switch_Interrupt_Delay_Counter++;

				if (Switch_Interrupt_Delay_Counter > TIMER1_TICKS_2S) {
					Switch_Enable_External_Interrupt();
					Switch_Interrupt_Disabled = 0;
				}
				Switch_Interrupt_Timer_Value = Get_Timer_1_Count();
			}
		}

		if (Button_Pressed) {
			Switch_Handler();
		}

		if (Alarm_Interrupt) {
			Process_Alarm_Interrupt();
		}
	}
}

//-----------------------------------------------------------------------------
// PWM fade effect and LED control logic.
//-----------------------------------------------------------------------------
void LED_Handler(void) {
	if (red_led.pwm_blink_enabled) {
		red_led.pwm_timer_value = Get_Timer_1_Count();

		if (red_led.pwm_on_state) {
			if (red_led.pwm_Direction) {
				(red_led.pwm_value < 255) ?
				red_led.pwm_value++ : (red_led.pwm_Direction ^= 1);
			} else {
				(red_led.pwm_value > 0) ?
				red_led.pwm_value-- : (red_led.pwm_Direction ^= 1);

				(red_led.pwm_value > 0) ?
				red_led.pwm_value-- : (red_led.pwm_on_state ^= 1);
			}
			red_led.write(red_led.pwm_value);
		} else {
			red_led.pwm_delay++;
			if (red_led.pwm_delay > TIMER1_TICKS_4S) {
				red_led.pwm_on_state ^= 1;
				red_led.pwm_delay = 0;
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Handles switch press with debounce and disables further interrupts temporarily.
//-----------------------------------------------------------------------------
void Switch_Handler(void) {
	UW("SW\n");
	_delay_ms(50);

	if ((PIND & _BV(PIND3)) == 0) {
		gate_light.Toggle();
		UW("TG\n");
	}

	Switch_Disable_External_Interrupt();
	Switch_Interrupt_Delay_Counter = 0;
	Switch_Interrupt_Timer_Value = Get_Timer_1_Count();
	Switch_Interrupt_Disabled = 1;

	Button_Pressed = 0;
	Alarm_Interrupt = 0;
}

//-----------------------------------------------------------------------------
// Handles RTC alarm interrupt, toggles gate light as per schedule.
//-----------------------------------------------------------------------------
void Process_Alarm_Interrupt(void) {
	UW("AL\n");
	Time_Object t = rtc.Get_Time();
	PORTB ^= _BV(DDB5);
	Print_Time_Object(&t);

	gate_light.Invoke(&gate_light.On_Time, &gate_light.Off_Time, t,
					  gate_light.Turn_On, gate_light.Turn_Off);

	rtc.Clear_Primary_Alarm_Flag();
	rtc.Clear_Secondary_Alarm_Flag();

	Button_Pressed = 0;
	Alarm_Interrupt = 0;
}

//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------
ISR(TIMER1_OVF_vect) {
	red_led.pwm_timer_value = 0;
}

ISR(INT1_vect) {
	Button_Pressed = 1;
}

ISR(INT0_vect) {
	Alarm_Interrupt = 1;
}
