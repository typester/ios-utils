#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <net/if_dl.h>
#include <net/if_types.h>
#include <string.h>

static inline size_t macaddress(const char* if_name, unsigned char** result) {
    struct ifaddrs* addrs;
    struct ifaddrs* addr;
    const struct sockaddr_dl* dladdr;
    int r;
    size_t result_len = 0;

    r = getifaddrs(&addrs);
    assert(0 == r);

    addr = addrs;
    do {
        if (0 != strncmp(if_name, addr->ifa_name, strlen(if_name)))
            continue;

        if (addr->ifa_addr->sa_family == AF_LINK) {
            dladdr = (const struct sockaddr_dl*)addr->ifa_addr;

            if (dladdr->sdl_type == IFT_ETHER) {
                const unsigned char* maddr =
                    (const unsigned char*)LLADDR(dladdr);

                result_len = dladdr->sdl_alen;

                *result = (unsigned char*)malloc(result_len);
                assert(*result);

                memcpy(*result, maddr, result_len);

                break;
            }
        }
    } while (addr = addr->ifa_next);

    freeifaddrs(addrs);

    return result_len;
}

