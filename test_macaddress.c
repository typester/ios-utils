#include <stdio.h>
#include <string.h>

#include "macaddress.h"

static void plan(int num) {
    printf("1..%d\n", num);
}

static void ok(int ok, const char* msg) {
    static int testnum = 0;
    printf("%s %d - %s\n", ok ? "ok" : "not ok", ++testnum, msg);
}

int main(void) {
    plan(2);

    unsigned char* macaddr = NULL;
    size_t len = 0;

    len = macaddress("en0", &macaddr);

    ok(macaddr != NULL, "address allocated ok");
    ok(len == 6, "length ok");

    free(macaddr);

    return 0;
}

