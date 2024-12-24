// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <errno.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#include <cdefs.h>

#include <crust/std/Rc.h>

/**
 * @brief Reference counter
 */
struct Rc_s {
	/** Number of references */
	size_t refc;
	/** Spinlock-like protection */
	bool lock;

	/** Function used to free ptr when refc reaches 0 */
	void (*free)(void *ref);
	/** Protected pointer to user data */
	void *ptr;
};

__malloc_like(Rc_drop, 1) Rc_t Rc_create(void *ptr, void (*free)(void *ref))
{
	Rc_t rc;

	rc = calloc(1, sizeof(struct Rc_s));
	if (!rc)
		return NULL;

	rc->refc = 1;
	rc->lock = false;
	rc->free = free;
	rc->ptr = ptr;

	return rc;
}

Rc_t Rc_clone(Rc_t rc)
{
	if (!rc)
		return NULL;

	rc->refc += 1;

	return rc;
}

int Rc_lock(Rc_t rc)
{
	if (!rc)
		return -EINVAL;

	while (rc->lock)
		; /* loop until unlocked */
	
	rc->lock = true;

	return 0;
}

int Rc_unlock(Rc_t rc)
{
	if (!rc)
		return -EINVAL;

	rc->lock = false;

	return 0;
}

void *Rc_ref(Rc_t rc)
{
	if (!rc)
		return NULL;

	return rc->ptr;
}

ssize_t Rc_strong_count(Rc_t rc)
{
	if (!rc)
		return -EINVAL;

	return rc->refc;
}

void Rc_drop(Rc_t rc)
{
	if (!rc)
		return;

	rc->refc -= 1;
	if (!rc->refc) {
		if (rc->free)
			rc->free(rc->ptr);

		free(rc);
	}
}

int Rc_display(Rc_t rc)
{
	if (!rc) {
		printf("Rc<invalid>");
		return -EINVAL;
	}

	return printf("Rc<%zd, %p, %slocked>", Rc_strong_count(rc), Rc_ref(rc),
		      rc->lock ? "" : "un");
}
