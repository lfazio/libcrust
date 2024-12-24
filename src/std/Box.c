// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cdefs.h>

#include <crust/std/Box.h>

struct Box_s {
	void *ref;
	size_t size;
	bool allocated;
};

__malloc_like(Box_drop, 1) Box_t Box_new(void *ref, size_t size)
{
	Box_t box;
	
	if (!size)
		return NULL;

	box = calloc(1, sizeof(struct Box_s));
	if (!box)
		return NULL;

	box->ref = ref;
	if (!ref) {
		box->ref = calloc(1, size);
		if (!box->ref) {
			free(box);

			return NULL;
		}

		box->allocated = true;
	}
	box->size = size;

	return box;
}

void Box_drop(Box_t box)
{
	if (box && box->allocated)
		free(box->ref);

	free(box);
}

ssize_t Box_sizeof(Box_t box)
{
	if (!box)
		return -EINVAL;

	return box->size;
}

void *Box_ref(Box_t box)
{
	if (!box)
		return NULL;

	return box->ref;
}

int Box_display(Box_t box)
{
	if (!box) {
		printf("Box<invalid>");
		return -EINVAL;
	}

	return printf("Box<%p, %ld, %s>", Box_ref(box), Box_sizeof(box),
		      box->allocated ? "true" : "false");
}
