// void Bit_Write_Next(BitStreamType *stream, unsigned char bit) (0x00430D70): appends a bit (a new byte starts
// cleared).
#include "shared/bit_codec.hpp"

void __fastcall Bit_Write_Next(BitStreamType *stream, unsigned char bit)
{
    if (++stream->Bit == 8) {
        stream->Bit = 0;
        stream->Ptr++;
        *stream->Ptr = 0;
    }
    *stream->Ptr |= bit << stream->Bit;
}
