// int RLEEngine::Line_Decompress(void const *source, void *dest) const -- 0x0063D260 (TS rle.cpp)
// Decompress of a line written by Line_Compress (its size word gives the length).
#include "shared/rle_engine.hpp"

int RLEEngine::Line_Decompress(void const *source, void *dest) const
{
    unsigned short const *sptr = (unsigned short const *)source;
    int datalen = *sptr++;
    return Decompress(sptr, dest, datalen - sizeof(short));
}
