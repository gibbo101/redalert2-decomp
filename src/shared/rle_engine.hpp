// RLEEngine (rle.cpp; TibSun rle.h): run-length coding of zero bytes (a zero byte followed by the run
// length), whole buffers or a line prefixed by its 16-bit coded size. 0x0063D150-0x0063D2C2.
#ifndef RA2_SHARED_RLE_ENGINE_HPP
#define RA2_SHARED_RLE_ENGINE_HPP

class RLEEngine {
public:
    int Compress(void const *source, void *dest, int length) const;         // 0x0063D150
    int Decompress(void const *source, void *dest, int length) const;       // 0x0063D1F0
    int Line_Compress(void const *source, void *dest, int length) const;    // 0x0063D1B0
    int Line_Decompress(void const *source, void *dest) const;              // 0x0063D260
};

#endif
