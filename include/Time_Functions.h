/*
 * Time_Functions.h
 *
 * Created: 6/21/2020
 * Author: Lakmal Weerasinghe
 *
 * Time comparison and alarm utility functions for multi-light scheduling.
 */

#ifndef TIME_FUNCTIONS_H_
#define TIME_FUNCTIONS_H_

#include <stdint.h>
#include "RTC_Interface.h"
#include "Support_Functions.h"
#include "Light_Definitions.h"

#define GEQ >=
#define LEQ <=
#define NEQ !=
#define EEQ ==

Time_Object Get_Next_Alarm(Time_Object *Current_Time, Light_Object *Inside,
                           Light_Object *Frontside, Light_Object *Backside);

#endif /* TIME_FUNCTIONS_H_ */
