// Pipe::Put (0x0060EAF0, virtual slot 4)
// Passes data on; an unconnected pipe accepts and discards it.
#include "shared/pipe.hpp"

int Pipe::Put(void const *source, int length)
{
    if (ChainTo) {
        return ChainTo->Put(source, length);
    }
    return length;
}
