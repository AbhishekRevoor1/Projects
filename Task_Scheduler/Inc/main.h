/*
 * main.h
 *
 *  Created on: Sep 23, 2025
 *      Author: abhishek-revoor
 */

#ifndef MAIN_H_
#define MAIN_H_

#define STACK_SIZE          1024U
#define SCHEDULER_SIZE      1024U

#define SRAM_START          0x20000000U
#define SRAM_SIZE			((128) * (1024))
#define SRAM_END			((SRAM_START) + (SRAM_SIZE))

#define T1_STACK_START			SRAM_END
#define T2_STACK_START			((SRAM_END) - (1 * STACK_SIZE))
#define T3_STACK_START			((SRAM_END) - (2 * STACK_SIZE))
#define T4_STACK_START			((SRAM_END) - (3 * STACK_SIZE))
#define SCHEDULER_STACK_START	((SRAM_END) - (4 * SCHEDULER_SIZE))

#define TICK_HZ 				1000U
#define HSI_CLOCK 				16000000U
#define SYSTICK_TIM_CLK 		HSI_CLOCK

#define MAX_TASKS				4
#define DUMMY_XPSR				0x00100000U

#endif /* MAIN_H_ */
