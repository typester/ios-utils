#include <stdio.h>
#include <string.h>

#include "hex.h"

static void plan(int num) {
    printf("1..%d\n", num);
}

static void ok(int ok, const char* msg) {
    static int testnum = 0;
    printf("%s %d - %s\n", ok ? "ok" : "not ok", ++testnum, msg);
}

static void test_encode(void) {
    unsigned char binary[] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
    };
    unsigned char hexstring[sizeof(binary) * 2 + 1];

    hex(binary, sizeof(binary), hexstring);

    ok(0 == strncmp(hexstring, "0123456789abcdef", 16), "encode ok");
}

static void test_decode(void) {
    unsigned char hexstring[] = "0123456789abcdef";
    unsigned char binary[strlen(hexstring) / 2];
    unsigned char expected[] = {
        0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
    };

    unhex(hexstring, strlen(hexstring), binary);

    ok(0 == memcmp(binary, expected, strlen(hexstring)/2), "decode ok");
}

int main(void) {
    plan(2);

    test_encode();
    test_decode();

    return 0;
}

