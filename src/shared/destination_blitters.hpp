#include "shared/alpha_table_cache.hpp"
// Class names verified from the original MSVC RTTI complete object locators.
#ifndef RA2_DESTINATION_BLITTERS_HPP
#define RA2_DESTINATION_BLITTERS_HPP
#include "shared/blitter.hpp"
template <class T> class BlitTransRemapDest : public Blitter {
public:
    BlitTransRemapDest(T const * palette) : Palette(palette) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
};
template <class T> class BlitTransDarken : public Blitter {
public:
    BlitTransDarken(unsigned short mask) : ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    unsigned short ChannelMask; // +0x04
};
#endif
