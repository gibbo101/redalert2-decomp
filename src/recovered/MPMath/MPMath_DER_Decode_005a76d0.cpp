// XMP_DER_Decode(digit *result, unsigned char const *input, int precision) (0x005A76D0)
// Reads a DER INTEGER; malformed or oversized input leaves result unchanged.
#include "shared/mpmath.hpp"

void __fastcall XMP_DER_Decode(digit *result, unsigned char const *input, int precision)
{
    if (*input++ == 0x02) {
        unsigned byte_count;

        if ((*input & 0x80) == 0) {
            byte_count = *input++;
        } else {
            int length = *input++ & 0x7F;
            if (length > 2) {
                return;
            }
            byte_count = *input++;
            if (length > 1) {
                byte_count = (byte_count << 8) | *input++;
            }
        }

        if (byte_count <= precision * sizeof(digit)) {
            XMP_Signed_Decode(result, input, byte_count, precision);
        }
    }
}
