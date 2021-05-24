/*
 * File:   init_cmp.c
 * Author: YZ
 *
 * Created on December 18, 2019
 */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "globals.h"

volatile uint16_t ConfigureComparators(void) {

    // Disable the CMP module before the initialization
    DACCTRL1Lbits.DACON = 0;
    
	// Comparator Register settings
	DACCTRL1L = 0xB7; //CLKDIV 1:4; DACON disabled; DACSIDL disabled; FCLKDIV 1:8; CLKSEL AFPLLO - Auxiliary Clock with PLL Enabled ; 
	DACCTRL2L = 0x55; //TMODTIME 85; 
	DACCTRL2H = 0x8A; //SSTIME 138; 
	DAC1CONH = 0x00; //TMCB 0; 
	DAC1CONL = 0x8200; //CMPPOL Non Inverted; HYSPOL Rising Edge; HYSSEL None; DACEN disabled; FLTREN disabled; CBE disabled; IRQM Interrupts are disabled; INSEL CMP1A; DACOEN enabled; 

	//Slope Settings
	SLP1CONH = 0x00; //HME disabled; PSE Negative; SLOPEN disabled; TWME disabled; 
	SLP1CONL = 0x00; //HCFSEL None; SLPSTRT None; SLPSTOPB None; SLPSTOPA None; 
	SLP1DAT = 0x00; //SLPDAT 0; 
	DAC1DATL = 0x00; //DACDATL 0; 
	DAC1DATH = ISENSEREF; //DACDATH 2048; 

    // Enable
    DACCTRL1Lbits.DACON = 1;

    return (1);
}
