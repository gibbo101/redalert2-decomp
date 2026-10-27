#include "shared/alpha_table_cache.hpp"
// RTTI-named translucent indexed blitters; observed palette, alpha row table and channel mask.
#ifndef RA2_TRANS_LUCENT_ALPHA_BLITTER_HPP
#define RA2_TRANS_LUCENT_ALPHA_BLITTER_HPP
#include "shared/blitter.hpp"
template <class T>
class BlitTransLucent75Alpha : public Blitter {
public:
    BlitTransLucent75Alpha(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransLucent75Alpha() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length, int, int, int buffer, int level, int) const;
    virtual void BlitBackward(void *target, void const *source, int length, int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    T const *Palette; // +0x04
    unsigned short const (*AlphaTable)[256]; // +0x08
    unsigned short ChannelMask; // +0x0C
};
template <class T>
class BlitTransLucent25Alpha : public Blitter {
public:
    BlitTransLucent25Alpha(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransLucent25Alpha() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length, int, int, int buffer, int level, int) const;
    virtual void BlitBackward(void *target, void const *source, int length, int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    T const *Palette; // +0x04
    unsigned short const (*AlphaTable)[256]; // +0x08
    unsigned short ChannelMask; // +0x0C
};
template <class T>
class BlitTransLucent50Alpha : public Blitter {
public:
    BlitTransLucent50Alpha(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransLucent50Alpha() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length, int, int, int buffer, int level, int) const;
    virtual void BlitBackward(void *target, void const *source, int length, int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    T const *Palette; // +0x04
    unsigned short const (*AlphaTable)[256]; // +0x08
    unsigned short ChannelMask; // +0x0C
};
#endif
