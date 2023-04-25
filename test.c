#include <stdio.h>
#include <stdarg.h>

#include "test.h"

int tests_passed = 0;
int tests_failed = 0;
int tests_skipped = 0;

void
testf(const char *fmt, ...)
{
	/* TODO: write to buffer. write out on fail */

	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
}

int
main(int argc, char *argv[])
{
	struct test *t;

	for (t = tests; t->name != NULL; t++) {
		printf("%-24s	", t->name);

		switch (t->fn()) {
		case TEST_PASS: tests_passed++; puts("PASS"); break;
		case TEST_FAIL: tests_failed++; puts("FAIL"); break;
		case TEST_SKIP: tests_skipped++; puts("SKIP"); break;
		}
	}

	printf("\n%d passed, %d failed, %d skipped\n", tests_passed, tests_failed, tests_skipped);
	
	return tests_failed ? 1 : 0;
}
