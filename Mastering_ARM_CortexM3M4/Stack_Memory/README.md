# Lab - Switching CPU Access Level

In this lab, we explore how to switch the CPU access level from privileged to unprivileged using assembly language. The lab involves a function and its implementation in the main code.

## Function Definition

```c
enum CPU_Access_level {
    privileged,
    unprivileged
};

void Switch_CPU_Access_level(enum CPU_Access_level access_level) {
    switch (access_level) {
        case privileged:
            __asm("NOP \n\t NOP \n\t NOP \n\t");
            __asm("mrs r3,CONTROL \n\t"
                  "lsr r3,r3,#0x01 \n\t"
                  "lsr r3,r3,#0x01 \n\t"
                  "msr CONTROL , r3");
            __asm("NOP \n\t NOP \n\t NOP \n\t");
            break;
        case unprivileged:
            __asm("NOP \n\t NOP \n\t NOP \n\t");
            __asm("mrs r3,CONTROL \n\t"
                  "orr r3,r3,#0x01 \n\t"
                  "msr CONTROL , r3");
            __asm("NOP \n\t NOP \n\t NOP \n\t");
            break;
    }
}
```
![Switch_CPU_Access_level](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/715394f4-34d4-4fd3-bd37-b14543881785)

### Explanation

The function `Switch_CPU_Access_level` is defined to switch the CPU access level between privileged and unprivileged. It takes an argument `access_level` of the enumeration type `enum CPU_Access_level`, which can be either `privileged` or `unprivileged`.

The function utilizes inline assembly language instructions to manipulate the CONTROL register, which is used to control the CPU access level. The CONTROL register is a special register on ARM Cortex-M processors that controls whether the CPU is running in privileged or unprivileged mode.

In the `privileged` case, the function reads the current value of the CONTROL register, clears the second bit to switch to unprivileged mode, and then writes the modified value back to the CONTROL register.

In the `unprivileged` case, the function reads the current value of the CONTROL register, sets the second bit to switch to privileged mode, and then writes the modified value back to the CONTROL register.

## Main Code

In the main code, the function `Switch_CPU_Access_level` is called to switch from privileged to unprivileged mode.

```c
int main() {
    // Switch to unprivileged mode
    Switch_CPU_Access_level(unprivileged);

    // ... (other code)

    return 0;
}
```
![Main](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/6cb12f27-d066-4b17-b53f-9806dc39b3d3)

### Explanation

The `main` function calls the `Switch_CPU_Access_level` function with the argument `unprivileged`, which switches the CPU access level to unprivileged mode. After this call, the CPU will be operating in unprivileged mode until explicitly switched back to privileged mode.

Additionally, the code mentions an `IRQ_EXTI9_callback` function, which presumably is an interrupt handler for an external interrupt on line 9. In this interrupt handler, the CPU access level is switched to privileged using the `Switch_CPU_Access_level` function.
![EXTI](https://github.com/AhmedAdelWafdy7/MasterEmbeddedSystems/assets/107740350/75471a1b-66f4-448c-a34a-6755ec9b897f)

Please note that switching from unprivileged to privileged mode directly from thread mode is not allowed. To switch to privileged mode, you must enter handler mode by triggering an exception or an interrupt.

---
This lab demonstrates how to switch the CPU access level using assembly instructions. By understanding this process, you can effectively control the privilege levels of your ARM Cortex-M-based embedded applications.
Link to debugging video in KeiluVision :https://drive.google.com/file/d/1Bfu2EJeTVCM-8CMEKMHo2ntJpa1byOLj/view?usp=sharing
