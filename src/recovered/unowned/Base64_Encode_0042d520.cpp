#include "shared/base64.hpp"
// @ref ?unknown_base64_pad_79c61c@@3PBDB=0079c61c
// @ref ?unknown_base64_chars_79c620@@3PBDB=0079c620

int __fastcall Base64_Encode(void const *source, int slen, void *dest, int dlen)
{
    if (source == 0 || slen == 0 || dest == 0 || dlen == 0) {
        return 0;
    }
    int total = 0;
    unsigned char const *sptr = (unsigned char const *)source;
    char *dptr = (char *)dest;
    while (slen > 0 && dlen >= 4) {
        int pad = 0;
        union {
            unsigned long value;
            unsigned char bytes[4];
        } group;
        group.value = 0;
        group.bytes[2] = *sptr++;
        slen--;
        if (slen != 0) {
            group.bytes[1] = *sptr++;
            slen--;
        } else {
            pad++;
        }
        if (slen != 0) {
            group.bytes[0] = *sptr++;
            slen--;
        } else {
            pad++;
        }
        *dptr++ = unknown_base64_chars_79c620[(group.value >> 18) & 0x3f];
        *dptr++ = unknown_base64_chars_79c620[(group.value >> 12) & 0x3f];
        if (pad < 2) {
            *dptr = unknown_base64_chars_79c620[(group.value >> 6) & 0x3f];
        } else {
            *dptr = *unknown_base64_pad_79c61c;
        }
        dptr++;
        if (pad < 1) {
            *dptr = unknown_base64_chars_79c620[group.value & 0x3f];
        } else {
            *dptr = *unknown_base64_pad_79c61c;
        }
        dptr++;
        dlen -= 4;
        total += 4;
    }
    if (dlen > 0) {
        *dptr = 0;
    }
    return total;
}
