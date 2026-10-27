// SHAEngine::Process_Block(void const *source, SHADigest &acc) const (0x00674E60)
// One SHA-1 compression: expands the big-endian 16-word block to 80 words
// and runs the 80 steps, adding the result into acc.
#include "shared/sha.hpp"

#define Reverse_LONG(a) ((((a) >> 24) & 0x000000FFL) | (((a) >> 8) & 0x0000FF00L) | (((a) << 8) & 0x00FF0000L) | (((a) << 24) & 0xFF000000L))
// Rotates a left by n bits (an inline function, not a macro: that decides
// how the compiler orders the step sum).
inline unsigned long Rotate_Left(unsigned long a, int n) { return (a << n) | (a >> (32 - n)); }

void SHAEngine::Process_Block(void const *source, SHADigest &acc) const
{
    long block[PROC_BLOCK_SIZE / sizeof(long)];

    long const *data = (long const *)source;
    unsigned a;
    for (a = 0; a < SRC_BLOCK_SIZE / sizeof(long); a++) {
        block[a] = Reverse_LONG(data[a]);
    }

    for (a = SRC_BLOCK_SIZE / sizeof(long); a < PROC_BLOCK_SIZE / sizeof(long); a++) {
        unsigned long value = block[a - 3] ^ block[a - 8] ^ block[a - 14] ^ block[a - 16];
        block[a] = (long)Rotate_Left(value, 1);
    }

    SHADigest alt = acc;
    for (a = 0; a < PROC_BLOCK_SIZE / sizeof(long); a++) {
        unsigned long temp = Rotate_Left(alt.Long[0], 5) + Do_Function(a, alt.Long[1], alt.Long[2], alt.Long[3])
                           + alt.Long[4] + block[a] + Get_Constant(a);
        alt.Long[4] = alt.Long[3];
        alt.Long[3] = alt.Long[2];
        alt.Long[2] = Rotate_Left(alt.Long[1], 30);
        alt.Long[1] = alt.Long[0];
        alt.Long[0] = temp;
    }

    acc.Long[0] += alt.Long[0];
    acc.Long[1] += alt.Long[1];
    acc.Long[2] += alt.Long[2];
    acc.Long[3] += alt.Long[3];
    acc.Long[4] += alt.Long[4];
}
