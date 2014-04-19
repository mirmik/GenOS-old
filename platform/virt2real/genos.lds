ENTRY(boot)
SECTIONS 
{  
  EMIFStart  = 0x02000000;
  EMIFSize   = 0x02000000; 
  IRAMStart  = 0x00000000;
  IRAMSize   = 0x00008000;
  
  DRAMStart  = 0x00010000;
  DRAMSize   = 0x00008000;
  DDRStart   = 0x80000000;
  DDRSize    = 0x10000000;
  EXTERNAL_RAM_START = 0x80000000;
  EXTERNAL_RAM_END   = EXTERNAL_RAM_START + DDRSize;  
  
  STACKStart = EXTERNAL_RAM_START + DDRSize;




  /* The entry point address is fixed at 0x100 */
  . = 0x82000000;
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



_bss_start = .;
  .bss    : 
  {
    KEEP(*(.bss))
    #KEEP (*(COMMON))
    . = ALIGN(4);
  }
_bss_end = .;

	


__heap_start = .;

}
