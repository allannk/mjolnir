/* Set program entry point */
ENTRY(reset_handler)

/* End of RAM / Start of stack (4KB SRAM) */
_estack = 0x20001000;

/* Set minimum size for stack and dynamic memory. 
 * Linker generates an error if there is less RAM */
_Min_Leftover_RAM = 0x400;

MEMORY {
    FLASH ( rx )      : ORIGIN = 0x08000000, LENGTH = 32K
    RAM ( rxw )       : ORIGIN = 0x20000000, LENGTH = 4K
}

SECTIONS {
    /* Vector table goes first */
    .vector_table : {
        . = ALIGN(4);
        KEEP (*(.vector_table))
        . = ALIGN(4);
    } >FLASH

    /* 'text' section contains main program code */
    .text : {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
    } >FLASH

    /* 'rodata' contains readonly data such as 
     * constants, strings, and other info that wont change */
    .rodata : {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >FLASH

    /* 'data' is space set aside in RAM for 
     * things like variables that do change */
    _sidata = .;
    .data : AT(_sidata) {
        . = ALIGN(4);
        /* Mark start/end location for data section */
        _sdata = .;
        *(.data)
        *(.data*)
        _edata = .;
        . = ALIGN(4);
    } >RAM

    /* 'bss' section is similar to data section, but its
     * space is initialized to zeros at start of program */
    .bss : {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >RAM

    /* Dynamic allocations, for applications HEAP/STACK */
    .dynamic_allocations : {
        . = ALIGN(4);
        _ssystem_ram = .;
        . = . + _Min_Leftover_RAM;
        . = ALIGN(4);
        _esystem_ram = .;
    } >RAM
}

/* Explanation of SECTIONS:
 *
 *  `.` means current address. 
 *  `.ALIGN(4)` will align to next 4 bytes boundary
 *  `KEEP(...)` will skip garbage collection for specified part
 *  `xxx = .` will save the current address (useful for the startup script, to know boundaries where to zero-initialize, copy-initialize etc.)
 *  `.data : AT(_sidata)` will tell the linker to start .data section (code) at `_sidata`-location
 *
 *
 */
