#include "shared/alpha_table_cache.hpp"
// RTTI BlitTransZRemapXlatAlpha<unsigned short>; observed palette and alpha-row pointers.
#ifndef RA2_TRANS_REMAP_XLAT_ALPHA_BLITTER_HPP
#define RA2_TRANS_REMAP_XLAT_ALPHA_BLITTER_HPP
#include "shared/blitter.hpp"
template <class T>
class BlitTransZRemapXlatAlpha : public Blitter {
public:
    BlitTransZRemapXlatAlpha(unsigned char const *const * remap, T const * palette, int count) : Remap(remap), Palette(palette), AlphaTable(0) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransZRemapXlatAlpha() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int buffer, int level, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    unsigned char const *const *Remap; // +0x04 active remap table
    T const *Palette; // +0x08 palette indexed by source byte OR the alpha-row value
    unsigned short const (*AlphaTable)[256]; // +0x0C rows selected by scaled level
};
#endif
