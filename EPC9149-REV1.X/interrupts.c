/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */

#include <xc.h>
#include <stdint.h>        /* Includes uint16_t definition   */
#include <stdbool.h>       /* Includes true/false definition */

#include "globals.h"


void __attribute__ ( ( __interrupt__ , auto_psv ) ) _ADCAN9Interrupt(void)
{
    LATB |= (1 << 11);

    vout_adc = ADCBUF0;
    
    vin_adc = ADCBUF9;
//    iout_adc = ADCBUF1;
//    iout_adc_b = ADCBUF4;

    newadcavailable = 1;//means that some ADC has triggered interrupt since its measurement is available
    if ( (dt_ctrl.value & 0x000F) == 0x000F ) {
        systemstate = running;
    }        
    if (systemstate == softstart) {
        if ( !(dt_ctrl.bits.dt_r1_ready)) {
            // dt r1 not ready
            dt_r1 -= DUTYRAMPRATE;
            if (dt_r1 <= PWM_DEAD_TIME_RE1) {
                dt_r1 = PWM_DEAD_TIME_RE1;
                dt_ctrl.bits.dt_r1_ready = true;
            }
        }

        if ( !(dt_ctrl.bits.dt_f1_ready)) {
            // dt f1 not ready
            dt_f1 -= DUTYRAMPRATE;
            if (dt_f1 <= PWM_DEAD_TIME_FE1) {
                dt_f1 = PWM_DEAD_TIME_FE1;
                dt_ctrl.bits.dt_f1_ready = true;
            }
        }

        if ( !(dt_ctrl.bits.dt_r2_ready)) {
            // dt r2 not ready
            dt_r2 -= DUTYRAMPRATE;
            if (dt_r2 <= PWM_DEAD_TIME_RE2) {
                dt_r2 = PWM_DEAD_TIME_RE2;
                dt_ctrl.bits.dt_r2_ready = true;
            }
        }

        if ( !(dt_ctrl.bits.dt_f2_ready)) {
            // dt f2 not ready
            dt_f2 -= DUTYRAMPRATE;
            if (dt_f2 <= PWM_DEAD_TIME_FE2) {
                dt_f2 = PWM_DEAD_TIME_FE2;
                dt_ctrl.bits.dt_f2_ready = true;
            }
        }   
        
        // write dead times
        while (PG4STATbits.UPDATE == 1);
        PG4DTL = dt_f1;
        PG4DTH = dt_r1;
        PG4STATbits.UPDREQ = 1;

        while (PG2STATbits.UPDATE == 1);
        PG2DTL = dt_f2;
        PG2DTH = dt_r2;
        PG2STATbits.UPDREQ = 1;        
    }
//    v_loop_Update(&v_loop);
//    
//    i_loop_Update(&i_loop);
    
//    while (PG2STATbits.UPDATE == 1);
//    
//    PG2TRIGB = (DUTY_FIXED>>1)+ADC_TRIG_OFFSET;//i_trigger;
//    PG2DC = PWM_DUTY_FIXED2;//duty_out;
//    PG2TRIGB = i_trigger;
//    PG2DC = duty_out;    
    
//    i_loop_b_Update(&i_loop_b);
//    while (PG4STATbits.UPDATE == 1);

//    PG4TRIGA = (DUTY_FIXED>>1)+ADC_TRIG_OFFSET2; //i_trigger_b;
//    PG4DC = PWM_DUTY_FIXED1;//duty_out_b;    //
//    PG4TRIGA = i_trigger_b;
//    PG4DC = duty_out_b;    //    
    

    LATB &= ~(1 << 11);
//    
//    PG1STATbits.UPDREQ = 1; // Request PWM Data register update
//    PG2STATbits.UPDREQ = 1; // Update all PWM registers of PG2
//    LATB &= ~(1 << 10);    
    _ADCAN9IF = 0;
}

void __attribute__((interrupt, auto_psv)) _PWM2Interrupt(void) {
    _PWM2IF = 0;
}
