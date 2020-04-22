/*
 * pwmconfig.c
 *
 *  Created on: 12 abr. 2020
 *      Author: mauri
 */

#include "sapi.h"
#include "pwmconfig.h"

void pwminit (Spwm_t *pSpwm,pwmMap_t pwm){
	pwmConfig( 0, PWM_ENABLE );
	pwmConfig( pSpwm->Spwm=pwm, PWM_ENABLE_OUTPUT );
}

void pwm_increment(Spwm_t *pSpwm){
	if(pSpwm->dutycicle<255){
		pSpwm->dutycicle=pSpwm->dutycicle+10;
	}
	else{
		pSpwm->dutycicle=255;
	}
	uart(pSpwm->dutycicle);
	pwmWrite(pSpwm->Spwm,pSpwm->dutycicle);
}

void pwm_decrement(Spwm_t *pSpwm){
	if(pSpwm->dutycicle>0  ){
		pSpwm->dutycicle=pSpwm->dutycicle-10;
	}
	if(pSpwm->dutycicle>255){
		pSpwm->dutycicle=0;
	}
	uart(pSpwm->dutycicle);
	pwmWrite(pSpwm->Spwm,pSpwm->dutycicle);
}
static uint8_t map(uint16_t dato1,uint16_t dato2,uint16_t dato3,uint16_t dato4,uint16_t read){

	dato1=dato3;
	if (dato3>dato4){
		dato4=dato3-dato4;
		return dato1-(read*dato4/dato2);
	}
	else{
		dato4=dato4-dato3;
		return dato1+(read*dato4/dato2);
	}

}
void adc_pwm(Spwm_t *pSpwm){
	pSpwm->pwmval=adcRead(CH1);
	uart(pSpwm->pwmval);
	pwmWrite(pSpwm->Spwm,map(0,1023,0,255,pSpwm->pwmval));
}

void uart(uint16_t dato){
	char uartBuff[10];
	itoa(dato,uartBuff,10);
	uartWriteString( UART_USB, uartBuff );
	uartWriteString( UART_USB, ";\r\n" );
}

