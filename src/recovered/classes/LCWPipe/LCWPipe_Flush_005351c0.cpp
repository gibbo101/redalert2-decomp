// LCWPipe::Flush() (0x005351C0, virtual slot 1)
// Passes on whatever partial block or header is held, then flushes the
// chain. Returns the bytes passed down the chain.
// @ref ?LCW_Comp@@YIHPBXPAXH@Z=00534d40
#include "shared/lcw_pipe.hpp"

int LCWPipe::Flush()
{
    int total = 0;

    if (Counter > 0) {
        if (Control == DECOMPRESS) {
            // An incomplete header is passed on as raw data.
            if (BlockHeader.CompCount == 0xFFFF) {
                total += Pipe::Put(Buffer, Counter);
                Counter = 0;
            }
            if (Counter > 0) {
                total += Pipe::Put(&BlockHeader, sizeof(BlockHeader));
                total += Pipe::Put(Buffer, Counter);
                Counter = 0;
                BlockHeader.CompCount = 0xFFFF;
            }
        } else {
            int compressed = LCW_Comp(Buffer, Buffer2, Counter);
            BlockHeader.CompCount = (unsigned short)compressed;
            BlockHeader.UncompCount = (unsigned short)Counter;
            total += Pipe::Put(&BlockHeader, sizeof(BlockHeader));
            total += Pipe::Put(Buffer2, compressed);
            Counter = 0;
        }
    }
    total += Pipe::Flush();
    return total;
}
