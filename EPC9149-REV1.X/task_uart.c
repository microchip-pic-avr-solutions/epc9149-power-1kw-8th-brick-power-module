/*
 * File:   uart.c
 * Author: M91406.LA
 *
 * Created on November 2, 2019, 4:05 PM
 */


#include <xc.h>
#include "globals.h"
#include "user.h"

void SendData() {
    volatile char ReceivedChar;
    if (tx_active == false) { //only check for receiver when not transmitting
        /* Check for receive errors */
        if(U1STAbits.FERR == 1)
        {
            return;
        }
        /* Must clear the overrun error to keep UART receiving */
        if(U1STAbits.OERR == 1)
        {
            U1STAbits.OERR = 0;
            return;
        }
        /* Get the data */
        if(!(U1STAHbits.URXBE == 1)) {
            ReceivedChar = U1RXREG;
            if (rx_active == false) { // receiving first character
                if (ReceivedChar == 'A') {
                    // start transmit
                    tx_count = 1;
                    tx_active = true;

                    uint16_t adc2 = vout_adc;
                    uint16_t adc3 = vin_adc;
                    uint16_t adc4 = iout_adc_b;
                    uint16_t adc5 = PG2DTH;
                    
                    uint8_t x1 = adc2 & 0xFF; // low byte
                    uint8_t x2 = adc2 >> 8; // high byte
                    uint8_t x3 = adc3 & 0xFF; // low byte
                    uint8_t x4 = adc3 >> 8; // high byte
                    uint8_t x5 = adc4 & 0xFF; // low byte
                    uint8_t x6 = adc4 >> 8; // high byte
                    uint8_t x7 = adc5 & 0xFF; // low byte
                    uint8_t x8 = adc5 >> 8; // high byte

                    U1TXREG = x1;// Transmit low bit
                    U1TXREG = x2;// Transmit high bit
                    U1TXREG = x3;// Transmit low bit
                    U1TXREG = x4;// Transmit high bit
                    U1TXREG = x5;// Transmit low bit
                    U1TXREG = x6;// Transmit high bit
                    U1TXREG = x7;// Transmit low bit
                    U1TXREG = x8;// Transmit high bit
                }
                else if (ReceivedChar == 't') { // set new dead times
                    *rx_data = ReceivedChar;
                    rx_active = true;
                    rx_count = 1;
                }
                else if (ReceivedChar == 'G') { // start converter,
                    //i_set = 30;
                    uint8_t x1 = 'G';
                    uint8_t x2 = period_set & 0xFF; // low byte
                    uint8_t x3 = period_set >> 8; // high byte
                    uint8_t x4 = '0';
                    uint8_t x5 = '0';
                    uint8_t x6 = 'a';
                    uint8_t x7 = 'c';
                    uint8_t x8 = 'k';

                    U1TXREG = x1;// Transmit low bit
                    U1TXREG = x2;// Transmit high bit
                    U1TXREG = x3;// Transmit low bit
                    U1TXREG = x4;// Transmit high bit
                    U1TXREG = x5;// Transmit low bit
                    U1TXREG = x6;// Transmit high bit
                    U1TXREG = x7;// Transmit low bit
                    U1TXREG = x8;// Transmit high bit
                    status_go = true;
                }
                else if (ReceivedChar == 'C') { // send firmware version number
                    U1TXREG = 'v';
                    U1TXREG = 0;
                    U1TXREG = 1;
                    U1TXREG = 0;
                    U1TXREG = 0;
                    U1TXREG = 0;
                    U1TXREG = 0;
                    U1TXREG = 1;
                }
                else if (ReceivedChar == 'x') { // shut down converter
                    uint8_t x1 = 'x';
                    uint8_t x2 = 0; // low byte
                    uint8_t x3 = 0; // high byte
                    uint8_t x4 = '0';
                    uint8_t x5 = '0';
                    uint8_t x6 = 'a';
                    uint8_t x7 = 'c';
                    uint8_t x8 = 'k';

                    U1TXREG = x1;// Transmit low bit
                    U1TXREG = x2;// Transmit high bit
                    U1TXREG = x3;// Transmit low bit
                    U1TXREG = x4;// Transmit high bit
                    U1TXREG = x5;// Transmit low bit
                    U1TXREG = x6;// Transmit high bit
                    U1TXREG = x7;// Transmit low bit
                    U1TXREG = x8;// Transmit high bit
                    systemstate = off;
                }
                else if (ReceivedChar == 'R') { // read timing
                    // start transmit
                    tx_count = 11;
                    tx_active = true;                    
                    uint8_t x1 = 'R';
                    uint8_t x2 = PG4PER & 0xFF; // low byte
                    uint8_t x3 = PG4PER >> 8; // high byte
                    uint8_t x4 = PG4PHASE & 0xFF; // low byte
                    uint8_t x5 = PG4PHASE >> 8; // high byte                    
                    uint8_t x6 = PG2PHASE & 0xFF; // low byte
                    uint8_t x7 = PG2PHASE >> 8; // high byte

                    uint8_t x8 = 0;

                    U1TXREG = x1;// Transmit low bit
                    U1TXREG = x2;// Transmit high bit
                    U1TXREG = x3;// Transmit low bit
                    U1TXREG = x4;// Transmit high bit
                    U1TXREG = x5;// Transmit low bit
                    U1TXREG = x6;// Transmit high bit
                    U1TXREG = x7;// Transmit low bit
                    U1TXREG = x8;// Transmit high bit

                }                
            }  else  { // rx is active, keep receiving more data
                *(rx_data + rx_count) = ReceivedChar;
                rx_count++;
                if (rx_count > 15) { // received total 16 bytes
                    rx_active = false;
                    rx_count = 0;
                    // calculate checksum
                    uart_calc_checksum(rx_data);
                    if ( rx_checksum == *(rx_data + 15) ) {
                        // checksum is correct, decode integer 

                        period_set = *(rx_data + 1) + (*(rx_data + 2) << 8);
                        phase1_set = *(rx_data + 3) + (*(rx_data + 4) << 8);
                        phase2_set = *(rx_data + 5) + (*(rx_data + 6) << 8);
                        if ( *(rx_data + 8) != 0 ) {
                            dt1re_set = *(rx_data + 8);
                        }
                        if ( *(rx_data + 9) != 0 ) {
                            dt1fe_set = *(rx_data + 9);
                        }
                        if ( *(rx_data + 10) != 0 ) {
                            dt2re_set = *(rx_data + 10);
                        }
                        if ( *(rx_data + 11) != 0 ) {
                            dt2fe_set = *(rx_data + 11);                        
                        }

                        // set PWMs only when running
                        if (systemstate == running) {
                            while (PG4STATbits.UPDATE == 1);
                            PG4PER = period_set;
                            PG4DC = (period_set >> 1);
                            PG4PHASE = phase1_set;
                            PG4DTL = (dt1fe_set << 1);
                            PG4DTH = (dt1re_set << 1);
                            PG4STATbits.UPDREQ = 1;

                            while (PG2STATbits.UPDATE == 1);
                            PG2PER = period_set;
                            PG2DC = (period_set >> 1);
                            PG2PHASE = phase2_set;                            
                            PG2DTL = (dt2fe_set << 1);
                            PG2DTH = (dt2re_set << 1);
                            PG2STATbits.UPDREQ = 1;
                        }

                        // send acknowledgment data

                        uint8_t x1 = rx_data[0];
                        
                        uint16_t adc2 = vout_adc;
                        uint16_t adc3 = vin_adc;
                    
                        uint8_t x2 = adc2 & 0xFF; // low byte
                        uint8_t x3 = adc2 >> 8; // high byte
                        uint8_t x4 = adc3 & 0xFF; // low byte
                        uint8_t x5 = adc3 >> 8; // high byte
                        uint8_t x6 = dt2re_set;
                        uint8_t x7 = dt2fe_set;
                        uint8_t x8 = 'x';

                        U1TXREG = x1;// Transmit low bit
                        U1TXREG = x2;// Transmit high bit
                        U1TXREG = x3;// Transmit low bit
                        U1TXREG = x4;// Transmit high bit
                        U1TXREG = x5;// Transmit low bit
                        U1TXREG = x6;// Transmit high bit
                        U1TXREG = x7;// Transmit low bit
                        U1TXREG = x8;// Transmit high bit

                        // set new current reference
//                        period_set = rx_decoded;
                    } else {
                        uint8_t x1 = rx_data[0]+1;
                        uint8_t x2 = period_set & 0xFF; // low byte
                        uint8_t x3 = period_set >> 8; // high byte
                        uint8_t x4 = dt1re_set;
                        uint8_t x5 = dt1fe_set;
                        uint8_t x6 = dt2re_set;
                        uint8_t x7 = dt2fe_set;
                        uint8_t x8 = rx_checksum;

                        U1TXREG = x1;// Transmit low bit
                        U1TXREG = x2;// Transmit high bit
                        U1TXREG = x3;// Transmit low bit
                        U1TXREG = x4;// Transmit high bit
                        U1TXREG = x5;// Transmit low bit
                        U1TXREG = x6;// Transmit high bit
                        U1TXREG = x7;// Transmit low bit
                        U1TXREG = x8;// Transmit high bit                        
                    }
                }
            }
        }
    } else { // transmission is active
        if(U1STAbits.TRMT == 1) { // TX buffer empty, we can write

            if (tx_count == 1) {
                uint16_t adc4 = PG2DC;
                // uint16_t adc5 = duty_out;
                // uint16_t adc6 = temperature_adc;
                uint8_t x7 = systemstate;
                uint8_t x1 = adc4 & 0xFF; // low byte
                uint8_t x2 = adc4 >> 8; // high byte
                uint8_t x3 = (PG4DTH >> 1) & 0xFF; // low byte
                uint8_t x4 = (PG4DTL >> 1) & 0xFF;
                uint8_t x5 = (PG2DTH >> 1) & 0xFF;
                uint8_t x6 = (PG2DTL >> 1) & 0xFF;

                U1TXREG = x1;
                U1TXREG = x2;
                U1TXREG = x3;
                U1TXREG = x4;
                U1TXREG = x5;
                U1TXREG = x6;
                U1TXREG = x7;
                U1TXREG = 0;
                // finish transmission
                tx_active = false;
                tx_count = 0;
            } 
            else if (tx_count == 11) {
                uint8_t x1 = PG4DTH >> 1;
                uint8_t x2 = PG4DTL >> 1;
                uint8_t x3 = PG2DTH >> 1;
                uint8_t x4 = PG2DTL >> 1;
                U1TXREG = x1;
                U1TXREG = x2;
                U1TXREG = x3;
                U1TXREG = x4;
                U1TXREG = 0;
                U1TXREG = 0;
                U1TXREG = 0;
                U1TXREG = 0;       
                // finish transmission
                tx_active = false;
                tx_count = 0;                
            }
        }
    }
}

volatile uint16_t uart_calc_checksum(volatile uint8_t* data) {
    volatile uint16_t _sum = 0, _i;
    for(_i=0;_i<15;_i++) {
        _sum += *(data+_i);
    }
    // _sum = *(data) + *(data + 1) + *(data + 2);
    rx_checksum = (_sum & 0xFF);
    return (1);
}


