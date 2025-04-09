// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2024 Laurent Fazio <laurent.fazio@gmail.com>

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <cdefs.h>

#include <crust/std/Result.h>

void *Result_unwrap(Result_t *r)
{
	if (Result_is_ok(r))
		return (void *)r->ref;

	return NULL;
}

int Result_unwrap_err(Result_t *r)
{
	if (!r)
		return -EINVAL;

	if (Result_is_err(r))
		return r->err;

	return 0;
}

int Result_ok(Result_t *r, void *ref)
{
	if (!r)
		return -EINVAL;

	r->ok = true;
	r->ref = ref;

	return 0;
}

bool Result_is_ok(const Result_t *r)
{
	if (r && r->ok)
		return true;

	return false;
}

int Result_err(Result_t *r, int err)
{
	if (!r)
		return -EINVAL;

	r->ok = false;
	r->err = err;

	return 0;
}

bool Result_is_err(const Result_t *r)
{
	return !Result_is_ok(r);
}
