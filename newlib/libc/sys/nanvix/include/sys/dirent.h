/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _SYS_DIRENT_H_
#define _SYS_DIRENT_H_

#include <sys/_types.h>
#include <sys/cdefs.h>
#include <sys/syslimits.h>

#ifndef _INO_T_DECLARED
typedef __ino_t ino_t;
#define _INO_T_DECLARED
#endif

#ifndef _SSIZE_T_DECLARED
typedef _ssize_t ssize_t;
#define _SSIZE_T_DECLARED
#endif

#ifndef _RECLEN_T_DECLARED
typedef __reclen_t reclen_t;
#define _RECLEN_T_DECLARED
#endif

typedef struct _dirdesc
{
    int dd_fd;
    long dd_loc;
    long dd_size;
    char *dd_buf;
    int dd_len;
    long dd_seek;
} DIR;

struct dirent
{
    ino_t d_ino;               /* File serial number. */
    char d_name[NAME_MAX + 1]; /*Filename string of entry. */
};

struct posix_dent
{
    ino_t d_ino;               /* File serial number. */
    reclen_t d_reclen;         /* Length of this entry, including trailing padding if necessary. See posix_getdents().*/
    unsigned char d_type;      /* File type or unknown-file-type indication. */
    char d_name[NAME_MAX + 1]; /* Filename string of entry. */
};

/*
 * File types
 */
#define DT_UNKNOWN 0 /* Unknown file type. */
#define DT_FIFO 1    /* FIFO special. */
#define DT_CHR 2     /* Character special. */
#define DT_DIR 4     /* Directory. */
#define DT_BLK 6     /* Block special. */
#define DT_REG 8     /* Regular. */
#define DT_LNK 10    /* Symbolic link. */
#define DT_SOCK 12   /* Socket. */
#define DT_MQ 13     /* Message queue. */
#define DT_SEM 14    /* Semaphore. */
#define DT_SHM 15    /* Shared memory object. */

__BEGIN_DECLS
extern int alphasort(const struct dirent **, const struct dirent **);
extern int closedir(DIR *);
extern int dirfd(DIR *);
extern DIR *fdopendir(int);
extern DIR *opendir(const char *);
extern ssize_t posix_getdents(int, void *, size_t, int);
extern struct dirent *readdir(DIR *);
extern void rewinddir(DIR *);
extern int scandir(const char *, struct dirent ***, int (*)(const struct dirent *), int (*)(const struct dirent **, const struct dirent **));
#if __XSI_VISIBLE
extern void seekdir(DIR *, long);
extern long telldir(DIR *);
#endif
__END_DECLS

#endif
