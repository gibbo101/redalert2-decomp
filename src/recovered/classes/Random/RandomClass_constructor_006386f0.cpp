// RandomClass::RandomClass(unsigned seed) (0x006386F0): the linear congruential generator's seed.
// Unit-wide (Random.cpp 0x006386F0): random.hpp keeps the constructor out of line here.
#define RA2_RANDOM_UNIT
#include "shared/random.hpp"

RandomClass::RandomClass(unsigned seed) : Seed(seed)
{
}
