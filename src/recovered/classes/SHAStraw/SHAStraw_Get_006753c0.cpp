// int SHAStraw::Get(void *source, int slen) (0x006753C0)
// Draws data through the straw and adds it to the digest.
// @ref ?Get@Straw@@UAEHPAXH@Z=0069b0a0
// @ref ?Hash@SHAEngine@@QAEXPBXJ@Z=00674c90
#include "shared/sha_straw.hpp"

int SHAStraw::Get(void *source, int slen)
{
    if (source == 0 || slen < 1) {
        return 0;
    }

    int counter = Straw::Get(source, slen);
    if (!IsDisabled) {
        SHA.Hash(source, counter);
    }
    return counter;
}
