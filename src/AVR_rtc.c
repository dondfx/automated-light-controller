/*
 * AVR_rtc.c
 *
 * Created: 6/12/2020
 * Author: Lakmal Weerasinghe
 *
 * DS3231 RTC driver implementation for AVR using I2C (TWI).
 */

#include "AVR_rtc.h"
#include "AVR_uart.h"  // Assuming UART_Initialize() is declared here

RTC_Time_Object RTC_Time;
RTC_Temp_Object RTC_Temp;
RTC_Alarm_Object RTC_Alarm_1;
RTC_Alarm_Object RTC_Alarm_2;
CNT_Reg_Bits CNT_Reg = {0};
STA_Reg_Bits STA_Reg = {0};

void Configure_RTC(void) {
    UART_Initialize();
    Configure_TWI();
    RTC_Set_Aging_Register();

    DDRD &= ~_BV(DDD2);   // PD2 as input
    PORTD |= _BV(DDD2);   // Enable pull-up

    cli();
    EIMSK &= ~_BV(INT0);
    EICRA |= _BV(ISC01);  // Falling edge
    EIMSK |= _BV(INT0);
    EIFR  |= _BV(INTF0);
    sei();
}

void RTC_get_time(RTC_Time_Object *RTC_Time) {
    uint8_t reg[1] = {RTC_SEC_REG};
    uint8_t data[3] = {0};

    TWI_Master_Write(DS3231_ADDR, reg, 1, TWI_DO_NOT_TERMINATE);
    TWI_Master_Read(DS3231_ADDR, data, 3);

    RTC_Time->Seconds = BCD_DECODE(data[0]);
    RTC_Time->Minutes = BCD_DECODE(data[1]);
    RTC_Time->Hours   = BCD_DECODE(data[2] & 0x3F);
}

void RTC_get_temp(RTC_Temp_Object *RTC_Temp) {
    uint8_t reg[1] = {RTC_TEMPH_REG};
    uint8_t data[2] = {0};

    TWI_Master_Write(DS3231_ADDR, reg, 1, TWI_DO_NOT_TERMINATE);
    TWI_Master_Read(DS3231_ADDR, data, 2);

    RTC_Temp->Temp_ = data[0];
    RTC_Temp->Frac_ = (data[1] >> 6);
}

void RTC_set_time(RTC_Time_Object *RTC_Time) {
    uint8_t data[4] = {
        RTC_SEC_REG,
        BCD_ENCODE(RTC_Time->Seconds),
        BCD_ENCODE(RTC_Time->Minutes),
        BCD_ENCODE(RTC_Time->Hours)
    };
    TWI_Master_Write(DS3231_ADDR, data, 4, TWI_TERMINATE);
}

void RTC_set_CNT_register(CNT_Reg_Bits *CNT_Reg) {
    uint8_t data[2] = {
        RTC_CNT_REG,
        ((CNT_Reg->INTCN_bit << INTCN) |
         (CNT_Reg->A2IE_bit  << A2IE)  |
         (CNT_Reg->A1IE_bit  << A1IE))
    };
    TWI_Master_Write(DS3231_ADDR, data, 2, TWI_TERMINATE);
}

void RTC_set_STA_register(STA_Reg_Bits *STA_Reg) {
    uint8_t data[2] = {
        RTC_STA_REG,
        ((STA_Reg->OSF_bit      << OSF)     |
         (STA_Reg->EN32kHz_bit << EN32kHz) |
         (STA_Reg->A1F_bit      << A1F)     |
         (STA_Reg->A2F_bit      << A2F))
    };
    TWI_Master_Write(DS3231_ADDR, data, 2, TWI_TERMINATE);
}

void RTC_set_alarm_one(RTC_Alarm_Object *RTC_Alarm) {
    uint8_t data[5] = {
        RTC_AL1_SEC_REG,
        BCD_ENCODE(RTC_Alarm->Seconds),
        BCD_ENCODE(RTC_Alarm->Minutes),
        BCD_ENCODE(RTC_Alarm->Hours),
        _BV(A1M4)
    };

    TWI_Master_Write(DS3231_ADDR, data, 5, TWI_TERMINATE);

    CNT_Reg.A1IE_bit = 1;
    CNT_Reg.INTCN_bit = 1;
    RTC_set_CNT_register(&CNT_Reg);

    STA_Reg.A1F_bit = 0;
    RTC_set_STA_register(&STA_Reg);
}

void RTC_clear_alarm_one_flag(void) {
    STA_Reg.A1F_bit = 0;
    RTC_set_STA_register(&STA_Reg);
}

void RTC_set_alarm_two(RTC_Alarm_Object *RTC_Alarm) {
    uint8_t data[4] = {
        RTC_AL2_MIN_REG,
        BCD_ENCODE(RTC_Alarm->Minutes),
        BCD_ENCODE(RTC_Alarm->Hours),
        _BV(A2M4)
    };

    TWI_Master_Write(DS3231_ADDR, data, 4, TWI_TERMINATE);

    CNT_Reg.A2IE_bit = 1;
    CNT_Reg.INTCN_bit = 1;
    RTC_set_CNT_register(&CNT_Reg);

    STA_Reg.A2F_bit = 0;
    RTC_set_STA_register(&STA_Reg);
}

void RTC_clear_alarm_two_flag(void) {
    STA_Reg.A2F_bit = 0;
    RTC_set_STA_register(&STA_Reg);
}

void RTC_disable_alarm_one(void) {
    CNT_Reg.A1IE_bit = 0;
    CNT_Reg.INTCN_bit = 1;
    RTC_set_CNT_register(&CNT_Reg);
}

void RTC_disable_alarm_two(void) {
    CNT_Reg.A2IE_bit = 0;
    RTC_set_CNT_register(&CNT_Reg);
}

void RTC_Enable_Square_Wave(void) {
    CNT_Reg.INTCN_bit = 0;
    RTC_set_CNT_register(&CNT_Reg);
}

void RTC_Disable_Square_Wave(void) {
    CNT_Reg.INTCN_bit = 1;
    RTC_set_CNT_register(&CNT_Reg);
}

void RTC_Set_Aging_Register(void) {
    uint8_t data[2] = {RTC_AGING_REG, 0};
    TWI_Master_Write(DS3231_ADDR, data, 2, TWI_TERMINATE);
}

uint8_t RTC_Twos_Compliment(char val) {
    return (val >= 0) ? val : (~abs(val) + 1);
}
