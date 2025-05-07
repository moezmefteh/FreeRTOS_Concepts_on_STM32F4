#include "semaphore_sync.h"

osSemaphoreId_t gpioSemaphore;
const osSemaphoreAttr_t gpioSemaphoreAttributes = {
    .name = "gpioSemaphore"
};

void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void LED_Toggle_Task(void *argument)
{
    while (1)
    {
        if (osSemaphoreAcquire(gpioSemaphore, osWaitForever) == osOK)
        {
            // Toggle LED on PD12
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
            osDelay(500); // Simulate some processing time
        }
    }
}

void GPIO_Read_Task(void *argument)
{
    while (1)
    {
        // Read the current state of PD12 and reflect it on PD13
        GPIO_PinState state = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, state);

        // Now release the semaphore to allow the toggle task to proceed
        osSemaphoreRelease(gpioSemaphore);

        osDelay(100);  // Add a small delay to avoid CPU hogging
    }
}

void SemaphoreProtectionInit(void)
{
    gpioSemaphore = osSemaphoreNew(1, 1, &gpioSemaphoreAttributes);
    if (gpioSemaphore == NULL)
    {
        Error_Handler();
    }

    // Create the tasks
    osThreadNew(LED_Toggle_Task, NULL, NULL);
    osThreadNew(GPIO_Read_Task, NULL, NULL);
}
