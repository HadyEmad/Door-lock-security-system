/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the dc motor driver
 *
 * Author: Hady Emad
 *
 *******************************************************************************/


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DC_MOTOR_PORT PORTD_ID
#define DC_MOTOR_IN1_PIN PIN6_ID
#define DC_MOTOR_IN2_PIN PIN7_ID
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
}DcMotor_State;


DcMotor_State{
	MOTOR_OFF,MOTOR_ACW,MOTOR_CW
};

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Function to initialise DC motor pins */

void DcMotor_init(void);

/* Function to set speed and direction of the DC motor */

void DcMotor_Rotate(DcMotor_State state);

#endif /* DC_MOTOR_H_ */
