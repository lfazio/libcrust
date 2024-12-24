// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#define STR(x) #x
#define EVAL(x) x

#define __CONCAT1(x, y) x##y
#define __STRING(x) #x /* stringify without expanding x */
#define __XSTRING(x) __STRING(x) /* expand x, then stringify */

#ifndef min
#define min(a, b)                       \
	({                              \
		__typeof__(a) _a = (a); \
		__typeof__(b) _b = (b); \
		_a < _b ? _a : _b;      \
	})
#endif

#ifndef max
#define max(a, b)                       \
	({                              \
		__typeof__(a) _a = (a); \
		__typeof__(b) _b = (b); \
		_a > _b ? _a : _b;      \
	})
#endif

#ifndef likely
#define likely(x) __builtin_expect(!!(x), 1)
#endif
#ifndef unlikely
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif
#ifndef __weak
#define __weak __attribute__((__weak__))
#endif
#ifndef __unused
#define __unused __attribute__((__unused__))
#endif
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif
#ifndef __inline
#define __inline inline
#endif
#ifndef __always_inline
#define __always_inline __inline
#endif
#ifndef __volatile
#define __volatile volatile
#endif
#ifndef __aligned_new
#define __aligned(x) __attribute__((__aligned__(x)))
#endif
#ifndef __section
#define __section(x) __attribute__((__section__(x)))
#endif

#ifndef __malloc_like
#define __malloc_like(dtor, idx) __attribute__((malloc, malloc(dtor, idx)))
#endif

#ifndef __has_attribute
#define __has_attribute(x) 0
#endif

#if __has_attribute(__counted_by__)
#define __counted_by(member) __attribute__((__counted_by__(member)))
#else
#define __counted_by(member)
#endif

#define countof(array) (sizeof(array) / sizeof((array)[0]))
