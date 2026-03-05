/*
 * Copyright(c) 2011-2024 The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

/*============================================================================*
 * Imported Symbols                                                           *
 *============================================================================*/

.extern _start

/*============================================================================*
 * Exported Symbols                                                           *
 *============================================================================*/

.globl _do_start

/*============================================================================*
 * Text Section                                                               *
 *============================================================================*/

.section .crt0, "ax"

_do_start:
#ifdef __x86_64__
    /* x86_64: argp in %rdi, envp in %rsi (SysV ABI). */
    andq $-16, %rsp
    movq %rsp, %rbp
    call _start
#else
    /* x86: argp in %edx, envp in %ecx. */
    movl %esp, %ebp
    pushl %ecx
    pushl %edx
    call _start
#endif
1:  jmp 1b
