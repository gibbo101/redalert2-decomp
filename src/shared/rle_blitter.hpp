#include "shared/alpha_table_cache.hpp"
// RLE scanline blitters: zero followed by a count skips transparent destination pixels.
#ifndef RA2_SHARED_RLE_BLITTER_HPP
#define RA2_SHARED_RLE_BLITTER_HPP
// Advance an RLE source past the clipped pixels; return the nonpositive remainder.
inline int Skip_RLE_Pixels(unsigned char const *&source, int skip) {
    do {
        if (*source++ == 0) skip -= *source++;
        else skip--;
    } while (skip > 0);
    return skip;
}
class RLEBlitter {
public:
    virtual ~RLEBlitter() {}
    virtual void Blit(void *target, void const *source, int length, int skip,
                      int unknown5, int unknown6, int unknown7, int unknown8, int unknown9, int unknown10) const = 0;
};
template <class T>
class RLEBlitTransXlat : public RLEBlitter {
public:
    RLEBlitTransXlat(T const * palette) : Palette(palette) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int, int, int, int) const;
    T const *Palette; // +0x04 translation table indexed by the nonzero source byte
};
template <class T>
class RLEBlitTransXlatAlpha : public RLEBlitter {
public:
    RLEBlitTransXlatAlpha(T const * palette, int count) : Palette(palette), AlphaTable(0) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransXlatAlpha() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int buffer, int level, int, int) const;
    T const *Palette; // +0x04
    unsigned short const (*AlphaTable)[256]; // +0x08
};
template <class T>
class RLEBlitTransLucent75Alpha : public RLEBlitter {
public:
    RLEBlitTransLucent75Alpha(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent75Alpha() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int buffer, int level, int, int) const;
    T const *Palette; // +0x04
    unsigned short const (*AlphaTable)[256]; // +0x08
    unsigned short ChannelMask; // +0x0C excludes carry bits between packed colour channels
};
template <class T>
class RLEBlitTransLucent25Alpha : public RLEBlitter {
public:
    RLEBlitTransLucent25Alpha(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent25Alpha() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int buffer, int level, int, int) const;
    T const *Palette; // +0x04
    unsigned short const (*AlphaTable)[256]; // +0x08
    unsigned short ChannelMask; // +0x0C excludes carry bits between packed colour channels
};
template <class T>
class RLEBlitTransLucent50Alpha : public RLEBlitter {
public:
    RLEBlitTransLucent50Alpha(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent50Alpha() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int buffer, int level, int, int) const;
    T const *Palette; // +0x04
    unsigned short const (*AlphaTable)[256]; // +0x08
    unsigned short ChannelMask; // +0x0C excludes carry bits between packed colour channels
};
template <class T>
class RLEBlitTransZRemapXlatAlpha : public RLEBlitter {
public:
    RLEBlitTransZRemapXlatAlpha(unsigned char const *const * remap, T const * palette, int count) : RemapTable(remap), Palette(palette), AlphaTable(0) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransZRemapXlatAlpha() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int buffer, int level, int, int) const;
    unsigned char const *const *RemapTable; // +0x04 points to the active remapping table
    T const *Palette; // +0x08
    unsigned short const (*AlphaTable)[256]; // +0x0C
};
#endif
