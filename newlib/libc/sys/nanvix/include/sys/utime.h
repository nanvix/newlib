/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef __UTIME_H
#define __UTIME_H

#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

/*
 * Time structure.
 */
struct utimbuf
{
    time_t actime;  /* Access time */
    time_t modtime; /* Modification time */
};

extern int utime(const char *path, const struct utimbuf *times);

__END_DECLS

#endif /* __UTIME_H */
