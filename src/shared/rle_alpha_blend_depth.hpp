#include "shared/alpha_table_cache.hpp"
#ifndef RA2_RLE_ALPHA_BLEND_DEPTH_HPP
#define RA2_RLE_ALPHA_BLEND_DEPTH_HPP
#include "shared/rle_blitter.hpp"
template<class T> class RLEBlitTransLucent75AlphaZRead : public RLEBlitter {
public:
    RLEBlitTransLucent75AlphaZRead(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent75AlphaZRead() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int warp_offset, int adjustment) const;
 T const *Palette; // +4
 unsigned short const (*AlphaTable)[256]; // +8
 unsigned short ChannelMask; // +12
};
template<class T> class RLEBlitTransLucent50AlphaZRead : public RLEBlitter {
public:
    RLEBlitTransLucent50AlphaZRead(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent50AlphaZRead() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int warp_offset, int adjustment) const;
 T const *Palette; // +4
 unsigned short const (*AlphaTable)[256]; // +8
 unsigned short ChannelMask; // +12
};
template<class T> class RLEBlitTransLucent25AlphaZRead : public RLEBlitter {
public:
    RLEBlitTransLucent25AlphaZRead(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent25AlphaZRead() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int warp_offset, int adjustment) const;
 T const *Palette; // +4
 unsigned short const (*AlphaTable)[256]; // +8
 unsigned short ChannelMask; // +12
};
template<class T> class RLEBlitTransLucent75AlphaZReadWarp : public RLEBlitter {
public:
    RLEBlitTransLucent75AlphaZReadWarp(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent75AlphaZReadWarp() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int warp_offset, int adjustment) const;
 T const *Palette; // +4
 unsigned short const (*AlphaTable)[256]; // +8
 unsigned short ChannelMask; // +12
};
template<class T> class RLEBlitTransLucent50AlphaZReadWarp : public RLEBlitter {
public:
    RLEBlitTransLucent50AlphaZReadWarp(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent50AlphaZReadWarp() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int warp_offset, int adjustment) const;
 T const *Palette; // +4
 unsigned short const (*AlphaTable)[256]; // +8
 unsigned short ChannelMask; // +12
};
template<class T> class RLEBlitTransLucent25AlphaZReadWarp : public RLEBlitter {
public:
    RLEBlitTransLucent25AlphaZReadWarp(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent25AlphaZReadWarp() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int warp_offset, int adjustment) const;
 T const *Palette; // +4
 unsigned short const (*AlphaTable)[256]; // +8
 unsigned short ChannelMask; // +12
};
template<class T> class RLEBlitTransLucent75AlphaZReadWrite : public RLEBlitter {
public:
    RLEBlitTransLucent75AlphaZReadWrite(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent75AlphaZReadWrite() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int warp_offset, int adjustment) const;
 T const *Palette; // +4
 unsigned short const (*AlphaTable)[256]; // +8
 unsigned short ChannelMask; // +12
};
template<class T> class RLEBlitTransLucent50AlphaZReadWrite : public RLEBlitter {
public:
    RLEBlitTransLucent50AlphaZReadWrite(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent50AlphaZReadWrite() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int warp_offset, int adjustment) const;
 T const *Palette; // +4
 unsigned short const (*AlphaTable)[256]; // +8
 unsigned short ChannelMask; // +12
};
template<class T> class RLEBlitTransLucent25AlphaZReadWrite : public RLEBlitter {
public:
    RLEBlitTransLucent25AlphaZReadWrite(T const * palette, int count, unsigned short mask) : Palette(palette), AlphaTable(0), ChannelMask(mask) { AlphaTable = AlphaTableCache_008315B8.Get(count); }
    virtual ~RLEBlitTransLucent25AlphaZReadWrite() { AlphaTableCache_008315B8.Release(AlphaTable); AlphaTable = 0; }

 virtual void Blit(void *target, void const *source, int length, int skip, int depth, int depth_buffer, int buffer, int level, int warp_offset, int adjustment) const;
 T const *Palette; // +4
 unsigned short const (*AlphaTable)[256]; // +8
 unsigned short ChannelMask; // +12
};
#endif
