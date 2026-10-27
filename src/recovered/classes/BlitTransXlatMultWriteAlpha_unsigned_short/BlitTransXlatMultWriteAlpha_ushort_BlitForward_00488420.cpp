// Store clamped source-index-plus-level values for nonzero pixels, wrapping the buffer ring.
#include "shared/conditional_alpha_blitters.hpp"
#include "shared/blit.hpp"
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
template <>
void BlitTransXlatMultWriteAlpha<unsigned short>::BlitForward(void *target, void const *source, int length,
                                                         int level, int, int buffer, int scale, int) const
{
    unsigned short *dest = (unsigned short *)buffer;
    if (length > 0) {
        int count = length;
        int base = level;
        do {
            unsigned char color = *(unsigned char const *)source;
            source = (unsigned char const *)source + 1;
            if (color) {
                *dest = (unsigned short)(color * scale + base >= 255 ? 255 : color * scale + base);
            }
            dest++;
            dest = ZBufferPtr->Wrap_Pointer(dest);
        } while (--count);
    }
}
