/*
 * File:   globals.c
 * Author: M91406.LA
 *
 * Created on November 2, 2019, 4:52 PM
 */


#include <xc.h>
#include "npnz16b.h"

volatile uint16_t vin_adc, vout_adc, iout_adc, iout_adc_b, v_ref, i_ref, duty_out, duty_out_b, v_cfly, v_cfly_ref, deltaD_offset, cloop_out;
volatile uint16_t i_trigger, i_trigger_b;
volatile uint16_t period_set, phase1_set, phase2_set, duty1_set, duty2_set, dt1re_set, dt1fe_set, dt2re_set, dt2fe_set;
volatile uint16_t dt_r1, dt_f1, dt_r2, dt_f2;
volatile int16_t temperature_adc;
volatile int16_t isen[2];
volatile int16_t deltaDQ2;
//volatile int16_t maxdeltaDpos, maxdeltaDneg;
volatile int16_t systemstate, systemstateprevious, controlstate;
volatile int16_t statechanged;
volatile int16_t newadcavailable;
volatile int16_t numberofphases;
volatile int16_t mscounter;
volatile int16_t deltaD;
volatile int16_t rx_count;
volatile int16_t tx_count, low_iout_count;
volatile bool tx_active, rx_active, status_go;
volatile uint8_t rx_data[16];    // Encoded received data
volatile uint8_t rx_checksum;   // Calculated received data checksum
volatile uint16_t rx_decoded;   // Decoded rx data value
volatile int16_t pwm2_count;
volatile uint8_t command_int8;
volatile int16_t deltaDmax;
volatile extern cNPNZ16b_t v_loop, i_loop, i_loop_b;

