/* This file is a part of libmca, where code you would've written anyway lives.
 *   https://github.com/mca3/libmca * https://int21h.xyz/projects/libmca.html
 *
 * Copyright (c) 2023 mca
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
