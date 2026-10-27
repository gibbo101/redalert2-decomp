// RandomStraw::Scramble_Seed() (0x0063D790)
// Replaces each byte of the generator state, in turn, with the start of the
// SHA-1 digest of the whole state so far.
// @ref ?Hash@SHAEngine@@QAEXPBXJ@Z=00674c90
// @ref ?Result@SHAEngine@@QBEHPAX@Z=00674d10
#include "shared/random_straw.hpp"
#include "shared/sha.hpp"
#include "shared/crt_string.hpp"

void RandomStraw::Scramble_Seed()
{
    SHAEngine sha;
    for (unsigned index = 0; index < sizeof(Random); index++) {
        char digest[20];
        sha.Hash(&Random[0], sizeof(Random));
        sha.Result(digest);

        int tocopy = (sizeof(Random) - index > sizeof(digest)) ? sizeof(digest) : sizeof(Random) - index;
        memmove(((char *)&Random[0]) + index, digest, tocopy);
    }
}
