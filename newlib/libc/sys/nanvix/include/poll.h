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
#define POLLIN 1           /* Data other than high-priority data may be read without blocking. */
#define POLLPRI 2          /* High priority data may be read without blocking. */
#define POLLOUT 4          /* Normal data may be written without blocking. */
#define POLLERR 8          /* An error has occurred (revents only). */
#define POLLHUP 16         /* Device has been disconnected (revents only). */
#define POLLNVAL 32        /* Invalid fd member (revents only). */
#define POLLRDNORM POLLIN  /* Normal data may be read without blocking. */
#define POLLRDBAND POLLPRI /* Priority data may be read without blocking. */
#define POLLWRNORM POLLOUT /* Equivalent to POLLOUT. */
#define POLLWRBAND POLLOUT /* Priority data may be written. */

__BEGIN_DECLS
extern int poll(struct pollfd[], nfds_t, int);
extern int ppoll(struct pollfd[], nfds_t, const struct timespec *restrict, const sigset_t *restrict);
__END_DECLS

#endif
