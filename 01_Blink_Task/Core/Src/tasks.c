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

/* Definitions for tsk_led1 */
osThreadId_t tsk_led1Handle;
const osThreadAttr_t tsk_led1_attributes = {
  .name = "tsk_led1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for tsk_led2 */
osThreadId_t tsk_led2Handle;
const osThreadAttr_t tsk_led2_attributes = {
  .name = "tsk_led2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

void Blink_example(void){
	  /* creation of tsk_led1 */
	  tsk_led1Handle = osThreadNew(start_task_led1, NULL, &tsk_led1_attributes);

	  /* creation of tsk_led2 */
	  tsk_led2Handle = osThreadNew(start_task_led2, NULL, &tsk_led2_attributes);
}
