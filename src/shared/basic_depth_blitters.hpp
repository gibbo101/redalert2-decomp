#include "shared/alpha_table_cache.hpp"
// Class names verified from the original MSVC RTTI complete object locators.
#ifndef RA2_BASIC_DEPTH_BLITTERS_HPP
#define RA2_BASIC_DEPTH_BLITTERS_HPP
#include "shared/blitter.hpp"
template <class T> class BlitPlainXlatZRead : public Blitter {
public:
    BlitPlainXlatZRead(T const * palette) : Palette(palette) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
};
template <class T> class BlitTransXlatZRead : public Blitter {
public:
    BlitTransXlatZRead(T const * palette) : Palette(palette) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
};
template <class T> class BlitTransZRemapXlatZRead : public Blitter {
public:
    BlitTransZRemapXlatZRead(unsigned char const *const * remap, T const * palette) : RemapTable(remap), Palette(palette) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    unsigned char const *const *RemapTable; // +0x04
    T const *Palette; // +0x08
};
template <class T> class BlitTransDarkenZRead : public Blitter {
public:
    BlitTransDarkenZRead(unsigned short mask) : ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    unsigned short ChannelMask; // +0x04
};
template <class T> class BlitTransLucent75ZRead : public Blitter {
public:
    BlitTransLucent75ZRead(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
template <class T> class BlitTransLucent50ZRead : public Blitter {
public:
    BlitTransLucent50ZRead(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
template <class T> class BlitTransLucent25ZRead : public Blitter {
public:
    BlitTransLucent25ZRead(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
#endif
