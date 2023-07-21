# LAB5 - Integration of Assembly with C in STM32F103C8T6

In this lab, we explored the integration of assembly language with C programming on the STM32F103C8T6 microcontroller. By combining these two languages, we can leverage the efficiency and low-level capabilities of assembly with the ease and readability of C programming.

## Code Explanation

The following code snippet demonstrates how to integrate assembly instructions within a C code block:

```c
__asm("nop\n\t nop \n\t nop"); // Three assembly 'nop' instructions in sequence

// mov R0,VAL1
__asm("mov R0,%0" // Move the value of VAL1 into register R0
	  :          // Output operands (none in this case)
	  : "r" (VAL1) // Input operand - VAL1 variable
);
__asm("nop\n\t nop \n\t nop"); // Three assembly 'nop' instructions in sequence
```

Explanation:
1. The first line contains three assembly `nop` instructions separated by the escape sequence `\n\t`. The `nop` instruction is a "no-operation" instruction that takes up one CPU cycle but does nothing. These instructions are typically used for timing or synchronization purposes.

2. The second part of the code demonstrates how to use inline assembly to load a C variable (`VAL1`) into the ARM register R0. The `mov` instruction is used for this purpose. The syntax for inline assembly is `__asm("assembly_code" : output : input);`, where `output` and `input` are optional operands. In this case, we only have an input operand, which is the `VAL1` variable.



