// RandomStraw::Seed_Bit(int seed) (0x0063D390)
// Mixes the low bit of seed into the next seed bit; once every bit of the
// generator state has been seeded, the state is scrambled.
#include "shared/random_straw.hpp"

void RandomStraw::Seed_Bit(int seed)
{
    char *ptr = ((char *)&Random[0]) + ((SeedBits / 8) % sizeof(Random));
    if (seed & 0x01) {
        *ptr ^= (char)(1 << (SeedBits & 0x07));
    }
    SeedBits++;
    if (SeedBits == (sizeof(Random) * 8)) {
        Scramble_Seed();
    }
}
