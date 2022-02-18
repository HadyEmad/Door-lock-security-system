 /******************************************************************************
 *
 * File Name: buzzer.h
 *
 * Description: Header file for buzzer functions
 *
 * Author: Hady Emad
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#define BUZZER_PORT PORTA_ID
#define BUZZER_PIN 	PIN0_ID

void buzzer_init(void);
void buzzer_on(void);
void buzzer_off(void);


#endif /* BUZZER_H_ */
