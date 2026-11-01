// int RLEEngine::Compress(void const *source, void *dest, int length) const -- 0x0063D150 (TS rle.cpp)
// Copies source to dest replacing each run of zero bytes (at most 255) by a zero and the run length;
// returns the coded length (dest may be null to only measure it).
#include "shared/crt_memory.hpp"
#include "shared/rle_engine.hpp"
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

int RLEEngine::Compress(void const *source, void *dest, int length) const
{
    int outlen = 0;
    unsigned char const *sptr = (unsigned char const *)source;
    unsigned char *dptr = (unsigned char *)dest;

    while (length > 0) {
        if (*sptr == '\0') {
            int runcount = 0;
            while (sptr[runcount] == '\0' && runcount <= length) {
                runcount++;
            }
            runcount = MIN(runcount, 255);
            if (dptr != 0) {
                *dptr++ = '\0';
                *dptr++ = (unsigned char)runcount;
            }
            outlen += 2;
            sptr += runcount;
            length -= runcount;
        } else {
            if (dptr != 0) {
                *dptr++ = *sptr++;
            } else {
                sptr++;
            }
            outlen++;
            length--;
        }
    }
    return outlen;
}
