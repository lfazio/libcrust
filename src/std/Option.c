// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <cdefs.h>

#include <crust/std/Option.h>

void * Option_unwrap(const Option_t *o)
{
	if (Option_is_none(o))
		return NULL;

	return o->ref;
}

int Option_some(Option_t *o, void *ref)
{
	if (!o)
		return -EINVAL;

	o->some = true;
	o->ref = ref;

	return 0;
}

bool Option_is_some(const Option_t *o)
{
	if (o && o->some)
		return true;

	return false;
}

int Option_none(Option_t *o)
{
	if (!o)
		return -EINVAL;

	o->some = false;

	return 0;
}

bool Option_is_none(const Option_t *o)
{
	if (!o || !o->some)
		return true;

	return false;
}
