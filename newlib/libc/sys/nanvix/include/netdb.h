/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _NETDB_H_
#define _NETDB_H_

#include <sys/_types.h>
#include <sys/cdefs.h>

/* Make visible all symbols from the following headers. */
#include <inttypes.h>
#include <netinet/in.h>
#include <sys/socket.h>

/* socklen_t visible from <netinet/in.h> */

#ifndef _PATH_HEQUIV
#define _PATH_HEQUIV "/etc/hosts.equiv"
#endif
#define _PATH_HOSTS "/etc/hosts"
#define _PATH_NETWORKS "/etc/networks"
#define _PATH_PROTOCOLS "/etc/protocols"
#define _PATH_SERVICES "/etc/services"
#define _PATH_SERVICES_DB "/var/db/services.db"

#define h_errno (*__h_errno())

struct hostent
{
    char *h_name;       /* Official name of the host. */
    char **h_aliases;   /* A pointer to an array of pointers to alternative host names, terminated by a null pointer. */
    int h_addrtype;     /* Host address type. */
    int h_length;       /* Length of address (in bytes). */
    char **h_addr_list; /* A pointer to an array of pointers to network addresses (in network byte order) for the host,
                           terminated by a null pointer. */
};

struct netent
{
    char *n_name; /* Official, fully-qualified (including the domain) name of the host.  */
    char *
        *n_aliases; /* A pointer to an array of pointers to alternative network names, terminated by a null pointer. */
    int n_addrtype; /* The address type of the network. */
    uint32_t n_net; /* The network number, in host byte order. */
};

struct protoent
{
    char *p_name; /* Official name of the protocol. */
    char *
        *p_aliases; /* A pointer to an array of pointers to alternative protocol names, terminated by a null pointer. */
    int p_proto;    /* The protocol number. */
};

struct servent
{
    char *s_name; /* Official name of the service. */
    char *
        *s_aliases; /* A pointer to an array of pointers to alternative service names, terminated by a null pointer. */
    int s_port; /* A value which, when converted to uint16_t, yields the port number in network byte order at which the
                   service resides. */
    char *s_proto; /* The name of the protocol to use when contacting the service. */
};

struct addrinfo
{
    int ai_flags;             /* Input flags. */
    int ai_family;            /* Address family of socket. */
    int ai_socktype;          /* Socket type. */
    int ai_protocol;          /* Protocol of socket. */
    socklen_t ai_addrlen;     /* Length of socket address. */
    char *ai_canonname;       /* Socket address of socket. */
    struct sockaddr *ai_addr; /* Canonical name of service location. */
    struct addrinfo *ai_next; /* Pointer to next in list. */
};

/* Highest reserved Internet port number. */
#define IPPORT_RESERVED 1024

#if __BSD_VISIBLE
/* Error return codes from gethostbyname() and gethostbyaddr() (left in h_errno). */
#define NETDB_INTERNAL -1  /* see errno */
#define NETDB_SUCCESS 0    /* no problem */
#define HOST_NOT_FOUND 1   /* Authoritative Answer Host not found */
#define TRY_AGAIN 2        /* Non-Authoritative Host not found, or SERVERFAIL */
#define NO_RECOVERY 3      /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define NO_DATA 4          /* Valid name, no data record of requested type */
#define NO_ADDRESS NO_DATA /* no address, look for MX record */
#endif

/* Used in the ai_flags field of addrinfo structure. */
#define AI_PASSIVE 0x00000001     /* Socket address is intended for bind(). */
#define AI_CANONNAME 0x00000002   /* Request for canonical name. */
#define AI_NUMERICHOST 0x00000004 /* Return numeric host address as name. */
#define AI_NUMERICSERV 0x00000008 /* Inhibit service name resolution. */
#define AI_ALL 0x00000100         /* Query for both IPv4 and IPv6 addresses. */
#define AI_ADDRCONFIG                                                                                                  \
    0x00000400 /* Query for IPv4 addresses only when an IPv4 address is configured; query for IPv6 addresses only when \
                  an IPv6 address is configured.  */
#define AI_V4MAPPED                                                                                                    \
    0x00000800 /* If no IPv6 addresses are found, query for IPv4 addresses and return them to the caller as            \
                  IPv4-mapped IPv6 addresses. */

/* Used in the flags argument to getnameinfo() */
#define NI_NOFQDN 0x00000001      /* Only the nodename portion of the FQDN is returned for local hosts. */
#define NI_NUMERICHOST 0x00000002 /* The numeric form of the node's address is returned instead of its name. */
#define NI_NAMEREQD 0x00000004    /* Return an error if the node's name cannot be located in the database. */
#define NI_NUMERICSERV 0x00000008 /* The numeric form of the service address is returned instead of its name. */
#define NI_DGRAM 0x00000010       /* Indicates that the service is a datagram service (SOCK_DGRAM). */
#define NI_NUMERICSCOPE                                                                                                \
    0x00000020 /* For IPv6 addresses, the numeric form of the scope identifier is returned instead of its name. */
#define NI_MAXHOST 1025 /* Maximum length of a node name, including the terminating null byte. */
#define NI_MAXSERV 32   /* Maximum length of a service name, including the terminating null byte. */

/* Error values for getaddrinfo() and getnameinfo() */
#define EAI_AGAIN 2    /* The name could not be resolved at this time. Future attempts may succeed. */
#define EAI_BADFLAGS 3 /* The flags had an invalid value. */
#define EAI_FAIL 4     /* A non-recoverable error occurred. */
#define EAI_FAMILY                                                                                                     \
    5 /* The address family was not recognized or the address length was invalid for the specified family. */
#define EAI_MEMORY 6 /* There was a memory allocation failure. */
#define EAI_NONAME                                                                                                     \
    8 /* The name does not resolve for the supplied parameters. NI_NAMEREQD is set and the host's name cannot be       \
         located, or both nodename and servname were null. */
#define EAI_SERVICE 9   /* The service passed was not recognized for the specified socket type. */
#define EAI_SOCKTYPE 10 /* The intended socket type was not recognized. */
#define EAI_SYSTEM 11   /* A system error occurred. The error code can be found in errno. */
#define EAI_OVERFLOW 14 /* An argument buffer overflowed. */

__BEGIN_DECLS
extern void endhostent(void);
extern void endnetent(void);
extern void endprotoent(void);
extern void endservent(void);
#if __BSD_VISIBLE
extern struct hostent *gethostbyaddr(const void *, socklen_t, int);
extern struct hostent *gethostbyname(const char *);
extern int *__h_errno(void);
#endif
extern void freeaddrinfo(struct addrinfo *);
extern const char *gai_strerror(int);
extern int getaddrinfo(const char *restrict, const char *restrict, const struct addrinfo *restrict,
                       struct addrinfo **restrict);
extern struct hostent *gethostent(void);
extern int getnameinfo(const struct sockaddr *restrict, socklen_t, char *restrict, socklen_t, char *restrict, socklen_t,
                       int);
extern struct netent *getnetbyaddr(uint32_t, int);
extern struct netent *getnetbyname(const char *);
extern struct netent *getnetent(void);
extern struct protoent *getprotobyname(const char *);
extern struct protoent *getprotobynumber(int);
extern struct protoent *getprotoent(void);
extern struct servent *getservbyname(const char *, const char *);
extern struct servent *getservbyport(int, const char *);
extern struct servent *getservent(void);
extern void sethostent(int);
extern void setnetent(int);
extern void setprotoent(int);
extern void setservent(int);
__END_DECLS

#endif
