/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _DLFCN_H
#define _DLFCN_H

#include <sys/cdefs.h>

struct Dl_info
{
    char *dli_fname;       /* Pathname of mapped object file. */
    void *dli_fbase;       /* Base of mapped address range. */
    const char *dli_sname; /* Symbol name or null pointer. */
    void *dli_saddr;       /* Symbol address or null pointer.*/
};
typedef struct Dl_info Dl_info_t;

/* Use in dlopen(). */
#define RTLD_LOCAL 0  /* Relocations are performed at an implementation-defined time.     */
#define RTLD_LAZY 1   /* Relocations are performed when the object is loaded.               */
#define RTLD_NOW 2    /* All symbols are available for relocation processing of other modules.          */
#define RTLD_GLOBAL 4 /* All symbols are not made available for relocation processing by other modules. */

__BEGIN_DECLS
extern int dladdr(const void *restrict, Dl_info_t *restrict);
extern int dlclose(void *);
extern char *dlerror(void);
extern void *dlopen(const char *, int);
extern void *dlsym(void *restrict, const char *restrict);
__END_DECLS

#endif /* _DLFCN_H */
