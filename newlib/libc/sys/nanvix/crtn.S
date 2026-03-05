/* crtn.S for x86_64-nanvix - provides _init and _fini epilogues */

.section .init,"ax",@progbits
addq $8, %rsp
ret

.section .fini,"ax",@progbits
addq $8, %rsp
ret
