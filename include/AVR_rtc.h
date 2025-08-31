/*
 * AVR_rtc.h
 *
 * Created: 6/12/2020
 * Author: Lakmal Weerasinghe
 *
 * DS3231 RTC driver interface for AVR using I2C (TWI).
 */

#ifndef AVR_RTC_H_
#define AVR_RTC_H_

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "AVR_TWI.h"

// DS3231 I2C address
#define DS3231_ADDR  0x68

// BCD conversion macros
#define BCD_ENCODE(val)     (((val / 10) << 4) | (val % 10))
#define BCD_DECODE(val)     (((val >> 4) * 10) + (val & 0x0F))

// RTC register addresses
#define RTC_SEC_REG         0x00
#define RTC_MIN_REG         0x01
#define RTC_HRS_REG         0x02
#define RTC_DAY_REG         0x03
#define RTC_DAT_REG         0x04
#define RTC_MTH_REG         0x05
#define RTC_YRS_REG         0x06
#define RTC_AL1_SEC_REG     0x07
#define RTC_AL1_MIN_REG     0x08
#define RTC_AL1_HRS_REG     0x09
#define RTC_AL1_DAT_REG     0x0A
#define RTC_AL2_MIN_REG     0x0B
#define RTC_AL2_HRS_REG     0x0C
#define RTC_AL2_DAT_REG     0x0D
#define RTC_CNT_REG         0x0E
#define RTC_STA_REG         0x0F
#define RTC_AGING_REG       0x10
#define RTC_TEMPH_REG       0x11
#define RTC_TEMPL_REG       0x12

// Control register bits
#define EOSC    7
#define BBSQW   6
#define CONV    5
#define RS2     4
#define RS1     3
#define INTCN   2
#define A2IE    1
#define A1IE    0

// Status register bits
#define OSF     7
#define EN32kHz 3
#define BSY     2
#define A2F     1
#define A1F     0

// Alarm and hour register bit definitions
#define A1M1    7
#define A1M2    7
#define A1M3    7
#define A1M4    7
#define A2M2    7
#define A2M3    7
#define A2M4    7
#define DY_DT   6
#define _12_24  6
#define A_P_20H 5

// Time structure
typedef struct {
    char Seconds;
    char Minutes;
    char Hours;
} RTC_Time_Object;

// Date structure
typedef struct {
    char DayofWeek;
    char DayofMonth;
    char Month;
    char Year;
} RTC_Date_Object;

// Alarm structure
typedef struct {
    char Seconds;
    char Minutes;
    char Hours;
} RTC_Alarm_Object;

// Temperature structure
typedef struct {
    char Temp_;
    char Frac_;
} RTC_Temp_Object;

// Control register bitfield
typedef struct {
    unsigned INTCN_bit : 1;
    unsigned A2IE_bit  : 1;
    unsigned A1IE_bit  : 1;
} CNT_Reg_Bits;

// Status register bitfield
typedef struct {
    unsigned OSF_bit      : 1;
    unsigned EN32kHz_bit  : 1;
    unsigned A2F_bit      : 1;
    unsigned A1F_bit      : 1;
} STA_Reg_Bits;

// RTC API
void RTC_set_time(RTC_Time_Object *RTC_Time);
void RTC_get_time(RTC_Time_Object *RTC_Time);
void RTC_get_temp(RTC_Temp_Object *RTC_Temp);
void RTC_set_CNT_register(CNT_Reg_Bits *CNT_Reg);
void RTC_set_STA_register(STA_Reg_Bits *STA_Reg);
void RTC_set_alarm_one(RTC_Alarm_Object *RTC_Alarm);
void RTC_set_alarm_two(RTC_Alarm_Object *RTC_Alarm);
void RTC_clear_alarm_one_flag(void);
void RTC_clear_alarm_two_flag(void);
void RTC_disable_alarm_one(void);
void RTC_disable_alarm_two(void);
void RTC_Enable_Square_Wave(void);
void RTC_Disable_Square_Wave(void);
void RTC_Set_Aging_Register(void);
void Configure_RTC(void);
uint8_t RTC_Twos_Compliment(char val);

// Global objects
extern RTC_Time_Object RTC_Time;
extern RTC_Temp_Object RTC_Temp;
extern RTC_Alarm_Object RTC_Alarm_1;
extern RTC_Alarm_Object RTC_Alarm_2;
extern CNT_Reg_Bits CNT_Reg;
extern STA_Reg_Bits STA_Reg;

#endif /* AVR_RTC_H_ */
