# LAB6: Integrating Assembly with C in STM32F103C8T6

In this lab, we explore how to integrate assembly language with C code on the STM32F103C8T6 microcontroller. The STM32F103C8T6 is based on the ARM Cortex-M3 architecture, and it is widely used in various embedded systems applications.

## Code Explanation:

In the provided code, we have an example of how to use assembly instructions alongside C code. The code snippet below demonstrates some assembly instructions placed within a C code block:

```c
__asm("nop\n\t nop \n\t nop");
// mov R0,VAL1
__asm("add %0,%1,%2"
      : "=r" (VAL3)               // output
      : "r" (VAL1),
        "r" (VAL2)); 
__asm("nop\n\t nop \n\t nop");
```

- The `__asm` keyword is used to specify that the code within the parentheses is assembly code.

- The `nop` instruction is a no-operation assembly instruction that consumes one cycle of the processor but does nothing. It is often used for inserting delays or just padding.

- The instruction `mov R0,VAL1` is not supported in inline assembly on some compilers, so it might cause an error. Instead, we can use the appropriate constraints to achieve the desired operation.

- The instruction `add %0,%1,%2` adds the values of `VAL1` and `VAL2` and stores the result in `VAL3`.

- The `: "=r" (VAL3)` syntax indicates that `VAL3` is an output operand, and the `"r" (VAL1)` and `"r" (VAL2)` syntax specifies that `VAL1` and `VAL2` are input operands.

- The `"r"` constraint specifies that the value can be stored in any general-purpose register.

- The `"\n\t nop \n\t nop"` instructions are additional `nop` operations used for padding or delays.

