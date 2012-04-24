CC?=gcc
PROVE?=prove

test: build_hextest build_macaddresstest
	$(PROVE) -e '/bin/sh -c' ./test_hex
	$(PROVE) -e '/bin/sh -c' ./test_macaddress

build_hextest: test_hex.o
	$(CC) $(LDFLAGS) -o test_hex $^

build_macaddresstest: test_macaddress.o
	$(CC) $(LDFLAGS) -o test_macaddress $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
	rm -f test_hex
	rm -f test_macaddress
