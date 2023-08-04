# My Own Round Robin Priority-based Real-Time Operating System (RTOS)

## Introduction
I have developed my own Real-Time Operating System (RTOS) from scratch, designed to work with various processors/MCUs. This RTOS is based on the Round Robin scheduling algorithm with priority support and includes a subsystem for Mutex handling to prevent priority inversion.

## Project Structure
The project is organized into the following directories:

### inc
- **MRTOS_Porting.h**: This header file is used to port the RTOS to different processors/MCUs. It contains necessary definitions and configurations specific to the target platform.
- **MRTOS_Scheduler.h**: This header file includes function prototypes for tasks and supported APIs in the RTOS.
- **Queue Files**: This directory contains the necessary files for implementing the Queue data structure, which is used by the RTOS.

### src
- **MRTOS_Porting.c**: This source file contains the definitions for all processor faults as weak functions, which can be overridden when porting to different platforms.
- **MRTOS_Scheduler.c**: This source file defines the APIs of the RTOS. It's important not to edit anything in this file to maintain the integrity of the RTOS.
- **Queue Files**: This directory contains the necessary files for implementing the Queue data structure, which is used by the RTOS.

### Essential_MCAL_Libs
This directory includes essential Microcontroller Abstraction Layer (MCAL) libraries required for proper functioning of the RTOS with specific hardware.

## Context-Switching
The RTOS is designed to work efficiently with ARM Cortex-M3/4 architecture, which supports pre-emptive multitasking. Context switching between tasks is implemented using the MSP (Main Stack Pointer) and PSP (Process Stack Pointer). The MSP is used for handling interrupts, while the PSP is used during regular task execution.

The context switcher performs the following steps:
1. Save the context of the current task.
2. Update the current task with the next task to be executed.
3. Load the context of the task which is about to execute.

## Implementing Mutex & Priority Inversion Handling
The RTOS supports Mutex handling to prevent resource conflicts among tasks. It also addresses priority inversion by allowing higher-priority tasks to execute when waiting for resources held by lower-priority tasks.

To demonstrate this, the RTOS includes four tasks with the same priorities. Initially, the idle task will run. When Task1 is activated, the RTOS will execute it. Task1 will request Mutex one and then try to activate Task2, which triggers the SVC_Handler for context switching.

As Task2 has a higher priority than Task1, Task2 will execute next. Task2 will then request activation of Task3, which will request activation of Task4. After a short period, Task4 will ask for Mutex one, which is currently held by Task1. This situation represents priority inversion, and Task4 will wait until Task1 releases Mutex one.

Upon releasing Mutex one, Task4 will execute until its termination.

## Important Note
Please be cautious when editing the source files of the RTOS, especially MRTOS_Scheduler.c, as any unintended modifications may compromise the stability and functionality of the RTOS.


