// LZOStraw::LZOStraw(CompControl control, int blocksize) (0x0053EFB0)
// Allocates the block buffer; the compressed-block buffer is needed only
// when compressing.
#include "shared/lzo_straw.hpp"

LZOStraw::LZOStraw(CompControl control, int blocksize) :
    Control(control),
    Counter(0),
    Buffer(0),
    Buffer2(0),
    BlockSize(blocksize)
{
    SafetyMargin = BlockSize;
    Buffer = new char[BlockSize + SafetyMargin];
    if (control == COMPRESS) {
        Buffer2 = new char[BlockSize + SafetyMargin];
    }
}
