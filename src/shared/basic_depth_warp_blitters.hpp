#include "shared/alpha_table_cache.hpp"
// Non-alpha depth-test blends sampling a displaced destination pixel; names are hypotheses.
#ifndef RA2_BASIC_DEPTH_WARP_BLITTERS_HPP
#define RA2_BASIC_DEPTH_WARP_BLITTERS_HPP
#include "shared/blitter.hpp"
template <class T> class BlitTransLucent75ZReadWarp : public Blitter {
public:
    BlitTransLucent75ZReadWarp(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int warp_offset) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
template <class T> class BlitTransLucent50ZReadWarp : public Blitter {
public:
    BlitTransLucent50ZReadWarp(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int warp_offset) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
template <class T> class BlitTransLucent25ZReadWarp : public Blitter {
public:
    BlitTransLucent25ZReadWarp(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void BlitForward(void *target, void const *source, int length,
                             int depth, int depth_buffer, int, int, int warp_offset) const;
    virtual void BlitBackward(void *target, void const *source, int length,
                              int, int, int, int) const;
    T const *Palette; // +0x04
    unsigned short ChannelMask; // +0x08
};
#endif
