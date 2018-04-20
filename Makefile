CC=gcc
CFLAGS=-I. -O3 -Wall
LDFLAGS=
DEPS=mergenetsort.h mergenetsort.c main.c
OBJ=main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mergenetsort: $(OBJ)
	gcc -o $@ $^ $(LDFLAGS)

bench:	mergenetsort
	@if [ -x /usr/bin/perf ]; then \
	    echo "Perf stat for mergenetsort for 100 x 1000000 elements:"; \
	    perf stat ./mergenetsort m 1000000 > /dev/null; \
	    echo "Perf stat for qsort for 100 x 1000000 elements:"; \
	    perf stat ./mergenetsort q 1000000 > /dev/null; \
	else \
	    echo "Time for mergenetsort for 100 x 1000000 elements:"; \
	    time ./mergenetsort m 1000000 > /dev/null; \
	    echo "Time stat for qsort for 100 x 1000000 elements:"; \
	    time ./mergenetsort q 1000000 > /dev/null; \
	fi

test:	mergenetsort
	@TMPDIR=`mktemp -d`; \
	for i in `seq 1 1 200`; \
	do \
	    echo "Comparing result for $$i elements"; \
	    ./mergenetsort m $$i 1 > $$TMPDIR/m; \
	    ./mergenetsort p $$i 1 > $$TMPDIR/p; \
	    diff -urN $$TMPDIR/m $$TMPDIR/p; \
	done; \
	for i in `seq 3 7 20000`; \
	do \
	    echo "Comparing result for $$i elements"; \
	    ./mergenetsort m $$i 1 > $$TMPDIR/m; \
	    ./mergenetsort p $$i 1 > $$TMPDIR/p; \
	    diff -urN $$TMPDIR/m $$TMPDIR/p; \
	done; \
	for i in `seq 100000 1 101000`; \
	do \
	    echo "Comparing result for $$i elements"; \
	    ./mergenetsort m $$i 1 > $$TMPDIR/m; \
	    ./mergenetsort p $$i 1 > $$TMPDIR/p; \
	    diff -urN $$TMPDIR/m $$TMPDIR/p; \
	done; \
	for i in `seq 987654 1 988000`; \
	do \
	    echo "Comparing result for $$i elements"; \
	    ./mergenetsort m $$i 1 > $$TMPDIR/m; \
	    ./mergenetsort p $$i 1 > $$TMPDIR/p; \
	    diff -urN $$TMPDIR/m $$TMPDIR/p; \
	done; \
	rm $$TMPDIR/m; \
	rm $$TMPDIR/p; \
	rmdir $$TMPDIR

clean:
	rm -rf mergenetsort *.o
