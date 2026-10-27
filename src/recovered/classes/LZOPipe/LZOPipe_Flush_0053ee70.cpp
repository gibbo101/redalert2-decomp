// LZOPipe::Flush() (0x0053EE70, virtual slot 1)
// Passes on whatever partial block or header is held, then flushes the
// chain. Returns the bytes passed down the chain.
// @ref ?lzo1x_1_compress@@YIHPBEIPAEPAIPAX@Z=0053e420
#include "shared/lzo_pipe.hpp"

int LZOPipe::Flush()
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
            unsigned int compressed = 0;
            void *dictionary = new char[64 * 1024];
            lzo1x_1_compress((unsigned char *)Buffer, Counter, (unsigned char *)Buffer2, &compressed, dictionary);
            delete [] dictionary;
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
