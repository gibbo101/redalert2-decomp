// Random2Class::operator()() (0x00638840)
// XORs the lagged table entry into the current one and returns it; returns
// 0 while unknown_0x00 is set.
#include "shared/random.hpp"

int Random2Class::operator()()
{
    if (unknown_0x00) {
        return 0;
    }

    Table[Index1] ^= Table[Index2];
    int value = Table[Index1];

    Index1++;
    Index2++;
    if (Index1 >= 250) {
        Index1 = 0;
    }
    if (Index2 >= 250) {
        Index2 = 0;
    }
    return value;
}
