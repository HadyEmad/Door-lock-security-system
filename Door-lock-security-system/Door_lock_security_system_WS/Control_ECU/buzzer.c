 /******************************************************************************
 *
 * File Name: buzzer.c
 *
 * Description: Source file for buzzer functions
 *
 * Author: Hady Emad
 *
 *******************************************************************************/

#include "gpio.h"
#include "buzzer.h"

void buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
}

void buzzer_on(void){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);
}

void buzzer_off(void){
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}
