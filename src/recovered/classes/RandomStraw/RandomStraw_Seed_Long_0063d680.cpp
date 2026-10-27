// RandomStraw::Seed_Long(long seed) (0x0063D680)
// Seeds thirty-two bits, low bit first.
#include "shared/random_straw.hpp"

void RandomStraw::Seed_Long(long seed)
{
    for (int index = 0; index < 32; index++) {
        Seed_Bit(seed);
        seed >>= 1;
    }
}
