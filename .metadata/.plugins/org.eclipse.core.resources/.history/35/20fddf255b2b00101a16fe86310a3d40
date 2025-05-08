#ifndef UART_COMM_H
#define UART_COMM_H

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

void UART2_IRQHandler(void);
void UART_Transmit(uint8_t data);

void LED_Task(void *argument);
void UART_Receive_ISR(void);
void USART_Example();

#endif // UART_COMM_H
