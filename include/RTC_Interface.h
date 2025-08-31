/*
 * RTC_Interface.h
 *
 * Created: 6/15/2020
 * Author: Lakmal Weerasinghe
 *
 * High-level interface for AVR RTC abstraction.
 */

#ifndef RTC_INTERFACE_H_
#define RTC_INTERFACE_H_

#include <stdint.h>
#include "AVR_rtc.h"

// Time object (hour, minute, second)
typedef struct {
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
} Time_Object;

// RTC interface abstraction
typedef struct {
    Time_Object (*Get_Time)(void);
    void (*Set_Time)(Time_Object *);

    void (*Set_Primary_Alarm)(Time_Object *);
    void (*Set_Secondary_Alarm)(Time_Object *);

    void (*Clear_Primary_Alarm_Flag)(void);
    void (*Clear_Secondary_Alarm_Flag)(void);

    uint8_t (*Get_Secondary_Alarm_Status)(void);  // Optional; not implemented
} RTC_Interface;

// Global interface instance
extern RTC_Interface rtc;

// Dummy time array for testing
extern Time_Object t_test[18];
extern uint8_t t_test_count;

// Initialize interface and bind functions
void RTC_Initialize(void);

// For testing
Time_Object Get_Dummy_Time(void);

#endif /* RTC_INTERFACE_H_ */
