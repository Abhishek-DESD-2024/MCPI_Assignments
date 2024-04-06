/*
 * switch.c
 *
 *  Created on: Mar 27, 2024
 *      Author: akash
 */
#include "switch.h"

void SwitchInit(uint32_t pin)
{
	RCC->AHB1ENR |= BV(SWITCH_GPIO_EN);

	SWITCH_GPIO->MODER &= ~(BV(pin * 2 +1)| BV(pin * 2));

	SWITCH_GPIO->OSPEEDR &= ~(BV(pin * 2 +1)| BV(pin * 2));

	SWITCH_GPIO->PUPDR &= ~(BV(pin * 2 +1)| BV(pin * 2));
	// ENABLE FALLING EDGE DETECTION (IN FTSR)  FALLING TRIGGER SELECTION REGISTER
	EXTI->FTSR |= BV(SWITCH);
	// ENABEL UNMASKE EXTI INTERRUPT (IN IMR) 	ITERRUPT MASK REGISTER
	EXTI->IMR |= BV(SWITCH);
	// SELECT EXIT INTERRUPT (SYSCFG->EXTICRx)
	SYSCFG->EXTICR[0] &= ~(BV(3) | BV(2) | BV(1) | BV(0));
	// ENABLE EXTI IN NVIC(NESTED VECTOR INTERRUPT CONTROLLER) (ISER (INTERRUPT SET ENABLE) OR NVIC_ENABLEIRQ())
	//NVIC->ISER[0] |= BV(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI0_IRQn);
}

int SwitchGetState(uint32_t pin)
{

	uint32_t state = SWITCH_GPIO->IDR;

	if(state & BV(pin))
		return 1;
	return 0;
}

// GLOBAL FLAG FOR INTERRUPT
int exti0_flag = 0;

void EXTI0_IRQHandler(void)
{// ACKNOLEDGE INTERRUPT (IN PENDING RESISTOR)
	// ACC TO MANNUAL
	EXTI->PR |= BV(SWITCH);
	// HANDLE INTERRUPT
	exti0_flag = 1;
}
