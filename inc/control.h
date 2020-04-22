/*
 * control.h
 *
 *  Created on: 12 abr. 2020
 *      Author: mauri
 */

#ifndef PROGRAMAS_MAIN_INC_CONTROL_H_
#define PROGRAMAS_MAIN_INC_CONTROL_H_
#include "sapi.h"

typedef enum {HOME, SET_Y,SET_YADC,SET_R,SET_RADC,SET_G,SET_GADC,}stateMEF_t;
typedef struct {
stateMEF_t state;
delay_t delaycontrol;
}control_t;

bool_t controlMEFInit(control_t * pcontrol);
bool_t controlconfig(control_t * pcontrol);


#endif /* PROGRAMAS_MAIN_INC_CONTROL_H_ */
