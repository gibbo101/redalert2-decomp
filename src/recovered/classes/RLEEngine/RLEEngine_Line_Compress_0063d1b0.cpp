// int RLEEngine::Line_Compress(void const *source, void *dest, int length) const -- 0x0063D1B0 (TS rle.cpp)
// Compress behind a 16-bit size word (the coded length including the word).
#include "shared/rle_engine.hpp"
// @ref ?Compress@RLEEngine@@QBEHPBXPAXH@Z=0063d150

int RLEEngine::Line_Compress(void const *source, void *dest, int length) const
{
    if (dest != 0) {
        unsigned short *sizeptr = (unsigned short *)dest;
        int complen = Compress(source, sizeptr + 1, length) + sizeof(short);
        *sizeptr = (unsigned short)complen;
        return complen;
    }
    return Compress(source, 0, length) + sizeof(short);
}
