// RandomStraw::Get(void *buffer, int length) (0x0063D830, virtual slot 2)
// Fills the buffer with one byte from each generator in turn; returns the
// bytes delivered.
// @ref ??RRandom3Class@@QAEHXZ=00638970
#include "shared/random_straw.hpp"

int RandomStraw::Get(void *buffer, int length)
{
    if (buffer == 0 || length < 1) {
        return Straw::Get(buffer, length);
    }

    int total = 0;
    while (length > 0) {
        *(char *)buffer = (char)Random[Current++]();
        Current = Current % (sizeof(Random) / sizeof(Random[0]));
        buffer = (char *)buffer + sizeof(char);
        length--;
        total++;
    }
    return total;
}
