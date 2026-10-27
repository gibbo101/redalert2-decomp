// Random2Class::Random2Class(unsigned seed) (0x00638790)
// Fills the table from a Random3Class seeded with seed.
#include "shared/random.hpp"

Random2Class::Random2Class(unsigned seed) :
    Index1(0),
    Index2(103)
{
    Random3Class random(seed);
    for (int index = 0; index < 250; index++) {
        Table[index] = random;
    }
    unknown_0x00 = false;
}
