/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _SYS_POLL_H
#define _SYS_POLL_H

#include <sys/cdefs.h>

/* Make visible all symbols from the following headers. */
#include <signal.h>
#include <time.h>

struct pollfd
{
    int fd;        /* The following descriptor being polled. */
    short events;  /*  The input event flags. */
    short revents; /* The output event flags. */
};

/* Used for the number of file descriptors. */
typedef unsigned int nfds_t;

/* sigset_t  visible from <signal.h> */

/* timespec structure visible from <time.h> */

/* Bitwise flags for use in events or revents in the pollfd structure. */
#define POLLIN 0x0001      /* Data other than high-priority data may be read without blocking. */
#define POLLPRI 0x0002     /* High priority data may be read without blocking. */
#define POLLOUT 0x0004     /* Normal data may be written without blocking. */
#define POLLERR 0x0008     /* An error has occurred (revents only). */
#define POLLHUP 0x0010     /* Device has been disconnected (revents only). */
#define POLLNVAL 0x0020    /* Invalid fd member (revents only). */
#define POLLRDNORM 0x0040  /* Normal data may be read without blocking. */
#define POLLRDBAND 0x0080  /* Priority data may be read without blocking. */
#define POLLWRNORM POLLOUT /* Equivalent to POLLOUT. */
#define POLLWRBAND 0x0100  /* Priority data may be written. */

__BEGIN_DECLS
extern int poll(struct pollfd[], nfds_t, int);
extern int ppoll(struct pollfd[], nfds_t, const struct timespec *__restrict, const sigset_t *__restrict);
__END_DECLS

#endif
