
#ifndef SYSTEM_USER_DEFINES_H
#define SYSTEM_USER_DEFINES_H

#include <xc.h>
#include <stdint.h>

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define PWM_CLOCK   4000000000UL   // PWM Generator Base Clock Frequency in [Hz]

#define SWITCHFREQ  1000000UL  // define your switching frequency in [Hz]
#define PWM_PERIOD  ((uint16_t)(float)(PWM_CLOCK/SWITCHFREQ))
/* Gate driver minimum on-time */
#define GD_MIN_ONTIME   (float)18.0     // driver minimum on time in [ns]

/* Dead times */
#define DEAD_TIME_RE1   (float)22.0     // PWM1H rise edge deadtime (Primiary) in [ns]
#define DEAD_TIME_FE1   (float)22.0     // PWM1L rise edge deadtime [ns]
#define DEAD_TIME_RE2   (float)30.0     // PWM2H rise edge deadtime (Secondary) in [ns]
#define DEAD_TIME_FE2   (float)30.0     // PWM2L rise edge deadtime in [ns]
#define DEAD_TIME_MAX   (float)60.0     // Maximum dead time among the above 4 numbers [ns]

/* Duty cycle */
#define DUTY_CYCLE_1    (float)50     // primary duty cycle [%]
#define DUTY_CYCLE_2    (float)50     // secondary duty cycle [%]
#define MAXDUTYPERCENT  (float)90.0     // units are % to establish the maximum duty-cycle  ***DAVID***

/* Phase shift */
#define PHASE_SHIFT1    (float)20   // primary phase delay in [ns]
#define PHASE_SHIFT2    (float)0   // seconday phase delay in [ns]

/* Output regulation */
#define VOUTACTUALVOLTS 12//20.05 //***DAVID***
//#define INDUCTORCURRENTRIPPLE ((const int) (3300.0/10.0/4096*32768.0*10.0))
//#define INDUCTORCURRENTRIPPLE 5.5 //A

#define ADC_TRIG_OFFSET    2800//2672//1440
#define ADC_TRIG_OFFSET2   2160//1904// 1200  // need to update this
//#define ADCSAMPLEDELAY PWM_PERIOD-600
//#define SADCSAMPLEDELAY PWM_PERIOD-2200
#define ILIMITACTUALAMPS 17 //***DAVID*** output current
#define ISENSEREF 0x800
#define ISENSEOFFSET1 2036
#define ISENSEOFFSET2 2048
#define VOUTKEEPOFFATSTARTUP 3.0  //***DAVID*** pre-bias
#define VINMINFOR5V 6.5
#define RAMPRATE 30 //Vout ref ramp rate  // 30 for 28V, 45 for 56V
#define DUTYRAMPRATE 2 // duty ramp up rate for start up
#define MAXOFFSET 100 //***YZ*** max duty cycle imbalance units [250ps]

#define UVLO_ON 14.0 //***DAVID***
#define UVLO_OFF 12.0 //***DAVID***
#define OVLO_ON 80.0 //***DAVID***
#define OVLO_OFF 85.0 //***DAVID*** //cannot exceed 69 due to max ADC value and divider
#define TEMPERATURESD 1550 //***DAVID***
#define TEMPERATUREON 1500 //***DAVID***

#define VREF 3.3
#define ADCSCALE (1<<12)  //12 bit ADC value
//#define MAXTEMPERATURE 850 //850 = 85degC
//#define TEMPERATUREOFFSET 620 //remove 0.5V offset
//#define TEMPERATURESCALE ((const int) (3300.0/10.0/4096*32768.0*10.0)) //scale is 0.1degC = 1
//#define CURRENTSCALE ((const int) (0.15/3.3*4096))

// conversions
#define PWM_DEAD_TIME_RE1     (uint16_t)(DEAD_TIME_RE1 * 4) // Rising edge dead time 
#define PWM_DEAD_TIME_FE1     (uint16_t)(DEAD_TIME_FE1 * 4)  // Falling edge dead time
#define PWM_DEAD_TIME_RE2     (uint16_t)(DEAD_TIME_RE2 * 4) // Rising edge dead time 
#define PWM_DEAD_TIME_FE2     (uint16_t)(DEAD_TIME_FE2 * 4)  // Falling edge dead time
#define PWM_DEAD_TIME_MAX     (uint16_t)(DEAD_TIME_MAX * 4) 

#define DUTYMAX         ((uint16_t)(float)(PWM_PERIOD * MAXDUTYPERCENT / 100.0)) //
#define DUTYMIN         ((uint16_t)(GD_MIN_ONTIME * 4))

#define PWM_DUTY_FIXED1     ((uint16_t)(float)(PWM_PERIOD * DUTY_CYCLE_1 / 100.0))   // PWM1 fixed duty cycle
#define PWM_DUTY_FIXED2     ((uint16_t)(float)(PWM_PERIOD * DUTY_CYCLE_2 / 100.0))  // PWM2 fixed duty cycle

#define PWM1_PHASE_DELAY    ((uint16_t)(PHASE_SHIFT1 * 4))
#define PWM2_PHASE_DELAY    ((uint16_t)(PHASE_SHIFT2 * 4))

#define PWM_DEAD_TIME_START_R1      (PWM_DUTY_FIXED1 - PWM_DEAD_TIME_MAX - DUTYMIN + PWM_DEAD_TIME_RE1)   // primary start condition
#define PWM_DEAD_TIME_START_F1      (PWM_PERIOD - PWM_DUTY_FIXED1 - PWM_DEAD_TIME_MAX - DUTYMIN + PWM_DEAD_TIME_FE1)

#define PWM_DEAD_TIME_START_R2      (PWM_DUTY_FIXED2 - - PWM_DEAD_TIME_MAX - DUTYMIN + PWM_DEAD_TIME_RE2)   // secondary start condition
#define PWM_DEAD_TIME_START_F2      (PWM_PERIOD - PWM_DUTY_FIXED2 - PWM_DEAD_TIME_MAX - DUTYMIN + PWM_DEAD_TIME_FE2)

#define VOUTADC(X) ((const int) ((X * 4.75/(4.77+18.0)/VREF*ADCSCALE +0.5) )) //do not converter to Q15
#define VINADC(X) ((const int) ((X * 4.87/(110.0 + 4.87)/VREF * ADCSCALE + 0.5) )) //do not convert to Q15
#define IOUTADC(X) ((const int) ((X * 0.1 * 0.5)/VREF * ADCSCALE + 0.5)) //do not convert to Q15
#define VCFLYADC(X) ((const int) (X * 2.0/(39.0 + 2.0)/VREF * ADCSCALE + 0.5)) // do not convert to Q15

// normalizaiton definitions
#define BUCK_VIN_R1             (float)(110.0)  // Upper voltage divider resistor in kOhm
#define BUCK_VIN_R2             (float)(4.870)  // Lower voltage divider resistor in kOhm
#define BUCK_VIN_FEEDBACK_GAIN  (float)((BUCK_VIN_R2) / (BUCK_VIN_R1 + BUCK_VIN_R2))

#define BUCK_VIN_NORM_INV_G     (float)(1.0/BUCK_VIN_FEEDBACK_GAIN) // Inverted feedback gain required for value normalization
#define BUCK_VIN_NORM_SCALER    (int16_t)(ceil(log(BUCK_VIN_NORM_INV_G)) + 1) // VIN normalization
#define BUCK_VIN_NORM_FACTOR    (int16_t)((BUCK_VIN_NORM_INV_G / pow(2.0, BUCK_VIN_NORM_SCALER)) * (pow(2.0, 15)-1)) // VIN normalization factor scaled in Q15

// vout 
#define BUCK_VOUT_DIV_R1            (float)(18.00) // Upper voltage divider resistor in kOhm
#define BUCK_VOUT_DIV_R2            (float)(4.750) // Lower voltage divider resistor in kOhm
#define BUCK_VOUT_FEEDBACK_GAIN     (float)((BUCK_VOUT_DIV_R2) / (BUCK_VOUT_DIV_R1 + BUCK_VOUT_DIV_R2))

#define BUCK_VOUT_NORM_INV_G    (float)(1.0/BUCK_VOUT_FEEDBACK_GAIN) // Inverted feedback gain required for value normalization
#define BUCK_VOUT_NORM_SCALER   (int16_t)(ceil(log(BUCK_VOUT_NORM_INV_G)) + 1) // VOUT normalization  
#define BUCK_VOUT_NORM_FACTOR   (int16_t)((BUCK_VOUT_NORM_INV_G / pow(2.0, BUCK_VOUT_NORM_SCALER)) * (pow(2.0, 15)-1)) // VOUT normalization factor scaled in Q15


#define PWMDISABLED { PG2IOCONH &= 0xFFF3; PG4IOCONH &= 0xFFF3; }
#define PWMENABLE   { PG2IOCONH |= 0x000C; PG4IOCONH |= 0x000C; }

#define PWMHOLD     { PG2IOCONL |= 0x3000; PG4IOCONL |= 0x3000; } // Set override bits 
#define PWMRELEASE  { PG2IOCONL &= 0xCFFF; PG4IOCONL &= 0xCFFF; } // clear override bits


#define ENABLEINPUT PORTBbits.RB5

//// These macros are used for UART Transmission of Data
//#define BAUDRATE 		9600
//#define BRGVAL 		((FCY/BAUDRATE)/16)-1  //instruction cycle frequency = 70 MHz = fcy
//#define DELAY_105uS     asm volatile ("REPEAT, #4201"); Nop(); // 105uS delay
//#define DELAY_1uS     asm volatile ("REPEAT, #34"); Nop(); // 105uS delay was 69
//#define DELAY_5uS     asm volatile ("REPEAT, #349"); Nop(); // 105uS delay

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

//void InitApp(void);         /* I/O and Peripheral Initialization */

extern volatile uint16_t ConfigureOscillator(void);
extern volatile uint16_t ConfigureSystemTimer(void);
extern volatile uint16_t ConfigureGPIOs(void);
extern volatile uint16_t ConfigureUART(void);
extern volatile uint16_t ConfigureADC(void);
extern volatile uint16_t ConfigurePWM(void);
extern volatile uint16_t LaunchPWM(void);
extern volatile uint16_t ConfigureOPA (void);
extern volatile uint16_t ConfigureControlLoops(void);
extern volatile uint16_t ConfigureComparators(void);
extern volatile uint16_t PowerControlStateMachine(void);

extern void SendData(void);
extern volatile uint16_t uart_calc_checksum(volatile uint8_t* data);
//void FilterData(void);

// state machine for the whole converter
enum STATES {
    off,
    outputdischarged,
    waiting5v,
    chargeCfly,
    softstart_v,
    softstart,
    running,
    error
};

// state machine for determining the direction (positive or negative) for capacitor voltage balancing output signal (deltaDQ2)
enum CTRSTATES {
    v_only,
    vNi
};



#endif // end of SYSTEM_USER_DEFINES_H
