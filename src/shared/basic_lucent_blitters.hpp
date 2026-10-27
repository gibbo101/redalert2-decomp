#include "shared/alpha_table_cache.hpp"
// Non-alpha packed pixel blends; class names follow the RTTI alpha variants as hypotheses.
#ifndef RA2_BASIC_LUCENT_BLITTERS_HPP
#define RA2_BASIC_LUCENT_BLITTERS_HPP
#include "shared/blitter.hpp"
template <class T> class BlitTransLucent75 : public Blitter {
public:
    BlitTransLucent75(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
template <class T> class BlitTransLucent50 : public Blitter {
public:
    BlitTransLucent50(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
template <class T> class BlitTransLucent25 : public Blitter {
public:
    BlitTransLucent25(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
#endif
