// Blend alpha-translated RLE pixels after a signed adjustment/depth test.
// Zero runs advance output, adjustments, depth and alpha; left clipping leaves adjustments unchanged.
#include "shared/rle_alpha_blend_depth.hpp"
#include "shared/blit.hpp"
// @ref ?ABufferPtr@@3PAVABuffer@@A=00839c6c
// @ref ?ZBufferPtr@@3PAVZBuffer@@A=008315b4
template <>
void RLEBlitTransLucent75AlphaZReadWrite<unsigned short>::Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int buffer, int level, int, int adjustment) const
{
    unsigned short *output=(unsigned short *)target;
    unsigned short *depth_ptr = (unsigned short *)depth_buffer;
    unsigned char const *input = (unsigned char const *)source;
    char const *delta = (char const *)adjustment;
    unsigned short *alpha=(unsigned short *)buffer;
    int row=level>0?level:0;
    row=(int)((unsigned int)row*261u)>>11;
    if(row>254)row=254;
    unsigned short const *table=AlphaTable[row];
    if (skip > 0) {
        skip = Skip_RLE_Pixels(input, skip);
        skip = -skip;
        output = (unsigned short *)output + skip;
        length -= skip;
        depth_ptr = (unsigned short *)depth_buffer + skip;
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
        alpha=(unsigned short *)buffer+skip;
        alpha=ZBufferPtr->Wrap_Pointer(alpha);
    }
    while (length > 0) {
        unsigned char color = *input++;
        if (color == 0) {
            color = *input++;
            length -= color;
            output += color;
            delta += color;
            depth_ptr += color;
            alpha += color;
        } else {
            if (depth - *delta < *depth_ptr) {
                unsigned short previous=*output;
                *output++ = ((Palette[table[*alpha] | color] >> 2) & ChannelMask) + ((previous >> 2) & ChannelMask) * 3;
                *depth_ptr++=(unsigned short)(depth-*delta);
                ++delta; --length;
            } else {
                ++delta;
                output=(unsigned short *)output+1;
                ++depth_ptr; --length;
            }
            ++alpha;
        }
        depth_ptr = ABufferPtr->Wrap_Pointer(depth_ptr);
        alpha=ZBufferPtr->Wrap_Pointer(alpha);
    }
}
