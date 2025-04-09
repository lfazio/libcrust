// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/**
 * @brief Option structure to represent an optional value.
 */
struct Option {
	void *ref; /**< Reference to the value */
	bool some; /**< Indicates if the option contains a value */
};

/**
 * @brief Typedef for the Option structure.
 */
typedef struct Option Option_t;

/**
 * @brief Set the Option to contain a value.
 *
 * @param o Pointer to the Option instance.
 * @param ref Pointer to the value to be contained.
 * @return 0 on success, -EINVAL if the Option instance is NULL.
 */
int Option_some(Option_t *o, void *ref);

/**
 * @brief Macro to set the Option to contain a value.
 *
 * @param o Pointer to the Option instance.
 * @param ref Pointer to the value to be contained.
 */
#define Some(o, ref)                      \
	({                                \
		Option_some(&(o), (ref)); \
		o;                        \
	})
/**
 * @brief Check if the Option contains a value.
 *
 * @param o Pointer to the Option instance.
 * @return true if the Option contains a value, false otherwise.
 */
bool Option_is_some(const Option_t *o);

/**
 * @brief Set the Option to contain no value.
 *
 * @param o Pointer to the Option instance.
 * @return 0 on success, -EINVAL if the Option instance is NULL.
 */
int Option_none(Option_t *o);

/**
 * @brief Macro to set the Option to contain no value.
 *
 * @param o Pointer to the Option instance.
 */
#define None(o)                    \
	({                         \
		Option_none(&(o)); \
		o;                 \
	})
/**
 * @brief Check if the Option contains no value.
 *
 * @param o Pointer to the Option instance.
 * @return true if the Option contains no value, false otherwise.
 */
bool Option_is_none(const Option_t *o);

/**
 * @brief Unwrap the Option to get the contained value.
 *
 * @param o Pointer to the Option instance.
 * @return Pointer to the contained value, or NULL if the Option contains no value.
 */
void *Option_unwrap(const Option_t *o);

#ifdef __cplusplus
} // extern "C"
#endif
