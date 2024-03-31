#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "led.h"
#include "lcd.h"
#include "switch.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	SystemInit();
	LedInit(LED_ORANGE);
	SwitchInit(SWITCH);
	int count = 0;
	char strchar[20];

	while(1) {

		while(exti0_flag == 0)
			;
		LedBlink(LED_ORANGE, 500);

		LcdInit();
		count++;
		sprintf(strchar, "Count  = %d", count);
		//LcdPuts(LCD_LINE1 , "DESD - E3");
		LcdPuts(LCD_LINE2 , strchar);
		exti0_flag = 0;
	}
	return 0;
}








