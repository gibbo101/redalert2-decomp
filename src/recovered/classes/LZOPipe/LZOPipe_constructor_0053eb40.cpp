// LZOPipe::LZOPipe(CompControl control, int blocksize) (0x0053EB40)
// Allocates the staging and output buffers, each with a safety margin of a
// whole block for data that grows when compressed.
#include "shared/lzo_pipe.hpp"

LZOPipe::LZOPipe(CompControl control, int blocksize) :
    Control(control),
    Counter(0),
    Buffer(0),
    Buffer2(0),
    BlockSize(blocksize)
{
    SafetyMargin = BlockSize;
    Buffer = new char[BlockSize + SafetyMargin];
    Buffer2 = new char[BlockSize + SafetyMargin];
    BlockHeader.CompCount = 0xFFFF;
}
