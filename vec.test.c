#include <stddef.h>

#include "test.h"
#include "vec.h"

int
test_push(void)
{
	struct mca_vector *v = mca_vector_new(16);

	mca_vector_push(v, (void *)1);
	mca_vector_push(v, (void *)2);
	mca_vector_push(v, (void *)3);

	if (v->len != 3) {
		testf("v->len = %d, expected 3", v->len);
		mca_vector_free(v);
		return TEST_FAIL;
	}

	if (mca_vector_get(v, 0) != (void *)1) {
		testf("v[0] = %d, expected 1", mca_vector_get(v, 0));
		mca_vector_free(v);
		return TEST_FAIL;
	} else if (mca_vector_get(v, 1) != (void *)2) {
		testf("v[1] = %d, expected 2", mca_vector_get(v, 1));
		mca_vector_free(v);
		return TEST_FAIL;
	} else if (mca_vector_get(v, 2) != (void *)3) {
		testf("v[2] = %d, expected 3", mca_vector_get(v, 2));
		mca_vector_free(v);
		return TEST_FAIL;
	}

	mca_vector_free(v);
	return TEST_PASS;
}

int
test_pop(void)
{
	struct mca_vector *v = mca_vector_new(16);

	mca_vector_push(v, (void *)1);
	mca_vector_push(v, (void *)2);
	mca_vector_push(v, (void *)3);

	mca_vector_pop(v, 1);

	if (mca_vector_get(v, 0) != (void *)1) {
		testf("v[0] = %d, expected 1", mca_vector_get(v, 0));
		mca_vector_free(v);
		return TEST_FAIL;
	} else if (mca_vector_get(v, 1) != (void *)3) {
		testf("v[1] = %d, expected 3", mca_vector_get(v, 1));
		mca_vector_free(v);
		return TEST_FAIL;
	}

	mca_vector_pop(v, -1);

	if (v->len != 1) {
		testf("v.len = %d, expected 1", v->len);
		mca_vector_free(v);
		return TEST_FAIL;
	}

	if (mca_vector_get(v, 0) != (void *)1) {
		testf("v[0] = %d, expected 1", mca_vector_get(v, 0));
		mca_vector_free(v);
		return TEST_FAIL;
	}

	mca_vector_free(v);
	return TEST_PASS;
}

struct test tests[] = {
	{"push",	test_push},
	{"pop",		test_pop},
	{0},
};
