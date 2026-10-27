// Straw::Get (0x0069B0A0, virtual slot 2)
// Draws up to length bytes from the connected straw; nothing when unconnected.
#include "shared/straw.hpp"

int Straw::Get(void *buffer, int length)
{
    if (ChainTo) {
        return ChainTo->Get(buffer, length);
    }
    return 0;
}
