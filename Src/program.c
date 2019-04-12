/*
 * program.c
 *
 *  Created on: 11. apr 2019
 *      Author: JRE
 */


/* Lets write program here, where the cubeMX will not disturb us. */

#include "program.h"
#include "main.h"
#include "stdio.h"
#include "display_drv.h"

/************** Private function forward declarations ***************/
int _write(int file, char *ptr, int len);


/************ Public function declarations ************/

Public void program_init(void)
{
	//Initialize all program here.

	disp_init();
}

//This is called from while loop in main.
Public void mainLoop(void)
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	//_write(0u, "Hello!", 6u);
	//printf("Hello World!\r\n");
	HAL_Delay(1000u);
}

//Lets call this every 10ms.
Public void timer_callback_10ms(void)
{
#if 0
	static uint8_t cnt = 0u;
	if(++cnt > 100u)
	{
		cnt = 0u;
		printf("Timer! - Now 100Hz\r\n");
	}
#endif
	disp_scan();
}

/*************** Private function declarations *****************/
int _write(int file, char *ptr, int len)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, 0xffu);
	return len;
}
