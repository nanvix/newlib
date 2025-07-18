/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_

#include <sys/features.h>
#include <sys/_types.h>
#include <sys/cdefs.h>

/* May also make visible all symbols from the following headers. */
#include <fcntl.h>

/* Used as protection options. */
#define PROT_NONE 0  /* Page cannot be accessed. */
#define PROT_READ 1  /* Page can be read. */
#define PROT_WRITE 2 /* Page can be written. */
#define PROT_EXEC 4  /* Page can be executed. */

/* Used as flag options. */
#define MAP_SHARED 1           /* Share changes. */
#define MAP_PRIVATE 2          /* Changes are private. */
#define MAP_FIXED 0x10         /* Interpret addr exactly. */
#define MAP_ANONYMOUS 0x20     /* Map anonymous memory. */
#define MAP_ANON MAP_ANONYMOUS /* Synonym for MAP_ANONYMOUS. MAP_ANON shall have the same value as MAP_ANONYMOUS. */

/*
 * Flags for msync().
 */
#if __XSI_VISIBLE
#define MS_ASYNC 1      /* Perform asynchronous writes. */
#define MS_SYNC 2       /* Perform synchronous writes. */
#define MS_INVALIDATE 4 /* Invalidate mappings. */
#endif

/* Used to indicate a failure from mmap(). */
#define MAP_FAILED ((void *)-1)

/*
 * Flags for posix_madvise()
 */
#define POSIX_MADV_NORMAL                                                                                              \
    0 /* The application has no advice to give on its behavior with respect to the specified range. It is the default  \
         characteristic if no advice is given for a range of memory. */
#define POSIX_MADV_SEQUENTIAL                                                                                          \
    1 /* The application expects to access the specified range sequentially from lower addresses to higher addresses.  \
       */
#define POSIX_MADV_RANDOM 2   /* The application expects to access the specified range in a random order. */
#define POSIX_MADV_WILLNEED 3 /* The application expects to access the specified range in the near future. */
#define POSIX_MADV_DONTNEED                                                                                            \
    4 /* The application expects that it will not access the specified range in the near future. */

__BEGIN_DECLS

extern int mlock(const void *, size_t);
extern int mlockall(int);
extern void *mmap(void *, size_t, int, int, int, off_t);
extern int mprotect(void *, size_t, int);
#if __XSI_VISIBLE
extern int msync(void *, size_t, int);
#endif
extern int munlock(const void *, size_t);
extern int munlockall(void);
extern int munmap(void *, size_t);
extern int posix_madvise(void *, size_t, int);
extern int posix_mem_offset(const void *__restrict, size_t, off_t *__restrict, size_t *__restrict, int *__restrict);
extern int shm_open(const char *, int, mode_t);
extern int shm_unlink(const char *);
__END_DECLS

#endif /*  _SYS_MMAN_H_ */
