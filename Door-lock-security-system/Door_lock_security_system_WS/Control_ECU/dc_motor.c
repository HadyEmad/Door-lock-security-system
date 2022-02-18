/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the dc motor driver
 *
 * Author: Hady Emad
 *
 *******************************************************************************/

#include "gpio.h"
#include "common_macros.h"
#include "dc_motor.h"

/*
 * Setting the DC motor direction pins as output and initialising them by 0
 */

void DcMotor_init(void){
	GPIO_setupPinDirection(DC_MOTOR_PORT ,DC_MOTOR_IN1_PIN ,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT ,DC_MOTOR_IN2_PIN ,PIN_OUTPUT);
	GPIO_writePin(DC_MOTOR_PORT ,DC_MOTOR_IN1_PIN ,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT ,DC_MOTOR_IN2_PIN ,LOGIC_LOW);
}

/* Setting motor direction by writing state value to their port position*/
void DcMotor_Rotate(DcMotor_State state){
	uint8 port_value ;
	port_value = GPIO_readPort(DC_MOTOR_PORT);
	port_value = (port_value & 0x3F) | (state<<6);
	GPIO_writePort (DC_MOTOR_PORT,port_value);
}


