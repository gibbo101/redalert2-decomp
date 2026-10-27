#include "shared/alpha_table_cache.hpp"
#ifndef RA2_RLE_ACTIVE_ALPHA_DEPTH_HPP
#define RA2_RLE_ACTIVE_ALPHA_DEPTH_HPP
#include "shared/rle_blitter.hpp"
template <class T> class RLEBlitTransZRemapXlatAlphaZRead : public RLEBlitter {
public:
    RLEBlitTransZRemapXlatAlphaZRead(unsigned char const *const * remap, T const * palette, int count) : RemapTable(remap), Palette(palette), AlphaTable(0) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransZRemapXlatAlphaZRead() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int, int adjustments) const;
 unsigned char const *const *RemapTable; // +4; current remap pointer cell
 T const *Palette; // +8
 unsigned short const (*AlphaTable)[256]; // +12
};
template <class T> class RLEBlitTransZRemapXlatAlphaZReadWrite : public RLEBlitter {
public:
    RLEBlitTransZRemapXlatAlphaZReadWrite(unsigned char const *const * remap, T const * palette, int count) : RemapTable(remap), Palette(palette), AlphaTable(0) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransZRemapXlatAlphaZReadWrite() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int, int adjustments) const;
 unsigned char const *const *RemapTable; // +4; current remap pointer cell
 T const *Palette; // +8
 unsigned short const (*AlphaTable)[256]; // +12
};
#endif
