ENTRY(_start)

SECTIONS {

    /* Sections go at 1 MiB */
    . = 1M;

    /* Multiboot header */
    .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.text)
    }

    /* RO Data */
    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }

    /* RW Data (initialized) */
    .data BLOCK(4K) : ALIGN(4K) {
        *(.data)
    }

    /* RW Data (uninitialized) and stack */
    .bss BLOCK(4K) : ALIGN(4K) {
        *(COMMON)
        *(.bss)
    }

}
