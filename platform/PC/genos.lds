ENTRY(boot)


SECTIONS 
{


	/DISCARD/ :
		{*(.note.ABI-tag)}
  
  /* The entry point address is fixed at 0x100 */
  . = 0x000;
	.text : AT(0x0)
    {	
		*(.boot)
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

    } 
      
__exidx_start = .;
.ARM.exidx : { *(ARM.exidx*)}

	__exidx_end =  . ;



.int_table : 
{
    *(.int_table)
    . = ALIGN(4);
  }


_bss_start = .;
  .bss    : 
  {
    KEEP(*(.bss))
    KEEP (*(COMMON))
    . = ALIGN(4);
  }
_bss_end = .;

	


__heap_start = .;

}
