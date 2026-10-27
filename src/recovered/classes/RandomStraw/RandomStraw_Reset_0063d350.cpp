// RandomStraw::Reset() (0x0063D350)
// Discards the seed and all generator state.
#include "shared/random_straw.hpp"
#include "shared/crt_string.hpp"

void RandomStraw::Reset()
{
    SeedBits = 0;
    Current = 0;
    memset(Random, '\0', sizeof(Random));
}
