/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _SYS_RESOURCE_H_
#define _SYS_RESOURCE_H_

#include <sys/cdefs.h>
#include <sys/features.h>

/* May also make visible all symbols from the following headers. */
#include <sys/time.h>

#if __XSI_VISIBLE

/* Make visible struct timeval */
#include <sys/_timeval.h>

/* Make visible __id_t */
#include <sys/_types.h>

#ifndef _ID_T_DECLARED
typedef __id_t id_t;
#define _ID_T_DECLARED
#endif

#endif

#if __XSI_VISIBLE
/* Used as arguments for getpriority() and setpriority() */
#define PRIO_PROCESS 0 /* Identifies the who argument as a process ID. */
#define PRIO_PGRP 1    /* Identifies the who argument as a process group ID. */
#define PRIO_USER 2    /* Identifies the who argument as a user ID. */
#endif

/* Used as arguments for getrlimit() and setrlimit() */
#define RLIMIT_CORE 0 /* Limit on size of core image. */
#ifndef __XSI_VISIBLE
#define RLIMIT_CPU 1 /* Limit on CPU time per process. */
#endif
#define RLIMIT_FSIZE 2  /* Limit on file size. */
#define RLIMIT_DATA 3   /* Limit on data segment size. */
#define RLIMIT_STACK 4  /* Limit on stack size. */
#define RLIMIT_CORE 5   /* max core file size */
#define RLIMIT_NOFILE 6 /* Limit on number of open files. */
#define RLIMIT_AS 7     /* Limit on address space size. */

#define RLIM_INFINITY (~0UL)         /* A value of rlim_t indicating no limit. */
#define RLIM_SAVED_MAX RLIM_INFINITY /* A value of type rlim_t indicating an unrepresentable saved hard limit. */
#define RLIM_SAVED_CUR RLIM_INFINITY /* A value of type rlim_t indicating an unrepresentable saved soft limit.*/

/* Used for limit values. */
typedef unsigned long rlim_t;

struct rlimit
{
    rlim_t rlim_cur; /* The current (soft) limit. */
    rlim_t rlim_max; /* The hard limit. */
};

/* Used as arguments for getrusage() */
#ifdef __XSI_VISIBLE
#define RUSAGE_SELF 0      /* Returns information about the current process. */
#define RUSAGE_CHILDREN -1 /* Returns information about children of the current process. */
#endif

#if __XSI_VISIBLE
struct rusage
{
    struct timeval ru_utime; /* User time used. */
    struct timeval ru_stime; /* System time used. */
};
#endif

__BEGIN_DECLS
extern int getrlimit(int __resource, struct rlimit *__rlp);
extern int setrlimit(int __resource, const struct rlimit *__rlp);

#if __XSI_VISIBLE
extern int getrusage(int __who, struct rusage *__rusage);

extern int getpriority(int which, id_t who);
extern int setpriority(int which, id_t who, int value);
#endif
__END_DECLS

#endif
