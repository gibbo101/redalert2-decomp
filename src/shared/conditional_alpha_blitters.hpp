#include "shared/alpha_table_cache.hpp"
// Class names verified from the original MSVC RTTI complete object locators.
#ifndef RA2_CONDITIONAL_ALPHA_BLITTERS_HPP
#define RA2_CONDITIONAL_ALPHA_BLITTERS_HPP
#include "shared/blitter.hpp"
template <class T> class BlitTransXlatMultWriteAlpha : public Blitter {
public:
    BlitTransXlatMultWriteAlpha() {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    
};
template <class T> class BlitTranslucent50NonzeroAlpha : public Blitter {
public:
    BlitTranslucent50NonzeroAlpha(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
template <class T> class BlitTranslucent50ZeroAlpha : public Blitter {
public:
    BlitTranslucent50ZeroAlpha(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
#endif
