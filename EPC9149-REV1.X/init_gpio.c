/*
 * File:   init_gpio.c
 * Author: M91406.LA
 *
 * Created on November 2, 2019, 2:19 PM
 */


#include <xc.h>
#include <stdint.h>

volatile uint16_t ConfigureGPIOs(void) {

    //Set I/O pins to low level as default
    LATA = 0;
    LATB = (1 << 5);
    //all inputs are for ADC or the enable line, 1=input, 0=output
    TRISA = 0b10111;
    TRISB = (1 << 6);//(1 << 0) | (1 << 4) | (1 << 9) | (1 << 7);


//
//    CNPDBbits.CNPDB14 = 1;  // Enable intern pull down register (PWM1H)
//    CNPDBbits.CNPDB15 = 1;  // Enable intern pull down register (PWM1L)


    // CNPDBbits.CNPDB12 = 1;  // Enable intern pull down register (PWM2H)
    // CNPDBbits.CNPDB13 = 1;  // Enable intern pull down register (PWM2L)

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDA = 0x0000;
    CNPDB = 0x3300;
    CNPUA = 0x0000;
    CNPUB = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;


    //set analog pins to free others to be digital
    ANSELA = 0x001F;
    ANSELB = 0;//(1 << 2) | (1 << 3) | (1 << 4);
    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
     __builtin_write_RPCON(0x0000); // unlock PPS

     RPINR18bits.U1RXR = 0x0026;    //RB6->UART1:U1RX
     RPOR4bits.RP41R = 0x0023;    //RB9->PWM:PWM4L
     RPOR4bits.RP40R = 0x0022;    //RB8->PWM:PWM4H
     RPOR2bits.RP37R = 0x0001;    //RB5->UART1:U1TX

     __builtin_write_RPCON(0x0800); // lock PPS


    return(1);
}
