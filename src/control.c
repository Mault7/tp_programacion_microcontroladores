/*
 * control.c
 *
 *  Created on: 12 abr. 2020
 *      Author: mauri
 */
#include "sapi.h"
#include "debounce.h"
#include "control.h"
#include "pwmconfig.h"
#include "leds.h"

static debounceButton_t BT_UP;
static debounceButton_t BT_DOWN;
static debounceButton_t BT_HOME;
static debounceButton_t BT_EXIT;
static Spwm_t pwmY;
static Spwm_t pwmR;
static Spwm_t pwmG;


bool_t controlMEFInit(control_t * pcontrol){

	uartConfig( UART_USB, 115200 );

	if(pcontrol==NULL){
		return FALSE;
	}

	pcontrol->state=HOME;
	delayConfig(&pcontrol->delaycontrol,100);
	debounceSM_Init(&BT_UP, TEC1);
	debounceSM_Init(&BT_DOWN, TEC2);
	debounceSM_Init(&BT_HOME, TEC3);
	debounceSM_Init(&BT_EXIT, TEC4);
	pwminit(&pwmY,PWM7);
	pwminit(&pwmR,PWM8);
	pwminit(&pwmG,PWM9);
	adcConfig( ADC_ENABLE );

	return TRUE;
}
bool_t controlconfig(control_t * pcontrol){

	if (pcontrol==NULL){
		return FALSE;
	}

	debounceSM_Update(&BT_UP);
	debounceSM_Update(&BT_DOWN);
	debounceSM_Update(&BT_HOME);
	debounceSM_Update(&BT_EXIT);

	switch(pcontrol->state){
	case HOME:
		turnOffRGB();
		if (BT_HOME.buttonReleased){
			pcontrol->state=SET_Y;
		}
		if (BT_UP.buttonPressed && BT_DOWN.buttonPressed ){
			pcontrol->state=SET_YADC;
		}
		break;
	case SET_Y:
		if (delayRead(&pcontrol->delaycontrol)){
			turnOnBLUE();
		}
		if(BT_HOME.buttonReleased){
			pcontrol->state=SET_R;
		}
		if(BT_EXIT.buttonReleased){
			pcontrol->state=HOME;
		}
		if(BT_UP.buttonReleased){
			pwm_increment(&pwmY);
		}
		if (BT_DOWN.buttonReleased){
			pwm_decrement(&pwmY);
		}

		break;
	case SET_YADC:
		if(BT_HOME.buttonReleased){
			pcontrol->state=SET_RADC;
		}
		if(BT_EXIT.buttonReleased){
			pcontrol->state=HOME;
		}
		adc_pwm(&pwmY);
		break;
	case SET_R:
		if (delayRead(&pcontrol->delaycontrol)){
			turnOnRED();
		}
		if(BT_HOME.buttonReleased){
			pcontrol->state=SET_G;
		}
		if(BT_EXIT.buttonReleased){
			pcontrol->state=HOME;
		}
		if(BT_UP.buttonReleased){
			pwm_increment(&pwmR);
		}
		if (BT_DOWN.buttonReleased){
			pwm_decrement(&pwmR);
		}
		break;
	case SET_RADC:
		if(BT_HOME.buttonReleased){
			pcontrol->state=SET_GADC;
		}
		if(BT_EXIT.buttonReleased){
			pcontrol->state=HOME;
		}
		adc_pwm(&pwmR);
		break;
	case SET_G:
		if (delayRead(&pcontrol->delaycontrol)){
			turnOnGREEN();
		}
		if(BT_HOME.buttonReleased){

			pcontrol->state=SET_Y;
		}
		if(BT_EXIT.buttonReleased){
			pcontrol->state=HOME;
		}
		if(BT_UP.buttonReleased){
			pwm_increment(&pwmG);
		}
		if (BT_DOWN.buttonReleased){
			pwm_decrement(&pwmG);
		}
		break;
	case SET_GADC:
		if(BT_HOME.buttonReleased){
			pcontrol->state=SET_YADC;
		}
		if(BT_EXIT.buttonReleased){
			pcontrol->state=HOME;
		}
		adc_pwm(&pwmG);

		break;
	}
	return TRUE;
}



