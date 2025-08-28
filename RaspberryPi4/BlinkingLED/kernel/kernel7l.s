.global _start

.equ GPIO_BASE_ADDRESS 0xFE200000
.equ GPIO_SEL_REG_OFF 0x0
.equ GPIO_SET_REG_OFF 0x1C
.equ GPIO_CLR_REG_OFF 0x28

; GPIO_PIN compile time argument
_start:
    ldr r0, =GPIO_BASE_ADDRESS
    add r0, r0, GPIO_SEL_REG_OFFSET
    ldr r1, =[0] ; which select register
    ldr r2, GPIO_PIN ; which bit in select register
gpio_sel_calc:
    subs r3, r2, 10
    blt gpio_sel_calc_fin
    mov r2, r3
    add r1, r1, 1
    B gpio_sel_calc
gpio_sel_calc_fin:
    mul r1, r1, 32
    add r4, r0, r1 ; r4 is register address
    mul r5, r2, 3 ; r5 is bit offset
clear_sel:
    ldr r0, =[r4]
    ldr r1, =7
    lsl r1, r1, r5
    mvn r1, r1
    and r0, r1, r0
    str r0, [r4]
set_output:
    ldr r0, =[r4]
    ldr r1, =1
    lsl r1, r1, r5
    or r0, r1, r0
    str r0, [r4]

loop:
    bl set
    bl delay
    bl clear
    bl delay
    b loop

set:
    ldr r0, =GPIO_BASE_ADDRESS
    add r0, r0, GPIO_SET_REG_OFF
    ldr r1, =GPIO_PIN
    ldr r2, =1
    lsl r2, r2, r1
    str r2, [r0]
    bx lr

clear:
    ldr r0, =GPIO_BASE_ADDRESS
    add r0, r0, GPIO_CLR_REG_OFF
    ldr r1, =GPIO_PIN
    ldr r2, =1
    lsl r2, r2, r1
    str r2, [r0]
    bx lr

delay:
    ldr r0, = 0x2000000
delay_loop:
    subs r0, r0, 1
    bne delay_loop
    bx lr

