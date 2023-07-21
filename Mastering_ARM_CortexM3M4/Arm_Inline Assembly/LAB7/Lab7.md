# LAB7: Integrating Assembly with C on STM32F103C8T6

## Description

In this lab, we explored the integration of assembly language with C on the STM32F103C8T6 microcontroller. The main objective was to understand how to combine assembly code within a C program to perform specific tasks efficiently and gain better control over low-level hardware operations.

## Code Snippet

### Variable Definitions
```c
int Control_Reg_Thread_Mode = 0;
int IPSR_Handler_Mode = 0;
```

### Interrupt Service Routine (ISR) Callback
```c
void IRQ_EXTI9_callback(void){
    IRQ_flag = 1;

    // Inline assembly to read IPSR (Interrupt Program Status Register)
    __asm("NOP \n\t NOP \n\t NOP \n\t");
    __asm("MRS %[out0], IPSR"
          : [out0] "=r" (IPSR_Handler_Mode) );
    __asm("NOP \n\t NOP \n\t NOP \n\t");
}
```

### Main Function
```c
int main() {
    // Inline assembly to perform NOP instructions for delay
    __asm("nop\n\t nop \n\t nop");
    // Inline assembly to read Control Register (PSP or MSP) value
    __asm("MRS %[out0], control"
          : [out0] "=r" (Control_Reg_Thread_Mode) );
    __asm("nop\n\t nop \n\t nop");

    // Rest of the main code...
}
```

## Explanation

In this code snippet, we have a lab example where we integrate assembly code with C on the STM32F103C8T6 microcontroller. The `Control_Reg_Thread_Mode` and `IPSR_Handler_Mode` variables are defined to store specific register values.

The `IRQ_EXTI9_callback` function is an Interrupt Service Routine (ISR) callback. It is called when an external interrupt on line 9 is triggered. Within this ISR, we use inline assembly to read the `IPSR` (Interrupt Program Status Register) and store its value in the `IPSR_Handler_Mode` variable.

In the `main` function, we have inline assembly using NOP (No Operation) instructions to introduce some delay. After that, we read the value of the `control` register (PSP or MSP, depending on the current thread mode) using inline assembly and store it in the `Control_Reg_Thread_Mode` variable.

