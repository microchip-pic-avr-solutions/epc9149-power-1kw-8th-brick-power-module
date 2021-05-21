
#ifndef SYSTEM_GLOBALS_H
#define SYSTEM_GLOBALS_H

/******************************************************************************/
/* System Level #include's                                                    */
/******************************************************************************/
#include "user.h"
#include "npnz16b.h"
#include "v_loop.h"
#include "i_loop.h"
#include "i_loop_b.h"

/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/


/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

extern volatile uint16_t vin_adc, vout_adc, iout_adc, iout_adc_b, v_ref, i_ref, duty_out, duty_out_b, v_cfly, v_cfly_ref, deltaD_offset, cloop_out;
extern volatile uint16_t i_trigger, i_trigger_b;
extern volatile uint16_t period_set, phase1_set, phase2_set, duty1_set, duty2_set, dt1re_set, dt1fe_set, dt2re_set, dt2fe_set;
extern volatile uint16_t dt_r1, dt_f1, dt_r2, dt_f2;
extern volatile int16_t temperature_adc;
extern volatile int16_t isen[2];
extern volatile int16_t deltaDQ2;
//volatile int16_t maxdeltaDpos, maxdeltaDneg;
extern volatile int16_t systemstate, systemstateprevious, controlstate;
extern volatile int16_t statechanged;
extern volatile int16_t newadcavailable;
extern volatile int16_t numberofphases;
extern volatile int16_t mscounter;
extern volatile int16_t deltaD;
extern volatile int16_t rx_count;
extern volatile int16_t tx_count, low_iout_count;
extern volatile bool tx_active, rx_active, status_go;
extern volatile uint8_t rx_data[16];    // Encoded received data
extern volatile uint8_t rx_checksum;   // Calculated received data checksum
extern volatile uint16_t rx_decoded;   // Decoded rx data value
extern volatile int16_t pwm2_count;
extern volatile uint8_t command_int8;
extern volatile int16_t deltaDmax;
extern volatile cNPNZ16b_t v_loop, i_loop, i_loop_b;

// dead time control
typedef union{

	struct {
		volatile bool dt_r1_ready : 1;          // Bit 0: Flag bit indicating if rising edge dead time (primary) has reached
        volatile bool dt_f1_ready : 1;          // Bit 1: Flag bit indicating if falling edge dead time (primary) has reached
        volatile bool dt_r2_ready : 1;          // Bit 2: Flag bit indicating if rising edge dead time (secondary) has reached
        volatile bool dt_f2_ready : 1;          // Bit 3: Flag bit indicating if falling edge dead time (secondary) has reached
		volatile unsigned : 12;					// Bit <15:4>: (reserved)
	} __attribute__((packed)) bits; // Fault object status bit field for signle bit access  

	volatile uint16_t value;		// Fault object status word  

} DT_CTRL_STATUS_t;	// Fault object status

extern volatile DT_CTRL_STATUS_t dt_ctrl;

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/




#endif // end of SYSTEM_GLOBALS_H
