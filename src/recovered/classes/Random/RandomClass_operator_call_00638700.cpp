// RandomClass::operator()() (0x00638700)
// Advances the linear congruential seed and returns 15 of its bits.
#include "shared/random.hpp"

int RandomClass::operator()()
{
    Seed = (Seed * MULT_CONSTANT) + ADD_CONSTANT;
    return (Seed >> THROW_AWAY_BITS) & (~((~0) << SIGNIFICANT_BITS));
}
