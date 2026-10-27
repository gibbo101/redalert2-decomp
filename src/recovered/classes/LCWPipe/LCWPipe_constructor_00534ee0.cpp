// LCWPipe::LCWPipe(CompControl control, int blocksize) (0x00534EE0)
// Allocates the staging and output buffers with a safety margin of at least
// 128 bytes for blocks that grow when compressed.
#include "shared/lcw_pipe.hpp"

LCWPipe::LCWPipe(CompControl control, int blocksize) :
    Control(control),
    Counter(0),
    Buffer(0),
    Buffer2(0),
    BlockSize(blocksize)
{
    int margin = BlockSize / 128 + 1;
    if (margin < 128) {
        margin = 128;
    }
    SafetyMargin = margin;
    Buffer = new char[BlockSize + SafetyMargin];
    Buffer2 = new char[BlockSize + SafetyMargin];
    BlockHeader.CompCount = 0xFFFF;
}
