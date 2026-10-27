#include "shared/alpha_table_cache.hpp"
#ifndef RA2_RLE_REMAINING_WRITERS_HPP
#define RA2_RLE_REMAINING_WRITERS_HPP
#include "shared/rle_blitter.hpp"
template<class T> class RLEBlitTransXlatZReadWrite : public RLEBlitter {
public:
    void Write_Depth_Checked_Pixel(T *&dest, unsigned short *&depth_ptr, char const *&delta,
                                   int depth, unsigned char color, int &length) const {
        if (depth - *delta < *depth_ptr) {
            *dest++ = Palette[color];
            *depth_ptr++ = (unsigned short)(depth - *delta);
            ++delta;
            --length;
        } else {
            ++dest; ++depth_ptr; ++delta; --length;
        }
       
    }

    RLEBlitTransXlatZReadWrite(T const * palette) : Palette(palette) {}

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int, int, int, int adjustments) const;
 T const *Palette; // +4
};
template<class T> class RLEBlitTransDarkenZReadWrite : public RLEBlitter {
public:
    void Write_Depth_Checked_Pixel(T *&dest, unsigned short *&depth_ptr, char const *&delta,
                                   int depth, unsigned char color, int &length) const {
        if (depth - *delta < *depth_ptr) {
            *dest = (*dest >> 1) & ChannelMask;
            *depth_ptr++ = (unsigned short)(depth - *delta);
            ++delta; --length; ++dest;
        } else {
            ++delta; --length; ++depth_ptr; ++dest;
        }
    }

    RLEBlitTransDarkenZReadWrite(unsigned short mask) : ChannelMask(mask) {}

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int, int, int, int adjustments) const;
 unsigned short ChannelMask; // +4
};
#endif
