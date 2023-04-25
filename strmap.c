/* This file is a part of libmca, where code you would've written anyway lives.
 *    https://github.com/mca3/libmca * https://int21h.xyz/projects/libmca
 *
 * Copyright (c) 2023 mca
 * 
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with  or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define _XOPEN_SOURCE 500

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "strmap.h"

/* mca_strmap_new creates a new instance of mca_strmap.
 *
 * On error, NULL is returned.
 */
struct mca_strmap *
mca_strmap_new(void)
{
	struct mca_strmap *sm = NULL;

	if ((sm = malloc(sizeof(*sm))) == NULL)
		return NULL;

	memset(sm, 0, sizeof(*sm));
	return sm;
}

/* mca_strmap_get finds the entry for a key and returns the value.
 *
 * If the key was not found, NULL is returned.
 */
void *
mca_strmap_get(struct mca_strmap *sm, char *key)
{
	for (sm; sm != NULL; sm = sm->next) {
		if (sm->key && strcmp(sm->key, key) == 0)
			return sm->val;
	}

	return NULL;
}

/* mca_strmap_set sets a key in an mca_strmap to val.
 *
 * It is an error to pass NULL as val.
 *
 * If there is a hole in the strmap, then the hole is filled. If the key
 * already exists, then the value will be overwritten.
 *
 * If ret is not NULL, then if a value is overwritten, the old value that would
 * be overwritten will be placed in ret.
 * If a value was not overwritten, the value of ret is untouched.
 *
 * On error, -1 is returned.
 */
int
mca_strmap_set(struct mca_strmap *sm, char *key, void *val, void **ret)
{
	/* This is likely not very efficient. */
	assert(val != NULL);

	struct mca_strmap *k = sm, *hole = NULL;
	int attach = 0, found = 0;

	// Look for a hole or for an exact match.
	for (k = sm; k != NULL; k = k->next) {
		if (!hole && k->key == NULL)
			hole = k;
		else if (k->key && strcmp(k->key, key) == 0) {
			found = 1;
			break;
		}
	}

	// Use the hole if we found one and we did not find an exact match.
	if (hole && !found)
		k = hole;

	if (!k) {
		// Need to allocate new one.
		if (!(k = mca_strmap_new()))
			return -1;

		attach = 1;
	}

	// Set new values.
	if (!found) // Reuse existing.
		k->key = strdup(key);

	// Place the old value, if possible.
	if (ret)
		*ret = k->val;

	k->val = val;

	if (attach) {
		// Attach this one to the end.
		for (sm; sm->next != NULL; sm = sm->next)
			;
		sm->next = k;
	}

	return 1;
}

/* mca_strmap_del removes an entry for key in the strmap.
 *
 * The return value will be the value of the key that is being deleted, or NULL
 * if the key was not found.
 */
void *
mca_strmap_del(struct mca_strmap *sm, char *key)
{
	for (sm; sm != NULL; sm = sm->next) {
		if (!sm->key) continue;
		else if (strcmp(sm->key, key) == 0) {
			free(sm->key);
			sm->key = NULL;
			return sm->val;
		}
	}

	return NULL;
}

/* mca_strmap_free frees the entries on the strmap and the strmap itself.
 *
 * The values pointed to by each entry is not freed.
 * It is recommended that if each value needs to be printed, to do so first
 * using the mca_strmap_foreach macro.
 */
void
mca_strmap_free(struct mca_strmap *sm)
{
	if (sm->next)
		mca_strmap_free(sm->next);

	free(sm->key);
	free(sm);
}
