// PKPipe::Put_To(Pipe *pipe) (0x0060FAF0, virtual slot 3)
// Connects the output: this pipe feeds its Blowfish stage, which feeds pipe.
#include "shared/pk_pipe.hpp"

void PKPipe::Put_To(Pipe *pipe)
{
    if (BF.ChainTo != pipe) {
        if (pipe != 0 && pipe->ChainFrom != 0) {
            pipe->ChainFrom->Put_To(0);
            pipe->ChainFrom = 0;
        }

        if (BF.ChainTo != 0) {
            BF.ChainTo->ChainFrom = 0;
        }

        BF.ChainTo = pipe;
        if (pipe != 0) {
            pipe->ChainFrom = &BF;
        }
        BF.ChainFrom = this;
        ChainTo = &BF;
    }
}
