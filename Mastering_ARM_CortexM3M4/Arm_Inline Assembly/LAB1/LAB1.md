# Assembly Lab: Basic Program

The program demonstrates the concept of function calling and conditional branching in assembly language.

## Program Description

### Program Flow

The program is written for an architecture with a RESET entry point. The CPU starts execution from the RESET entry point and jumps to the `main` function.

### Main Function

The `main` function serves as the entry point of the program. It calls two other functions: `subtract` and `termination`.

### Subtract Function

The `subtract` function is called from the `main` function. It takes a single argument stored in register `r0`, decrements it by 1, and then checks if the result is not equal to 0. If the result is not zero, the function loops back to itself (recursive call). Otherwise, it returns to the calling function using the `mov pc, lr` instruction.

### Termination Function

The `termination` function is called from the `main` function after the `subtract` function is executed. This function can be used to handle any cleanup or additional actions before the program terminates.

## Program Code

```assembly
RESET ; CPU entry point
	mov		r0, #5    ; Load initial value (5) into r0
	bl		main      ; Call the main function

main
	bl		subtract  ; Call the subtract function
	bl		termination ; Call the termination function

subtract
	sub		r0, r0 , #1  ; Subtract 1 from r0
	cmp		r0, #0       ; Compare r0 with 0
	bne		subtract     ; If r0 is not equal to 0, loop (recursive call)
	mov		pc,lr        ; Return to the calling function using the link register

termination
	; Any additional code for cleanup or termination actions can be added here
```

## Usage

The program contains assembly instructions and is designed to be assembled and executed on a specific architecture. The behavior of the program depends on the specific hardware it runs on.

