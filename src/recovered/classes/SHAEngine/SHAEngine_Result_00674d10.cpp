// SHAEngine::Result(void *result) const (0x00674D10)
// Pads a copy of the staged data with the end bit and the bit length,
// hashes it into a copy of the accumulator and returns the big-endian
// digest (20 bytes). A cached digest is copied out first but always
// recomputed (original behaviour).
// @ref ?Process_Block@SHAEngine@@ABEXPBXAATSHADigest@1@@Z=00674e60
#include "shared/sha.hpp"
#include "shared/crt_memory.hpp"

#define Reverse_LONG(a) ((((a) >> 24) & 0x000000FFL) | (((a) >> 8) & 0x0000FF00L) | (((a) << 8) & 0x00FF0000L) | (((a) << 24) & 0xFF000000L))

int SHAEngine::Result(void *result) const
{
    if (IsCached) {
        memcpy(result, &FinalResult, sizeof(FinalResult));
    }

    long length = Length + PartialCount;
    int partialcount = PartialCount;
    char partial[SRC_BLOCK_SIZE];
    memcpy(partial, Partial, sizeof(Partial));

    // End the data with a 1 bit.
    partial[partialcount] = (char)0x80;

    // Without room for the 8-byte length, finish this block first.
    SHADigest acc = Acc;
    if ((SRC_BLOCK_SIZE - partialcount) < 9) {
        if (partialcount + 1 < SRC_BLOCK_SIZE) {
            memset(&partial[partialcount + 1], '\0', SRC_BLOCK_SIZE - (partialcount + 1));
        }
        Process_Block(&partial[0], acc);
        partialcount = 0;
    } else {
        partialcount++;
    }

    // The bit length (low 32 bits) ends the last block, big-endian.
    memset(&partial[partialcount], '\0', SRC_BLOCK_SIZE - partialcount);
    *(long *)(&partial[SRC_BLOCK_SIZE - 4]) = Reverse_LONG((length * 8));
    Process_Block(&partial[0], acc);

    memcpy((char *)&FinalResult, &acc, sizeof(acc));
    for (int index = 0; index < sizeof(FinalResult) / sizeof(long); index++) {
        (long &)FinalResult.Long[index] = Reverse_LONG(FinalResult.Long[index]);
    }
    (bool &)IsCached = true;
    memcpy(result, &FinalResult, sizeof(FinalResult));
    return sizeof(FinalResult);
}
