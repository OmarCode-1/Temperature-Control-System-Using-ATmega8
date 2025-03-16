/*
 * ADC_driver.c
 *
 * Created: 2/15/2025 9:16:33 AM
 *  Author: Omar
 */ 
#include <avr/io.h>
#include "ADC_driver.h"

void initADC(void)
{
    // Set the AREF = RVCC .
    ADMUX |= (1 << REFS0);
    
    // Set prescaller 128 and enable the adc .
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADEN);
}

uint16_t readADC(unsigned char bit_channel)
{
    // Select the the bit channel and make safety mask .
    ADMUX = (ADMUX & 0xF0) | (bit_channel & 0x0F);

    // Enable the start conversion mode .
    ADCSRA |= (1 << ADSC);

    // Wait the conversion is complete .
    while(ADCSRA & (1 << ADSC));

    return ADC;
}