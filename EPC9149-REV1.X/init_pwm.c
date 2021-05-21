

#include <xc.h>
#include <stdint.h>
#include "user.h"

volatile uint16_t ConfigurePWM(void) {

    /* init pwm module */
    // Make sure power to the peripheral is enabled
    PMD1bits.PWMMD = 0; // PWM Module Disable: PWM module is enabled

    // PWM GENERATOR ENABLE
    PG1CONLbits.ON = 0; // PWM Generator #1 Enable: PWM Generator is not enabled
    PG2CONLbits.ON = 0; // PWM Generator #2 Enable: PWM Generator is not enabled
    PG3CONLbits.ON = 0; // PWM Generator #3 Enable: PWM Generator is not enabled
    PG4CONLbits.ON = 0; // PWM Generator #4 Enable: PWM Generator is not enabled

    // PWM CLOCK CONTROL REGISTER
    // MCLKSEL AFPLLO - Auxiliary Clock with PLL Enabled; HRERR disabled; LOCK disabled; DIVSEL 1:2;
    PCLKCON = 0x03;
    // PCLKCONbits.LOCK = 0;       // Lock bit: Write-protected registers and bits are unlocked
    // PCLKCONbits.DIVSEL = 0b00;  // PWM Clock Divider Selection: Divide ratio is 1:2
    // PCLKCONbits.MCLKSEL = 0b11; // PWM Master Clock Selection: Auxiliary PLL post-divider output

    // FREQUENCY SCALE REGISTER & FREQUENCY SCALING MINIMUM PERIOD REGISTER
    FSCL = 0x0000;      // Reset frequency scaling register
    FSMINPER = 0x0000;  // Reset frequency scaling minimum register

    // MASTER PHASE, DUTY CYCLE AND PERIOD REGISTERS
    MPHASE = 0;     // Reset master phase
    MDC    = 0;     // Reset master duty cycle
    // MPER 16;
//    MPER = 0x10;
    // MPER   = 0;     // Master period PWM_PERIOD

    // LINEAR FEEDBACK SHIFT REGISTER
    LFSR = 0x0000;      // Reset linear feedback shift register

    // COMBINATIONAL TRIGGER REGISTERS
    // CTA1EN disabled; CTA2EN disabled; CTA3EN disabled; CTA4EN disabled;
    CMBTRIGL = 0x00;
    // CTB3EN disabled; CTB2EN disabled; CTB1EN disabled; CTB4EN disabled;
    CMBTRIGH = 0x00;
    // CMBTRIGLbits.CTA1EN = 0; // Disable Trigger Output from PWM Generator #1 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA2EN = 0; // Disable Trigger Output from PWM Generator #2 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA3EN = 0; // Disable Trigger Output from PWM Generator #3 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA4EN = 0; // Disable Trigger Output from PWM Generator #4 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA5EN = 0; // Disable Trigger Output from PWM Generator #5 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA6EN = 0; // Disable Trigger Output from PWM Generator #6 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA7EN = 0; // Disable Trigger Output from PWM Generator #7 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA8EN = 0; // Disable Trigger Output from PWM Generator #8 as Source for Combinational Trigger A
    //
    // CMBTRIGHbits.CTB1EN = 0; // Disable Trigger Output from PWM Generator #1 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB2EN = 0; // Disable Trigger Output from PWM Generator #2 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB3EN = 0; // Disable Trigger Output from PWM Generator #3 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB4EN = 0; // Disable Trigger Output from PWM Generator #4 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB5EN = 0; // Disable Trigger Output from PWM Generator #5 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB6EN = 0; // Disable Trigger Output from PWM Generator #6 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB7EN = 0; // Disable Trigger Output from PWM Generator #7 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB8EN = 0; // Disable Trigger Output from PWM Generator #8 as Source for Combinational Trigger B

    // COMBINATORIAL PWM LOGIC A CONTROL REGISTERS A-F
//    LOGCONAbits.PWMS1A = 0b0000; // Combinatorial PWM Logic Source #1 Selection: PWM1H
//    LOGCONAbits.S1APOL = 0;      // Combinatorial PWM Logic Source #1 Polarity: Input is positive logic
//    LOGCONAbits.PWMS2A = 0b0010; // Combinatorial PWM Logic Source #2 Selection: PWM2H
//    LOGCONAbits.S2APOL = 0;      // Combinatorial PWM Logic Source #2 Polarity: Input is positive logic
//    LOGCONAbits.PWMLFA = 0b01;   // Combinatorial PWM Logic Function Selection: PWMS1y & PWMS2y (AND)
//    LOGCONAbits.PWMLFAD = 0b000; // Combinatorial PWM Logic Destination Selection: No assignment, combinatorial PWM logic function is disabled

    // Reset further combinatorial logic registers
    // PWMLFA PWMS1 or PWMS2;; S1APOL Positive logic; S2APOL Positive logic; PWMLFAD No Assignment; PWMS1A PWM1H; PWMS2A PWM1H;
    LOGCONA = 0x0000;
    LOGCONB = 0x0000; // LOGCONB: COMBINATORIAL PWM LOGIC CONTROL REGISTER B
    LOGCONC = 0x0000; // LOGCONC: COMBINATORIAL PWM LOGIC CONTROL REGISTER C
    LOGCOND = 0x0000; // LOGCOND: COMBINATORIAL PWM LOGIC CONTROL REGISTER D
    LOGCONE = 0x0000; // LOGCONE: COMBINATORIAL PWM LOGIC CONTROL REGISTER E
    LOGCONF = 0x0000; // LOGCONF: COMBINATORIAL PWM LOGIC CONTROL REGISTER F

    // PWM EVENT OUTPUT CONTROL REGISTERS A-F
    // PWMEVTAbits.EVTAOEN = 0;    // PWM Event Output Enable: Event output signal is internal only
    // PWMEVTAbits.EVTAPOL = 0;    // PWM Event Output Polarity: Event output signal is active-high
    // PWMEVTAbits.EVTASTRD = 0;   // PWM Event Output Stretch Disable: Event output signal is stretched to eight PWM clock cycles minimum
    // PWMEVTAbits.EVTASYNC = 0;   // PWM Event Output Sync: Event output is not synchronized to the system clock
    // PWMEVTAbits.EVTASEL = 0b0000; // PWM Event Selection: Source is selected by the PGTRGSEL[2:0] bits
    // PWMEVTAbits.EVTAPGS = 0b000;  // PWM Event Source Selection: PWM Generator 1

    // Reset further PWM event output registers
    PWMEVTA = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER A
    PWMEVTB = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER B
    // EVTASEL ADC trigger 2; EVTASYNC Not synchronized; EVTAPOL Active-high; EVTAPGS PG1; EVTASTRD Stretched to 8 PWM clock cycles minimum; EVTAOEN enabled; 
//    PWMEVTB = 0x8090;
//    // EVTBPGS PG2; EVTBSYNC Not synchronized; EVTBPOL Active-high; EVTBSEL ADC Trigger 1; EVTBSTRD Stretched to 8 PWM clock cycles minimum; EVTBOEN enabled; 
//    PWMEVTA = 0x8081;    
    PWMEVTC = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER C
    PWMEVTD = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER D
    PWMEVTE = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER E
    PWMEVTF = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER F    
    
    
    /* init pwm 2 */
    // PWM GENERATOR x CONTROL REGISTERS
    // PG2CONLbits.ON = 0; // PWM Generator #1 Enable: PWM Generator is not enabled
    // PG2CONLbits.TRGCNT = 0b000; // Trigger Count Select: PWM Generator produces one PWM cycle after triggered
    // PG2CONLbits.HREN = 1; // High-Resolution mode is not enabled for PWM Generator 1
    // PG2CONLbits.CLKSEL = 0b01; // Clock Selection: PWM Generator uses Master clock selected by the MCLKSEL[1:0] (PCLKCON[1:0]) control bits
    // PG2CONLbits.MODSEL = 0b000; // PWM Mode Selection: Independent Edge PWM mode
    PG2CONL = 0x0089;  // High-Resolution enabled, PWM Generator uses Master clock selected by the MCLKSEL[1:0] (PCLKCON[1:0]) control bits, Edge PWM2H
    


    PG2CONHbits.MDCSEL = 0; // Master Duty Cycle Register Selection: PWM Generator uses PGxDC register
    PG2CONHbits.MPERSEL = 0; // Master Period Register Selection: PWM Generator uses MPER register
    PG2CONHbits.MPHSEL = 0; // Master Phase Register Selection: PWM Generator uses PGxPHASE register
    PG2CONHbits.MSTEN = 0; // Master Update Enable: PWM Generator does not broadcast the UPDREQ status bit state or EOC signal
    PG2CONHbits.UPDMOD = 0b000; // PWM Buffer Update Mode Selection: SOC
    PG2CONHbits.TRGMOD = 1; // PWM Generator Trigger Mode Selection: PWM Generator operates in Retriggerable mode
    PG2CONHbits.SOCS = 0b0100; // Start-of-Cycle Selection: Trigger output selected by PG4

    // ************************
    PG2IOCONLbits.CLMOD = 0;   // If PCI current limit is active, then the CLDAT[1:0] bits define the PWM output levels
    PG2IOCONLbits.SWAP = 0;    // Swap PWM Signals to PWMxH and PWMxL Device Pins: PWMxH/L signals are mapped to their respective pins
    PG2IOCONLbits.OVRENH = 1;  // User Override Enable for PWMxH Pin: OVRDAT1 provides data for output on the PWMxH pin
    PG2IOCONLbits.OVRENL = 1;  // User Override Enable for PWMxL Pin: OVRDAT0 provides data for output on the PWMxL pin
    PG2IOCONLbits.OVRDAT = 0b00; // Data for PWMxH/PWMxL Pins if Override Event is Active: PWMxL=OVRDAT0, PWMxH=OVRDAR1
    PG2IOCONLbits.OSYNC = 0b00; // User Output Override Synchronization Control: User output overrides via the OVRENH/L and OVRDAT[1:0] bits are synchronized to the local PWM time base (next Start-of-Cycle)

    PG2IOCONLbits.FLTDAT = 0b00; // Data for PWMxH/PWMxL Pins if Fault Event is Active: PWMxL=FLTDAT0, PWMxH=FLTDAR1
    PG2IOCONLbits.CLDAT = 0b00; // Data for PWMxH/PWMxL Pins if Current-Limit Event is Active: PWMxL=CLDAT0, PWMxH=CLDAR1
    PG2IOCONLbits.FFDAT = 0b00; // Data for PWMxH/PWMxL Pins if Feed-Forward Event is Active: PWMxL=CLDAT0, PWMxH=CLDAR1
    PG2IOCONLbits.DBDAT = 0b00; // Data for PWMxH/PWMxL Pins if Debug Mode Event is Active: PWMxL=DBDAT0, PWMxH=DBDAR1

    // PGxIOCONH: PWM GENERATOR x I/O CONTROL REGISTER HIGH
    // PG2IOCONHbits.CAPSRC = 0b000;  // Time Base Capture Source Selection: No hardware source selected for time base capture ? software only
    // PG2IOCONHbits.DTCMPSEL = 0; // Dead-Time Compensation Selection: Dead-time compensation is controlled by PCI Sync logic
    // PG2IOCONHbits.PMOD = 0b00; // PWM Generator Output Mode Selection: PWM Generator outputs operate in Complementary mode
    // PG2IOCONHbits.PENH = 0; // PWMxH Output Port Enable: GPIO registers TRISx, LATx, Rxx registers control the PWMxH output pin
    // PG2IOCONHbits.PENL = 0; // PWMxL Output Port Enable: GPIO registers TRISx, LATx, Rxx registers control the PWMxL output pin
    // PG2IOCONHbits.POLH = 0; // PWMxH Output Port Enable: Output pin is active-high
    // PG2IOCONHbits.POLL = 0; // PWMxL Output Port Enable: Output pin is active-high
    PG2IOCONH = 0x0000;

    // PWM GENERATOR x STATUS REGISTER
    PG2STAT = 0x0000;   // Reset to default

    // PWM GENERATOR x EVENT REGISTER LOW
    PG2EVTLbits.ADTR1PS     = 0b01001;      // ADC Trigger 1 Postscaler Selection = 1:10
    PG2EVTLbits.ADTR1EN3    = 0b0;          // PG2TRIGC  Compare Event is disabled as trigger source for ADC Trigger 1
    PG2EVTLbits.ADTR1EN2    = 0b1;          // PG2TRIGB  Compare Event is  enabled as trigger source for ADC Trigger 1
    PG2EVTLbits.ADTR1EN1    = 0b0;          // PG2TRIGA  Compare Event is disabled as trigger source for ADC Trigger 1
    PG2EVTLbits.UPDTRG      = 0b00;         // User must set the UPDATE bit
    PG2EVTLbits.PGTRGSEL    = 0b001;        // PGxTRIGA compare event is the PWM Generator trigger

    // PWM GENERATOR x EVENT REGISTER HIGH
    PG2EVTHbits.FLTIEN      = 0b0;          // PCI Fault interrupt is disabled
    PG2EVTHbits.CLIEN       = 0b0;          // PCI Current-Limit interrupt is disabled
    PG2EVTHbits.FFIEN       = 0b0;          // PCI Feed-Forward interrupt is disabled
    PG2EVTHbits.SIEN        = 0b0;          // PCI Sync interrupt is disabled
    PG2EVTHbits.IEVTSEL     = 0b11;         // Time base interrupts are disabled
    PG2EVTHbits.ADTR2EN3    = 0b0;          // PG2TRIGC register compare event is disabled as trigger source for ADC Trigger 2
    PG2EVTHbits.ADTR2EN2    = 0b0;          // PG2TRIGB register compare event is disabled as trigger source for ADC Trigger 2
    PG2EVTHbits.ADTR2EN1    = 0b1;          // PG2TRIGA register compare event is  enabled as trigger source for ADC Trigger 2
    PG2EVTHbits.ADTR1OFS    = 0b00000;      // ADC Trigger 1 offset = No offset
//    PG2EVTH = 0x0300;

    // Reset further PCI control registers
    PG2CLPCIH       = 0x0000;          // PWM GENERATOR CL PCI REGISTER HIGH (not used)
    PG2CLPCIL       = 0x0000;          // PWM GENERATOR CL PCI REGISTER LOW  (not used)
    PG2FPCIH        = 0x0000;          // PWM GENERATOR F  PCI REGISTER HIGH (not used)
    PG2FPCIL        = 0x0000;          // PWM GENERATOR F  PCI REGISTER LOW  (not used)
    PG2FFPCIH       = 0x0000;          // PWM GENERATOR FF PCI REGISTER HIGH (not used)
    PG2FFPCIL       = 0x0000;          // PWM GENERATOR FF PCI REGISTER LOW  (not used)
    PG2SPCIH        = 0x0000;          // PWM GENERATOR S  PCI REGISTER HIGH (not used)
    PG2SPCIL        = 0x0000;          // PWM GENERATOR S  PCI REGISTER LOW  (not used)

    // PWM GENERATOR x LEADING-EDGE BLANKING REGISTER HIGH/LOW
    PG2LEBH     = 0x0000;   // Leading Edge Blanking not used
    PG2LEBL     = 0x0000;   // Leading Edge Blanking not used

    // PGxPHASE: PWM GENERATOR x PHASE REGISTER
    PG2PHASE    = PWM2_PHASE_DELAY;

    // PGxDC: PWM GENERATOR x DUTY CYCLE REGISTER
    PG2DC       = PWM_DUTY_FIXED2;

    // PGxDCA: PWM GENERATOR x DUTY CYCLE ADJUSTMENT REGISTER
    PG2DCA      = 0x0000;

    // PGxPER: PWM GENERATOR x PERIOD REGISTER
    PG2PER      = PWM_PERIOD;   

    // PGxTRIGA: PWM GENERATOR x TRIGGER A REGISTER
    PG2TRIGA    = 0;

    // PGxTRIGB: PWM GENERATOR x TRIGGER B REGISTER
    PG2TRIGB    = ADC_TRIG_OFFSET;

    // PGxTRIGC: PWM GENERATOR x TRIGGER C REGISTER
    PG2TRIGC    = 0;

    // PGxDTL: PWM GENERATOR x DEAD-TIME REGISTER LOW
    PG2DTL      = PWM_DEAD_TIME_START_F2;

    // PGxDTH: PWM GENERATOR x DEAD-TIME REGISTER HIGH
    PG2DTH      = PWM_DEAD_TIME_START_R2;    
    
    /* init pwm 4 */
    // PWM GENERATOR x CONTROL REGISTERS
    // PWM GENERATOR x CONTROL REGISTERS
    // PG4CONLbits.ON = 0; // PWM Generator #1 Enable: PWM Generator is not enabled
    // PG4CONLbits.TRGCNT = 0b000; // Trigger Count Select: PWM Generator produces one PWM cycle after triggered
    // PG4CONLbits.HREN = 1; // High-Resolution mode is not enabled for PWM Generator 1
    // PG4CONLbits.CLKSEL = 0b01; // Clock Selection: PWM Generator uses Master clock selected by the MCLKSEL[1:0] (PCLKCON[1:0]) control bits
    // PG4CONLbits.MODSEL = 0b000; // PWM Mode Selection: Independent Edge PWM mode
    PG4CONL = 0x0089;

    PG4CONHbits.MDCSEL = 0; // Master Duty Cycle Register Selection: PWM Generator uses PGxDC register
    PG4CONHbits.MPERSEL = 0; // Master Period Register Selection: PWM Generator uses MPER register
    PG4CONHbits.MPHSEL = 0; // Master Phase Register Selection: PWM Generator uses PGxPHASE register
    PG4CONHbits.MSTEN = 0; // Master Update Enable: PWM Generator does not broadcast the UPDREQ status bit state or EOC signal
    PG4CONHbits.UPDMOD = 0b000; // PWM Buffer Update Mode Selection: Slaved SOC update
    PG4CONHbits.TRGMOD = 1; // PWM Generator Trigger Mode Selection: PWM Generator operates in Retriggerable mode
    PG4CONHbits.SOCS = 0b0000; // Start-of-Cycle Selection: self SOC


    PG4IOCONL = PG2IOCONL;
    PG4IOCONH = PG2IOCONH;
    PG4STAT   = PG2STAT;
    
    PG4EVTLbits.ADTR1PS     = 0b01001;      // ADC Trigger 1 Postscaler Selection = 1:10
    PG4EVTLbits.ADTR1EN3    = 0b0;          // PG4TRIGC  Compare Event is disabled as trigger source for ADC Trigger 1
    PG4EVTLbits.ADTR1EN2    = 0b1;          // PG4TRIGB  Compare Event is enabled as trigger source for ADC Trigger 1
    PG4EVTLbits.ADTR1EN1    = 0b0;          // PG4TRIGA  Compare Event is  disabled as trigger source for ADC Trigger 1
    PG4EVTLbits.UPDTRG      = 0b00;         // User must set the UPDATE bit
    PG4EVTLbits.PGTRGSEL    = 0b000;        // EOC // PGxTRIGA compare event is the PWM Generator trigger   
    
    // PWM GENERATOR x EVENT REGISTER HIGH
    PG4EVTHbits.FLTIEN      = 0b0;          // PCI Fault interrupt is disabled
    PG4EVTHbits.CLIEN       = 0b0;          // PCI Current-Limit interrupt is disabled
    PG4EVTHbits.FFIEN       = 0b0;          // PCI Feed-Forward interrupt is disabled
    PG4EVTHbits.SIEN        = 0b0;          // PCI Sync interrupt is disabled
    PG4EVTHbits.IEVTSEL     = 0b11;         // Time base interrupts are disabled
    PG4EVTHbits.ADTR2EN3    = 0b0;          // PG2TRIGC register compare event is disabled as trigger source for ADC Trigger 2
    PG4EVTHbits.ADTR2EN2    = 0b0;          // PG2TRIGB register compare event is disabled as trigger source for ADC Trigger 2
    PG4EVTHbits.ADTR2EN1    = 0b1;          // PG2TRIGA register compare event is  enabled as trigger source for ADC Trigger 2
    PG4EVTHbits.ADTR1OFS    = 0b00000;      // ADC Trigger 1 offset = No offset
    
    PG4CLPCIH = PG2CLPCIH;
    PG4CLPCIL = PG2CLPCIL;
    PG4FPCIH  = PG2FPCIH;
    PG4FPCIL  = PG2FPCIL;
    PG4FFPCIH = PG2FFPCIH;
    PG4FFPCIL = PG2FFPCIL;
    PG4SPCIH  = PG2SPCIH;
    PG4SPCIL  = PG2SPCIL;
    PG4LEBH   = PG2LEBH;
    PG4LEBL   = PG2LEBL;
    PG4PHASE  = PWM1_PHASE_DELAY;
    PG4DC     = PWM_DUTY_FIXED1;
    PG4DCA    = PG2DCA;
    PG4PER    = PWM_PERIOD;
    // PGxTRIGA: PWM GENERATOR x TRIGGER A REGISTER
    PG4TRIGA  = ADC_TRIG_OFFSET;//PWM2_PHASE_DELAY; //(DUTY_FIXED >> 1);    
    PG4TRIGB  = ADC_TRIG_OFFSET;
    PG4TRIGC  = PG2TRIGC;
    PG4DTL    = PWM_DEAD_TIME_START_F1;
    PG4DTH    = PWM_DEAD_TIME_START_R1;    
    
    return (1);
}

volatile uint16_t LaunchPWM(void) {

    volatile uint16_t timeout=0;

    PG2CONLbits.ON = 1; // PWM Generator #2 Enable: PWM Generator is enabled
    PG4CONLbits.ON = 1; // PWM Generator #4 Enable: PWM Generator is enabled

    while((!PCLKCONbits.HRRDY) && (!PCLKCONbits.HRERR) && (timeout++ < 8000)); // Wait for READY bit

    if(timeout >= 8000) // if High Resolution Ready Bit has not been set or error occurred
    { return(0); }      // skip ENABLE and return failure code

    PG2STATbits.UPDREQ = 1; // Update all PWM registers of PG2
    PG4STATbits.UPDREQ = 1; // Update all PWM registers of PG4

    while(((PG2STATbits.UPDATE) || (PG4STATbits.UPDATE)) && (timeout++<8000));

//    PG2IOCONHbits.PENH = 1; // PWMxH Output Port Enable: PWM generator controls the PWMxH output pin
//    PG2IOCONHbits.PENL = 1; // PWMxH Output Port Enable: PWM generator controls the PWMxL output pin
//    PG4IOCONHbits.PENH = 1; // PWMxH Output Port Enable: PWM generator controls the PWMxH output pin
//    PG4IOCONHbits.PENL = 1; // PWMxH Output Port Enable: PWM generator controls the PWMxL output pin
//
//    // SAFE, GLITCH-FREE STARTUP AS OVERRIDE LOGIC IS SYNCHRONIZED BY EOC
//    PG2IOCONLbits.OVRENH = 0;  // User Override Enable for PWMxH Pin: User override disabled
//    PG2IOCONLbits.OVRENL = 0;  // User Override Enable for PWMxL Pin: User override disabled
//    PG4IOCONLbits.OVRENH = 0;  // User Override Enable for PWMxH Pin: User override disabled
//    PG4IOCONLbits.OVRENL = 0;  // User Override Enable for PWMxL Pin: User override disabled

    return(1);

}