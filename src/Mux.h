/*
 * Mux.h
 *
 * Created: 1/27/2025 10:08:53 AM
 *  Author: Omar Ibrahim
 */ 


#ifndef MUX_H_
#define MUX_H_

unsigned char readMux();
void digitalWrite(volatile unsigned char* port, unsigned char pin, int status);


#endif /* MUX_H_ */