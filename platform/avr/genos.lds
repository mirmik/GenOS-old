ENTRY(boot)
SECTIONS 
{  

  /* The entry point address is fixed at 0x100 */
  . = 0x0000000;
  .boot    : AT (0x00)
  { *(.boot)
    . = ALIGN(4);
  }

.int_table : 
{
    *(.int_table)
    . = ALIGN(4);
  }

	.text :
    {
        KEEP(*(.isr_vector .isr_vector.*))
        *(.text .text.* .gnu.linkonce.t.*)
    
        KEEP(*(.isr_vector .isr_vector.*))
        *(.glue_7t) *(.glue_7)
        *(.rodata .rodata* .gnu.linkonce.r.*)

        /* C++ Static constructors/destructors (eabi) */
        . = ALIGN(4);
        KEEP(*(.init))

        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;

        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;

        . = ALIGN(4);
        KEEP(*(.fini))

        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;

        /* C++ Static constructors/destructors (elf) */
        . = ALIGN(4);
        _ctor_start = .;
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*crtend.o(.ctors))
        _ctor_end = .;

        . = ALIGN(4);
        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))
	. = ALIGN(4);
    }
    
    
/* Секция инициализированных данных */
    .data :
    {
        *(.data)
        . = ALIGN(4);
    }
    
__exidx_start = .;
.ARM.exidx : { *(ARM.exidx*)}

	__exidx_end =  . ;
    
    
/* Секция неинициализированных данных */    
	.bss :
    {
		
        *(.bss)
        . = ALIGN(4);
        
    }
    
    _text_begin = LOADADDR(.text) ;
    _text_end = LOADADDR(.text) + SIZEOF(.text) ;
    _data_begin = LOADADDR(.data) ;
    _data_end = LOADADDR(.data) + SIZEOF(.data) ;
    _bss_begin = LOADADDR(.bss) ;
    _bss_end = LOADADDR(.bss) + SIZEOF(.bss) ;
    
/* Место в памяти, где уже нет кода ядра */
    end = .; _end = .; __end = .;  



__heap_start = .;

}
