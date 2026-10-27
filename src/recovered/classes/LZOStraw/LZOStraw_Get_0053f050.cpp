// LZOStraw::Get(void *buffer, int length) (0x0053F050, virtual slot 2)
// Hands out processed bytes, refilling a block at a time from the chained
// straw: decompressing reads a block header and its compressed block (into a
// temporary buffer) and uncompresses it into Buffer; compressing reads
// BlockSize bytes and compresses them behind a header in Buffer2. Returns
// the bytes delivered.
// @ref ?lzo1x_1_compress@@YIHPBEIPAEPAIPAX@Z=0053e420
// @ref ?lzo1x_decompress@@YIHPBEIPAEPAIPAX@Z=0053e970
#include "shared/lzo_straw.hpp"
#include "shared/crt_string.hpp"

int LZOStraw::Get(void *buffer, int length)
{
    int total = 0;

    if (buffer == 0 || length < 1) {
        return 0;
    }

    while (length > 0) {
        if (Counter > 0) {
            int count = (length < Counter) ? length : Counter;
            if (Control == DECOMPRESS) {
                memmove(buffer, &Buffer[BlockHeader.UncompCount - Counter], count);
            } else {
                memmove(buffer, &Buffer2[(BlockHeader.CompCount + sizeof(BlockHeader)) - Counter], count);
            }
            buffer = (char *)buffer + count;
            length -= count;
            Counter -= count;
            total += count;
        }
        if (length == 0) {
            break;
        }

        if (Control == DECOMPRESS) {
            int incount = Straw::Get(&BlockHeader, sizeof(BlockHeader));
            if (incount != sizeof(BlockHeader)) {
                break;
            }

            char *staging = new char[BlockHeader.CompCount];
            incount = Straw::Get(staging, BlockHeader.CompCount);
            if (incount != BlockHeader.CompCount) {
                if (staging) {
                    delete [] staging;
                }
                break;
            }

            unsigned int uncompressed = sizeof(BlockHeader);
            lzo1x_decompress((unsigned char *)staging, BlockHeader.CompCount, (unsigned char *)Buffer, &uncompressed, 0);
            delete [] staging;
            Counter = BlockHeader.UncompCount;
        } else {
            BlockHeader.UncompCount = (unsigned short)Straw::Get(Buffer, BlockSize);
            if (BlockHeader.UncompCount == 0) {
                break;
            }
            void *dictionary = new char[64 * 1024];
            unsigned int compressed = 0;
            lzo1x_1_compress((unsigned char *)Buffer, BlockHeader.UncompCount, (unsigned char *)&Buffer2[sizeof(BlockHeader)], &compressed, dictionary);
            BlockHeader.CompCount = (unsigned short)compressed;
            delete [] dictionary;
            memmove(Buffer2, &BlockHeader, sizeof(BlockHeader));
            Counter = BlockHeader.CompCount + sizeof(BlockHeader);
        }
    }

    return total;
}
