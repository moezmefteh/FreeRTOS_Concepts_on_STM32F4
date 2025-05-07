/*
 * tasks.c
 *
 *  Created on: May 6, 2025
 *      Author: moez.meftah@celadodc-rswl.com
 */

#include "main.h"
#include "cmsis_os.h"

void start_task_led1(void *arg){
	for(;;){
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		osDelay(500);
	}
}

void start_task_led2(void *arg){
	for(;;){
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		osDelay(300);
	}
}
