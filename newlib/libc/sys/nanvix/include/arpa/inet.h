/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _ARPA_INET_H_
#define _ARPA_INET_H_

#include <sys/_types.h>
#include <sys/cdefs.h>

/* Required for byteorder functions. */
#include <machine/endian.h>

#ifndef _UINT16_T_DECLARED
typedef __uint16_t uint16_t;
#define _UINT16_T_DECLARED
#endif

#ifndef _UINT32_T_DECLARED
typedef __uint32_t uint32_t;
#define _UINT32_T_DECLARED
#endif

#ifndef _IN_ADDR_T_DECLARED
typedef uint32_t in_addr_t;
#define _IN_ADDR_T_DECLARED
#endif

#ifndef _IN_PORT_T_DECLARED
typedef uint16_t in_port_t;
#define _IN_PORT_T_DECLARED
#endif

#ifndef _SOCKLEN_T_DECLARED
typedef __socklen_t socklen_t;
#define _SOCKLEN_T_DECLARED
#endif

#ifndef _STRUCT_IN_ADDR_DECLARED
struct in_addr
{
    in_addr_t s_addr;
};
#define _STRUCT_IN_ADDR_DECLARED
#endif

/* Used to help applications to declare buffers of the proper size to store IPv4 addresses in string format. */
#define INET_ADDRSTRLEN 16 /* Length of the string form for IP. */

__BEGIN_DECLS
#ifndef _BYTEORDER_PROTOTYPED
#define _BYTEORDER_PROTOTYPED
extern uint32_t htonl(uint32_t);
extern uint16_t htons(uint16_t);
extern uint32_t ntohl(uint32_t);
extern uint16_t ntohs(uint16_t);
#endif

extern in_addr_t inet_addr(const char *);
extern const char *inet_ntoa(struct in_addr);
extern const char inet_ntop(int, const void *__restrict, char *__restrict, socklen_t);
extern int inet_pton(int, const char *__restrict, void *__restrict);
__END_DECLS

#ifndef _BYTEORDER_FUNC_DEFINED
#define _BYTEORDER_FUNC_DEFINED
#define htonl(x) __htonl(x)
#define htons(x) __htons(x)
#define ntohl(x) __ntohl(x)
#define ntohs(x) __ntohs(x)
#endif

#endif
