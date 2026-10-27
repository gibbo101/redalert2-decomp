#include "shared/alpha_table_cache.hpp"
#ifndef RA2_RLE_ALPHA_DEPTH_HPP
#define RA2_RLE_ALPHA_DEPTH_HPP
#include "shared/rle_blitter.hpp"
template <class T> class RLEBlitTransXlatAlphaZRead : public RLEBlitter {
public:
    RLEBlitTransXlatAlphaZRead(T const * palette, int count) : Palette(palette), AlphaTable(0) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransXlatAlphaZRead() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int, int adjustments) const;
 T const *Palette; // +4
 unsigned short const (*AlphaTable)[256]; // +8
};
template <class T> class RLEBlitTransXlatAlphaZReadWrite : public RLEBlitter {
public:
    RLEBlitTransXlatAlphaZReadWrite(T const * palette, int count) : Palette(palette), AlphaTable(0) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransXlatAlphaZReadWrite() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int, int adjustments) const;
 T const *Palette; // +4
 unsigned short const (*AlphaTable)[256]; // +8
};
#endif
