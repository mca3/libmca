#include <assert.h>
#include <unistd.h>

#include "test.h"
#include "ev.h"

static int
test_readable(struct mca_ev *ev, int fd, void *userdata)
{
	char data[1];
	*(int*)userdata = 1;

	assert(read(fd, data, sizeof(data)) != -1);

	return 0;
}

static int
test_writable(struct mca_ev *ev, int fd, void *userdata)
{
	write(fd, "a", 1);
	mca_ev_set_flags(ev, fd, MCA_EV_WRITE, 0);

	return 0;
}

int
test_read(void)
{
	struct mca_ev *ev;
	int flag = 0;
	int sp[2];

	if (mca_ev_new(&ev) == -1)
		return TEST_FAIL;

	mca_ev_set_userdata(ev, &flag);
	ev->on_readable = test_readable;
	ev->on_writable = test_writable;

	if (pipe(sp) == -1) {
		testf("failed to open pipe");

		mca_ev_free(ev);
		close(sp[0]);
		close(sp[1]);
		return TEST_FAIL;
	}

	mca_ev_append(ev, sp[0], MCA_EV_READ);
	mca_ev_append(ev, sp[1], MCA_EV_WRITE);

	// Poll once for write
	// Poll again for read
	if (mca_ev_flush(ev, 0) == -1) {
		testf("flush failed");

		mca_ev_free(ev);
		close(sp[0]);
		close(sp[1]);
		return TEST_FAIL;
	}

	if (mca_ev_poll(ev, 0) == -1) {
		testf("poll failed");

		mca_ev_free(ev);
		close(sp[0]);
		close(sp[1]);
		return TEST_FAIL;
	}

	mca_ev_free(ev);

	if (flag)
		return TEST_PASS;
	return TEST_FAIL;
}

int
test_remove(void)
{
	struct mca_ev *ev;
	int flag = 0;
	int sp[2];

	if (mca_ev_new(&ev) == -1)
		return TEST_FAIL;

	mca_ev_set_userdata(ev, &flag);
	ev->on_readable = test_readable;
	ev->on_writable = test_writable;

	if (pipe(sp) == -1) {
		testf("failed to open pipe");

		mca_ev_free(ev);
		close(sp[0]);
		close(sp[1]);
		return TEST_FAIL;
	}

	mca_ev_append(ev, sp[1], MCA_EV_WRITE);
	mca_ev_append(ev, sp[0], MCA_EV_READ);

	// Poll once for write
	// Poll again for read
	if (mca_ev_flush(ev, 0) == -1) {
		testf("flush failed");

		mca_ev_free(ev);
		close(sp[0]);
		close(sp[1]);
		return TEST_FAIL;
	}

	mca_ev_remove(ev, sp[1]);

	if (mca_ev_poll(ev, 0) == -1) {
		testf("poll failed");

		mca_ev_free(ev);
		close(sp[0]);
		close(sp[1]);
		return TEST_FAIL;
	}

	mca_ev_free(ev);

	if (flag)
		return TEST_PASS;
	return TEST_FAIL;
}

struct test tests[] = {
	{"read",	test_read},
	{"remove",	test_remove},
	{0},
};
