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
Run `make test` to ensure everything works.

### strmap

strmap.c contains an implemention of a string indexed map, backed by a linked
list.

**Note**: When traversing the map, many string comparisons will be done, but I
may make it FNV based.
The keys are also dynamically duplicated and are owned by strmap.
Please don't play with them.

### test

test.c contains a (rather broken) test harness.

### vec

vec.c has a dynamically allocated array of `void *` pointers.

I may modify this a bit to make it so you don't need to use pointers.
