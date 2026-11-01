// int Bit_Expand_7(unsigned char const *source, unsigned char *dest, unsigned count) (0x00430DA0): copies count
// bits, inserting a set bit after every seventh; returns one more than the number inserted.
#include "shared/bit_codec.hpp"

int __fastcall Bit_Expand_7(unsigned char const *source, unsigned char *dest, unsigned count)
{
    BitStreamType in;
    BitStreamType out;
    unsigned index = 0;
    int written = 1;
    Bit_Write_Start(&out, dest, Bit_Read_Start(&in, (unsigned char *)source));
    while (--count) {
        if (++index % 7 == 0) {
            Bit_Write_Next(&out, 1);
            written++;
        }
        Bit_Write_Next(&out, Bit_Read_Next(&in));
    }
    return written;
}
