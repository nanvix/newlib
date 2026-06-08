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

/*
 * `_do_start` is the kernel-entry trampoline that lands here via IRET from
 * a freshly-created process trap frame.  EDX holds `argp` and ECX holds
 * `envp`.  This stub pushes both arguments and calls `_start`.
 *
 * Declared `.weak` so that consumers linking Nanvix's `libnvx_crt0.a` (which
 * provides a stronger SSE-aligned `_do_start` that satisfies the i386 SysV
 * ABI's 16-byte stack-alignment requirement at the CALL site) cleanly
 * override this fallback at link time.  Bare-newlib consumers (no
 * `libnvx_crt0.a` in the link) still get the original behavior because the
 * weak symbol is the only definition the linker sees.
 *
 * Archive-extraction caveat: standard ld will NOT pull a member out of an
 * archive solely to override an already-satisfied weak symbol.  For the
 * override to take effect, `libnvx_crt0.a`'s `_do_start` member must be
 * extracted via some other reference (a co-archive symbol the link
 * actually needs) or via `-Wl,--whole-archive`.  The current Nanvix
 * link lines satisfy this prerequisite; a future refactor that strips
 * `libnvx_crt0.a` down to a single-symbol member must re-add a hook
 * (an extra reference, or `--whole-archive`) or the broken-for-SSE
 * fallback below will silently win again.
 *
 * This change eliminates the duplicate-strong-symbol clash between
 * `crt0.o` and `libnvx_crt0.a` that previously forced every Nanvix guest
 * binary's link line to use `-Wl,--allow-multiple-definition`.
 */
.weak _do_start

/*============================================================================*
 * Text Section                                                               *
 *============================================================================*/

.section .crt0, "ax"

_do_start:
    movl %esp, %ebp
    pushl %ecx
    pushl %edx
    call _start
1:  jmp 1b
