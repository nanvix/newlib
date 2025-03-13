/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _GCC_LIMITS_H_
#include_next <limits.h>
#endif

#include <sys/syslimits.h>

#ifndef __POSIX_LIMITS_H
#define __POSIX_LIMITS_H

#include <sys/_types.h>

// The value that can be stored in an object of type ssize_t.
#define _POSIX_SSIZE_MAX 32767

// Maximum value for an object of type ssize_t.
#ifdef __SIZE_MAX__
#define SSIZE_MAX (__SIZE_MAX__ >> 1)
#elif defined(__SIZEOF_SIZE_T__) && defined(__CHAR_BIT__)
#define SSIZE_MAX ((1UL << (__SIZEOF_SIZE_T__ * __CHAR_BIT__ - 1)) - 1)
#else /* historic fallback, wrong in most cases */
#define SSIZE_MAX _POSIX_SSIZE_MAX
#endif

// The number of data keys per process.
#define _POSIX_THREAD_KEYS_MAX 128

// Maximum number of data keys that can be created by a process.
#define PTHREAD_KEYS_MAX _POSIX_THREAD_KEYS_MAX


#endif
