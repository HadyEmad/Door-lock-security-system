 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum{
	NO_PARITY,EVEN_PARITY=2,ODD_PARITY
}UART_parityMode;

typedef enum{
	NO_INT,UDR_INT,TX_INT,TX_UDR_INT,RX_INT,RX_UDR_INT,RX_TX_INT,RX_TX_UDR_INT
}UART_interruptMode;

typedef enum{
	ONE_STOP_BIT,TWO_STOP_BIT
}UART_stopBitSelect;

typedef enum{
	CHAR_SIZE_5,CHAR_SIZE_6,CHAR_SIZE_7,CHAR_SIZE_8,CHAR_SIZE_9=0b111,
}UART_charSize;

typedef struct{
	UART_stopBitSelect stop_bit;
	UART_charSize char_size;
	UART_parityMode parity_mode;
	UART_interruptMode interrupt_mode;
	uint32 baud_rate;
}UART_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(UART_configType *UART_config);
/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint16 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint16 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

/*
 * Description :
 * Send 4 bytes numbers by looping on 4 times on the UART_sendByte function and making a 1 byte pointer that increases
 * each iteration to point to the next byte of the number.
 */
void UART_sendLong(uint32 number);

/*
 * Description :
 * Receive 4 bytes numbers by looping on 4 times on the UART_recieveByte function and making a 1 byte pointer that increases
 * each iteration to point to the next byte of the number.
 */
void UART_recieveLong(uint32 *number);

#endif /* UART_H_ */
