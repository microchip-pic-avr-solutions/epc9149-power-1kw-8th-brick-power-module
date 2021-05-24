/*
 * File:   init_timer.c
 * Author: M91406.LA
 *
 * Created on November 2, 2019, 1:44 PM
 */


#include <xc.h>
#include <stdint.h>

/*!ConfigureSystemTimer()
 * *********************************************************************************
 * Summary: Initialize standard 16-bit timer
 * 
 * Description:
 * This timer is used to create a deterministic state machine base clock.
 * This base clock period and related state machine call time step will help
 * to organize and manage control step intervals for soft-start, fault-handling
 * and auto-recovery of the power supply.
 * 
 * ********************************************************************************/

volatile uint16_t ConfigureSystemTimer(void) {
    
//    T1CONbits.TON = 0; // Timer1 = disabled
//    T1CONbits.TSIDL = 0; // Timer1 Stop in Idle Mode = Continues module operation in Idle mode
//    T1CONbits.TGATE = 0; // Timer1 Gated Time Accumulation Enable = Gated time accumulation is disabled
//    T1CONbits.TCKPS = 0b00; // Timer1 Input Clock Prescale Select = 1:1
//    T1CONbits.TSYNC = 0; // Timer1 External Clock Input Synchronization Selection = Does not synchronize external clock input
//    T1CONbits.TCS = 0; // Timer1 Clock Source Selection = Internal clock (FP)
//    
//    PR1 = 7000;
//            
//    _T1IP = 1;
//    _T1IF = 0;
//    _T1IE = 0;
    
    T1CONbits.TON = 0;  // Timer1 On: Stops 16-bit Timer1 during configuration
    T1CONbits.TSIDL = 0; // Timer1 Stop in Idle Mode: Continues module operation in Idle mode
    T1CONbits.TMWDIS = 0; // Asynchronous Timer1 Write Disable: Back-to-back writes are enabled in Asynchronous mode
    T1CONbits.TMWIP = 0; // Asynchronous Timer1 Write in Progress: Write to the timer in Asynchronous mode is complete
    T1CONbits.PRWIP = 0; // Asynchronous Period Write in Progress: Write to the Period register in Asynchronous mode is complete
    T1CONbits.TECS = 0b01; // Timer1 Extended Clock Select: FP clock
    T1CONbits.TGATE = 0; // Timer1 Gated Time Accumulation Enable: Gated time accumulation is disabled when TCS = 0
    T1CONbits.TCKPS = 0; // Timer1 Input Clock Prescale Select: 1:1
    T1CONbits.TSYNC = 0; // Timer1 External Clock Input Synchronization Select: Does not synchronize the External Clock input
    T1CONbits.TCS = 0; // Timer1 Clock Source Select: Internal peripheral clock
    
    // Reset Timer Counter Register TMR to Zero; 
    TMR1 = 0x00;
    //Period = 0.0001 s; Frequency = 100000000 Hz; PR 9999; 
    PR1 = 7999;
    // Reset interrupt and interrupt flag bit
    _T1IP = 1;  // Set interrupt priority to one
    _T1IF = 0;  // Reset interrupt flag bit
    _T1IE = 0;  // Disable Timer1 interrupt    
    
    return (1);
}
