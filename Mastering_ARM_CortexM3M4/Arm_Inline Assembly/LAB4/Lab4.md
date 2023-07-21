# LAB4: Integrating Assembly with C in STM32F103C8T6

In this lab, we explored the integration of assembly language with C programming on the STM32F103C8T6 microcontroller.

## Code Explanation

### Inline Assembly
In this part of the code, we are using inline assembly, which allows us to directly embed assembly instructions within C code. The `__asm` keyword is used to indicate the start of an inline assembly block.

### NOP (No Operation)
The `NOP` (No Operation) assembly instruction performs no operation and is often used as a placeholder for a delay or to align instructions. In the given code snippet, three `NOP` instructions are used, separated by newline and tab characters (`\n\t`), to introduce a small delay.

### Move Immediate to Register
The `MOV` assembly instruction moves an immediate value (constant) to a register. In the code, `R0` is a general-purpose register, and we are moving the value of the variable `VAL1` into `R0`. The `%0` in the second line of code indicates that the value of `VAL1` will be substituted at that position in the assembly code.

### Complete Code
```c
__asm("nop\n\t nop \n\t nop"); // Three NOP instructions for a delay

// Move the value of VAL1 to R0 register using inline assembly
__asm("mov R0,%0" 
      :"=r"(VAL1) );

__asm("nop\n\t nop \n\t nop"); // Three NOP instructions for a delay
```

This code snippet demonstrates the use of inline assembly to introduce delays and perform data movement between C variables and registers on the STM32F103C8T6 microcontroller.
