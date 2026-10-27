#include "shared/alpha_table_cache.hpp"
// Original RTTI class and exact method field offsets.
#ifndef RA2_RLE_DARKEN_DEPTH_HPP
#define RA2_RLE_DARKEN_DEPTH_HPP
#include "shared/rle_blitter.hpp"
template <class T> class RLEBlitTransDarkenZRead : public RLEBlitter {
public:
    RLEBlitTransDarkenZRead(unsigned short mask) : ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    unsigned short ChannelMask; // +0x04; original word mask accesses
};
#endif
