// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

/**
 * @brief Forward declaration of the Box type.
 */
struct Box_s;

/**
 * @brief Typedef for the Box structure.
 */
typedef struct Box_s *Box_t;

/**
 * @brief Create a new Box.
 *
 * @param ref Pointer to the data to be boxed. If NULL, memory will be allocated.
 * @param size Size of the data to be boxed.
 * @return A new Box instance, or NULL on failure.
 */
Box_t Box_new(void *ref, size_t size);

/**
 * @brief Drop (frees) the Box.
 *
 * @param box The Box to be freed.
 */
void Box_drop(Box_t box);

/**
 * @brief Get the size of the data in the Box.
 *
 * @param box The Box instance.
 * @return The size of the data, or -EINVAL if the Box @arg box is NULL.
 */
ssize_t Box_sizeof(Box_t box);

/**
 * @brief Get a reference to the data in the Box.
 *
 * @param box The Box instance.
 * @return A pointer to the data, or NULL if the Box is NULL.
 */
void *Box_ref(Box_t box);

/**
 * @brief Displays the Box information.
 *
 * @param box The Box instance.
 * @return The number of characters printed, or -EINVAL if the Box is NULL.
 */
int Box_display(Box_t box);

/**
 * @brief Macro to downcast the Box reference to a specific type.
 *
 * @param b The Box instance.
 * @param T The type to downcast to.
 * @return A pointer to the data cast to the specified type.
 */
#define Box_downcast(b, T) ((T *)Box_ref(b))

#ifdef __cplusplus
} // extern "C"
#endif