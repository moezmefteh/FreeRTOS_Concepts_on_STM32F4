#include <mutex_sync.h>

osMutexId_t dataMutex;
const osMutexAttr_t dataMutexAttributes = {
    .name = "dataMutex"
};

volatile int sharedCounter = 0;

void WriterTask(void *argument) {
    while (1) {
        if (osMutexAcquire(dataMutex, osWaitForever) == osOK) {
            sharedCounter++;
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
            osMutexRelease(dataMutex);
        }
        osDelay(1000);
    }
}

void ReaderTask(void *argument) {
    while (1) {
        if (osMutexAcquire(dataMutex, osWaitForever) == osOK) {
            int temp = sharedCounter;
            if (temp % 2 == 0) {
                HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
            }
            osMutexRelease(dataMutex);
        }
        osDelay(500);
    }
}

void MutexExampleInit(void) {
    dataMutex = osMutexNew(&dataMutexAttributes);
    if (dataMutex == NULL) {
        Error_Handler();
    }
    osThreadNew(WriterTask, NULL, NULL);
    osThreadNew(ReaderTask, NULL, NULL);
}
/*
int counter = 0;
osMutexId_t counterMutex;
const osMutexAttr_t counterMutexAttributes = {
    .name = "counterMutex"
};

void Increment_Task(void *argument)
{
    while (1)
    {
        if (osMutexAcquire(counterMutex, osWaitForever) == osOK)
        {
            counter++;
            osMutexRelease(counterMutex);
            osDelay(500);
        }
    }
}

void Decrement_Task(void *argument)
{
    while (1)
    {
        if (osMutexAcquire(counterMutex, osWaitForever) == osOK)
        {
            counter--;
            osMutexRelease(counterMutex);
            osDelay(500);
        }
    }
}

void Read_Task(void *argument)
{
    while (1)
    {
        if (osMutexAcquire(counterMutex, osWaitForever) == osOK)
        {
            printf("Counter value: %d\n", counter);
            osMutexRelease(counterMutex);
            osDelay(1000);
        }
    }
}

void MutexExampleInit(void)
{
    counterMutex = osMutexNew(&counterMutexAttributes);
    if (counterMutex == NULL)
    {
        Error_Handler();
    }

    osThreadNew(Increment_Task, NULL, NULL);
    osThreadNew(Decrement_Task, NULL, NULL);
    osThreadNew(Read_Task, NULL, NULL);
}
*/

void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
