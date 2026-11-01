// bool Bit_Read_Next(BitStreamType *stream) (0x00430D30): the next bit.
#include "shared/bit_codec.hpp"

bool __fastcall Bit_Read_Next(BitStreamType *stream)
{
    if (++stream->Bit == 8) {
        stream->Bit = 0;
        stream->Ptr++;
    }
    return (*stream->Ptr & (1 << stream->Bit)) > 0 ? true : false;
}
