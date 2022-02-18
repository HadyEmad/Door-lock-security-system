 /******************************************************************************
 *
 * Module: timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR TIMER0 driver
 *
 * Author: Hady Emad
 *
 *******************************************************************************/

#include "timer.h"
#include "common_macros.h"
#include <avr\io.h>
#include <avr\interrupt.h>

/*******************************************************************************
 *                              Global variables                               *
 *******************************************************************************/

static volatile void (*timer_callBackPtr)(void) = NULL_PTR; /* Pointer to timer callback function */

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/*Timer0 overflow mode ISR*/
ISR (TIMER0_OVF_vect) {
	/* Call the Call Back function in the application after the overflow */
	if (timer_callBackPtr != NULL_PTR) {
		timer_callBackPtr();
	}
}

/*Timer0 compare match mode ISR*/
ISR (TIMER0_COMP_vect)
{
	/* Call the Call Back function in the application after the compare match */

	if (timer_callBackPtr != NULL_PTR) {
		timer_callBackPtr();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

 /*Configure timer parameters and start it */
void TIMER_init(TIMER_configType *timer_config) {
	TCNT0 = timer_config->initial_value; /* Set Timer initial value */
	OCR0 = timer_config->compare_value; /* Set Timer compare value  */
	TIMSK = (TIMSK & 0xFC) | timer_config->mode; /* Enabling interrupts */
	TCCR0 = (1 << FOC0);  /* Non PWM mode FOC0=1 */
	if (timer_config->mode == CTC_MODE) /* Set Timer mode (overflow or ctc)*/
		SET_BIT(TCCR0, WGM01);
	TCCR0 |= timer_config->clock | (timer_config->oc_pin << 4); /*Configuring prescaler and oc0 pin */
}

/*Setting timer callback function*/
void TIMER_setCallBack(void (*a_ptr)(void)) {
	timer_callBackPtr = a_ptr;
}

/*Stopping timer and clearing timer registers*/
void TIMER_DeInit(void) {
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;
	TIMSK = (TIMSK & 0xFC);
}
