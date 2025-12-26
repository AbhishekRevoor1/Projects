/*
 * stm32f407xx_gpio_deriver.c
 *
 *  Created on: Nov 8, 2025
 *      Author: abhishek-revoor
 */
#include "stm32f407xx_gpio_driver.h"



/*********************************************************************
 * @fn      		  - GPIO_PeriClockControl
 *
 * @brief             - This function helps to to Enable or disable the Clock to the particular GPIO Port
 *
 * @param[in]         - Base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE macos to enable or disable the clock
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none

 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		} else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		} else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		} else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		} else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		} else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		} else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		} else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		} else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		} else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		} else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		} else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		} else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		} else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		} else if(pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DI();
		} else if(pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		} else if(pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DI();
		}
	}
}

/*********************************************************************
 * @fn      		  - GPIO_Init
 *
 * @brief             - This function helps to to initialize the registers of particular GPIO Port
 *
 * @param[in]         - Uses a structure to configure the registers
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none

 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp = 0;
	//1. Configure the mode of the GPIO pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <<(2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);    //Clear Bits
		pGPIOHandle->pGPIOx->MODER |= temp;		//Set bits
	}
	else
	{
		//GPIO PIN Interrupt Mode Configuration
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//1. Configure the FTSR
			EXTI -> FTSR |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//2. Clear the corresponding RTSR bit
			EXTI -> RTSR &= ~(1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//1. Configure the RTSR
			EXTI -> RTSR |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//2. Clear the corresponding FTSR bit
			EXTI -> FTSR &= ~(1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//1. Configure the FTSR and RTSR
			EXTI -> FTSR |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI -> RTSR |= (1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		//2. Configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_CLK_EN();
		SYSCFG ->EXTICR[temp1] = portcode << (temp2 * 4);

		//3. Enable the EXTI interrupt delivery using IMR
		EXTI -> IMR |=(1<<pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	//2. Configure the speed of the pin
	temp = 0;
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed <<(2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	//3. Configure the PULL UP or PULL DOWN mode of the pin
	temp = 0;
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl <<(2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	//4. Configure the Output type of the pin(PUSH PULL or OPEN DRAIN)
	temp = 0;
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	//5. Configure the Alternate functionality mode of the the pin
	temp = 0;
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		uint8_t temp1, temp2;
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF <<  (temp2 * 4));
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (temp2 * 4));
	}

}

/*********************************************************************
 * @fn      		  - GPIO_DeInit
 *
 * @brief             - This function helps to de-intialize the register's of the particular GPIO Port
 *
 * @param[in]         - Base address of the gpio peripheral
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none

 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	} else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	} else if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	} else if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	} else if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	} else if(pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	} else if(pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	} else if(pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	} else if(pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();
	}
}

/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPin
 *
 * @brief             - This function helps to read data from a pin of the particular GPIO Port
 *
 * @param[in]         - Base address of the gpio peripheral
 * @param[in]         - pin number of the port
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none

 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)(pGPIOx->IDR >> PinNumber) & 0x00000001;
	return value;
}

/*********************************************************************
 * @fn      		  - GPIO_ReadFromInputPort
 *
 * @brief             - This function helps to read data from the particular GPIO Port
 *
 * @param[in]         - Base address of the gpio peripheral
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - uint8_t
 *
 * @Note              - none

 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;
}

/*********************************************************************
 * @fn      		  - GPIO_WriteToOutputPin
 *
 * @brief             - This function helps to write data to a particular pin of the particular GPIO Port
 *
 * @param[in]         - Base address of the gpio peripheral
 * @param[in]         - pin number of the gpio port
 * @param[in]         -	value needs to be written
 *
 * @return            - uint16_t
 *
 * @Note              - none

 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1<<PinNumber);
	}else
	{
		pGPIOx->ODR &= ~(1<<PinNumber);
	}
}

/*********************************************************************
 * @fn      		  - GPIO_WriteoOutputPort
 *
 * @brief             - This function helps to write data to the particular GPIO Port
 *
 * @param[in]         - Base address of the gpio peripheral
 * @param[in]         - 16 bit value to be wriiten
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none

 */
void GPIO_WriteoOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}

/*********************************************************************
 * @fn      		  - GPIO_ToggleOutputPin
 *
 * @brief             - This function helps to toggle the output pin of the particular GPIO Port
 *
 * @param[in]         - Base address of the gpio peripheral
 * @param[in]         - pin number
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none

 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^= (1<<PinNumber);
}

/*********************************************************************
 * @fn      		  - GPIO_IRQITConfig
 *
 * @brief             - This function helps to configure the interrupt to a particular pin the particular GPIO Port
 *
 * @param[in]         - Interrupt Number
 * @param[in]         - Interrupt Priority
 * @param[in]         - Enable or Disable Maco
 *
 * @return            - none
 *
 * @Note              - none

 */
void GPIO_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <=31)
		{
			//Set ISER0 Register
			*NVIC_ISER0 |= (1<<IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64)
		{
			//Set ISER1 Register
			*NVIC_ISER1 |= (1<<(IRQNumber%32));
		}else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			//Set ISER Register
			*NVIC_ISER2 |= (1<<(IRQNumber%64));
		}
	}else
	{
		if(IRQNumber <=31)
		{
			//Set ICER0 Register
			*NVIC_ICER0 |= (1<<IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64)
		{
			//Set ICER0 Register
			*NVIC_ICER1 |= (1<<(IRQNumber%32));
		}else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			//Set ICER0 Register
			*NVIC_ICER0 |= (1<<(IRQNumber%64));
		}
	}
}

/*********************************************************************
 * @fn      		  - GPIO_IRQPriorityConfig
 *
 * @brief             - This function helps to Interrupt priority of a pin of the particular GPIO Port
 *
 * @param[in]         - IRQ Number
 * @param[in]         - IRQ Priority
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none

 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	//1. Calculate the required the IPR Register.
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + (iprx)) |= ( IRQPriority << shift_amount);
}
/*********************************************************************
 * @fn      		  - GPIO_IRQConfig
 *
 * @brief             - This function helps to handle the interrupt generated by a pin of the particular GPIO Port
 *
 * @param[in]         - Pin number
 * @param[in]         -
 * @param[in]         -
 *
 * @return            - none
 *
 * @Note              - none

 */
void GPIO_IRQHandling(uint8_t PinNumber)
{
	//clear the EXTI PR register corresponding to the pin number
	if(EXTI->PR & (1 << PinNumber))
	{
		EXTI->PR |= (1<< PinNumber);
	}
}
