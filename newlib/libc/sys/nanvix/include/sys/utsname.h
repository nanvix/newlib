/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _SYS_UTSNAME_H
#define _SYS_UTSNAME_H

#include <sys/cdefs.h>

#define _UTSNAME_LENGTH 65

struct utsname
{
    char sysname[_UTSNAME_LENGTH];  /* Name of this implementation of the operating system. */
    char nodename[_UTSNAME_LENGTH]; /* Name of this node within the communications network to which this node is
                                       attached, if any. */
    char release[_UTSNAME_LENGTH];  /* Current release level of this implementation. */
    char version[_UTSNAME_LENGTH];  /* Current version level of this release. */
    char machine[_UTSNAME_LENGTH];  /* Name of the hardware type on which the system is running. */
};

__BEGIN_DECLS
extern int uname(struct utsname *);
__END_DECLS

#endif
