 /******************************************************************************
 *
 * Module: timer
 *
 * File Name: timer.h
 *
 * Description: Header file for the AVR TIMER0 driver
 *
 * Author: Hady Emad
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	NORMAL_MODE=1,CTC_MODE
}TIMER_mode;

typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,
	EXTERNAL_FALLING,EXTERNAL_RISING
}TIMER_clock;

typedef enum{
	NORMAL_OC_PIN,TOGGLE_OC_PIN,CLEAR_OC_PIN,SET_OC_PIN
}TIMER_ocPinMode;

typedef struct{
	TIMER_mode mode;
	TIMER_clock clock;
	uint8 initial_value;
	uint8 compare_value ;
	TIMER_ocPinMode oc_pin ;
}TIMER_configType;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*Configure timer parameters and start it */
void TIMER_init(TIMER_configType *timer_config);

/*Setting timer callback function*/
void TIMER_setCallBack(void (*a_ptr) (void));

/*Setting timer callback function*/
void TIMER_DeInit(void);

#endif /* TIMER_H_ */
