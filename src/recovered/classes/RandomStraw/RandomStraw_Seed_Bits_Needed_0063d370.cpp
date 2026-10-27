// RandomStraw::Seed_Bits_Needed() const (0x0063D370)
// Seed bits still wanted before the generators are fully seeded.
#include "shared/random_straw.hpp"

int RandomStraw::Seed_Bits_Needed() const
{
    const int total = sizeof(Random) * 8;
    if (SeedBits < total) {
        return total - SeedBits;
    }
    return 0;
}
