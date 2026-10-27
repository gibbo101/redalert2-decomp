#include "shared/alpha_table_cache.hpp"
// Original RTTI class and exact method field offsets.
#ifndef RA2_BASIC_RLE_DEPTH_BLITTERS_HPP
#define RA2_BASIC_RLE_DEPTH_BLITTERS_HPP
#include "shared/rle_blitter.hpp"
template <class T> class RLEBlitTransXlatZRead : public RLEBlitter {
public:
    RLEBlitTransXlatZRead(T const * palette) : Palette(palette) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    T const *Palette; // +0x04
};
#endif
