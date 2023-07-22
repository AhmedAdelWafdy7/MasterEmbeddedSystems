# Lab: Stack Memory

In this lab, we explore the concept of stack memory and implement a simple multitasking system using function pointers and stack memory. The code provided demonstrates two tasks (Task A and Task B) that will be executed in a multitasking environment.

## Tasks and Stack Size

First, we define the stack size for each task:

```c
#define TASKA_Stack_Size 100 //100 Bytes
#define TASKB_Stack_Size 100 //100 Bytes
```

Next, we initialize the boundaries for the Main Stack Pointer (MSP) and the Process Stack Pointers (PSP) for both tasks:

```c
extern int _estack;

// Main Stack
unsigned int _S_MSP = &_estack;
unsigned int _E_MSP;

// Process Stack Task A Boundaries
unsigned int _S_PSP_TA; // Start of PSP for Task A
unsigned int _E_PSP_TA; // End of PSP for Task A

// Process Stack Task B Boundaries
unsigned int _S_PSP_TB; // Start of PSP for Task B
unsigned int _E_PSP_TB; // End of PSP for Task B
```

## Task Functions

We define two task functions: `TaskA` and `TaskB`. Each task takes different numbers of arguments and returns an integer result.

```c
int TaskA(int a, int b, int c) {
    return a + b + c;
}

int TaskB(int a, int b, int c, int d) {
    return a + b + c;
}
```

## Main OS Function

The `Main_OS` function initializes the stack boundaries and sets up the initial execution environment for the multitasking system.

```c
void Main_OS() {
    // Main Stack
    _E_MSP = (_S_MSP - 512);

    // Task B
    _S_PSP_TA = (_E_MSP - 8);
    _E_PSP_TA = (_S_PSP_TA - TASKA_Stack_Size);

    // Task A
    _S_PSP_TB = (_E_PSP_TA - 8);
    _E_PSP_TB = (_S_PSP_TB - TASKB_Stack_Size);

    // Task switching logic
    while (1) {
        __asm("nop");
        if (TaskA_flag == 1) {
            // Set PSP Register = _S_PSP_TA
            OS_SET_PSP(_S_PSP_TA);

            // SP -> PSP
            OS_SWITCH_SP_to_PSP;

            // Switch_CPU Access level from privileged to unprivileged
            Switch_CPU_Access_level(unprivileged);

            TaskA_flag = TaskA(1, 2, 3);

            // Switch_CPU Access level from unprivileged to privileged
            OS_Generate_Exception;

            // SP -> MSP
            OS_SWITCH_SP_to_MSP;

        } else if (TaskB_flag == 1) {
            // Set PSP Register = _S_PSP_TB
            OS_SET_PSP(_S_PSP_TB);

            // SP -> PSP
            OS_SWITCH_SP_to_PSP;

            // Switch_CPU Access level from privileged to unprivileged
            Switch_CPU_Access_level(unprivileged);

            TaskB_flag = TaskB(1, 2, 3, 4);

            // Switch_CPU Access level from unprivileged to privileged
            OS_Generate_Exception;

            // SP -> MSP
            OS_SWITCH_SP_to_MSP;
        }
    }
}
```

## Helper Functions

Several helper functions are used in the `Main_OS` function:

1. `OS_SET_PSP(add)`: Sets the Process Stack Pointer (PSP) to the given address.
2. `OS_SWITCH_SP_to_PSP`: Switches the Stack Pointer (SP) to the PSP.
3. `OS_Generate_Exception`: Generates a Supervisor Call (SVC) exception to switch CPU access level from unprivileged to privileged.
4. `OS_SWITCH_SP_to_MSP`: Switches the Stack Pointer (SP) back to the Main Stack Pointer (MSP).
5. `Switch_CPU_Access_level`: Switches CPU access level between privileged and unprivileged.

## Interrupt Handling

The multitasking system is triggered by two external interrupts. When the first interrupt occurs, Task A is executed. When the second interrupt occurs, Task B is executed.

```c
void IRQ_EXTI9_callback(void) {
    if (IRQ_flag == 0) {
        TaskA_flag = 1;
        IRQ_flag = 1;
    } else if (IRQ_flag == 1) {
        TaskB_flag = 1;
        IRQ_flag = 0;
    }
}
```

## Execution of Main OS

1. **Initial Configuration:**
   When the program runs, the Stack Pointer (SP) initially points to the Main Stack Pointer (MSP). The MSP is used for handling exceptions, interrupts, and privileged operations.
   ![MSP=SP](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/b9e517df-105e-4513-a0ed-4d22cd112f28)


3. **First IRQ (Interrupt Request):**
   When the first IRQ happens (e.g., a timer interrupt), the main OS will set the Process Stack Pointer (PSP) for the task that needs to be executed. PSP is specific to each task and used for handling task context switching.
![Set PSP](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/f1502849-b338-49d5-b816-2bca890f5895)

4. **Switch to PSP:**
   The main OS switches the SP to the PSP so that the task can now utilize its own dedicated stack space. This ensures that each task has its isolated memory region for storing temporary data.
![OS_SWITCH_SP_to_PSP](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/f18aae0e-706f-410f-a2fe-81e0a0cf62f7)

![Switch SP to PSP](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/c7d30c72-2a3b-47e7-b9bd-0963bc0ba79b)


5. **Switch CPU Access Level:**
   The CPU access level is switched to unprivileged mode since tasks typically run in unprivileged mode to prevent unauthorized access to system resources.
![Switch_CPU_Access_level](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/55954c86-8e28-4738-8a63-59be8a1e044a)

![Switch to unprivliged](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/bcc72b1d-4926-45d3-b20c-3582ca8f2eea)

6. **Task Execution:**
   Now, the main OS executes Task A. Task A uses its dedicated stack space (PSP) for storing local variables, return addresses, and other temporary data during its execution.
![Excecute taskA](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/2e129415-ca49-4002-9ad2-37470143d6dd)

7. **Generating SVC Exception:**
   As Task A is running in unprivileged mode, it cannot directly switch back to privileged mode (MSP). To regain privilege, Task A generates an SVC (Supervisor Call) exception.
![generate SVC Exception](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/63ac62c4-12f5-405c-934c-a5d57f104cab)

![Generate Exception to switch to privilged](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/5916c459-5916-4375-9fc1-92273926de45)

8. **Switch SP to MSP:**
   When the SVC exception occurs, the main OS switches the SP back to the MSP, regaining privilege and allowing the main OS to handle system-wide operations.

![Switch SP to MSp](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/adaa772f-38d5-416a-95e9-62f32b58ca29)

9. **Handling Other IRQs:**
   If another IRQ (e.g., another task needs to run) happens during task execution, the main OS will repeat the process by setting the PSP for the new task and executing it similarly.

By following this approach, the main OS can efficiently switch between multiple tasks and ensure that each task operates in its own protected environment. This enables multitasking and the smooth execution of multiple tasks in an embedded system.




## Video Debugging

A video demonstrating the debugging process of Task B using Keil uVision is provided.

---

In conclusion, this lab explores stack memory and demonstrates multitasking using function pointers and stack switching. The code sets up a simple multitasking system and switches between two tasks based on external interrupts. The video debugging further illustrates the

 execution flow of Task B. 
 

https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/9dd96442-f529-4503-a6f3-473ef2780585

