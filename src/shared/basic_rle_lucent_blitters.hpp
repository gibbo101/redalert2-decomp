#include "shared/alpha_table_cache.hpp"
// Non-alpha RLE packed-pixel blends; class names are behavioral hypotheses.
#ifndef RA2_BASIC_RLE_LUCENT_BLITTERS_HPP
#define RA2_BASIC_RLE_LUCENT_BLITTERS_HPP
#include "shared/rle_blitter.hpp"
template <class T> class RLEBlitTransDarken : public RLEBlitter {
public:
    RLEBlitTransDarken(unsigned short mask) : ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int, int, int, int) const;
    unsigned short ChannelMask; // +0x04
};
template <class T> class RLEBlitTransLucent75 : public RLEBlitter {
public:
    RLEBlitTransLucent75(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
template <class T> class RLEBlitTransLucent50 : public RLEBlitter {
public:
    RLEBlitTransLucent50(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
template <class T> class RLEBlitTransLucent25 : public RLEBlitter {
public:
    RLEBlitTransLucent25(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int, int, int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
#endif
