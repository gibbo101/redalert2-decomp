// LCWStraw::LCWStraw(CompControl control, int blocksize) (0x005352D0)
// Allocates the block buffer; the compressed-block buffer is needed only
// when compressing.
#include "shared/lcw_straw.hpp"

LCWStraw::LCWStraw(CompControl control, int blocksize) :
    Control(control),
    Counter(0),
    Buffer(0),
    Buffer2(0),
    BlockSize(blocksize)
{
    SafetyMargin = BlockSize / 128 + 1;
    Buffer = new char[BlockSize + SafetyMargin];
    if (control == COMPRESS) {
        Buffer2 = new char[BlockSize + SafetyMargin];
    }
}
