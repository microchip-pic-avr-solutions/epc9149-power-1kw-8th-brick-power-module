/*
 * File:   power_control.c
 * Author: M91406.LA
 *
 * Created on November 2, 2019, 3:52 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "globals.h"

volatile DT_CTRL_STATUS_t dt_ctrl;

volatile uint16_t PowerControlStateMachine(void) {
    
//    static uint16_t delay=0;
//    volatile uint32_t _vout=0, _vin=0, _start_dc=0;
//    static uint16_t delayTest;
    
    if (systemstate != systemstateprevious) {
        statechanged = 1;
        systemstateprevious = systemstate;
    }
    
    
    switch (systemstate) {
        case off:
            if (statechanged == 1) {
                statechanged = 0; //allow for delay for on/off events
                mscounter = 0;
            }
            
            PWMDISABLED;
            PWMHOLD;
            dt_ctrl.value = 0;
            v_ref = 0;
            i_ref = 0;
//            i_ref = IOUTADC(2.8);


            if ((mscounter > 100)) //&& 
                 //   (vin_adc > VINADC(UVLO_ON)) && 
                //    (vin_adc < VINADC(OVLO_ON))  &&
                  //  (temperature_adc < TEMPERATUREON) 
            {
                systemstate = outputdischarged;
                
            }
            break;

        case outputdischarged:
            statechanged = 0;
            if (vout_adc < VOUTADC(VOUTKEEPOFFATSTARTUP)) {
                systemstate = softstart;
//                duty_out = DUTYMIN;
//                duty_out_b = DUTYMIN;
                dt_r1 = PWM_DEAD_TIME_START_R1;
                dt_f1 = PWM_DEAD_TIME_START_F1;
                dt_r2 = PWM_DEAD_TIME_START_R2;
                dt_f2 = PWM_DEAD_TIME_START_F2;
                
                PWMENABLE;
                PWMRELEASE;
//                PG4IOCONL &= 0xCFFF;
                // enable controller
//                v_loop.status.bits.enable = 1;
//                i_loop.status.bits.enable = 1;   
//                i_loop_b.status.bits.enable = 1;                
            }
//                if (ENABLEINPUT == 0) {
//                    systemstate = off;
//                }
            break;
            


        case softstart:

            if (statechanged == 1) {
                statechanged = 0;
//                    Iout_PID.controlReference = IOUTADC(ILIMITACTUALAMPS);
            }
            if (newadcavailable == 1) {
                newadcavailable = 0;
                newadcavailable = 0;
                if ( (dt_ctrl.value & 0x000F) == 0x000F ) {
                    systemstate = running;
                }                
                
                // calculate expected duty cycle based on vin and vout
//                if ( (vout_adc > 0) && (vin_adc >0) ) {
//                    // calculate prebias
//                    _vout = __builtin_muluu(
//                        vout_adc,
//                        BUCK_VOUT_NORM_FACTOR);
//                    _vout >>= (16 - BUCK_VOUT_NORM_SCALER);
//
//                    _vin = __builtin_muluu(
//                        vin_adc,
//                        BUCK_VIN_NORM_FACTOR);
//                    _vin >>= (16 - BUCK_VIN_NORM_SCALER);
//
//                    _start_dc = __builtin_muluu(_vout, PWM_PERIOD);
//                    _start_dc = __builtin_divud(_start_dc, (uint16_t)_vin);    
//                    iout_adc_b = (uint16_t)_start_dc;
//                    /* to determine if the output voltage has reached expected value before increase duty cycle
//                     * _start_dc = vout/vin*PWM_PERIOD  (normal operation: 1/4*PWM_PERIOD)
//                     * duty_fixed = 1/2*PWM_PERIOD
//                    */
//                }
                
\
            }


//                if (ENABLEINPUT == 0)//|| (vin_adc < VINADC(UVLO_OFF))
//                       // || (vin_adc > VINADC(OVLO_OFF))) 
//                {
//                    systemstate = off;
//                }
            break;

        case running:

            statechanged = 0;
//                if (ENABLEINPUT == 0)//|| (vin_adc < VINADC(UVLO_OFF)) 
//                      //  || (vin_adc > VINADC(OVLO_OFF))) 
//                {
//                    systemstate = off;
//                }
            if (newadcavailable == 1) {

                newadcavailable = 0;
                newadcavailable = 0;

            }
            break;

        case error:
            break;
    }
    
    
    return (1);
}
