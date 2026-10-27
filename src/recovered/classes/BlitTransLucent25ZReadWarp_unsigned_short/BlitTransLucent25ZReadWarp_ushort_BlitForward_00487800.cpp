// Depth test before accessing the source byte; wrap the supplied depth scanline.
#include "shared/basic_depth_warp_blitters.hpp"
#include "shared/blit.hpp"
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
template <>
void BlitTransLucent25ZReadWarp<unsigned short>::BlitForward(void *target, void const *source, int length,
                                      int depth, int depth_buffer, int, int, int warp_offset) const
{
    unsigned short *depth_ptr = (unsigned short *)depth_buffer;
    if (length > 0) {
        int count = length;
        do {
            if (depth < *depth_ptr++) {
                unsigned char color = *(unsigned char const *)source;
                if (color) {
                    *(unsigned short *)target = ((Palette[color] >> 2) & ChannelMask) * 3 + ((((unsigned short *)target)[warp_offset] >> 2) & ChannelMask);
                }
            }
            source = (unsigned char const *)source + 1;
            target = (unsigned short *)target + 1;
            depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
        } while (--count);
    }
}
