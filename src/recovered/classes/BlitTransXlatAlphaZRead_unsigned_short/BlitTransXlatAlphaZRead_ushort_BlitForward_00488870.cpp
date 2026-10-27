// Depth-test each source pixel before reading its index and translating through the alpha row.
#include "shared/trans_xlat_alpha_read_blitter.hpp"
#include "shared/blit.hpp"
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
template <>
void BlitTransXlatAlphaZRead<unsigned short>::BlitForward(void *target, void const *source, int length,
                                                        int depth, int depth_buffer, int buffer, int level, int) const
{
    unsigned short *depth_ptr = (unsigned short *)depth_buffer;
    unsigned short *alpha = (unsigned short *)buffer;
    int row = level > 0 ? level : 0;
    row = (row * 261) >> 11;
    if (row > 254) row = 254;
    unsigned short const *table = AlphaTable[row];
    if (length > 0) {
        int count = length;
        do {
            if (depth < *depth_ptr++) {
                unsigned char color = *(unsigned char const *)source;
                if (color) {
                    unsigned int translated = table[*alpha];
                    *(unsigned short *)target = Palette[translated | color];
                }
            }
            source = (unsigned char const *)source + 1;
            target = (unsigned short *)target + 1;
            depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
            alpha++;
            alpha = ZBufferPtr->Wrap_Pointer(alpha);
        } while (--count);
    }
}
