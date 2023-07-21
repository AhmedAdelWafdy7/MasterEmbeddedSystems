# LAB3: Integrating Assembly with C in STM32F103C8T6

In this lab, we explored the integration of assembly language with C code for the STM32F103C8T6 microcontroller. The STM32F103C8T6, also known as the Blue Pill board, is a popular development board based on the ARM Cortex-M3 processor.

## Code Explanation

The code used in this lab demonstrates a simple assembly instruction, NOP (No Operation), integrated into a C program. The NOP instruction is a single-cycle operation that does nothing. It is often used as a placeholder to introduce delays or align instructions.

### Code Snippet:
```c
__asm("NOP \n\t NOP \n\t NOP \n\t");
```

In the above code snippet, the `__asm` keyword is used to introduce inline assembly code in the C program. The `NOP` instruction is repeated three times to create a delay of three cycles.

## Purpose of Using NOP Instruction

The NOP instruction is commonly used for the following purposes:

1. **Delay Generation**: In some applications, you may need to introduce a specific delay between two instructions or operations. The NOP instruction can be used to create the desired delay, ensuring proper timing in the program.

2. **Instruction Alignment**: In certain cases, you may want to align instructions to optimize execution time or ensure compatibility with specific hardware requirements. Inserting NOP instructions allows you to align the instructions accordingly.

3. **Debugging and Testing**: NOP instructions can be used as markers during debugging and testing phases. They provide visual indicators when monitoring the program's execution in real-time.

