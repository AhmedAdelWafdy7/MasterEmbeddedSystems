# Lab: SVC and PendSV in ARM Cortex-M3

This lab demonstrates the implementation of SVC (Supervisor Call) and PendSV (Pendable Service) handlers in an ARM Cortex-M3 based microcontroller. SVC is used to invoke privileged functions, and PendSV is a special exception used to trigger context switching between tasks in a real-time operating system (RTOS).

## Implementation Details

### SVC_Handler

In the code, we have implemented the `SVC_Handler` function, which is called when an SVC instruction is executed. The `SVC_Handler` function switches the CPU access level to privileged mode and forwards the execution to the `OS_SVC` function.

```c
__attribute__((naked)) void SVC_Handler() {
    __asm("tst lr, #4 \n\t"
          "ITE EQ \n\t"
          "mrseq r0, MSP \n\t"
          "mrsne r0, PSP \n\t"
          "B OS_SVC");
}
```

### OS_SVC_Set

The `OS_SVC_Set` function is used to invoke different SVC services based on the `SVC_ID`. It takes two integer parameters `a` and `b`, and an `SVC_ID`. The function executes an SVC instruction with the corresponding SVC number to request a specific service from the `OS_SVC` function.

```c
int OS_SVC_Set(int a, int b, int SVC_ID) {
    int result;
    switch (SVC_ID) {
        case 1: // OS // Add
            __asm("svc #0x00");
            break;
        case 2: // OS // Sub
            __asm("svc #0x01");
            break;
        case 3: // OS // Mul
            __asm("svc #0x02");
            break;
    }

    // r0 ===> return value
    __asm("mov %0, r0" : "=r"(result));
    return result;
}
```

### OS_SVC

The `OS_SVC` function is the actual SVC service handler. It receives the stack frame of the SVC request and extracts the SVC number from the stack frame. Based on the SVC number, it performs the corresponding operation.

```c
void OS_SVC(int *Stack_Frame) {
    uint8_t SVC_number;
    uint32_t val1, val2;
    val1 = Stack_Frame[0];
    val2 = Stack_Frame[1];
    SVC_number = *((unsigned char *)(((unsigned char *)Stack_Frame[6]) - 2));

    switch (SVC_number) {
        case 1: // OS // Add
            Stack_Frame[0] = val1 + val2;
            break;
        case 2: // OS // Sub
            Stack_Frame[0] = val1 - val2;
            break;
        case 3: // OS // Mul
            Stack_Frame[0] = val1 * val2;
            break;
        case 4: // OS PendSV
            SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
            break;
    }
}
```

### PendSV_Handler

The `PendSV_Handler` function is an empty handler for the PendSV exception. In a real-world scenario, this handler would perform the context switching and task scheduling in an RTOS environment.

```c
void PendSV_Handler(void) {
    // Add context switching and task scheduling code here
}
```

### Main Code

In the main code, we demonstrate how to use the SVC services. We call the `OS_SVC_Set` function with different arguments to request different operations (Add, Subtract, Multiply). Additionally, we invoke an SVC service with `SVC_ID = 4` to trigger the PendSV exception, which would initiate context switching in an RTOS environment.

```c
int main() {
    int IRQ_flag;
    IRQ_flag = OS_SVC_Set(3, 2, 1); // Request Add operation
    IRQ_flag = OS_SVC_Set(3, 2, 2); // Request Sub operation
    IRQ_flag = OS_SVC_Set(3, 2, 3); // Request Mul operation
    IRQ_flag = OS_SVC_Set(3, 3, 4); // Request PendSV operation

    // Add your application code here

    while (1) {
        // Your main application code goes here
    }

    return 0;
}
```

## Simulation Video with Keil uVision

Include a link to the simulation video with Keil uVision, demonstrating the behavior of the implemented SVC and PendSV handlers.



https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/d5beb5ec-75ee-430c-ab84-a621721f699a



## Conclusion

The SVC and PendSV handlers in ARM Cortex-M3 are powerful mechanisms for implementing privileged functions and context switching in an RTOS. By using SVC instructions, the main code can request specific services from the SVC service handler. PendSV, on the other hand, is a special exception used to perform context switching between tasks, providing multitasking capabilities in embedded systems.
