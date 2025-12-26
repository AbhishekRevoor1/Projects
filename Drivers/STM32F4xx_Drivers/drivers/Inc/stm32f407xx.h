/*
 * stm32f407xx.h
 *
 *  Created on: Nov 7, 2025
 *      Author: abhishek-revoor
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>
#define __vo volatile

//***************************** Processor specific details****************************************/
//ARMCortex M4 Processor NVIC ISERx Register Addresses
#define NVIC_ISER0 					((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1 					((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2 					((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3 					((__vo uint32_t*)0xE000E10C)

//ARMCortex M4 Processor NVIC ICERx Register Addresses
#define NVIC_ICER0 					((__vo uint32_t*)0XE000E180)
#define NVIC_ICER1 					((__vo uint32_t*)0XE000E184)
#define NVIC_ICER2 					((__vo uint32_t*)0XE000E188)
#define NVIC_ICER3 					((__vo uint32_t*)0XE000E18C)

//Memory Base addresses
#define FLASH_BASEADDR				0x08000000U						//Base Address of Flash/code memory (1024KB)
#define SRAM1_BASEADDR				0x20000000U						//Base Address of SRAM1/Data memory (112KB)
#define SRAM2_BASEADDR				(SRAM1_BASEADDR + 0x00001C00U)	//Base Address of SRAM2Data memory  (16KB)
#define ROM_BASEADDR				0x1FFF0000U						//Base Address of ROM memory		(30KB)
#define SRAM						SRAM1_BASEADDR


//Peripheral BUS base addresses
#define PERIPH_BASEADDR				0x40000000U						//Peripheral's Base Address
#define	APB1PERIPH_BASEADDR			PERIPH_BASE						//APB1 Peripheral's Base Address
#define	APB2PERIPH_BASEADDR			0x40010000U						//APB2 Peripheral's Base Address
#define	AHB1PERIPH_BASEADDR			0x40020000U						//AHB1 Peripheral's Base Address
#define	AHB2PERIPH_BASEADDR			0x50000000U						//AHB2 Peripheral's Base Address

//RCC base address
#define RCC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x3800U) //RCC REGISTER BASE ADDRESS

//Interrupt priority base address macros
#define NVIC_PR_BASE_ADDR			((__vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED		4

//Base address of the peripherals used in this project which are hanging on AHB1 BUS
#define GPIOA_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0000U) //GPIO_A REGISTER BASE ADDRESS
#define GPIOB_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0400U)	//GPIO_B REGISTER BASE ADDRESS
#define GPIOC_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0800U)	//GPIO_C REGISTER BASE ADDRESS
#define GPIOD_BASEADDR				(AHB1PERIPH_BASEADDR + 0x0C00U)	//GPIO_D REGISTER BASE ADDRESS
#define GPIOE_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1000U)	//GPIO_E REGISTER BASE ADDRESS
#define GPIOF_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1400U)	//GPIO_F REGISTER BASE ADDRESS
#define GPIOG_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1800U)	//GPIO_G REGISTER BASE ADDRESS
#define GPIOH_BASEADDR				(AHB1PERIPH_BASEADDR + 0x1C00U)	//GPIO_H REGISTER BASE ADDRESS
#define GPIOI_BASEADDR				(AHB1PERIPH_BASEADDR + 0x2000U)	//GPIO_I REGISTER BASE ADDRESS

//Base address of the peripherals used in this project which are hanging on APB1 BUS
#define I2C1_BASEADDR				(APB1PERIPH_BASEADDR + 0x5400U)	//I2C1 REGISTER BASE ADDRESS
#define I2C2_BASEADDR				(APB1PERIPH_BASEADDR + 0x5800U)	//I2C2 REGISTER BASE ADDRESS
#define I2C3_BASEADDR				(APB1PERIPH_BASEADDR + 0x5C00U)	//I2C3 REGISTER BASE ADDRESS
#define SPI2_BASEADDR				(APB1PERIPH_BASEADDR + 0x3800U)	//SPI2 REGISTER BASE ADDRESS
#define SPI3_BASEADDR				(APB1PERIPH_BASEADDR + 0x3C00U)	//SPI3 REGISTER BASE ADDRESS
#define USART2_BASEADDR				(APB1PERIPH_BASEADDR + 0x4400U)	//USART2 REGISTER BASE ADDRESS
#define USART3_BASEADDR				(APB1PERIPH_BASEADDR + 0x4800U)	//USART3 REGISTER BASE ADDRESS
#define UART4_BASEADDR				(APB1PERIPH_BASEADDR + 0x4C00U)	//UART4 REGISTER BASE ADDRESS
#define UART5_BASEADDR				(APB1PERIPH_BASEADDR + 0x5000U)	//UART5 REGISTER BASE ADDRESS

//Base address of the peripherals used in this project which are hanging on APB2 BUS
#define SPI1_BASEADDR				(APB2PERIPH_BASEADDR + 0x3000U)	//SPI1 REGISTER BASE ADDRESS
#define USART1_BASEADDR				(APB2PERIPH_BASEADDR + 0x1000U)	//USART1 REGISTER BASE ADDRESS
#define USART6_BASEADDR				(APB2PERIPH_BASEADDR + 0x1400U)	//USART6 REGISTER BASE ADDRESS
#define EXTI_BASEADDR				(APB2PERIPH_BASEADDR + 0x3C00U)	//EXTI REGISTER BASE ADDRESS
#define SYSCFG_BASEADDR				(APB2PERIPH_BASEADDR + 0x3800U)	//SYSCFG REGISTER BASE ADDRESS



/*****************************************Peripheral Register structure Definitions***************************************************/

//GPIO peripheral Structure

typedef struct
{
	__vo uint32_t MODER;											//GPIO port mode register
	__vo uint32_t OTYPER;											//GPIO port output type register
	__vo uint32_t OSPEEDR;											//GPIO port output speed register
	__vo uint32_t PUPDR;											//GPIO port pull-up/pull-down register
	__vo uint32_t IDR;												//GPIO port input data register
	__vo uint32_t ODR;												//GPIO port output data register
	__vo uint32_t BSRR;												//GPIO port bit set/reset register
	__vo uint32_t LCKR;												//GPIO port configuration lock register
	__vo uint32_t AFR[2];											//AFR[0] : GPIO alternate function low Register ; AFR[1] GPIO alternate function high Register
}GPIO_RegDef_t;

/*******************************************************************************************************************************/
//peripheral Definitions(peripheral base address type-casted to peripheral structure)

#define GPIOA						((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB						((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC						((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD						((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE						((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF						((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG						((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH						((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI						((GPIO_RegDef_t*)GPIOI_BASEADDR)

/********************************************** PROVIDING CLCOK TO THE PERIPHERALS USING RCC ******************************************/
//RCC PERIPHERAL STRUCTURE
typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTRCR;
	__vo uint32_t RESERVED0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t RESERVED1[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	__vo uint32_t RESERVED2;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t RESERVED3[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	__vo uint32_t RESERVED4;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	__vo uint32_t RESERVED5[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t RESERVED6[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
}RCC_RegDef_t;

#define RCC 							((RCC_RegDef_t*)RCC_BASEADDR)


//EXTI peripheral register structure definition
typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t RTSR;
	__vo uint32_t FTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;

// EXTI macros

#define EXTI							((EXTI_RegDef_t*)EXTI_BASEADDR)

#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40

#define NVIC_IRQ_PRI0		0
#define NVIC_IRQ_PRI15		15


//Peripheral registr defination structure for SYSCFG
typedef struct
{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	__vo uint32_t CMPCR;
}SYSCFG_RefDef_t;

#define SYSCFG							((SYSCFG_RefDef_t*)SYSCFG_BASEADDR)

//SYSCFG macros

#define GPIO_BASEADDR_TO_CODE(x)		( (x == GPIOA)?0:\
										  (x == GPIOB)?1:\
										  (x == GPIOC)?3:\
										  (x == GPIOD)?4:\
										  (x == GPIOE)?5:\
										  (x == GPIOF)?6:\
										  (x == GPIOG)?7:\
										  (x == GPIOH)?8:\
										  (x == GPIOI)?9:0 )

/************************************Clock Enable macros for GPIO's*****************************************/

#define GPIOA_PCLK_EN()					(RCC -> AHB1ENR |= (1<<0))		//GPIO_A CLOCK ENABLE
#define GPIOB_PCLK_EN()					(RCC -> AHB1ENR |= (1<<1))		//GPIO_B CLOCK ENABLE
#define GPIOC_PCLK_EN()					(RCC -> AHB1ENR |= (1<<2))		//GPIO_C CLOCK ENABLE
#define GPIOD_PCLK_EN()					(RCC -> AHB1ENR |= (1<<3))		//GPIO_D CLOCK ENABLE
#define GPIOE_PCLK_EN()					(RCC -> AHB1ENR |= (1<<4))		//GPIO_E CLOCK ENABLE
#define GPIOF_PCLK_EN()					(RCC -> AHB1ENR |= (1<<5))		//GPIO_F CLOCK ENABLE
#define GPIOG_PCLK_EN()					(RCC -> AHB1ENR |= (1<<6))		//GPIO_G CLOCK ENABLE
#define GPIOH_PCLK_EN()					(RCC -> AHB1ENR |= (1<<7))		//GPIO_H CLOCK ENABLE
#define GPIOI_PCLK_EN()					(RCC -> AHB1ENR |= (1<<8))		//GPIO_I CLOCK ENABLE

/************************************Clock Enable macros for APB1 BUS peripherals*****************************************/

#define I2C1_CLK_EN()					(RCC -> APB1ENR |= (1<<21))		//I2C1 Clock Enable
#define I2C2_CLK_EN()					(RCC -> APB1ENR |= (1<<22))		//I2C2 Clock Enable
#define I2C3_CLK_EN()					(RCC -> APB1ENR |= (1<<23))		//I2C3 Clock Enable
#define SPI2_CLK_EN()					(RCC -> APB1ENR |= (1<<14))		//SPI2 Clock Enable
#define SPI3_CLK_EN()					(RCC -> APB1ENR |= (1<<15))		//SPI3 Clock Enable
#define USART2_CLK_EN()					(RCC -> APB1ENR |= (1<<17))		//USART2 Clock Enable
#define USART3_CLK_EN()					(RCC -> APB1ENR |= (1<<18))		//USART3 Clock Enable
#define UART4_CLK_EN()					(RCC -> APB1ENR |= (1<<19))		//UART4
#define UART5_CLK_EN()					(RCC -> APB1ENR |= (1<<20))		//UART5 Clock Enable


/************************************Clock Enable macros for APB2 BUS peripherals*****************************************/

#define SPI1_CLK_EN()					(RCC -> APB2ENR |= (1<<12))		//SPI1 Clock Enable
#define USART1_CLK_EN()					(RCC -> APB2ENR |= (1<<4))		//USART1 Clock Enable
#define USART6_CLK_EN()					(RCC -> APB2ENR |= (1<<5))		//USART6 Clock Enable
//#define EXTI_CLK_EN()					(RCC -> APB2ENR |= (1<<21))		//EXTI Clock Enable
#define SYSCFG_CLK_EN()					(RCC -> APB2ENR |= (1<<14))		//SYSCFG Clock Enable

/***************************************************************************************************************************/
/***************************************************************************************************************************/

/************************************Clock Disable macros for GPIO's*****************************************/

#define GPIOA_PCLK_DI()					(RCC -> AHB1ENR &= ~(1<<0))		//GPIO_A CLOCK ENABLE
#define GPIOB_PCLK_DI()					(RCC -> AHB1ENR &= ~(1<<1))		//GPIO_B CLOCK ENABLE
#define GPIOC_PCLK_DI()					(RCC -> AHB1ENR &= ~(1<<2))		//GPIO_C CLOCK ENABLE
#define GPIOD_PCLK_DI()					(RCC -> AHB1ENR &= ~(1<<3))		//GPIO_D CLOCK ENABLE
#define GPIOE_PCLK_DI()					(RCC -> AHB1ENR &= ~(1<<4))		//GPIO_E CLOCK ENABLE
#define GPIOF_PCLK_DI()					(RCC -> AHB1ENR &= ~(1<<5))		//GPIO_F CLOCK ENABLE
#define GPIOG_PCLK_DI()					(RCC -> AHB1ENR &= ~(1<<6))		//GPIO_G CLOCK ENABLE
#define GPIOH_PCLK_DI()					(RCC -> AHB1ENR &= ~(1<<7))		//GPIO_H CLOCK ENABLE
#define GPIOI_PCLK_DI()					(RCC -> AHB1ENR &= ~(1<<8))		//GPIO_I CLOCK ENABLE

/************************************Clock Disable macros for APB1 BUS peripherals*****************************************/

#define I2C1_CLK_DI()					(RCC -> APB1ENR &= ~(1<<21))		//I2C1 Clock Enable
#define I2C2_CLK_DI()					(RCC -> APB1ENR &= ~(1<<22))		//I2C2 Clock Enable
#define I2C3_CLK_DI()					(RCC -> APB1ENR &= ~(1<<23))		//I2C3 Clock Enable
#define SPI2_CLK_DI()					(RCC -> APB1ENR &= ~(1<<14))		//SPI2 Clock Enable
#define SPI3_CLK_DI()					(RCC -> APB1ENR &= ~(1<<15))		//SPI3 Clock Enable
#define USART2_CLK_DI()					(RCC -> APB1ENR &= ~(1<<17))		//USART2 Clock Enable
#define USART3_CLK_DI()					(RCC -> APB1ENR &= ~(1<<18))		//USART3 Clock Enable
#define UART4_CLK_DI()					(RCC -> APB1ENR &= ~(1<<19))		//UART4
#define UART5_CLK_DI()					(RCC -> APB1ENR &= ~(1<<20))		//UART5 Clock Enable


/************************************Clock Disable macros for APB2 BUS peripherals*****************************************/

#define SPI1_CLK_DI()					(RCC -> APB2ENR &= ~(1<<12))		//SPI1 Clock Enable
#define USART1_CLK_DI()					(RCC -> APB2ENR &= ~(1<<4))		//USART1 Clock Enable
#define USART6_CLK_DI()					(RCC -> APB2ENR &= ~(1<<5))		//USART6 Clock Enable
//#define EXTI_CLK_DI()					(RCC -> APB2ENR &= ~(1<<21))		//EXTI Clock Enable
#define SYSCFG_CLK_DI()					(RCC -> APB2ENR &= ~(1<<14))		//SYSCFG Clock Enable



/****************************************RESET REGISTERS*******************************************/
#define GPIOA_REG_RESET()					do { (RCC -> AHB1RSTR |= (1 << 0));		(RCC -> AHB1RSTR &= ~(1 << 0)); } while(0)
#define GPIOB_REG_RESET()					do { (RCC -> AHB1RSTR |= (1 << 1));		(RCC -> AHB1RSTR &= ~(1 << 1)); } while(0)
#define GPIOC_REG_RESET()					do { (RCC -> AHB1RSTR |= (1 << 2));		(RCC -> AHB1RSTR &= ~(1 << 2)); } while(0)
#define GPIOD_REG_RESET()					do { (RCC -> AHB1RSTR |= (1 << 3));		(RCC -> AHB1RSTR &= ~(1 << 3)); } while(0)
#define GPIOE_REG_RESET()					do { (RCC -> AHB1RSTR |= (1 << 4));		(RCC -> AHB1RSTR &= ~(1 << 4)); } while(0)
#define GPIOF_REG_RESET()					do { (RCC -> AHB1RSTR |= (1 << 5));		(RCC -> AHB1RSTR &= ~(1 << 5)); } while(0)
#define GPIOG_REG_RESET()					do { (RCC -> AHB1RSTR |= (1 << 6));		(RCC -> AHB1RSTR &= ~(1 << 6)); } while(0)
#define GPIOH_REG_RESET()					do { (RCC -> AHB1RSTR |= (1 << 7));		(RCC -> AHB1RSTR &= ~(1 << 7)); } while(0)
#define GPIOI_REG_RESET()					do { (RCC -> AHB1RSTR |= (1 << 8));		(RCC -> AHB1RSTR &= ~(1 << 8)); } while(0)



//***************************************Handy Macros******************************************/
#define ENABLE				1
#define DISABLE				0
#define SET					ENABLE
#define RESET				DISABLE
#define GPIO_PIN_SET		SET
#define GPIO_PIN_RESET		RESET


#include "stm32f407xx_gpio_driver.h"


#endif /* INC_STM32F407XX_H_ */
