# 1 "crt0.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "crt0.S"

.global __start_bss
.global __end_bss

init: .global init

  push {lr}
  @Bss allocation
  mov r0, #0
  ldr r1, =__start_bss
  ldr r2, =__end_bss
  2:cmp r1, r2
  strne r0, [r1],#4
  bne 2b

  @Branching main
  BL main
  pop {lr}
  bx lr
