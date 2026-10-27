// SHAEngine::Hash(void const *data, long length) (0x00674C90)
// Adds data to the digest: completes a staged block, hashes whole blocks
// straight from the source and stages the remainder.
// @ref ?Process_Block@SHAEngine@@ABEXPBXAATSHADigest@1@@Z=00674e60
// @ref ?Process_Partial@SHAEngine@@AAEXAAPBXAAJ@Z=00674bf0
#include "shared/sha.hpp"

void SHAEngine::Hash(void const *data, long length)
{
    IsCached = false;

    Process_Partial(data, length);
    if (length == 0) {
        return;
    }

    long blocks = length / SRC_BLOCK_SIZE;
    long const *source = (long const *)data;
    for (int bcount = 0; bcount < blocks; bcount++) {
        Process_Block(source, Acc);
        Length += (long)SRC_BLOCK_SIZE;
        source += SRC_BLOCK_SIZE / sizeof(long);
        length -= (long)SRC_BLOCK_SIZE;
    }

    data = source;
    Process_Partial(data, length);
}
