// XMP_DER_Encode(digit const *from, unsigned char *output, int precision) (0x005A7610)
// Writes the number as a DER INTEGER (tag, length, two's complement
// big-endian bytes); returns the bytes written.
#include "shared/mpmath.hpp"
#include "shared/crt_memory.hpp"

int __fastcall XMP_DER_Encode(digit const *from, unsigned char *output, int precision)
{
    unsigned char buffer[MAX_UNIT_PRECISION * sizeof(digit) + 1];

    int header_length = 0;
    unsigned number_length = XMP_Encode(buffer, from, precision);
    output[header_length++] = 0x02;
    header_length += XMP_DER_Length_Encode(number_length, &output[header_length]);
    memcpy(&output[header_length], buffer, number_length);
    return header_length + number_length;
}
