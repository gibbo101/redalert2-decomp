// Depth-test each source pixel before reading its index and translating through the alpha row.
#include "shared/trans_remap_xlat_alpha_depth_blitter.hpp"
#include "shared/blit.hpp"
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
template <>
void BlitTransZRemapXlatAlphaZReadWrite<unsigned short>::BlitForward(void *target, void const *source, int length,
                                                        int depth, int depth_buffer, int buffer, int level, int) const
{
    unsigned short *depth_ptr = (unsigned short *)depth_buffer;
    unsigned short *alpha = (unsigned short *)buffer;
    int row = level > 0 ? level : 0;
    row = (row * 261) >> 11;
    if (row > 254) row = 254;
    unsigned short const *table = AlphaTable[row];
    unsigned char const *remap = *Remap;
    if (length > 0) {
        int count = length;
        do {
            unsigned short value = *depth_ptr;
            if (depth < value) {
                unsigned char color = *(unsigned char const *)source;
                if (color) {
                    unsigned int translated = table[*alpha];
                    *(unsigned short *)target = Palette[translated | remap[color]];
                    *depth_ptr = (unsigned short)depth;
                }
            }
            source = (unsigned char const *)source + 1;
            target = (unsigned short *)target + 1;
            depth_ptr++;
            depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
        } while (--count);
    }
}
