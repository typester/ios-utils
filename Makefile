CC?=gcc
PROVE?=prove

test: build_test
	$(PROVE) -e '/bin/sh -c' ./test

build_test: test.o
	$(CC) $(LDFLAGS) -o test $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
	rm -f test_request
	rm -f test_response
