// unsigned Bit_Compress_7(unsigned char const *source, unsigned char *dest, unsigned count) (0x00430E80): the
// inverse of Bit_Expand_7: copies count bits, dropping the bit after every seventh; returns the bytes written.
#include "shared/bit_codec.hpp"

unsigned __fastcall Bit_Compress_7(unsigned char const *source, unsigned char *dest, unsigned count)
{
    BitStreamType in;
    BitStreamType out;
    unsigned bytes = (count + 7) / 8;
    Bit_Write_Start(&out, dest, Bit_Read_Start(&in, (unsigned char *)source));
    unsigned index = 0;
    while (--count) {
        if (++index % 7 == 0) {
            Bit_Read_Next(&in);
        }
        Bit_Write_Next(&out, Bit_Read_Next(&in));
    }
    return bytes;
}
