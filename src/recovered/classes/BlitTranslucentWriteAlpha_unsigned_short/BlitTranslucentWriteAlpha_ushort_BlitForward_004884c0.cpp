// Blend expanded RGB channels using the wrapping alpha buffer.
#include "shared/translucent_write_alpha_blitter.hpp"
#include "shared/blit.hpp"
#include "shared/rgb_class.hpp"
#include "shared/hicolor.hpp"
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
inline RGBClass Expand_Hicolor_Pixel(unsigned short pixel)
{
    return RGBClass((unsigned char)((pixel >> unknown_shift_852fb8) << unknown_shift_852fbc),
                    (unsigned char)((pixel >> unknown_shift_852fc8) << unknown_shift_852fcc),
                    (unsigned char)((pixel >> unknown_shift_852fc0) << unknown_shift_852fc4));
}
template <>
void BlitTranslucentWriteAlpha<unsigned short>::BlitForward(void *target, void const *source, int length,
                                                          int, int, int buffer, int, int) const
{
    unsigned short *alpha = (unsigned short *)buffer;
    if (length > 0) {
        int count = length;
        do {
            unsigned char color = *(unsigned char const *)source;
            source = (unsigned char const *)source + 1;
            if (color) {
                unsigned int weight = *alpha;
                unsigned int inverse = 255 - weight;
                if (weight == 255) weight = 256;
                RGBClass foreground = Expand_Hicolor_Pixel(Palette[color]);
                RGBClass background = Expand_Hicolor_Pixel(*(unsigned short *)target);
                int red = (int)(background.Red * inverse + foreground.Red * weight) >> 8;
                int green = (int)(background.Green * inverse + foreground.Green * weight) >> 8;
                int blue = (int)(background.Blue * inverse + foreground.Blue * weight) >> 8;
                if (blue > 255) blue = 255;
                int bounded_green = green > 255 ? 255 : green;
                *(unsigned short *)target = (unsigned short)Build_Hicolor_Pixel(red > 255 ? 255 : red, bounded_green, blue);
            }
            target = (unsigned short *)target + 1;
            ++alpha;
            alpha = ZBufferPtr->Wrap_Pointer(alpha);
        } while (--count);
    }
}
