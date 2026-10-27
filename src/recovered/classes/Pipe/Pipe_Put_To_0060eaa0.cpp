// Pipe::Put_To (0x0060EAA0, virtual slot 3)
// Connects this pipe to feed pipe (or disconnects with null). The previous
// target is flushed; a pipe already fed by another is taken from it first.
#include "shared/pipe.hpp"

void Pipe::Put_To(Pipe *pipe)
{
    if (ChainTo != pipe) {
        if (pipe && pipe->ChainFrom) {
            pipe->ChainFrom->Put_To(0);
            pipe->ChainFrom = 0;
        }
        if (ChainTo) {
            ChainTo->ChainFrom = 0;
            ChainTo->Flush();
        }
        ChainTo = pipe;
        if (pipe) {
            pipe->ChainFrom = this;
        }
    }
}
