// SHAEngine::Process_Partial(void const *&data, long &length) (0x00674BF0)
// Stages source bytes in Partial when a block is already partly staged or
// fewer than a block's bytes remain, advancing data and length; hashes
// Partial once it holds a whole block.
// @ref ?Process_Block@SHAEngine@@ABEXPBXAATSHADigest@1@@Z=00674e60
#include "shared/sha.hpp"
#include "shared/crt_memory.hpp"

void SHAEngine::Process_Partial(void const *&data, long &length)
{
    if (length == 0 || data == 0) {
        return;
    }

    if (PartialCount == 0 && length >= SRC_BLOCK_SIZE) {
        return;
    }

    int add_count = ((int)length < (int)SRC_BLOCK_SIZE - PartialCount) ? (int)length : (int)SRC_BLOCK_SIZE - PartialCount;
    memcpy(&Partial[PartialCount], data, add_count);
    data = ((char const *)data) + add_count;
    PartialCount += add_count;
    length -= add_count;

    if (PartialCount == SRC_BLOCK_SIZE) {
        Process_Block(&Partial[0], Acc);
        Length += (long)SRC_BLOCK_SIZE;
        PartialCount = 0;
    }
}
