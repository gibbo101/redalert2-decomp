#include "shared/base64.hpp"
// @ref ?unknown_base64_table_79c624@@3PAEA=0079c624

int __fastcall Base64_Decode(void const *source, int slen, void *dest, int dlen)
{
    if (source == 0 || slen == 0 || dest == 0 || dlen == 0) {
        return 0;
    }
    int total = 0;
    unsigned char const *sptr = (unsigned char const *)source;
    unsigned char *dptr = (unsigned char *)dest;
    while (slen > 0 && dlen > 0) {
        union {
            unsigned long value;
            unsigned char bytes[4];
        } group;
        group.value = 0;
        int count;
        for (count = 0; count < 4;) {
            if (slen <= 0) {
                break;
            }
            unsigned char character = *sptr++;
            slen--;
            unsigned char code = unknown_base64_table_79c624[character];
            if (code != 0xfe) {
                if (code == 0xff) {
                    slen = 0;
                    break;
                }
                switch (count) {
                case 0:
                    group.value = (group.value & 0xff03ffff) | ((code & 0x3f) << 18);
                    break;
                case 1:
                    group.value = (group.value & 0xfffc0fff) | ((code & 0x3f) << 12);
                    break;
                case 2:
                    group.value = (group.value & 0xfffff03f) | ((code & 0x3f) << 6);
                    break;
                case 3:
                    group.value = (group.value & 0xffffffc0) | (code & 0x3f);
                    break;
                }
                count++;
            }
        }
        *dptr++ = group.bytes[2];
        dlen--;
        total++;
        if (dlen > 0 && count > 2) {
            *dptr++ = group.bytes[1];
            dlen--;
            total++;
        }
        if (dlen > 0 && count > 3) {
            *dptr++ = group.bytes[0];
            dlen--;
            total++;
        }
    }
    return total;
}
