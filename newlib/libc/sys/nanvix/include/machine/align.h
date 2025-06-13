/*
 * Copyright(c) The Maintainers of Nanvix.
 * Licensed under the MIT License.
 */

#ifndef _MACHINE__ALIGN_H_
#define _MACHINE__ALIGN_H_

#define _ALIGNBYTES (sizeof(long long) - 1UL)

#define _ALIGN(_p) (((unsigned long)(_p) + _ALIGNBYTES) & ~_ALIGNBYTES)

#endif /* !_MACHINE__ALIGN_H_ */
