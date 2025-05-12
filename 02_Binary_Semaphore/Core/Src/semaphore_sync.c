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

void StartTask1(void *argument)
{
    while (1)
    {
        // Read state of PD12 (no need for semaphore here, reading is safe)
        GPIO_PinState state = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, state);

        // Acquire semaphore for shared PD14 toggle
        if (osSemaphoreAcquire(gpioSemaphore, osWaitForever) == osOK)
        {
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
            osSemaphoreRelease(gpioSemaphore);
        }

        osDelay(500);
    }
}

void StartTask2(void *argument)
{
    while (1)
    {
        // Read state of PD12 (no need for semaphore here, reading is safe)
        GPIO_PinState state = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, state);

        // Acquire semaphore for shared PD14 toggle
        if (osSemaphoreAcquire(gpioSemaphore, osWaitForever) == osOK)
        {
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
            osSemaphoreRelease(gpioSemaphore);
        }

        osDelay(5000);
    }
}

void SemaphoreProtectionInit(void)
{
    // Create a binary semaphore to protect the shared GPIO
    gpioSemaphore = osSemaphoreNew(1, 1, &gpioSemaphoreAttributes);
    if (gpioSemaphore == NULL)
    {
        Error_Handler();
    }

    // Create the tasks
    osThreadNew(StartTask1, NULL, NULL);
    osThreadNew(StartTask2, NULL, NULL);
}
