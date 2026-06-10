/*
FUNCTION
<<rpmatch>>---determine whether response to question is affirmative or negative

INDEX
	rpmatch

SYNOPSIS
	#include <stdlib.h>
	int rpmatch(const char *<[response]>);

DESCRIPTION
The <<rpmatch>> function determines whether <[response]> is an affirmative
or negative response to a question according to the current locale.

RETURNS
<<rpmatch>> returns 1 if <[response]> is affirmative, 0 if negative, or -1
if not recognized as either.

PORTABILITY
<<rpmatch>> is a BSD extension also found in glibc.

NOTES
No supporting OS subroutines are required.
*/

/* This code is originally taken from FreeBSD. */
/*-
 * Copyright (c) 2004-2005 Tim J. Robbins.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#include <sys/types.h>

#include <stdlib.h>

#ifndef _NO_REGEX

#include <langinfo.h>
#include <regex.h>

int
rpmatch (const char *response)
{
	regex_t yes, no;
	int ret;

	if (regcomp(&yes, nl_langinfo(YESEXPR), REG_EXTENDED|REG_NOSUB) != 0)
		return (-1);
	if (regcomp(&no, nl_langinfo(NOEXPR), REG_EXTENDED|REG_NOSUB) != 0) {
		regfree(&yes);
		return (-1);
	}
	if (regexec(&yes, response, 0, NULL, 0) == 0)
		ret = 1;
	else if (regexec(&no, response, 0, NULL, 0) == 0)
		ret = 0;
	else
		ret = -1;
	regfree(&yes);
	regfree(&no);
	return (ret);
}

#else /* _NO_REGEX */

/*
 * Targets whose newlib build does not compile the POSIX regex engine
 * (regcomp/regexec/regfree live in newlib/libc/posix, which is omitted on
 * such targets) opt out by defining _NO_REGEX via newlib_cflags in
 * configure.host, in the same style as the existing _NO_SIGPROCMASK /
 * _NO_POPEN / _NO_POSIX_SPAWN opt-outs (see newlib/configure.host).
 *
 * Without the opt-out, rpmatch() would leave an unresolved reference to
 * regcomp/regexec/regfree, which only surfaces when the containing object
 * is force-included (e.g. ld --whole-archive).  Such targets provide only
 * the C/POSIX locale, whose YESEXPR / NOEXPR are "^[yY]" / "^[nN]"; match
 * that directly instead of going through the regex engine.
 */
int
rpmatch (const char *response)
{
	if (response == NULL)
		return (-1);
	switch (response[0]) {
	case 'y':
	case 'Y':
		return (1);
	case 'n':
	case 'N':
		return (0);
	default:
		return (-1);
	}
}

#endif /* _NO_REGEX */
