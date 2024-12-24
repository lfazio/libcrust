// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

/** Forward declaration */
struct Rc_s;

/** Reference Counter type */
typedef struct Rc_s *Rc_t;

/**
 * @brief Create a new reference counter that can handle
 * a reference to a pointer.
 *
 * @param[in,nullable] ptr Pointer to user data
 * @param[in,nullable] free Function to free @arg ptr if provided.
 *
 * @return the newly created reference counter, NULL if impossible.
 */
Rc_t Rc_create(void *ptr, void (*free)(void *ref));

/**
 * @def Rc_new(ptr)
 * @brief Create a new reference counter with no free() function provided.
 *
 * @param[in,nullable] ptr Pointer to user data
 *
 * @return the newly created reference counter, NULL if impossible.
 */
#define Rc_new(ptr) Rc_create(ptr, NULL)

/**
 * @brief Acquire a lock on the reference counter, the user is responsible to
 * lock/unlock before any access to @arg rc.
 *
 * @param[in] rc The reference counter to use
 *
 * @return 0 if successful
 * @return -EINVAL if rc is NULL
 */
int Rc_lock(Rc_t rc);

/**
 * @brief Release a lock on the reference counter, the user is responsible to
 * lock/unlock before any access to @arg rc.
 *
 * @param[in] rc The reference counter to use
 *
 * @return 0 if successful
 * @return -EINVAL if rc is NULL
 */
int Rc_unlock(Rc_t rc);

/**
 * @brief Access to the protected user pointer, and cast it to @arg T type.
 *
 * @param[in] rc The reference counter to use
 *
 * @return The user pointer protected by the reference counter @arg rc
 * @return NULL if rc is invalid
 */
void *Rc_ref(Rc_t rc);

/**
 * @def Rc_downcast(rc, T)
 * @brief Access to the protected user pointer, and cast it to @arg T type.
 *
 * @param[in] rc The reference counter to use
 * @param[in] T The type to cast auto
 *
 * @return The user pointer protected by the reference counter @arg rc
 * @return NULL if rc is invalid
 */
#define Rc_downcast(rc, T) ((T *)Rc_ref(rc))

/**
 * @brief Clone a reference counter, this means that the counter is incremented
 * each time Rc_clone() is used.
 *
 * @param[in] rc The reference counter to clone
 *
 * @return The user pointer protected by the reference counter @arg rc
 * @return NULL if rc is invalid
 */
Rc_t Rc_clone(Rc_t rc);

/**
 * @brief Get the number of references to the reference counter @arg rc
 *
 * @param[in] rc The reference counter to get info from
 *
 * @return The number of references to @arg rc
 * @return -EINVAL if rc is invalid
 */
ssize_t Rc_strong_count(Rc_t rc);

/**
 * @brief Drop a reference to the @arg rc. When the number of reference
 * reach 0, use free() function is not NULL.
 *
 * @param[in] rc The reference counter to use
 */
void Rc_drop(Rc_t rc);

/**
 * @brief Display the @arg rc for trace purpose
 *
 * @note Use printf internally.
 *
 * @param[in] rc The reference counter to use
 */
int Rc_display(Rc_t rc);

#ifdef __cplusplus
} // extern "C"
#endif