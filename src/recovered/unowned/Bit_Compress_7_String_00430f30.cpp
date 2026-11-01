// unsigned Bit_Compress_7_String(unsigned char const *source, unsigned short *dest, unsigned count) (0x00430F30):
// Bit_Compress_7 into a wide string: stops after a null character (returns the characters including it), else
// after count characters, terminating the last one.
#include "shared/bit_codec.hpp"

unsigned __fastcall Bit_Compress_7_String(unsigned char const *source, unsigned short *dest, unsigned count)
{
    BitStreamType in;
    BitStreamType out;
    Bit_Write_Start(&out, (unsigned char *)dest, Bit_Read_Start(&in, (unsigned char *)source));
    unsigned index = 0;
    int bits = 0;
    unsigned chars = 0;
    while (chars < count) {
        if (++index % 7 == 0) {
            Bit_Read_Next(&in);
        }
        Bit_Write_Next(&out, Bit_Read_Next(&in));
        if (++bits % 16 == 0) {
            chars++;
            if (*(unsigned short *)(out.Ptr - 2) == 0) {
                return chars;
            }
        }
    }
    dest[count - 1] = 0;
    return chars;
}
