CC = cc
CFLAGS ?= -std=c99
MODULES = strmap vec

all: libmca.a test

libmca.a: $(MODULES:=.o)

%.o: %.c
	@printf 'CC	%s\n' "$@"
	@$(CC) -c -o $@ $(CFLAGS) $(LDFLAGS) $^

.PHONY: clean test

test: $(MODULES:=.test)

%.test: %.o %.test.o test.o
	$(CC) -o $@ $(CFLAGS) $^
	./$@

clean:
	rm -f $(MODULES:=.test)
	rm -f $(MODULES:=.test.o)
	rm -f $(MODULES:=.o)
	rm -f *.gcov *.gcda *.gcno
