#include "shared/alpha_table_cache.hpp"
// Original RTTI template names; exact method accesses evidence the palette/mask offsets.
#ifndef RA2_RLE_LUCENT_DEPTH_HPP
#define RA2_RLE_LUCENT_DEPTH_HPP
#include "shared/rle_blitter.hpp"
template <class T> class RLEBlitTransLucent75ZRead : public RLEBlitter {
public:
    RLEBlitTransLucent75ZRead(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    T const *Palette;            // +0x04
    unsigned short ChannelMask;  // +0x08; bits retained after shifting a packed pixel
};
template <class T> class RLEBlitTransLucent50ZRead : public RLEBlitter {
public:
    RLEBlitTransLucent50ZRead(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    T const *Palette;            // +0x04
    unsigned short ChannelMask;  // +0x08; bits retained after shifting a packed pixel
};
template <class T> class RLEBlitTransLucent25ZRead : public RLEBlitter {
public:
    RLEBlitTransLucent25ZRead(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    T const *Palette;            // +0x04
    unsigned short ChannelMask;  // +0x08; bits retained after shifting a packed pixel
};
template <class T> class RLEBlitTransLucent75ZReadWarp : public RLEBlitter {
public:
    RLEBlitTransLucent75ZReadWarp(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    T const *Palette;            // +0x04
    unsigned short ChannelMask;  // +0x08; bits retained after shifting a packed pixel
};
template <class T> class RLEBlitTransLucent50ZReadWarp : public RLEBlitter {
public:
    RLEBlitTransLucent50ZReadWarp(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    T const *Palette;            // +0x04
    unsigned short ChannelMask;  // +0x08; bits retained after shifting a packed pixel
};
template <class T> class RLEBlitTransLucent25ZReadWarp : public RLEBlitter {
public:
    RLEBlitTransLucent25ZReadWarp(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    T const *Palette;            // +0x04
    unsigned short ChannelMask;  // +0x08; bits retained after shifting a packed pixel
};
template <class T> class RLEBlitTransLucent75ZReadWrite : public RLEBlitter {
public:
    RLEBlitTransLucent75ZReadWrite(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    T const *Palette;            // +0x04
    unsigned short ChannelMask;  // +0x08; bits retained after shifting a packed pixel
};
template <class T> class RLEBlitTransLucent50ZReadWrite : public RLEBlitter {
public:
    RLEBlitTransLucent50ZReadWrite(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    T const *Palette;            // +0x04
    unsigned short ChannelMask;  // +0x08; bits retained after shifting a packed pixel
};
template <class T> class RLEBlitTransLucent25ZReadWrite : public RLEBlitter {
public:
    RLEBlitTransLucent25ZReadWrite(T const * palette, unsigned short mask) : Palette(palette), ChannelMask(mask) {}

    virtual void Blit(void *target, void const *source, int length, int skip,
                      int depth, int depth_buffer, int, int, int, int adjustment) const;
    T const *Palette;            // +0x04
    unsigned short ChannelMask;  // +0x08; bits retained after shifting a packed pixel
};
#endif
