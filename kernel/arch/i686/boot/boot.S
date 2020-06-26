/* Multiboot header */
.set ALIGN,    1<<0              /* Align on page boundaries */
.set MEMINFO,  1<<1              /* Memory Map */
.set FLAGS,    ALIGN | MEMINFO   /* Set bits for flags */
.set MAGIC,    0x1BADB002        /* Multiboot `magic` number */
.set CHECKSUM, -(MAGIC + FLAGS)  /* Checksum. 0x1BADBOO2 + FLAGS + Checksum == 0 */

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Stack setup */
.section .bss
.align 16         /* 16 byte aligned; x86 requirement */
stack_bottom:
.skip 0x4000      /* 16 KiB Stack */
stack_top:

/* Kernel Load */
.section .text
.global _start
.type _start, @function
_start:
    /* Now in 32bit protected mode */
    mov $stack_top, %esp

    /* Initialize processer state and features here */

    /* Get to the kernel */
    call kmain

    /* Inifinte loop: wait for interrupts, but disable interrupts */
    cli
1:  hlt
    jmp 1b

.size _start, . - _start
