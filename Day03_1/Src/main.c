

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "led.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


int main(void)
{
	SystemInit();
	DelayMs(1);
	LedInit(LED_GREEN);
	LedInit(LED_ORANGE);
	LedInit(LED_RED);
	LedInit(LED_BLUE);
	while(1) {
		LedBlink(LED_GREEN, 200);
		LedBlink(LED_ORANGE, 200);
		LedBlink(LED_RED, 200);
		LedBlink(LED_BLUE, 200);

		DelayMs(1000);
		LedBlink(LED_BLUE, 200);
		LedBlink(LED_RED, 200);
		LedBlink(LED_ORANGE, 200);
		LedBlink(LED_GREEN, 200);
			}

	return 0;
}
