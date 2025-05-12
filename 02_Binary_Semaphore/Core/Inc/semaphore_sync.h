#ifndef __SEMAPHORE_SYNC_H
#define __SEMAPHORE_SYNC_H

#include "main.h"
#include "cmsis_os.h"

void StartTask1(void *argument);
void StartTask2(void *argument);
void SemaphoreProtectionInit(void);

#endif
