#include "shared/alpha_table_cache.hpp"
// Class names verified from the original MSVC RTTI complete object locators.
#ifndef RA2_BYTE_RLE_BLITTERS_HPP
#define RA2_BYTE_RLE_BLITTERS_HPP
#include "shared/rle_blitter.hpp"
template <class T> class RLEBlitTransZRemapXlat : public RLEBlitter {
public:
    RLEBlitTransZRemapXlat(unsigned char const *const * remap, T const * palette) : RemapTable(remap), Palette(palette) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int, int, int, int) const;
    unsigned char const *const *RemapTable; // +0x04
    T const *Palette; // +0x08
};
template <class T> class RLEBlitTransRemapXlat : public RLEBlitter {
public:
    RLEBlitTransRemapXlat(unsigned char const * remap, T const * palette) : RemapTable(remap), Palette(palette) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int, int, int, int) const;
    unsigned char const *RemapTable; // +0x04
    T const *Palette; // +0x08
};
template <class T> class RLEBlitTransRemapDest : public RLEBlitter {
public:
    RLEBlitTransRemapDest(T const * palette) : Palette(palette) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int, int, int, int) const;
    T const *Palette; // +0x04
};
#endif
