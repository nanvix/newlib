/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _SYS__IOVEC_H_
#define _SYS__IOVEC_H_

#include <sys/_types.h>

#ifndef _SIZE_T_DECLARED
typedef __size_t size_t;
#define _SIZE_T_DECLARED
#endif

struct iovec
{
    void *iov_base; /* Base address of a memory region for input or output. */
    size_t iov_len; /* The size of the memory pointed to by iov_base. */
};

#endif
