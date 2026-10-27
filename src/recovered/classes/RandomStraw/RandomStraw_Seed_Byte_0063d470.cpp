// RandomStraw::Seed_Byte(char seed) (0x0063D470)
// Seeds eight bits, low bit first.
#include "shared/random_straw.hpp"

void RandomStraw::Seed_Byte(char seed)
{
    for (int index = 0; index < 8; index++) {
        Seed_Bit(seed);
        seed >>= 1;
    }
}
