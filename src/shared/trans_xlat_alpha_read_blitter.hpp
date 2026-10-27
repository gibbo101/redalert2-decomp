#include "shared/alpha_table_cache.hpp"
// RTTI BlitTransXlatAlphaZRead<unsigned short>; observed palette and alpha-row pointers.
#ifndef RA2_TRANS_XLAT_ALPHA_READ_BLITTER_HPP
#define RA2_TRANS_XLAT_ALPHA_READ_BLITTER_HPP
#include "shared/blitter.hpp"
template <class T>
class BlitTransXlatAlphaZRead : public Blitter {
public:
    BlitTransXlatAlphaZRead(T const * palette, int count) : Palette(palette), AlphaTable(0) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransXlatAlphaZRead() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int buffer, int level, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    T const *Palette; // +0x04 palette indexed by source byte OR the alpha-row value
    unsigned short const (*AlphaTable)[256]; // +0x08 rows selected by scaled level
};
template <class T>
class BlitTransLucent75AlphaZRead : public Blitter {
public:
    BlitTransLucent75AlphaZRead(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransLucent75AlphaZRead() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int buffer, int level, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    T const *Palette; // +0x04 palette indexed by source byte OR the alpha-row value
    unsigned short const (*AlphaTable)[256]; // +0x08 rows selected by scaled level
    unsigned short ChannelMask; // +0x0c packed channel mask
};
template <class T>
class BlitTransLucent50AlphaZRead : public Blitter {
public:
    BlitTransLucent50AlphaZRead(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransLucent50AlphaZRead() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int buffer, int level, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    T const *Palette; // +0x04 palette indexed by source byte OR the alpha-row value
    unsigned short const (*AlphaTable)[256]; // +0x08 rows selected by scaled level
    unsigned short ChannelMask; // +0x0c packed channel mask
};
template <class T>
class BlitTransLucent25AlphaZRead : public Blitter {
public:
    BlitTransLucent25AlphaZRead(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransLucent25AlphaZRead() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int buffer, int level, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    T const *Palette; // +0x04 palette indexed by source byte OR the alpha-row value
    unsigned short const (*AlphaTable)[256]; // +0x08 rows selected by scaled level
    unsigned short ChannelMask; // +0x0c packed channel mask
};
template <class T>
class BlitTransZRemapXlatAlphaZRead : public Blitter {
public:
    BlitTransZRemapXlatAlphaZRead(unsigned char const *const * remap, T const * palette, int count) : Remap(remap), Palette(palette), AlphaTable(0) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~BlitTransZRemapXlatAlphaZRead() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int buffer, int level, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int a, int b, int c, int d) const {
        BlitForward(target, source, length, a, b, c, d, 0);
    }
    unsigned char const *const *Remap; // +0x04 active remap table holder
    T const *Palette; // +0x08 palette indexed by source byte OR the alpha-row value
    unsigned short const (*AlphaTable)[256]; // +0x0C rows selected by scaled level
};
#endif
