// int SHAPipe::Put(void const *source, int slen) (0x00675380)
// Adds the data to the digest and passes it on.
// @ref ?Put@Pipe@@UAEHPBXH@Z=0060eaf0
// @ref ?Hash@SHAEngine@@QAEXPBXJ@Z=00674c90
#include "shared/sha_pipe.hpp"

int SHAPipe::Put(void const *source, int slen)
{
    SHA.Hash(source, slen);
    return Pipe::Put(source, slen);
}
