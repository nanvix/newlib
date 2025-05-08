/* sys/utmp.h

   This software is a copyrighted work licensed under the terms of the
   Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
   details. */

#ifndef UTMP_H
#define UTMP_H

#include <paths.h>
#include <sys/types.h>
#include <time.h>

#define WTMP_FILE "/etc/wtmp"

#ifdef __cplusplus
extern "C" {
#endif

#define UT_LINESIZE 16
#define UT_NAMESIZE 16
#define UT_HOSTSIZE 256
#define UT_IDLEN 2

#define RUN_LVL 1
#define BOOT_TIME 2
#define NEW_TIME 3
#define OLD_TIME 4

#define INIT_PROCESS 5
#define LOGIN_PROCESS 6
#define USER_PROCESS 7
#define DEAD_PROCESS 8

#ifdef __cplusplus
}
#endif

#define UTMP_FILE "/etc/utmp"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ut_name
#define ut_name ut_user
#endif

#if __GNUC__ >= 8
#define ATTRIBUTE_NONSTRING __attribute__((nonstring))
#else
#define ATTRIBUTE_NONSTRING
#endif

struct utmp {
    short ut_type;
    pid_t ut_pid;
    char ut_line[UT_LINESIZE] ATTRIBUTE_NONSTRING;
    char ut_id[UT_IDLEN];
    time_t ut_time;
    char ut_user[UT_NAMESIZE] ATTRIBUTE_NONSTRING;
    char ut_host[UT_HOSTSIZE] ATTRIBUTE_NONSTRING;
    long ut_addr;
};

extern struct utmp *getutent(void);
extern struct utmp *getutid(struct utmp *);
extern struct utmp *getutline(struct utmp *);
extern struct utmp *pututline(const struct utmp *);
extern void endutent(void);
extern void setutent(void);
extern void utmpname(const char *);

void login(const struct utmp *);
int logout(const char *);
int login_tty(int);
void updwtmp(const char *, const struct utmp *);
void logwtmp(const char *, const char *, const char *);

#ifdef __cplusplus
}
#endif
#endif /* UTMP_H */
