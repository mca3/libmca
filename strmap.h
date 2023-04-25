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

#ifndef LIBMCA_STRMAP_H
#define LIBMCA_STRMAP_H
struct mca_strmap {
	char *key;
	void *val;

	struct mca_strmap *next;
};

struct mca_strmap *mca_strmap_new(void);
void *mca_strmap_get(struct mca_strmap *sm, char *key);
int mca_strmap_set(struct mca_strmap *sm, char *key, void *val, void **ret);
void *mca_strmap_del(struct mca_strmap *sm, char *key);
void mca_strmap_free(struct mca_strmap *sm);

#define mca_strmap_foreach(sm, name) \
	for (struct mca_strmap *name = sm; name != NULL; name = name->next) \
		if (!(name)->key) continue; \
		else

#endif
