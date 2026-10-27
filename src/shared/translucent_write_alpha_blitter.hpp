// Original MSVC RTTI: BlitTranslucentWriteAlpha<unsigned short>, palette at+4.
#ifndef RA2_TRANSLUCENT_WRITE_ALPHA_BLITTER_HPP
#define RA2_TRANSLUCENT_WRITE_ALPHA_BLITTER_HPP
#include "shared/blitter.hpp"
template <class T> class BlitTranslucentWriteAlpha : public Blitter {
public:
    BlitTranslucentWriteAlpha(T const *palette) : Palette(palette) {}
    virtual void BlitForward(void *target, void const *source, int length,
                             int, int, int buffer, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
};
#endif
