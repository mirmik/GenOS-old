#ifndef CONTEXT_H
#define CONTEXT_H


class Processor_p
{	
}
#endif

//#define STACK_POINTER;

#define PROCESSOR_PRINT_STATE(a) {PUSH_PROCESSOR_STATE; a->print_state(STACK_POINTER); POP_PROCESSOR_STATE;}


/* Для реализации в теле platform части
#define PUSH_PROCESSOR_STATE
#define POP_PROCESSOR_STATE
*/
