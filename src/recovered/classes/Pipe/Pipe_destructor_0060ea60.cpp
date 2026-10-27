// Pipe::~Pipe (0x0060EA60)
// Unlinks this pipe from both neighbours, reconnecting them to each other.
#include "shared/pipe.hpp"

// The scalar deleting destructor the linker kept was compiled in another
// object file, where this destructor was not visible and is called rather
// than inlined; auto_inline(off) reproduces that copy here.
#pragma auto_inline(off)
Pipe::~Pipe()
{
    if (ChainTo) {
        ChainTo->ChainFrom = ChainFrom;
    }
    if (ChainFrom) {
        ChainFrom->Put_To(ChainTo);
    }
    ChainFrom = 0;
    ChainTo = 0;
}
#pragma auto_inline(on)
