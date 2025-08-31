/*
 * Light_Definitions.h
 *
 * Created: 7/5/2020
 * Author: Lakmal Weerasinghe
 *
 * Interface for light control using time-based scheduling.
 */

#ifndef LIGHT_DEFINITIONS_H_
#define LIGHT_DEFINITIONS_H_

#include <stdint.h>
#include "RTC_Interface.h"

// Light object with time-based state control
typedef struct {
    void (*Turn_Off)(void);
    void (*Turn_On)(void);
    void (*Toggle)(void);

    void (*Invoke)(
        Time_Object *on_time,
        Time_Object *off_time,
        Time_Object current_time,
        void (*on_callback)(void),
        void (*off_callback)(void)
    );

    uint8_t (*Get_State)(void);
    void (*Set_State)(uint8_t);

    Time_Object On_Time;
    Time_Object Off_Time;
} Light_Object;

// Global instance for gate light
extern Light_Object gate_light;

#endif /* LIGHT_DEFINITIONS_H_ */
