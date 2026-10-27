#include "shared/alpha_table_cache.hpp"
// RTTI BlitTransXlatAlphaZReadWrite<unsigned short>; observed palette and alpha-row pointers.
#ifndef RA2_TRANS_XLAT_ALPHA_DEPTH_BLITTER_HPP
#define RA2_TRANS_XLAT_ALPHA_DEPTH_BLITTER_HPP
#include "shared/blitter.hpp"
template <class T>
class BlitTransXlatAlphaZReadWrite : public Blitter {
public:
    BlitTransXlatAlphaZReadWrite(T const * palette, int count) : Palette(palette), AlphaTable(0) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransXlatAlphaZReadWrite() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int buffer, int level, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    T const *Palette; // +0x04 palette indexed by source byte OR the alpha-row value
    unsigned short const (*AlphaTable)[256]; // +0x08 rows selected by scaled level
};
#endif
