// void Bit_Write_Start(BitStreamType *stream, unsigned char *data, bool bit) (0x00430D60): starts writing at data
// with bit as bit 0.
#include "shared/bit_codec.hpp"

void __fastcall Bit_Write_Start(BitStreamType *stream, unsigned char *data, bool bit)
{
    stream->Ptr = data;
    stream->Bit = 0;
    *data = bit;
}
