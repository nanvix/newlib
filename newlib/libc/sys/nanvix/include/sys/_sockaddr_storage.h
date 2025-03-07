/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _SYS__SOCKADDR_STORAGE_H_
#define _SYS__SOCKADDR_STORAGE_H_

#include <sys/_types.h>

#ifndef _SA_FAMILY_T_DECLARED
typedef __sa_family_t sa_family_t;
#define _SA_FAMILY_T_DECLARED
#endif

#define _SS_MAXSIZE 16U
#define _SS_PADSIZE (_SS_MAXSIZE - sizeof(unsigned char) - sizeof(sa_family_t))

struct sockaddr_storage
{
    unsigned char ss_len;  /* Total length. */
    sa_family_t ss_family; /* Address family */
    char __ss_pad1[_SS_PADSIZE];
};

#endif
