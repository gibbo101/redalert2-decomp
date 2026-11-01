// int RLEEngine::Decompress(void const *source, void *dest, int length) const -- 0x0063D1F0 (TS rle.cpp)
// Expands Compress's coding of length source bytes into dest; returns the bytes written.
#include "shared/rle_engine.hpp"

int RLEEngine::Decompress(void const *source, void *dest, int length) const
{
    unsigned char *dptr = (unsigned char *)dest;
    unsigned char const *sptr = (unsigned char const *)source;

    while (length > 0) {
        unsigned char value = *sptr++;
        length--;
        if (value == '\0') {
            int outlen = *sptr++;
            length--;
            if (outlen > 0) {
                memset(dptr, '\0', outlen);
                dptr += outlen;
            }
        } else {
            *dptr++ = value;
        }
    }
    return dptr - (unsigned char const *)dest;
}
