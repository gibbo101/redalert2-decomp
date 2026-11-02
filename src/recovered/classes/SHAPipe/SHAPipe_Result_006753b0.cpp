// int SHAPipe::Result(void *result) const (0x006753B0)
// Writes the digest of the data put so far.
// @ref ?Result@SHAEngine@@QBEHPAX@Z=00674d10
#include "shared/sha_pipe.hpp"

int SHAPipe::Result(void *result) const
{
    return SHA.Result(result);
}
