
//#include "types.h"

/*

#ifndef _CPU_REGISTER_H
#define _CPU_REGISTER_H

extern uint32_t processor_length;
void proc_length_init();

extern uint32_t stack_pointer;
#define GET_STACK_POINTER(a) asm("movl %%esp , %0":"=a"(a));
#define SET_STACK_POINTER(a) asm("movl %0 , %%esp"::"a"(a));



extern uint32_t processor_length;
extern size_t helper_a;
extern size_t helper_b;

//#define PROC_STATE(m) 				\
{	SAVE_CONTEXT();					\
									\
	GET_STACK_POINTER(helper_a);	\
	helper_b=(uint32_t)(m + processor_length);\
	SET_STACK_POINTER(helper_b);	\
	SAVE_CONTEXT();					\	
//	SET_STACK_POINTER(helper_a);	\
									\
	LOAD_CONTEXT();					\
}


#define PROC_STATE(m)\
{					\
	SAVE_CONTEXT();					\
	proc_length_init();				\
	GET_STACK_POINTER(helper_a);	\
	helper_b=(size_t)m-helper_a;								\
	for (;processor_length;processor_length--) {*((uint8_t*)helper_a+helper_b) = *((uint8_t*)helper_a);helper_a++;;}	\
	LOAD_CONTEXT();					\
};

#include "debug/debug.h"
#define PROCESSOR_PRINT(a,b) {  \
debug_print("PROC_STATE:\n\r");\
debug_print_dump((void*)a,b);	\
debug_print("transcript:\r\n"); \
debug_print("eax :");dpr_inthex(*((int*)(a+28)));dln	\
debug_print("ebx :");dpr_inthex(*((int*)(a+16)));dln	\
debug_print("ecx :");dpr_inthex(*((int*)(a+24)));dln	\
debug_print("edx :");dpr_inthex(*((int*)(a+20)));dln	\
debug_print("esp :");dpr_inthex(*((int*)(a+8)));dln	\
debug_print("TODO..."); \
}

#define PROC_PRINT(m)\
{					\
	SAVE_CONTEXT();					\
	proc_length_init();				\
	GET_STACK_POINTER(helper_a);	\
	PROCESSOR_PRINT(helper_a,processor_length);			\
	LOAD_CONTEXT();					\
};





#endif
*/
