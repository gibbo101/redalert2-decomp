// Depth test before accessing the source byte; wrap the supplied depth scanline.
#include "shared/basic_depth_write_blitters.hpp"
#include "shared/blit.hpp"
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
template <>
void BlitPlainXlatZReadWrite<unsigned short>::BlitForward(void *target, void const *source, int length,
                                      int depth, int depth_buffer, int, int, int) const
{
    unsigned short *depth_ptr = (unsigned short *)depth_buffer;
    if (length > 0) {
        int count = length;
        do {
            if (depth < *depth_ptr) {
                unsigned char color = *(unsigned char const *)source;
                *(unsigned short *)target = Palette[color];
                *depth_ptr = (unsigned char)depth;
            }
            ++depth_ptr;
            source = (unsigned char const *)source + 1;
            target = (unsigned short *)target + 1;
            depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
        } while (--count);
    }
}
