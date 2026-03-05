/* crti.S for x86_64-nanvix - provides _init and _fini prologues */

.section .init,"ax",@progbits
.globl _init
.type _init, @function
_init:
subq $8, %rsp   /* Align stack to 16 bytes (ABI: RSP = 16n-8 at entry) */

.section .fini,"ax",@progbits
.globl _fini
.type _fini, @function
_fini:
subq $8, %rsp   /* Align stack to 16 bytes */
