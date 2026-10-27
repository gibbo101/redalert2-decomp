// LCWPipe::Put(void const *source, int length) (0x00534F90, virtual slot 4)
// Decompressing: gathers each 4-byte block header and its compressed block,
// then passes the uncompressed block on. Compressing: gathers BlockSize
// bytes, then passes the block header and compressed block on. Returns the
// bytes passed down the chain.
// @ref ?LCW_Comp@@YIHPBXPAXH@Z=00534d40
// @ref ?LCW_Uncomp@@YIHPBXPAXK@Z=00534b50
#include "shared/lcw_pipe.hpp"
#include "shared/crt_string.hpp"

int LCWPipe::Put(void const *source, int length)
{
    if (source == 0 || length < 1) {
        return Pipe::Put(source, length);
    }

    int total = 0;

    if (Control == DECOMPRESS) {
        while (length > 0) {
            // Accumulate the block header first.
            if (BlockHeader.CompCount == 0xFFFF) {
                int count = (length < sizeof(BlockHeader) - Counter) ? length : sizeof(BlockHeader) - Counter;
                memmove(Buffer + Counter, source, count);
                source = (char const *)source + count;
                length -= count;
                Counter += count;

                if (Counter == sizeof(BlockHeader)) {
                    memmove(&BlockHeader, Buffer, sizeof(BlockHeader));
                    Counter = 0;
                }
            }

            // Then the compressed block; uncompress it once complete.
            if (length > 0) {
                int needed = BlockHeader.CompCount - Counter;
                int count = (length < needed) ? length : needed;
                memmove(Buffer + Counter, source, count);
                length -= count;
                source = (char const *)source + count;
                Counter += count;

                if (Counter == BlockHeader.CompCount) {
                    LCW_Uncomp(Buffer, Buffer2);
                    total += Pipe::Put(Buffer2, BlockHeader.UncompCount);
                    Counter = 0;
                    BlockHeader.CompCount = 0xFFFF;
                }
            }
        }
    } else {
        // Complete a partially filled block first.
        if (Counter > 0) {
            int needed = BlockSize - Counter;
            int count = (length < needed) ? length : needed;
            memmove(Buffer + Counter, source, count);
            Counter += count;
            source = (char const *)source + count;
            length -= count;

            if (Counter == BlockSize) {
                int compressed = LCW_Comp(Buffer, Buffer2, BlockSize);
                BlockHeader.CompCount = (unsigned short)compressed;
                BlockHeader.UncompCount = (unsigned short)BlockSize;
                total += Pipe::Put(&BlockHeader, sizeof(BlockHeader));
                total += Pipe::Put(Buffer2, compressed);
                Counter = 0;
            }
        }

        // Compress whole blocks straight from the source.
        while (length >= BlockSize) {
            int compressed = LCW_Comp(source, Buffer2, BlockSize);
            source = (char const *)source + BlockSize;
            length -= BlockSize;
            BlockHeader.CompCount = (unsigned short)compressed;
            BlockHeader.UncompCount = (unsigned short)BlockSize;
            total += Pipe::Put(&BlockHeader, sizeof(BlockHeader));
            total += Pipe::Put(Buffer2, compressed);
        }

        // Keep the remainder for the next block.
        if (length > 0) {
            memmove(Buffer, source, length);
            Counter = length;
        }
    }

    return total;
}
