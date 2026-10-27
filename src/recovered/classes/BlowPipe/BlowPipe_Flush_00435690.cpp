// BlowPipe::Flush() (0x00435690, virtual slot 1)
// Passes a held partial block on unprocessed, then flushes the chain.
// Returns the bytes passed down the chain.
#include "shared/blow_pipe.hpp"

int BlowPipe::Flush()
{
    int total = 0;
    if (Counter > 0 && BF != 0) {
        total += Pipe::Put(Buffer, Counter);
    }
    Counter = 0;
    total += Pipe::Flush();
    return total;
}
