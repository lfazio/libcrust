// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/**
 * @brief Result structure to represent a value that can either be a success or an error.
 */
struct Result {
	union {
		void *ref; /**< Reference to the value if the result is successful */
		int err; /**< Error code if the result is an error */
	};
	bool ok; /**< Indicates if the result is successful */
};

/**
 * @brief Typedef for the Result structure.
 */
typedef struct Result Result_t;

/**
 * @brief Sets the Result to be successful with a value.
 *
 * @param r Pointer to the Result instance.
 * @param ref Pointer to the value to be contained.
 * @return 0 on success, -EINVAL if the Result instance is NULL.
 */
int Result_ok(Result_t *r, void *ref);

/**
 * @brief Macro to set the Result to be successful with a value.
 *
 * @param r Pointer to the Result instance.
 * @param ref Pointer to the value to be contained.
 */
#define Ok(r, ref) Result_ok((r), (ref))

/**
 * @brief Check if the Result is successful.
 *
 * @param r Pointer to the Result instance.
 * @return true if the Result is successful, false otherwise.
 */
bool Result_is_ok(Result_t *r);

/**
 * @brief Set the Result to be an error with an error code.
 *
 * @param r Pointer to the Result instance.
 * @param err Error code to be contained.
 * @return 0 on success, -EINVAL if the Result instance is NULL.
 */
int Result_err(Result_t *r, int err);

/**
 * @brief Macro to set the Result to be an error with an error code.
 *
 * @param r Pointer to the Result instance.
 * @param err Error code to be contained.
 */
#define Err(r, err) Result_err((r), (err))

/**
 * @brief Check if the Result is an error.
 *
 * @param r Pointer to the Result instance.
 * @return true if the Result is an error, false otherwise.
 */
bool Result_is_err(Result_t *r);

/**
 * @brief Unwrap the Result to get the contained value if successful.
 *
 * @param r Pointer to the Result instance.
 * @return Pointer to the contained value, or NULL if the Result is an error.
 */
void *Result_unwrap(Result_t *r);

/**
 * @brief Unwrap the Result to get the contained error code if an error.
 *
 * @param r Pointer to the Result instance.
 * @return The contained error code, or -EINVAL if the Result is NULL or successful.
 */
int Result_unwrap_err(Result_t *r);

#ifdef __cplusplus
} // extern "C"
#endif