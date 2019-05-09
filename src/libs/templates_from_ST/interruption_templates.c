/*
 * interruption_templates.c
 *
 *  Created on: 2019. m�rc. 12.
 *      Author: Lilla
 */

#include "interruption_templates.h"

/* we don't need to explicitly call the HAL_NVIC_SetPriorityGrouping function,
	 * because the grouping defaults to NVIC_PRIORITYGROUP_2:
	 * HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
	 */

uint32_t last_debounce_time = 0;		 // the last time the output pin was toggled
const uint32_t debounce_delay = 150; // the debounce time in ms (increase if the output flickers)
volatile int push_counter = 0;

void init_timer(void)
{
	//initialize TIM2
	__HAL_RCC_TIM2_CLK_ENABLE();			//giving clock
	HAL_TIM_Base_DeInit(&tim_handle); // de-initialize the TIM_Base, because of safety reasons
	// configuration of the basic mode of the timer (which direction should it count, what is the maximum value, etc.)
	tim_handle.Instance = TIM2;						 //register base address
	tim_handle.Init.Prescaler = 10800 - 1; // 108000000 / 10800 = 10000 -> speed of 1 count-up: 1 /10000 s = 0.1 ms
	tim_handle.Init.Period = 5000 - 1;		 // 5000 x 0.1 ms = 500 ms = 0.5 s period */
	tim_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	tim_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_TIM_Base_Init(&tim_handle);				 //configure the timer
	HAL_NVIC_SetPriority(TIM2_IRQn, 2, 0); //set TIM2 interrupt priority
	HAL_NVIC_EnableIRQ(TIM2_IRQn);				 //enable the interrupt to HAL
}

void init_PWM(void)
{
	//initialize TIM3 for PWM
	__HAL_RCC_TIM3_CLK_ENABLE();					//giving clock
	HAL_TIM_Base_DeInit(&pwm_tim_handle); // de-initialize the TIM_Base, because of safety reasons
	// configuration of the basic mode of the timer (which direction should it count, what is the maximum value, etc.)
	pwm_tim_handle.Instance = TIM3;						 //register base address
	pwm_tim_handle.Init.Prescaler = 10800 - 1; // 108000000 / 10800 = 10000 -> speed of 1 count-up: 1 /10000 s = 0.1 ms
	pwm_tim_handle.Init.Period = 5000 - 1;		 // 5000 x 0.1 ms = 500 ms = 0.5 s period */
	pwm_tim_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	pwm_tim_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_TIM_PWM_Init(&pwm_tim_handle); //configure the PWM timer
	sConfig.Pulse = 50;
	sConfig.OCMode = TIM_OCMODE_PWM1;
	sConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfig.OCFastMode = TIM_OCFAST_ENABLE;
	HAL_TIM_PWM_ConfigChannel(&pwm_tim_handle, &sConfig, TIM_CHANNEL_1);

	HAL_NVIC_SetPriority(TIM3_IRQn, 2, 0); //set TIM2 interrupt priority
	HAL_NVIC_EnableIRQ(TIM3_IRQn);				 //enable the interrupt to HAL
}
