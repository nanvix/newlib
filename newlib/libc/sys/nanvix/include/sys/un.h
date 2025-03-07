/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _SYS_UN_H_
#define _SYS_UN_H_

#include <sys/_types.h>

#ifndef _SA_FAMILY_T_DECLARED
typedef __sa_family_t sa_family_t;
#define _SA_FAMILY_T_DECLARED
#endif

/* Size of the sun_path field in sockaddr_un structure. */
#define SUNPATHLEN 14

/* Unix socket domain. */
struct sockaddr_un
{
    unsigned char sun_len;     /* Sockaddr length. */
    sa_family_t sun_family;    /* Address family. */
    char sun_path[SUNPATHLEN]; /* Socket pathname storage. */
};

#endif
