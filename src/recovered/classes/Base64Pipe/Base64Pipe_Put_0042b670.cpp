// Base64Pipe::Put (0x0042B670), Westwood's B64PIPE.CPP: codes the data in
// whole groups, keeping a partial group in the buffer for the next call.
#include "shared/base64_pipe.hpp"
#include "shared/base64.hpp"
#include "shared/crt_string.hpp"

int Base64Pipe::Put(void const *source, int slen)
{
    if (source == 0 || slen < 1) {
        return Pipe::Put(source, slen);
    }

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

    if (Counter > 0) {
        int len = (slen < (fromsize - Counter)) ? slen : (fromsize - Counter);
        memmove(&from[Counter], source, len);
        Counter += len;
        slen -= len;
        source = ((char *)source) + len;

        if (Counter == fromsize) {
            int outcount;
            if (Control == ENCODE) {
                outcount = Base64_Encode(from, fromsize, to, tosize);
            } else {
                outcount = Base64_Decode(from, fromsize, to, tosize);
            }
            total += Pipe::Put(to, outcount);
            Counter = 0;
        }
    }

    while (slen >= fromsize) {
        int outcount;
        if (Control == ENCODE) {
            outcount = Base64_Encode(source, fromsize, to, tosize);
        } else {
            outcount = Base64_Decode(source, fromsize, to, tosize);
        }
        source = ((char *)source) + fromsize;
        total += Pipe::Put(to, outcount);
        slen -= fromsize;
    }

    if (slen > 0) {
        memmove(from, source, slen);
        Counter = slen;
    }
    return total;
}
