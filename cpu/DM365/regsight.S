

.global STACK_POINTER
STACK_POINTER:
mov r0,sp
bx lr


.global R2_REGISTER
R2_REGISTER:
mov r0,r2
bx lr

.global R0_REGISTER
R0_REGISTER:
bx lr


.global FP_REGISTER
FP_REGISTER:
mov r0,fp
bx lr

.global CPU_MODE
CPU_MODE:
MRS  r0, cpsr
bx lr

.global SPSR_REGISTER
SPSR_REGISTER:
MRS  r0, spsr
bx lr














