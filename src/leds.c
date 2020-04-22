/*
 * leds.c
 *
 *  Created on: 13 abr. 2020
 *      Author: mauri
 */


#include "sapi.h"
#include "leds.h"

void turnOnRED(void){
	gpioWrite(LEDG,OFF);
	gpioWrite(LEDB,OFF);
	gpioToggle(LEDR);
}
void turnOnGREEN(void){
	gpioWrite(LEDR,OFF);
	gpioWrite(LEDB,OFF);
	gpioToggle(LEDG);
}
void turnOnBLUE(void){
	gpioWrite(LEDR,OFF);
	gpioWrite(LEDG,OFF);
	gpioToggle(LEDB);
}
void turnOffRGB(void){
	gpioWrite(LEDR,OFF);
	gpioWrite(LEDG,OFF);
	gpioWrite(LEDB,OFF);
}
