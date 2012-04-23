#include <stdio.h>
#include <stdlib.h>

static inline unsigned char* hex(unsigned char* s, size_t s_len, unsigned char* r) {
    static const unsigned char hex_strings[] = "0123456789abcdef";
    int i;

    for (i = 0; i < s_len; i++) {
        r[i*2]     = hex_strings[ s[i]>>4 & 0xf ];
        r[i*2 + 1] = hex_strings[ s[i]    & 0xf ];
    }

    return r;
}

static inline unsigned char unhex_char(unsigned char s) {
    if (0x30 <= s && s <= 0x39) { /* 0-9 */
        return s - 0x30;
    }
    else if (0x41 <= s && s <= 0x46) { /* A-F */
        return s - 0x41 + 0xa;
    }
    else if (0x61 <= s && s <= 0x69) { /* a-f */
        return s - 0x61 + 0xa;
    }
    else {
        fprintf(stderr, "invalid hex string: %c\n", s);
        abort();
    }
}

static inline unsigned char* unhex(unsigned char* s, size_t s_len, unsigned char* r) {
    int i;

    for (i = 0; i < s_len; i += 2) {
        r[i/2] = (unhex_char(s[i]) << 4) | (unhex_char(s[i+1]) & 0xf);
    }

    return r;
}
