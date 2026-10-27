#include "shared/alpha_table_cache.hpp"
// Original RTTI remap classes; capture *RemapTable once per call.
#ifndef RA2_RLE_REMAP_DEPTH_HPP
#define RA2_RLE_REMAP_DEPTH_HPP
#include "shared/rle_blitter.hpp"
template <class T> class RLEBlitTransZRemapXlatZRead : public RLEBlitter {
public:
    RLEBlitTransZRemapXlatZRead(unsigned char const *const * remap, T const * palette) : RemapTable(remap), Palette(palette) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    unsigned char const *const *RemapTable; // +0x04; shared current-remap pointer cell
    T const *Palette;                       // +0x08
};
template <class T> class RLEBlitTransZRemapXlatZReadWrite : public RLEBlitter {
public:
    RLEBlitTransZRemapXlatZReadWrite(unsigned char const *const * remap, T const * palette) : RemapTable(remap), Palette(palette) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    unsigned char const *const *RemapTable; // +0x04; shared current-remap pointer cell
    T const *Palette;                       // +0x08
};
#endif
