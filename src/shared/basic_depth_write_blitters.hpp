#include "shared/alpha_table_cache.hpp"
// Non-alpha depth-test/write operations. Class names remain behavioral hypotheses.
#ifndef RA2_BASIC_DEPTH_WRITE_BLITTERS_HPP
#define RA2_BASIC_DEPTH_WRITE_BLITTERS_HPP
#include "shared/blitter.hpp"
template <class T> class BlitPlainXlatZReadWrite : public Blitter {
public:
    BlitPlainXlatZReadWrite(T const * palette) : Palette(palette) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
};
template <class T> class BlitTransXlatZReadWrite : public Blitter {
public:
    BlitTransXlatZReadWrite(T const * palette) : Palette(palette) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
};
template <class T> class BlitTransZRemapXlatZReadWrite : public Blitter {
public:
    BlitTransZRemapXlatZReadWrite(unsigned char const *const * remap, T const * palette) : RemapTable(remap), Palette(palette) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    unsigned char const *const *RemapTable; // +0x04
    T const *Palette; // +0x08
};
template <class T> class BlitTransLucent50ZReadWrite : public Blitter {
public:
    BlitTransLucent50ZReadWrite(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
template<class T> class BlitTransDarkenZReadWrite : public Blitter {
public:
    BlitTransDarkenZReadWrite(unsigned short mask) : ChannelMask(mask) {}

    virtual void BlitForward(void *, void const *, int, int, int, int, int, int) const;
    virtual void BlitBackward(void *, void const *, int, int, int, int, int) const;
    unsigned short ChannelMask; // +4
};
template<class T> class BlitTransLucent75ZReadWrite : public Blitter {
public:
    BlitTransLucent75ZReadWrite(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *, void const *, int, int, int, int, int, int) const;
    virtual void BlitBackward(void *, void const *, int, int, int, int, int) const;
    T const *Palette; // +4
    unsigned short ChannelMask; // +8
};
template<class T> class BlitTransLucent25ZReadWrite : public Blitter {
public:
    BlitTransLucent25ZReadWrite(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *, void const *, int, int, int, int, int, int) const;
    virtual void BlitBackward(void *, void const *, int, int, int, int, int) const;
    T const *Palette; // +4
    unsigned short ChannelMask; // +8
};
#endif
