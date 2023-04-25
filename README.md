# libmca

Commonly written routines I don't want to write again.
You probably don't want to write them either.

Pilfering encouraged; please take what you need and put it into your own
project.
All files here are 100% independent from each other and copy from each other
when copying needs to be done.

## Files of interest

Everything here has a corresponding `.c` and `.h` file, and if you're pulling it
out from here, you want both.

Test cases are contained in `.test.c`.
Run `make test` to ensure everything works; the test suite generally tests as
much code as it possibly can.

### ev

ev contains a simple `poll(2)` event loop.

Users can simply call `mca_ev_poll` in a loop; when -1 is returned, the error
may be fatal, or it may just be `EINTR`.

In the future, I would like to expand it to use `epoll(7)`, or if absolutely
necessary, `select(2)`.

### strmap

strmap contains an implemention of a string indexed map, backed by a linked
list.

**Note**: When traversing the map, many string comparisons will be done, but I
may make it FNV based.
The keys are also dynamically duplicated and are owned by strmap.
Please don't play with them.

### test

test contains a (rather broken) test harness.

### vec

vec has a dynamically allocated array of `void *` pointers.

I may modify this a bit to make it so you don't need to use pointers.
