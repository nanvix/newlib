/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _NETINET_IN_H_
#define _NETINET_IN_H_

#include <sys/_types.h>

/* Make visible all symbols from the following headers. */
#include <arpa/inet.h>
#include <inttypes.h>

/* in_addr_t visible from <arpa/inet.h> */

/* in_port_t visible from <arpa/inet.h> */

#ifndef _SA_FAMILY_T_DECLARED
typedef __sa_family_t sa_family_t;
#define _SA_FAMILY_T_DECLARED
#endif

/* in_addr visible from <arpa/inet.h> */

/* socklen_t visible from <arpa/inet.h> */

/* Socket address, internet style. */
struct sockaddr_in
{
    uint8_t sin_len;
    sa_family_t sin_family;
    in_port_t sin_port;
    struct in_addr sin_addr;
    char sin_zero[8];
};

/* Used as values of the level argument of getsockopt() and setsockopt() */
#define IPPROTO_IP 0   /* Internet protocol. */
#define IPPROTO_ICMP 1 /* Control message protocol. */
#define IPPROTO_TCP 6  /* Transmission control protocol. */
#define IPPROTO_UDP 17 /* User datagram protocol. */
#if __POSIX_VISIBLE >= 200112
#define IPPROTO_IPV6 41 /* Internet Protocol Version 6. */
#define IPPROTO_RAW 255 /* Raw IP Packets Protocol. */
#endif

/* Used as a local address in the structure passed to bind(). */
#define INADDR_ANY ((in_addr_t)0x00000000) /* IPv4 wildcard address. */

/* Used as destination address in the structure passed to connect(), sendmsg(), and sendto(). */
#define INADDR_BROADCAST ((in_addr_t)0xffffffff) /* IPv4 broadcast address. */

/* INET_ADDRSTRLEN visible from <arpa/inet.h> */

/* htonl() visible from <arpa/inet.h> */
/* htons() visible from <arpa/inet.h> */
/* ntohl() visible from <arpa/inet.h> */
/* ntohs() visible from <arpa/inet.h> */

#endif /* !_NETINET_IN_H_*/
