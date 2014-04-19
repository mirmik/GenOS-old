






#define IRQ_FLAG_REMOVE(a) {\
        if (a<32) AINTC->IRQ0 |= 1 << a;\
        else AINTC->IRQ1 |= 1 << (a-32);\
        } 


#define IRQ_E()  asm(".include \"arm_asm_def.h\" \n\r \
push {r0}  \n\r \
mrs r0, cpsr \n\r \
bic r0, #I_BIT \n\r \
msr cpsr , r0 \n\r \
pop {r0}  ");


#define FIQ_E()  asm(".include \"arm_asm_def.h\" \n\r \
push {r0}  \n\r \
mrs r0, cpsr \n\r \
bic r0, #F_BIT \n\r \
msr cpsr , r0 \n\r \
pop {r0}  ");


#define IRQ_D()  asm(".include \"arm_asm_def.h\" \n\r \
push {r0}  \n\r \
mrs r0, cpsr \n\r \
orr r0, #I_BIT \n\r \
msr cpsr , r0 \n\r \
pop {r0}  ");


#define FIQ_D()  asm(".include \"arm_asm_def.h\" \n\r \
push {r0}  \n\r \
mrs r0, cpsr \n\r \
orr r0, #F_BIT \n\r \
msr cpsr , r0 \n\r \
pop {r0}  ");


