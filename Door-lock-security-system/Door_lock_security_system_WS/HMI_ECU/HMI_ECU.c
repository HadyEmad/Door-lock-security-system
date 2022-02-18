/******************************************************************************
 *
 * File Name: HMI_ECU.c
 *
 * Description: Source file for the human interface mcu
 *
 * Author: Hady Emad
 *
 *******************************************************************************/
#include <avr\io.h>
#include "keypad.h"
#include "lcd.h"
#include "timer_delay.h"
#include "uart.h"

/*******************************************************************************
 *                           Definitions		                               *
 *******************************************************************************/


#define SEND_PASS	 	0xF1
#define CHECK_PASS 		0XF2
#define PASS_OK			0xF3
#define OPEN_DOOR		0xF4
#define BUZZER_ON		0xF6
#define RIGHT_PASS		0xF7
#define WRONG_PASS		0xF8
#define CHANGE_PASS		0xF9

/*******************************************************************************
 *                           Functions prototypes                              *
 *******************************************************************************/

uint32 ask_for_pass(void);
void ask_for_new_pass(uint32 *pass, uint32 *repass);
void show_main_options(uint8 *option);
void open_door(uint8 *pass_attempts, uint8 *option);
void change_pass(uint8 *pass_attempts, uint8 *option);
uint8 check_pass(void);

/*******************************************************************************
 *                          ECU Main function                                  *
 *******************************************************************************/

int main() {

	SREG |= (1 << 7);
	uint8 option = 1;
	uint8 pass_attempts = 3;
	LCD_init();
	UART_configType UART_config = { ONE_STOP_BIT, CHAR_SIZE_8, NO_PARITY,
			NO_INT, 14400 };
	UART_init(&UART_config);

	while (1) {

		switch (option) {

		/* Creating new password step */
		case 1: {
			uint32 pass = 0;
			uint32 repass = 0;
			ask_for_new_pass(&pass, &repass);
			if (pass == repass) {
				LCD_clearScreen();
				LCD_displayString("Password match !");
				delay_millis(3000);

				UART_sendByte(SEND_PASS);

				while (UART_recieveByte() != PASS_OK) {
				};

				UART_sendLong(pass);
				option = 2;
			} else {
				LCD_clearScreen();
				LCD_displayString("Pass mismatch !");
				LCD_displayStringRowColumn(1, 0, "Please try again");
				option = 1;
				delay_millis(3000);
			}
		}
			break;

			/* Showing main menu step */
		case 2:
			show_main_options(&option);
			break;

			/* Opening the door step */
		case 3:
			open_door(&pass_attempts, &option);
			break;

			/* Changing password step */

		case 4:
			change_pass(&pass_attempts, &option);
			break;
		default: {

		}

		}

	}
}

/*******************************************************************************
 *                           Function definitions                              *
 *******************************************************************************/

void ask_for_new_pass(uint32 *pass, uint32 *repass) {
	LCD_clearScreen();
	LCD_displayString("Please enter new ");
	LCD_displayStringRowColumn(1, 0, "password: ");
	while (*pass < 100000) {
		*pass += KEYPAD_getPressedKey();
		*pass *= 10;
		LCD_displayCharacter('*');
		delay_millis(400);
	}
	*pass /= 10;
	while (KEYPAD_getPressedKey() != 13) {
	};
	delay_millis(400);
	LCD_clearScreen();
	LCD_displayString("Please re-enter");
	LCD_displayStringRowColumn(1, 0, "password: ");
	while (*repass < 100000) {
		*repass += KEYPAD_getPressedKey();
		*repass *= 10;
		LCD_displayCharacter('*');
		delay_millis(400);
	}
	*repass /= 10;
	while (KEYPAD_getPressedKey() != 13) {
	};
	delay_millis(400);
}

uint32 ask_for_pass(void) {
	uint32 password = 0;
	delay_millis(400);
	LCD_clearScreen();
	LCD_displayString("Please enter  ");
	LCD_displayStringRowColumn(1, 0, "password: ");
	while (password < 100000) {
		password += KEYPAD_getPressedKey();
		password *= 10;
		LCD_displayCharacter('*');
		delay_millis(400);
	}
	password /= 10;
	while (KEYPAD_getPressedKey() != 13) {
	};
	delay_millis(400);

	return password;
}

void show_main_options(uint8 *option) {
	uint8 key;
	LCD_clearScreen();
	LCD_displayString("+ :open the door");
	LCD_displayStringRowColumn(1, 0, "- :change pass");
	key = KEYPAD_getPressedKey();
	delay_millis(400);
	if (key == '+')
		*option = 3;
	else if (KEYPAD_getPressedKey() == '-')
		*option = 4;
	else {
		LCD_clearScreen();
		LCD_displayString("Wrong choice!");
		LCD_displayStringRowColumn(1, 0, "Please try again");
		*option = 2;
	}
}

uint8 check_pass(void) {
	uint32 pass;
	pass = ask_for_pass();
	while (UART_recieveByte() != PASS_OK) {
	};
	UART_sendLong(pass);
	if (UART_recieveByte() == RIGHT_PASS) {
		return RIGHT_PASS;
	} else
		return WRONG_PASS;
}

void open_door(uint8 *pass_attempts, uint8 *option) {
	UART_sendByte(OPEN_DOOR);
	uint8 pass_state = check_pass();

	if (pass_state == RIGHT_PASS) {
		*pass_attempts = 3;
		LCD_clearScreen();
		LCD_displayString("Unlocking door");
		delay_millis(15000);
		LCD_clearScreen();
		LCD_displayString("Door is opened");
		delay_millis(3000);
		LCD_clearScreen();
		LCD_displayString("Locking door");
		delay_millis(15000);
		*option = 2;
	} else {
		*pass_attempts = *pass_attempts - 1;
		if (*pass_attempts > 0) {
			LCD_clearScreen();
			LCD_displayString("Wrong password!");
			LCD_displayStringRowColumn(1, 0, "Please try again");
			delay_millis(3000);
			*option = 3;
		} else {
			UART_sendByte(BUZZER_ON);
			LCD_clearScreen();
			LCD_displayString("There must be ");
			LCD_displayStringRowColumn(1, 0, "a threat !");
			delay_millis(60000);
			*pass_attempts = 3;
			*option = 2;
		}
	}

}

void change_pass(uint8 *pass_attempts, uint8 *option) {
	UART_sendByte(CHANGE_PASS);
	uint8 pass_state = check_pass();
	if (pass_state == RIGHT_PASS) {
		*pass_attempts = 3;
		*option = 1;
	} else {
		*pass_attempts -= 1;
		if (*pass_attempts > 0) {
			LCD_clearScreen();
			LCD_displayString("Wrong password!");
			LCD_displayStringRowColumn(1, 0, "Please try again");
			delay_millis(3000);
			*option = 4;
		} else {
			UART_sendByte(BUZZER_ON);
			LCD_clearScreen();
			LCD_displayString("There must be ");
			LCD_displayStringRowColumn(1, 0, "a threat !");
			delay_millis(60000);
			*pass_attempts = 3;
			*option = 2;
		}
	}
}
