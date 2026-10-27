// Random3Class::Random3Class(unsigned seed1, unsigned seed2) (0x00638950)
#include "shared/random.hpp"

Random3Class::Random3Class(unsigned seed1, unsigned seed2) :
    Seed(seed1),
    Index(seed2)
{
}
