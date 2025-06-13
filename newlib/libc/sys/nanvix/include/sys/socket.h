/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _SYS_SOCKET_H_
#define _SYS_SOCKET_H_

#include <machine/align.h>
#include <sys/_types.h>
#include <sys/cdefs.h>

/* Make visible all symbols from the following headers. */
#include <sys/uio.h>

#ifndef _SOCKLEN_T_DECLARED
typedef __socklen_t socklen_t;
#define _SOCKLEN_T_DECLARED
#endif

#ifndef _SA_FAMILY_T_DECLARED
typedef __sa_family_t sa_family_t;
#define _SA_FAMILY_T_DECLARED
#endif

struct sockaddr
{
    unsigned char sa_len;  /* Total length */
    sa_family_t sa_family; /* Address family. */
    char sa_data[14];      /*  Socket address (variable-length data). */
};

#include <sys/_sockaddr_storage.h>

/*
 * Message header for recvmsg() and sendmsg() calls.
 */
struct msghdr
{
    void *msg_name;           /* Optional address. */
    socklen_t msg_namelen;    /* Size of address. */
    struct iovec *msg_iov;    /* Scatter/gather array. */
    int msg_iovlen;           /* Number of members in msg_iov. */
    void *msg_control;        /* Ancillary data. */
    socklen_t msg_controllen; /* Ancillary data buffer len. */
    int msg_flags;            /* Flags on received message. */
};

/*
 * Header for ancillary data objects in msg_control buffer in msghdr structure.
 */
struct cmsghdr
{
    socklen_t cmsg_len; /* Data byte count, including the cmsghdr. */
    int cmsg_level;     /* Originating protocol. */
    int cmsg_type;      /* Protocol-specific type.*/
};

/* Indicates that the data array contains the access rights to be sent or received. */
#define SCM_RIGHTS 0x01

/*
 * If the argument is a pointer to a cmsghdr structure, this macro shall return an unsigned character pointer to the
 * data array associated with the cmsghdr structure.
 */
#define CMSG_DATA(cmsg) ((unsigned char *)(cmsg) + _ALIGN(sizeof(struct cmsghdr)))

/*
 * If the argument is a pointer to a msghdr structure, this macro shall return a pointer to the first cmsghdr structure
 * in the ancillary data associated with this msghdr structure, or a null pointer if either there is no ancillary data
 * associated with the msghdr structure (msg_controllen is zero) or there is insufficient room in the ancillary data for
 * a complete cmsghdr structure (msg_controllen is non-zero but less than sizeof(struct cmsghdr)).
 */
#define CMSG_FIRSTHDR(mhdr)                                                                                            \
    ((mhdr)->msg_controllen >= sizeof(struct cmsghdr) ? (struct cmsghdr *)(mhdr)->msg_control : (struct cmsghdr *)0)

/*
 * If the first argument is a pointer to a msghdr structure and the second argument is a pointer to a cmsghdr structure
 * in the ancillary data pointed to by the msg_control field of that msghdr structure, this macro shall return a pointer
 * to the next cmsghdr structure, or a null pointer if the second argument points to the last cmsghdr and data array
 * pair in the ancillary data. If the ancillary data contains another cmsghdr structure after this one but the cmsg_len
 * value in that structure is such that the data array following that structure would extend beyond the end of the
 * ancillary data, it is unspecified whether this macro returns a pointer to that cmsghdr structure or returns a null
 * pointer.
 */
#define CMSG_NXTHDR(mhdr, cmsg)                                                                                        \
    ((char *)(cmsg) == (char *)0 ? CMSG_FIRSTHDR(mhdr)                                                                 \
     : ((char *)(cmsg) + _ALIGN(((struct cmsghdr *)(cmsg))->cmsg_len) + _ALIGN(sizeof(struct cmsghdr)) >               \
        (char *)(mhdr)->msg_control + (mhdr)->msg_controllen)                                                          \
         ? (struct cmsghdr *)0                                                                                         \
         : (struct cmsghdr *)(void *)((char *)(cmsg) + _ALIGN(((struct cmsghdr *)(cmsg))->cmsg_len)))

/*
 * If the argument has a type such that its value can be assigned to an object of type socklen_t, this macro shall
 * return the space required by an ancillary data object of the specified length and its cmsghdr structure, including
 * any padding needed to satisfy alignment requirements. This macro can be used, for example, to allocate space
 * dynamically for the ancillary data. This macro should not be used to initialize the cmsg_len member of a cmsghdr
 * structure. If the argument is an integer constant expression, this macro shall expand to an integer constant
 * expression.
 * */
#define CMSG_SPACE(l) (_ALIGN(sizeof(struct cmsghdr)) + _ALIGN(l))

/*
 * If the argument has a type such that its value can be assigned to an object of type socklen_t, this macro shall
 * return the value to store in the cmsg_len member of the cmsghdr structure for an ancillary data object of the
 * specified length, taking into account any padding needed to satisfy alignment requirements. If the argument is an
 * integer constant expression, this macro shall expand to an integer constant expression.
 */
#define CMSG_LEN(l) (_ALIGN(sizeof(struct cmsghdr)) + (l))

/*
 * Used for manipulating linger option.
 */
struct linger
{
    int l_onoff;  /* Indicates whether linger option is enabled. */
    int l_linger; /* Linger time, in seconds. */
};

/* Socket types. */
#define SOCK_STREAM 1    /* Byte-stream socket. */
#define SOCK_DGRAM 2     /* Datagram socket. */
#define SOCK_RAW 3       /* Taw-protocol interface. */
#define SOCK_SEQPACKET 5 /* Sequenced-packet socket. */

/* Socket creation flags used in socket(), socketpair() and accept4(). */
#define SOCK_CLOEXEC                                                                                                   \
    0x10000000 /*Create a socket file descriptor with the FD_CLOEXEC flag atomically set on that file descriptor. */
#define SOCK_NONBLOCK                                                                                                  \
    0x20000000 /* Create a socket file descriptor with the O_NONBLOCK flag atomically set on the new open file         \
                  description. */
#define SOCK_CLOFORK                                                                                                   \
    0x40000000 /* Create a socket file descriptor with the FD_CLOFORK flag atomically set on that file descriptor. */

/*
 * Used as the level argument of setsockop() and getsockopt().
 */
#define SOL_SOCKET 0xffff /* options for socket level */

/*
 * Used as the option_name argument of setsockopt() and getsockopt().
 */
#define SO_DEBUG 0x00000001      /* Debugging information is being recorded. */
#define SO_ACCEPTCONN 0x00000002 /* Socket is accepting connections. */
#define SO_REUSEADDR 0x00000004  /* Reuse of local addresses is supported. */
#define SO_KEEPALIVE 0x00000008  /* Connections are kept alive with periodic messages. */
#define SO_DONTROUTE 0x00000010  /* Bypass normal routing. */
#define SO_BROADCAST 0x00000020  /* Transmission of broadcast messages is supported. */
#define SO_LINGER 0x00000080     /* Socket lingers on close. */
#define SO_OOBINLINE 0x00000100  /* Out-of-band data is transmitted in line. */
#define SO_SNDBUF 0x1001         /* Send buffer size. */
#define SO_RCVBUF 0x1002         /* Receive buffer size. */
#define SO_SNDLOWAT 0x1003       /* Send "low water mark". */
#define SO_RCVLOWAT 0x1004       /* Receive "low water mark". */
#define SO_SNDTIMEO 0x1005       /* Send timeout. */
#define SO_RCVTIMEO 0x1006       /* Receive timeout. */
#define SO_ERROR 0x1007          /* Socket error status. */
#define SO_TYPE 0x1008           /* Socket type. */
#define SO_PROTOCOL 0x1016       /* Socket protocol. */
#define SO_DOMAIN 0x1019         /* Socket domain. */

/*
 * The maximum backlog queue length.
 */
#define SOMAXCONN 128

/* Use for the msg_flags in the msghdr structure. */
#define MSG_OOB 0x00000001       /* Out-of-band data. */
#define MSG_PEEK 0x00000002      /* Leave received data in queue. */
#define MSG_DONTROUTE 0x00000004 /* Send without using routing tables.  */
#define MSG_EOR 0x00000008       /* Terminates a record (if supported by the protocol). */
#define MSG_TRUNC 0x00000010     /* Normal data truncated. */
#define MSG_CTRUNC 0x00000020    /* Control data truncated.  */
#define MSG_WAITALL 0x00000040   /* Attempt to fill the read buffer. */
#define MSG_NOSIGNAL                                                                                                   \
    0x00020000 /* No SIGPIPE generated when an attempt to send is made on a stream-oriented socket that is no longer   \
                  connected.  */
#define MSG_CMSG_CLOEXEC                                                                                               \
    0x00040000 /* Atomically set the FD_CLOEXEC flag on any file descriptors created via SCM_RIGHTS during recvmsg().  \
                */
#define MSG_CMSG_CLOFORK                                                                                               \
    0x00080000 /* Atomically set the FD_CLOFORK flag on any file descriptors created via SCM_RIGHTS during recvmsg().  \
                */

/* Address families. */
#define AF_UNSPEC 0 /* Unspecified. */
#define AF_UNIX 1   /* UNIX domain sockets. */
#define AF_INET 2   /* Internet domain sockets for use with IPv4 addresses. */

#if __BSD_VISIBLE
/* Protocol families, same as address families for now. */
#define PF_UNSPEC AF_UNSPEC
#define PF_UNIX PF_LOCAL
#define PF_INET AF_INET
#endif

/* Used as howto arguments in shutdown(). */
#define SHUT_RD 0   /* Disables further receive operations. */
#define SHUT_WR 1   /* Disables further send and receive operations. */
#define SHUT_RDWR 2 /* Disables further send operations. */

__BEGIN_DECLS
extern int accept(int, struct sockaddr *restrict, socklen_t *restrict);
extern int accept4(int, struct sockaddr *restrict, socklen_t *restrict, int);
extern int bind(int, const struct sockaddr *, socklen_t);
extern int connect(int, const struct sockaddr *, socklen_t);
extern int getpeername(int, struct sockaddr *restrict, socklen_t *restrict);
extern int getsockname(int, struct sockaddr *restrict, socklen_t *restrict);
extern int getsockopt(int, int, int, void *restrict, socklen_t *restrict);
extern int listen(int, int);
extern ssize_t recv(int, void *, size_t, int);
extern ssize_t recvfrom(int, void *restrict, size_t, int, struct sockaddr *restrict, socklen_t *restrict);
extern ssize_t recvmsg(int, struct msghdr *, int);
extern ssize_t send(int, const void *, size_t, int);
extern ssize_t sendmsg(int, const struct msghdr *, int);
extern ssize_t sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
extern int setsockopt(int, int, int, const void *, socklen_t);
extern int shutdown(int, int);
extern int sockatmark(int);
extern int socket(int, int, int);
extern int socketpair(int, int, int, int[2]);
__END_DECLS

#endif
