/*
 *  GPIO.h
 *
 *  Created: 2/15/2025 9:11:22 AM
 *  Author: Omar
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#define DDR_PWM_PIN DDRB
#define PORT_PWM_PIN PORTB
#define PWM_PIN 3


#define DDR_SWs_Ins DDRD
#define PORT_SWs PORTD
#define SW_DPIN PIND
#define IN_ONE 3
#define IN_TWO 4
#define LEFT_SW_PIN 5
#define RIGHT_SW_PIN 6

/* set bit number (bit_number) on a 8-bits register/variable (reg)*/
#define MY_SB(reg, bit_number) (reg |= (1 << bit_number))     

/* clear bit number (bit_number) on a 8-bits register/variable (reg)*/
#define MY_CB(reg, bit_number) (reg &= (~(1 << bit_number)))  

/* return value of bit number (bit_number) on a 8-bits register/variable (reg)*/
#define MY_BV(reg, bit_number) (((reg) >> (bit_number)) & 1)  

/* High Byt Low Bye*/
#define LOW_BYTE(data) (((data) &= 0x0F))
#define HIGH_BYTE(data) (((data) &= 0xF0))

#endif /* GPIO_H_ */