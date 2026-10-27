// XMP_DER_Length_Encode(unsigned long length, unsigned char *output) (0x005A7590)
// Writes a DER length field (short form below 128, else a count byte and
// the big-endian length); returns its size.
#include "shared/mpmath.hpp"

// Bytes needed to hold value (at least one).
static inline int Length_Bytes(unsigned long value)
{
    int count = sizeof(value);
    while (count != 0 && !(value >> ((count - 1) * 8))) {
        count--;
    }
    return count;
}

int __fastcall XMP_DER_Length_Encode(unsigned long length, unsigned char *output)
{
    int header_length = 0;

    if (length <= 0x7F) {
        output[0] = (unsigned char)length;
        header_length = 1;
    } else {
        output[0] = (unsigned char)(Length_Bytes(length) | 0x80);
        header_length = 1;
        for (int index = Length_Bytes(length); index != 0; index--) {
            output[header_length++] = (unsigned char)(length >> ((index - 1) * 8));
        }
    }
    return header_length;
}
