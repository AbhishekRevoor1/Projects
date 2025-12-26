/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Nov 8, 2025
 *      Author: abhishek-revoor
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"

/***********************************GPIO Configuration Structure***********************************************/
typedef struct
{
	uint8_t GPIO_PinNumber;   		//For Possible inputs refer @GPIO PIN NUMBER section macros
	uint8_t GPIO_PinMode;	  		//For Possible inputs refer @GPIO_PIN_MODE section macros
	uint8_t GPIO_PinSpeed;	  		//For Possible inputs refer @GPIO_PIN_SPEED section macros
	uint8_t GPIO_PinPuPdControl;	//For Possible inputs refer @GPIO_PIN_PULLUP_PULLDOWN section macros
	uint8_t GPIO_PinOPType;			//For Possible inputs refer @GPIO_OUTPUT_PIN_TYPE section macros
	uint8_t GPIO_PinAltFunMode;		//For Possible inputs refer
}GPIO_PinConfig_t;


/**********************************GPIO Handler Structure****************************************************/
typedef struct
{
	GPIO_RegDef_t	*pGPIOx;			//Pointer to hold the base address of the GPIO peripheral which pin belongs
	GPIO_PinConfig_t GPIO_PinConfig;	//Holds the GPIO PIN configuration settings
}GPIO_Handle_t;

//@GPIO_PIN_MODE
//GPIO Possible modes macros
#define GPIO_MODE_IN		0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ALTFN		2
#define GPIO_MODE_ANALOG	3
#define GPIO_MODE_IT_FT		4
#define GPIO_MODE_IT_RT		5
#define GPIO_MODE_IT_RFT	6

//@GPIO_OUTPUT_PIN_TYPE
//GPIO possible output types
#define GPIO_OP_TYPE_PP		0   //PUSH PULL
#define GPIO_OP_TYPE_OD		1	//OPEN DRAIN

//@GPIO_PIN_SPEED
//GPIO pin possible output speeds
#define GPIO_SPEED_LOW		0
#define GPIO_SPEED_MEDIUM	1
#define GPIO_SPEED_FAST		2
#define GPIO_SPEED_HIGH		3

//@GPIO_PIN_PULLUP_PULLDOWN
//GPIO pin Pull Up and Pull Down macros
#define GPIO_NO_PUPD		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2

//@GPIO PIN NUMBER
//GPIO pin number macros
#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15

//

/**************************************************************************************************************
							APIs Supported by This Driver
**************************************************************************************************************/

//Clock Control
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

//Initialization and De-initialization

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

//Data Read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteoOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

//IRQ Configuration and ISR handling
void GPIO_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);



#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
