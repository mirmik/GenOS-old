


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







.global eabase
/*
eabase:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int00:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT


__int01:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int02:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int03:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int04:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int05:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int06:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int07:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int08:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int09:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int10:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int11:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int12:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int13:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int14:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int15:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int16:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int17:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int18:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int19:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int20:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int21:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int22:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int23:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int24:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int25:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int26:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int27:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int28:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int29:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int30:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int31:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int32:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int33:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int34:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int35:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int36:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int37:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int38:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int39:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int40:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int41:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int42:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int43:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int44:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int45:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int46:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int47:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int48:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int49:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int50:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int51:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int52:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int53:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int54:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int55:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int56:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int57:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int58:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int59:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int60:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int61:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int62:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT

__int63:
ldr pc, [pc,#20]
nop
nop
nop
nop
nop
nop
.word empty_INT
*/
