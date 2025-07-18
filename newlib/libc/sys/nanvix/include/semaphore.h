/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <sys/cdefs.h>
#include <sys/time.h>
#include <fcntl.h>

/* Used for performing operations in semaphores. */
typedef unsigned sem_t;

/* Used to indicate that a semaphore operation failed. */
#define SEM_FAILED ((sem_t *)0)

__BEGIN_DECLS
extern int sem_close(sem_t *);
extern int sem_destroy(sem_t *);
extern int sem_getvalue(sem_t *__restrict, int *__restrict);
extern int sem_init(sem_t *, int, unsigned int);
extern sem_t *sem_open(const char *, int, ...);
extern int sem_post(sem_t *);
extern int sem_timedwait(sem_t *__restrict, const struct timespec *__restrict);
extern int sem_trywait(sem_t *);
extern int sem_unlink(const char *);
extern int sem_wait(sem_t *);
__END_DECLS


#endif /* _SEMAPHORE_H */
