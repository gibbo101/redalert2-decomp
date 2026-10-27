// RandomStraw::Seed_Short(short seed) (0x0063D580)
// Seeds sixteen bits, low bit first.
#include "shared/random_straw.hpp"

void RandomStraw::Seed_Short(short seed)
{
    for (int index = 0; index < 16; index++) {
        Seed_Bit(seed);
        seed >>= 1;
    }
}
