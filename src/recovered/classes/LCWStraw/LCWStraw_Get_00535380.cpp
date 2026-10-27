// LCWStraw::Get(void *buffer, int length) (0x00535380, virtual slot 2)
// Hands out processed bytes, refilling a block at a time from the chained
// straw: decompressing reads a block header and its compressed block (placed
// at the end of Buffer) and uncompresses it into Buffer; compressing reads
// BlockSize bytes and compresses them behind a header in Buffer2. Returns
// the bytes delivered.
// @ref ?LCW_Comp@@YIHPBXPAXH@Z=00534d40
// @ref ?LCW_Uncomp@@YIHPBXPAXK@Z=00534b50
#include "shared/lcw_straw.hpp"
#include "shared/crt_string.hpp"

int LCWStraw::Get(void *buffer, int length)
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

            char *staging = &Buffer[(BlockSize + SafetyMargin) - BlockHeader.CompCount];
            incount = Straw::Get(staging, BlockHeader.CompCount);
            if (incount != BlockHeader.CompCount) {
                break;
            }

            LCW_Uncomp(staging, Buffer);
            Counter = BlockHeader.UncompCount;
        } else {
            BlockHeader.UncompCount = (unsigned short)Straw::Get(Buffer, BlockSize);
            if (BlockHeader.UncompCount == 0) {
                break;
            }
            BlockHeader.CompCount = (unsigned short)LCW_Comp(Buffer, &Buffer2[sizeof(BlockHeader)], BlockHeader.UncompCount);
            memmove(Buffer2, &BlockHeader, sizeof(BlockHeader));
            Counter = BlockHeader.CompCount + sizeof(BlockHeader);
        }
    }

    return total;
}
