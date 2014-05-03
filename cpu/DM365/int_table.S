


.global _int_vect_table_for_copy_h 
.global _undefined_instruction
.global _software_interrupt
.global _prefetch_abort
.global _data_abort
.global _not_used
.global _irq
.global _fiq
.global blink
.section .text
_int_vect_table_for_copy_h:
	
	ldr		pc,	_undefined_instruction
    ldr     pc, _software_interrupt
    ldr     pc, _prefetch_abort
	ldr     pc, _data_abort
    ldr     pc, _not_used
    ldr     pc, _irq
    ldr     pc, _fiq

_undefined_instruction:
        .word undefined_instruction
_software_interrupt:
        .word software_interrupt
_prefetch_abort:
        .word prefetch_abort
_data_abort:
        .word data_abort
_not_used:
        .word not_used
_irq:
        .word irq
_fiq:
        .word fiq



 .global interrupt_copy_def
 .global empty_INT
 interrupt_copy_def:
ldr pc, __empty_int
__empty_int:
.word empty_INT
