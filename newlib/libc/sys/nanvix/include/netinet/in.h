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

/*
 * IPv6 address
 */
struct in6_addr
{
    union {
        uint8_t __u6_addr8[16];
        uint16_t __u6_addr16[8];
        uint32_t __u6_addr32[4];
    } __u6_addr; /* 128-bit IP6 address */
};

#define s6_addr __u6_addr.__u6_addr8

/*
 * Socket address for IPv6.
 */
struct sockaddr_in6
{
    uint8_t sin6_len;          /* length of this struct */
    sa_family_t sin6_family;   /* AF_INET6 */
    in_port_t sin6_port;       /* Transport layer port # */
    uint32_t sin6_flowinfo;    /* IP6 flow information */
    struct in6_addr sin6_addr; /* IP6 address */
    uint32_t sin6_scope_id;    /* scope zone index */
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

/*
 * Used as a local address in the structure passed to bind() when the socket is
 * bound to the loopback interface.
 */
#if __BSD_VISIBLE
#define INADDR_LOOPBACK ((in_addr_t)0x7f000001) /* IPv4 loopback address. */
#endif /* __BSD_VISIBLE */

/* INET_ADDRSTRLEN visible from <arpa/inet.h> */

/* Length of the string from for IPv6 */
#define INET6_ADDRSTRLEN 46

/*
 * Unspecified IPv6 address.
 */
#define IN6_IS_ADDR_UNSPECIFIED(a)                                                                                     \
    ((a)->__u6_addr.__u6_addr32[0] == 0 && (a)->__u6_addr.__u6_addr32[1] == 0 && (a)->__u6_addr.__u6_addr32[2] == 0 && \
     (a)->__u6_addr.__u6_addr32[3] == 0)

/*
 * Loopback IPv6 address.
 */
#define IN6_IS_ADDR_LOOPBACK(a)                                                                                        \
    ((a)->__u6_addr.__u6_addr32[0] == 0 && (a)->__u6_addr.__u6_addr32[1] == 0 && (a)->__u6_addr.__u6_addr32[2] == 0 && \
     (a)->__u6_addr.__u6_addr32[3] == ntohl(1))

/*
 * IPv4 compatible address.
 */
#define IN6_IS_ADDR_V4COMPAT(a)                                                                                        \
    ((a)->__u6_addr.__u6_addr32[0] == 0 && (a)->__u6_addr.__u6_addr32[1] == 0 && (a)->__u6_addr.__u6_addr32[2] == 0 && \
     (a)->__u6_addr.__u6_addr32[3] != 0 && (a)->__u6_addr.__u6_addr32[3] != ntohl(1))

/*
 * IPv4 mapped address.
 */
#define IN6_IS_ADDR_V4MAPPED(a)                                                                                        \
    ((a)->__u6_addr.__u6_addr32[0] == 0 && (a)->__u6_addr.__u6_addr32[1] == 0 &&                                       \
     (a)->__u6_addr.__u6_addr32[2] == ntohl(0x0000ffff))

/* htonl() visible from <arpa/inet.h> */
/* htons() visible from <arpa/inet.h> */
/* ntohl() visible from <arpa/inet.h> */
/* ntohs() visible from <arpa/inet.h> */

#endif /* !_NETINET_IN_H_*/
