// Straw::~Straw (0x0069B010)
// Unlinks this straw from both neighbours, reconnecting them to each other.
#include "shared/straw.hpp"

// The scalar deleting destructor the linker kept was compiled in another
// object file, where this destructor was not visible and is called rather
// than inlined; auto_inline(off) reproduces that copy here.
#pragma auto_inline(off)
Straw::~Straw()
{
    if (ChainTo) {
        ChainTo->ChainFrom = ChainFrom;
    }
    if (ChainFrom) {
        ChainFrom->Get_From(ChainTo);
    }
    ChainFrom = 0;
    ChainTo = 0;
}
#pragma auto_inline(on)
