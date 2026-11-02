// int SHAStraw::Result(void *result) const (0x00675400)
// Writes the digest of the data drawn so far.
// @ref ?Result@SHAEngine@@QBEHPAX@Z=00674d10
#include "shared/sha_straw.hpp"

int SHAStraw::Result(void *result) const
{
    return SHA.Result(result);
}
