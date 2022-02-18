 /******************************************************************************
 *
 * Module: timer_delay
 *
 * File Name: timer_delay.c
 *
 * Description: Source file for the timer_delay
 *
 * Author: Hady Emad
 *
 *******************************************************************************/

#include "timer.h"

/*variable to increase after each interrupt*/
static volatile uint32 tik;

/*function that process the time after each interrupt*/

static void time_processing(void);

void delay_millis(uint32 time) {
	/* Configuring timer to work in the normal mode with 1024 prescaler starting from 0 */
	TIMER_configType TIMER_config = { NORMAL_MODE, F_CPU_1024, 0, 0,
			NORMAL_OC_PIN };
	uint32 tik_time,max_tiks;
	/* Calculating the time of one overflow */
	tik_time = ((float)1024 / F_CPU) * 256 * 1000;
	/* Resetting the number of overflows */
	tik = 0;
	/*Calculating needed number of overflows to achieve given polling time*/
	max_tiks=time/tik_time;
	/*Setting timer callback function*/
	TIMER_setCallBack(&time_processing);
	/*Initiating timer to begin counting*/
	TIMER_init(&TIMER_config);
	while (tik < max_tiks) {


	}

	/*Stopping timer and clearing timer registers*/
	TIMER_DeInit();
}

static void time_processing(void) {
	tik++;
}
