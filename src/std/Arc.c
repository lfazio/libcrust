// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <errno.h>
#if defined(__cplusplus)
/* C++ atomic header */
#include <atomic>
#define atomic_size_t std::atomic<size_t>
#define atomic_bool std::atomic<bool>
#else
#include <stdatomic.h>
#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <cdefs.h>

#include <crust/std/Arc.h>

/**
 * @brief Atomic Reference Counter structure
 */
struct Arc_s {
	/** Number of references */
	atomic_size_t refc;
	/** Spinlock-like protection */
	atomic_bool lock;

	/** Function used to free ptr when refc reaches 0 */
	void (*free)(void *ref);
	/** Protected pointer to user data */
	void *ptr;
};

__malloc_like(Arc_drop, 1) Arc_t Arc_create(void *ptr, void (*free)(void *ref))
{
	Arc_t arc;

	arc = calloc(1, sizeof(struct Arc_s));
	if (!arc)
		return NULL;

	atomic_init(&arc->refc, 1);
	atomic_init(&arc->lock, false);
	arc->free = free;
	arc->ptr = ptr;

	return arc;
}

Arc_t Arc_clone(Arc_t arc)
{
	if (!arc)
		return NULL;

	atomic_fetch_add(&arc->refc, 1);

	return arc;
}

int Arc_lock(Arc_t arc)
{
	bool expected = false;

	if (!arc)
		return -EINVAL;

	while (atomic_compare_exchange_strong(&arc->lock, &expected, true))
		; // Loop until lock is acquired

	return 0;
}

int Arc_unlock(Arc_t arc)
{
	bool expected = true;

	if (!arc)
		return -EINVAL;

	while (atomic_compare_exchange_strong(&arc->lock, &expected, false))
		; // Loop until lock is released

	return 0;
}

void *Arc_ref(Arc_t arc)
{
	if (!arc)
		return NULL;

	return arc->ptr;
}

ssize_t Arc_strong_count(Arc_t arc)
{
	if (!arc)
		return -EINVAL;

	return atomic_load(&arc->refc);
}

void Arc_drop(Arc_t arc)
{
	if (!arc)
		return;

	atomic_fetch_sub(&arc->refc, 1);
	if (!atomic_load(&arc->refc)) {
		if (arc->free)
			arc->free(arc->ptr);

		free(arc);
	}
}

int Arc_display(Arc_t arc)
{
	if (!arc) {
		printf("Arc<invalid>");
		return -EINVAL;
	}

	return printf("Arc<%zd, %p, %slocked>", Arc_strong_count(arc), Arc_ref(arc),
		      atomic_load(&arc->lock) ? "" : "un");
}
