// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Stringify a macro argument.
 */
#define STR(x) #x

/**
 * @brief Evaluate a macro argument.
 */
#define EVAL(x) x

/**
 * @brief Concatenate two tokens.
 */
#define __CONCAT1(x, y) x##y

/**
 * @brief Stringify a macro argument without expanding it.
 */
#define __STRING(x) #x

/**
 * @brief Expand a macro argument, then stringify it.
 */
#define __XSTRING(x) __STRING(x)

#ifndef min
/**
 * @brief Get the minimum of two values.
 */
#define min(a, b)                       \
	({                              \
		__typeof__(a) _a = (a); \
		__typeof__(b) _b = (b); \
		_a < _b ? _a : _b;      \
	})
#endif

#ifndef max
/**
 * @brief Get the maximum of two values.
 */
#define max(a, b)                       \
	({                              \
		__typeof__(a) _a = (a); \
		__typeof__(b) _b = (b); \
		_a > _b ? _a : _b;      \
	})
#endif

#ifndef likely
/**
 * @brief Hint that an expression is likely to be true.
 */
#define likely(x) __builtin_expect(!!(x), 1)
#endif

#ifndef unlikely
/**
 * @brief Hint that an expression is unlikely to be true.
 */
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif

#ifndef __weak
/**
 * @brief Define a weak symbol.
 */
#define __weak __attribute__((__weak__))
#endif

#ifndef __unused
/**
 * @brief Mark a variable or function as unused.
 */
#define __unused __attribute__((__unused__))
#endif

#ifndef __packed
/**
 * @brief Pack a structure to minimize memory usage.
 */
#define __packed __attribute__((__packed__))
#endif

#ifndef __inline
/**
 * @brief Define an inline function.
 */
#define __inline inline
#endif

#ifndef __always_inline
/**
 * @brief Define a function that is always inlined.
 */
#define __always_inline __inline
#endif

#ifndef __volatile
/**
 * @brief Define a volatile variable.
 */
#define __volatile volatile
#endif

#ifndef __aligned
/**
 * @brief Align a variable or structure to a specified boundary.
 */
#define __aligned(x) __attribute__((__aligned__(x)))
#endif

#ifndef __section
/**
 * @brief Place a variable or function in a specified section.
 */
#define __section(x) __attribute__((__section__(x)))
#endif

#ifndef __malloc_like
/**
 * @brief Mark a function as malloc-like, indicating it returns a pointer to allocated memory.
 */
#define __malloc_like(dtor, idx) __attribute__((malloc, malloc(dtor, idx)))
#endif

#ifndef __has_attribute
/**
 * @brief Check if an attribute is supported.
 */
#define __has_attribute(x) 0
#endif

#if __has_attribute(__counted_by__)
#define __counted_by(member) __attribute__((__counted_by__(member)))
#else
#define __counted_by(member)
#endif

#define countof(array) (sizeof(array) / sizeof((array)[0]))

#ifdef __cplusplus
} // extern "C"
#endif