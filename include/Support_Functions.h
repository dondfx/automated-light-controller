/*
 * Support_Functions.h
 *
 * Created: 7/3/2020
 * Author: Lakmal Weerasinghe
 *
 * Utility functions for time comparison and light control logic.
 */

#ifndef SUPPORT_FUNCTIONS_H_
#define SUPPORT_FUNCTIONS_H_

#include <stdint.h>
#include "Triac.h"
#include "Light_Definitions.h"

// Comparison macros for readability
#define GEQ >=
#define LEQ <=
#define NEQ !=
#define EEQ ==

#ifdef __cplusplus
extern "C" {
#endif

// Core function prototypes
uint8_t Time_Comparator(Time_Object *t1, Time_Object *t2);
uint8_t Get_Process_Flag(Time_Object *t_On, Time_Object *t_Off, Time_Object *t_Now);
uint8_t Match_Time_Zone(Time_Object *Current_Time, Time_Object *EEPROM_Time, Light_Object *light);

void Display_Time(uint8_t Carriage_Return);
void Print_Time_Object(Time_Object *t);

#ifdef __cplusplus
}
#endif

#endif /* SUPPORT_FUNCTIONS_H_ */
