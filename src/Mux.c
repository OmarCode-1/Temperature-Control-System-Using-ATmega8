/*
 * Mux.c
 *
 * Created: 1/27/2025 10:08:40 AM
 *  Author: Omar Ibrahim
 */ 

#include <avr/io.h>
#include "GPIO.h"
#include "Mux.h"

void digitalWrite(volatile unsigned char* port, unsigned char pin, int status)
{
    /**
     * this function made to set or clear the bin of port .
     */
    if (status) {
        MY_SB(*port, pin);
    } else {
        MY_CB(*port, pin);
    }
}

unsigned char readMux()
{   
    /**
     *********************************************************************** 
     *      7-segment ==> a, b, c, d, e, f, g, h
     *      abc_reading_vlue (value of them)
     *********************************************************************** 
     *           *----------------------------------------------*
     *           | abc_reading_value          |      7-seg      |
     *           |----------------------------|-----------------|
     *           |              0             |        a        |
     *           |              1             |        b        |
     *           |              2             |        c        |
     *           |              3             |        d        |
     *           |              7             |        e        |
     *           |              6             |        f        |
     *           |              5             |        g        |
     *           |              4             |        h        |
     *           *----------------------------------------------*
     *********************************************************************** 
     *      abc_reading_vlue is one (byte) ==> 0b00000  0 0 0
     *                                                  C B A
     *      the last three bits is C B A
     *      
     *      bit-0 ==> A
     *      bit-1 ==> B
     *      bit-2 ==> C
     ************************************************************************ 
     *      Example : 
     *          -> if i need read the (d) value
     *          -> i will set the (abc_reading_vlue[3]) variable is 3
     *          -> the i variable is 0b00000011
     *          -> i will take the last 3 bits ==> 011
     *          -> write them into C(S2) B(S1) A(S0)
     *          -> C = 0    |   B = 1   |   A = 1
     *          -> and i will read the output pin (Y pin) 
     *          -------------------- Note --------------------
     *      I will repeat this process on all input (from a to h).
     */

    unsigned char temp_value = 0;
    
    for(unsigned char i = 0; i < 8; i++)
    {
        // read C input of Mux .
        digitalWrite(&PORTD, 2, MY_BV(i, 2));

        // read B input of Mux .
        digitalWrite(&PORTD, 1, MY_BV(i, 1));

        // read A input of Mux .
        digitalWrite(&PORTD, 0, MY_BV(i, 0));

        // read pin by pin and store it .
        temp_value |= (MY_BV(PINB, 2) << i);
    }

    // return value of floor .
    return temp_value;
}