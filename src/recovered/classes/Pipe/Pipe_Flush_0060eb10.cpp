// Pipe::Flush (0x0060EB10, virtual slot 1)
// Flushes the connected pipe; nothing to do when unconnected.
#include "shared/pipe.hpp"

int Pipe::Flush()
{
    if (ChainTo) {
        return ChainTo->Flush();
    }
    return 0;
}
