#include "shared/alpha_table_cache.hpp"
// RTTI BlitTransXlatAlphaZReadWarp<unsigned short>; observed palette and alpha-row pointers.
#ifndef RA2_TRANS_LUCENT_ALPHA_WARP_BLITTER_HPP
#define RA2_TRANS_LUCENT_ALPHA_WARP_BLITTER_HPP
#include "shared/blitter.hpp"
template <class T>
class BlitTransLucent75AlphaZReadWarp : public Blitter {
public:
    BlitTransLucent75AlphaZReadWarp(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransLucent75AlphaZReadWarp() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int buffer, int level, int warp_offset) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    T const *Palette; // +0x04 palette indexed by source byte OR the alpha-row value
    unsigned short const (*AlphaTable)[256]; // +0x08 rows selected by scaled level
    unsigned short ChannelMask; // +0x0c packed channel mask
};
template <class T>
class BlitTransLucent50AlphaZReadWarp : public Blitter {
public:
    BlitTransLucent50AlphaZReadWarp(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransLucent50AlphaZReadWarp() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int buffer, int level, int warp_offset) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    T const *Palette; // +0x04 palette indexed by source byte OR the alpha-row value
    unsigned short const (*AlphaTable)[256]; // +0x08 rows selected by scaled level
    unsigned short ChannelMask; // +0x0c packed channel mask
};
template <class T>
class BlitTransLucent25AlphaZReadWarp : public Blitter {
public:
    BlitTransLucent25AlphaZReadWarp(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransLucent25AlphaZReadWarp() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int buffer, int level, int warp_offset) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    T const *Palette; // +0x04 palette indexed by source byte OR the alpha-row value
    unsigned short const (*AlphaTable)[256]; // +0x08 rows selected by scaled level
    unsigned short ChannelMask; // +0x0c packed channel mask
};
#endif
