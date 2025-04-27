/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _SYS_UIO_H_
#define _SYS_UIO_H_

#include <sys/_iovec.h>
#include <sys/_types.h>
#include <sys/cdefs.h>

#ifndef _SSIZE_T_DECLARED
typedef __ssize_t ssize_t;
#define _SSIZE_T_DECLARED
#endif

#ifndef _OFF_T_DECLARED
typedef __off_t off_t;
#define _OFF_T_DECLARED
#endif

__BEGIN_DECLS
extern ssize_t readv(int, const struct iovec *, int);
extern ssize_t writev(int, const struct iovec *, int);
#if __BSD_VISIBLE
extern ssize_t preadv(int, const struct iovec *, int, off_t);
extern ssize_t pwritev(int, const struct iovec *, int, off_t);
#endif
__END_DECLS

#endif
