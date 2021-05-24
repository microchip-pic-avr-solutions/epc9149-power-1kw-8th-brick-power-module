/*
 * File:   init_cmp.c
 * Author: Y07281
 *
 * Created on December 18, 2019
 */

#include <xc.h>
#include <stdint.h>
#include "user.h"


volatile uint16_t ConfigureOPA (void) {

    // Set the OPA2 to the options selected in the User Interface

    // AMPEN2 enabled; AMPEN1 disabled; AMPON enabled; 
    AMPCON1L = 0x8002; //Disabling AMPPON bit initially
    // NCHDIS2 Wide input voltage range; NCHDIS1 Wide input voltage range; 
    AMPCON1H = 0x00;
    
    AMPCON1Lbits.AMPEN2 = 1; //Enable OPA2;
    
    return (1);
}
