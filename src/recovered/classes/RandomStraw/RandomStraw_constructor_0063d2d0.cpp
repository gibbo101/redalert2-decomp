// RandomStraw::RandomStraw() (0x0063D2D0)
// Starts with an empty (all zero) seed.
// @ref ??0Random3Class@@QAE@II@Z=00638950
#include "shared/random_straw.hpp"

RandomStraw::RandomStraw() :
    SeedBits(0),
    Current(0)
{
    Reset();
}
