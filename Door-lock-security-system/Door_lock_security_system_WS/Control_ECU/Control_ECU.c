/******************************************************************************
 *
 * File Name: Control_ECU.c
 *
 * Description: Source file for the control ECU
 *
 * Author: Hady Emad
 *
 *******************************************************************************/

#include <avr\io.h>
#include "uart.h"
#include "external_eeprom.h"
#include "buzzer.h"
#include "dc_motor.h"
#include "twi.h"
#include "timer_delay.h"

/*******************************************************************************
 *                           Definitions		                               *
 *******************************************************************************/

#define REC_PASS 		0xF1
#define CHECK_PASS 		0XF2
#define PASS_OK			0xF3
#define OPEN_DOOR		0xF4
#define BUZZER_ON		0xF6
#define RIGHT_PASS		0xF7
#define WRONG_PASS		0xF8
#define CHANGE_PASS		0xF9
#define PASSWORD_ADDRESS	0x0300

/*******************************************************************************
 *                           Functions prototypes                              *
 *******************************************************************************/

uint8 check_pass(void);

/*******************************************************************************
 *                          ECU Main function                                  *
 *******************************************************************************/

int main(void) {

	uint8 option = 0;
	UART_configType UART_config = { ONE_STOP_BIT, CHAR_SIZE_8, NO_PARITY,NO_INT, 14400 };
	TWI_configType TWI_config = { 100000, 5 };
	SREG |= (1 << 7);
	UART_init(&UART_config);
	TWI_init(&TWI_config);
	buzzer_init();
	DcMotor_init();
	LCD_init();

	while (1) {

		switch (option) {

		case REC_PASS: {
			uint32 pass;
			UART_sendByte(PASS_OK);
			UART_recieveLong(&pass);
			EEPROM_writeLong(pass, PASSWORD_ADDRESS);
		}
			option = 0;
			break;

		case BUZZER_ON:
			buzzer_on();
			delay_millis(60000);
			buzzer_off();
			option = 0;
			break;

		case OPEN_DOOR: {
			uint8 pass_state;
			pass_state = check_pass();
			if (pass_state == RIGHT_PASS) {
				UART_sendByte(RIGHT_PASS);
				DcMotor_Rotate(MOTOR_CW);
				delay_millis(15000);
				DcMotor_Rotate(MOTOR_OFF);
				delay_millis(3000);
				DcMotor_Rotate(MOTOR_ACW);
				delay_millis(15000);
				DcMotor_Rotate(MOTOR_OFF);
			} else {
				UART_sendByte(WRONG_PASS);
			}
		}
			option = 0;
			break;

		case CHANGE_PASS: {
			uint8 pass_state;
			pass_state = check_pass();
		if (pass_state == RIGHT_PASS){
			UART_sendByte(RIGHT_PASS);

		}else{
			UART_sendByte(WRONG_PASS);
		}
	}
		option=0;
		break;
	default:
		option = UART_recieveByte();
		}
	}

}

/*******************************************************************************
 *                           Function definitions                              *
 *******************************************************************************/
uint8 check_pass(void) {
	uint32 saved_pass, rec_pass;
	EEPROM_readLong(PASSWORD_ADDRESS, &saved_pass);
	UART_sendByte(PASS_OK);
	UART_recieveLong(&rec_pass);
	if (saved_pass == rec_pass) {
		return RIGHT_PASS;
	} else {
		return WRONG_PASS;
	}
}
