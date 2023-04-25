#include <stddef.h>

#include "strmap.h"
#include "test.h"

int
test_add(void)
{
	int a = 1, b = 2, c = 3;
	struct mca_strmap *sm = mca_strmap_new();

	mca_strmap_set(sm, "test", &a, NULL);
	mca_strmap_set(sm, "test2", &b, NULL);
	mca_strmap_set(sm, "test3", &c, NULL);

	if (mca_strmap_get(sm, "test") == &a &&
			mca_strmap_get(sm, "test2") == &b &&
			mca_strmap_get(sm, "test3") == &c) {
		mca_strmap_free(sm);
		return TEST_PASS;
	}

	mca_strmap_free(sm);
	return TEST_FAIL;
}

int
test_del(void)
{
	int a = 1, b = 2, c = 3;
	struct mca_strmap *sm = mca_strmap_new();

	mca_strmap_set(sm, "test", &a, NULL);
	mca_strmap_set(sm, "test2", &b, NULL);
	mca_strmap_set(sm, "test3", &c, NULL);

	mca_strmap_del(sm, "test2");
	mca_strmap_del(sm, "test");

	if (mca_strmap_get(sm, "test") != NULL || mca_strmap_get(sm, "test2") != NULL) {
		mca_strmap_free(sm);
		testf("test and test2 are still keys");
		return TEST_FAIL;
	}

	mca_strmap_set(sm, "test2", &b, NULL);
	mca_strmap_set(sm, "test3", &c, NULL);

	mca_strmap_del(sm, "test");

	if (mca_strmap_get(sm, "test") != NULL) {
		mca_strmap_free(sm);
		testf("test is still a key");
		return TEST_FAIL;
	}

	mca_strmap_free(sm);
	return TEST_PASS;
}

int
test_overwrite(void)
{
	int a = 1, b = 2, c = 3, *d;
	struct mca_strmap *sm = mca_strmap_new();

	mca_strmap_set(sm, "test", &a, NULL);
	mca_strmap_set(sm, "test2", &b, NULL);
	mca_strmap_set(sm, "test3", &c, NULL);
	mca_strmap_set(sm, "test2", &a, NULL);
	mca_strmap_set(sm, "test", &c, (void**)&d);

	if (mca_strmap_get(sm, "test") == &c &&
			mca_strmap_get(sm, "test2") == &a &&
			mca_strmap_get(sm, "test3") == &c &&
			d == &a) {
		mca_strmap_free(sm);
		return TEST_PASS;
	}

	mca_strmap_free(sm);
	return TEST_FAIL;
}

struct test tests[] = {
	{"add",		test_add},
	{"delete",	test_del},
	{"overwrite",	test_overwrite},
	{0},
};
