// LZOPipe::Put(void const *source, int length) (0x0053EBE0, virtual slot 4)
// Decompressing: gathers each 4-byte block header and its compressed block,
// then passes the uncompressed block on. Compressing: gathers BlockSize
// bytes, then passes the block header and compressed block on. Returns the
// bytes passed down the chain.
// @ref ?lzo1x_1_compress@@YIHPBEIPAEPAIPAX@Z=0053e420
// @ref ?lzo1x_decompress@@YIHPBEIPAEPAIPAX@Z=0053e970
#include "shared/lzo_pipe.hpp"
#include "shared/crt_string.hpp"

int LZOPipe::Put(void const *source, int length)
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
                    unsigned int uncompressed = sizeof(BlockHeader);
                    lzo1x_decompress((unsigned char *)Buffer, BlockHeader.CompCount, (unsigned char *)Buffer2, &uncompressed, 0);
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
            source = (char const *)source + count;
            length -= count;
            Counter += count;

            if (Counter == BlockSize) {
                unsigned int compressed = sizeof(BlockHeader);
                void *dictionary = new char[64 * 1024];
                lzo1x_1_compress((unsigned char *)Buffer, BlockSize, (unsigned char *)Buffer2, &compressed, dictionary);
                delete [] dictionary;
                BlockHeader.CompCount = (unsigned short)compressed;
                BlockHeader.UncompCount = (unsigned short)BlockSize;
                total += Pipe::Put(&BlockHeader, sizeof(BlockHeader));
                total += Pipe::Put(Buffer2, compressed);
                Counter = 0;
            }
        }

        // Compress whole blocks straight from the source.
        while (length >= BlockSize) {
            unsigned int compressed = 0;
            void *dictionary = new char[64 * 1024];
            lzo1x_1_compress((unsigned char const *)source, BlockSize, (unsigned char *)Buffer2, &compressed, dictionary);
            delete [] dictionary;
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
