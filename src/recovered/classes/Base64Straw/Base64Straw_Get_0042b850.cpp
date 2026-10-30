// Base64Straw::Get (0x0042B850), Westwood's B64STRAW.CPP: draws data from the
// chain and codes it a group at a time.
#include "shared/base64_straw.hpp"
#include "shared/base64.hpp"
#include "shared/crt_string.hpp"

int Base64Straw::Get(void *source, int slen)
{
    int total = 0;
    char *from;
    int fromsize;
    char *to;
    int tosize;

    if (Control == ENCODE) {
        from = PBuffer;
        fromsize = sizeof(PBuffer);
        to = CBuffer;
        tosize = sizeof(CBuffer);
    } else {
        from = CBuffer;
        fromsize = sizeof(CBuffer);
        to = PBuffer;
        tosize = sizeof(PBuffer);
    }

    while (slen > 0) {
        if (Counter > 0) {
            int len = (slen < Counter) ? slen : Counter;
            memmove(source, &to[tosize - Counter], len);
            Counter -= len;
            slen -= len;
            source = ((char *)source) + len;
            total += len;
        }
        if (slen == 0) break;

        int incount = Straw::Get(from, fromsize);
        if (Control == ENCODE) {
            Counter = Base64_Encode(from, incount, to, tosize);
        } else {
            Counter = Base64_Decode(from, incount, to, tosize);
        }
        if (Counter == 0) break;
    }
    return total;
}
