// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

struct Arc_s;

/** Atomic Reference Counter type */
typedef struct Arc_s *Arc_t;

/**
 * @brief Create a new reference counter that can handle
 * a reference to a pointer.
 *
 * @param[in,nullable] ptr Pointer to user data
 * @param[in,nullable] free Function to free @arg ptr if provided.
 *
 * @return the newly created reference counter, NULL if impossible.
 */
Arc_t Arc_create(void *ptr, void (*free)(void *ref));

/**
 * @def Arc_new(ptr)
 * @brief Create a new reference counter with no free() function provided.
 *
 * @param[in,nullable] ptr Pointer to user data
 *
 * @return the newly created reference counter, NULL if impossible.
 */
#define Arc_new(ptr) Arc_create(ptr, NULL)

/**
 * @brief Acquire a lock on the reference counter, the user is responsible to
 * lock/unlock before any access to @arg arc.
 *
 * @param[in] arc The reference counter to use
 *
 * @return 0 if successful
 * @return -EINVAL if arc is NULL
 */
int Arc_lock(Arc_t arc);

/**
 * @brief Release a lock on the reference counter, the user is responsible to
 * lock/unlock before any access to @arg arc.
 *
 * @param[in] arc The reference counter to use
 *
 * @return 0 if successful
 * @return -EINVAL if arc is NULL
 */
int Arc_unlock(Arc_t arc);

/**
 * @brief Release a lock on the reference counter, the user is responsible to
 * lock/unlock before any access to @arg arc.
 *
 * @param[in] arc The reference counter to use
 *
 * @return The user pointer protected by the reference counter @arg arc
 * @return NULL if arc is invalid
 */
void *Arc_ref(Arc_t arc);

/**
 * @def Arc_downcast(rc, T)
 * @brief Access to the protected user pointer, and cast it to @arg T type.
 *
 * @param[in] arc The reference counter to use
 * @param[in] T The type to cast auto
 *
 * @return The user pointer protected by the reference counter @arg arc
 * @return NULL if arc is invalid
 */
#define Arc_downcast(rc, T) ((T *)Arc_ref(rc))

/**
 * @brief Clone a reference counter, this means that the counter is incremented
 * each time Arc_clone() is used.
 *
 * @param[in] arc The reference counter to clone
 *
 * @return The user pointer protected by the reference counter @arg arc
 * @return NULL if arc is invalid
 */
Arc_t Arc_clone(Arc_t arc);

/**
 * @brief Get the number of references to the reference counter @arg arc
 *
 * @param[in] arc The reference counter to get info from
 *
 * @return The number of references to @arg arc
 * @return -EINVAL if arc is invalid
 */
ssize_t Arc_strong_count(Arc_t arc);

/**
 * @brief Drop a reference to the @arg arc. When the number of reference
 * reach 0, use free() function is not NULL.
 *
 * @param[in] arc The reference counter to use
 */
void Arc_drop(Arc_t arc);

/**
 * @brief Display the @arg arc for trace purpose
 *
 * @note Use printf internally.
 *
 * @param[in] arc The reference counter to use
 */
int Arc_display(Arc_t arc);

#ifdef __cplusplus
} // extern "C"
#endif