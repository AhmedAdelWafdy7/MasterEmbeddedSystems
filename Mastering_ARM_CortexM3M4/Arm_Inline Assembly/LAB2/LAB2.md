# Lab 2: Introduction to ARM Assembly Programming

This lab introduces ARM assembly programming with a simple assembly code snippet. The code demonstrates basic operations and control flow using ARM instructions.

## Code Explanation:

```assembly
RESET ; CPU entry point
    mov     r0, #5          ; Load 5 into register r0
    bl      main            ; Branch to the main function

main:
    mov     r2, #0x100      ; Load the memory address 0x100 into register r2
    str     r0, [r2]        ; Store the value of r0 into the memory address pointed by r2
    ldr     r3, [r2]        ; Load the value from the memory address pointed by r2 into r3
    STRB    r0, [r2, #0x01] ; Store the least significant byte of r0 into the address r2+1
    STRB    r0, [r2, #0x02] ; Store the least significant byte of r0 into the address r2+2
    STRB    r0, [r2, #0x03] ; Store the least significant byte of r0 into the address r2+3
    bl      termination     ; Branch to the termination function

subtract:
    sub     r0, r0, #1      ; Subtract 1 from the value of r0
    cmp     r0, #0          ; Compare the value of r0 with 0
    bne     subtract        ; Branch to the subtract label if r0 is not equal to 0
    mov     pc, lr          ; Return from the function

termination:
```

## Execution Flow:

1. The code starts executing from the `RESET` label, which is the CPU entry point.
2. The value 5 is loaded into register `r0`.
3. The program branches to the `main` function.
4. In the `main` function:
   - The memory address `0x100` is loaded into register `r2`.
   - The value of `r0` is stored into the memory location pointed by `r2`.
   - The value from the memory location pointed by `r2` is loaded into `r3`.
   - The least significant byte of `r0` is stored into the memory addresses `r2+1`, `r2+2`, and `r2+3`.
   - The program branches to the `termination` function.
5. In the `termination` function, the program reaches the end and stops.

The code demonstrates basic operations like loading, storing, and control flow using conditional branching (`bne`). The `subtract` function decrements the value of `r0` until it becomes zero and then returns.

