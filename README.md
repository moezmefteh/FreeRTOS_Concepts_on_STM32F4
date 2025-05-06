# FreeRTOS Concepts on STM32F4

This repository showcases various FreeRTOS concepts implemented on the STM32F4 series of microcontrollers. It serves as a comprehensive guide to understand the key features and principles of FreeRTOS, including task management, inter-task communication, and synchronization, using STM32CubeIDE as the development environment.

## Project Overview

The goal of this repository is to provide practical examples and demonstrations of FreeRTOS running on STM32F4 microcontrollers. Each example highlights a specific FreeRTOS feature and its usage in embedded systems, such as task creation, semaphores, queues, timers, and more.

### Key Concepts Covered:
- **Task Management**: Creating and managing tasks with different priorities.
- **Inter-task Communication**: Using queues and semaphores to communicate between tasks.
- **Synchronization**: Implementing mutexes and event groups.
- **Timers**: Using software timers for time-based operations.
- **System Monitoring**: Implementing FreeRTOS system statistics for debugging.

## Prerequisites

- **STM32F4 Development Board** (e.g., STM32F4 Discovery or Nucleo board)
- **STM32CubeIDE**: The project is developed using STM32CubeIDE, a comprehensive development environment provided by STMicroelectronics.
- **FreeRTOS**: This project uses the FreeRTOS kernel integrated into STM32CubeMX.
- **STM32CubeMX**: Used for generating initialization code for STM32 peripherals.

## Setup Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/moezmefteh/FreeRTOS_Concepts_on_STM32F4.git
cd FreeRTOS_Concepts_on_STM32F4
