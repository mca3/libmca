#define TEST_PASS 0
#define TEST_FAIL 1
#define TEST_SKIP 2

struct test {
	char *name;
	int (*fn)(void);
};

extern struct test tests[];

extern int tests_passed;
extern int tests_failed;
extern int tests_skipped;

void testf(const char *fmt, ...);
