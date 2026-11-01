// bool Bit_Read_Start(BitStreamType *stream, unsigned char *data) (0x00430D20): starts reading at data; bit 0.
#include "shared/bit_codec.hpp"

bool __fastcall Bit_Read_Start(BitStreamType *stream, unsigned char *data)
{
    stream->Ptr = data;
    stream->Bit = 0;
    return *data & 1 ? true : false;
}
