/*
 * pwmconfig.h
 *
 *  Created on: 12 abr. 2020
 *      Author: mauri
 */

#ifndef PROGRAMAS_MAIN_INC_PWMCONFIG_H_
#define PROGRAMAS_MAIN_INC_PWMCONFIG_H_
#include "sapi.h"

typedef struct {
	uint16_t dutycicle;
	uint16_t pwmval;
	pwmMap_t Spwm;
}Spwm_t;

void pwminit (Spwm_t *pSpwm,pwmMap_t pwm);

void pwm_increment(Spwm_t *pSpwm);
void pwm_decrement(Spwm_t *pSpwm);
void pwm_adc(Spwm_t *pSpwm);

#endif /* PROGRAMAS_MAIN_INC_PWMCONFIG_H_ */
